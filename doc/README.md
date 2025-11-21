# Czar Compiler Documentation

This directory contains documentation and development notes for the Czar compiler.

## Build Instructions

### Prerequisites
- CMake 3.20 or higher
- C++23 compatible compiler:
  - GCC 11+ (with `-std=c++23` or `-std=c++2b`)
  - Clang 14+
  - MSVC 2022 (Visual Studio 17.0+)

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

```bash
./build/bin/czar
```

On Windows:
```powershell
.\build\bin\Release\czar.exe
```

## Development Notes

This section will contain language design notes, implementation details, and other development documentation.
