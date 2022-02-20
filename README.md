# Iris Engine

## Environment Setup

Suggested setups per OS:

### Windows

* Install CMake.
* Install the [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022) with the "Desktop development with C++" workload.

### macOS

If using VS Code, set up [LLDB](https://code.visualstudio.com/docs/cpp/lldb-mi).

Install dependencies via Homebrew:

```
brew install \
irrlicht \
assimp \
cmake \
llvm \
pkg-config
```

## Project Setup

Clone the repo with submodules:

```
git clone --recurse-submodules git@github.com:Riari/iris-engine.git
```

Bootstrap vcpkg:

```
.\external\vcpkg\bootstrap-vcpkg.bat -disableMetrics # Windows
.\external\vcpkg\bootstrap-vcpkg.sh -disableMetrics # Unix shells
```

### CLion

#### Windows

Create a Visual Studio toolchain and point it to the VS Build Tools directory, e.g.:

```
C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools
```

If using Ninja, set the generator specified in the CMake Debug profile to `Ninja`.

## Build

### Command line

Install dependencies:

```
.\external\vcpkg\vcpkg install
```

Run CMake. For example, with Ninja and a suitable C++ compiler installed, run:

```
cmake . -DCMAKE_BUILD_TYPE=Debug -G Ninja
```

### VS Code

Install these extensions:

* [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
* [CodeLLDB](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb)
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)

Use the `CMake: ` commands in the command palette to configure, build, and debug the project.

### CLion

Allow CLion to load the CMake project and generate a debug configuration. It should work out of the box with the project's `CMakeLists.txt`.
