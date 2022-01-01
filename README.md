# Iris Engine

## Setup

Install the [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022) with the "Desktop development with C++" workload.

Clone the repo with submodules:

```
git clone --recurse-submodules git@github.com:Riari/iris-engine.git
```

Bootstrap vcpkg:

```
.\external\vcpkg\bootstrap-vcpkg.bat -disableMetrics
```

### CLion

Create a Visual Studio toolchain and point it to the VS Build Tools directory, e.g.:

```
C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools
```

If using Ninja, set the generator specified in the CMake Debug profile to `Ninja`.

## Build

### CLion

Allow CLion to load the CMake project and generate a debug configuration. It should work out of the box with the project's `CMakeLists.txt`.

### Command line

Install dependencies:

```
.\external\vcpkg\vcpkg install
```

Run CMake. For example, with Ninja and a suitable C++ compiler installed, run:

```
cmake . -DCMAKE_BUILD_TYPE=Debug -G Ninja
```