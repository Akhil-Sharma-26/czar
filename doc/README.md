# Czar Compiler Documentation

This directory contains documentation and development notes for the Czar compiler.

## Build Instructions

### Prerequisites
- CMake 3.20 or higher
- C++23 compatible compiler:
  - GCC 13+ (recommended for complete C++23 support with `-std=c++23`)
  - Clang 14+
  - MSVC 2022 (Visual Studio 17.0+, version 17.9+ recommended)

### Building on Linux

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Building on Windows (MSVC)

Using Visual Studio Developer Command Prompt or PowerShell:

```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Or open the generated solution file in Visual Studio.

### Running the Compiler

After building, the executable will be in `build/bin/`:

**Linux/Mac:**
```bash
./build/bin/czar
```

**Windows (with multi-config generators like Visual Studio):**
```powershell
.\build\bin\Release\czar.exe
```

**Windows (with single-config generators like Ninja):**
```powershell
.\build\bin\czar.exe
```

## Development Notes

This section will contain language design notes, implementation details, and other development documentation.
