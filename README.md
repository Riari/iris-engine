# Iris Engine

## Setup

Clone with submodules:

```
git clone --recurse-submodules git@github.com:Riari/iris-engine.git
```

Bootstrap vcpkg:

```
.\external\vcpkg\bootstrap-vcpkg.bat -disableMetrics
```

Install assimp x64:

```
.\external\vcpkg\vcpkg install
```

Run CMake:

```
cmake . -DCMAKE_BUILD_TYPE=Debug -G Ninja -DCMAKE_TOOLCHAIN_FILE=.\external\vcpkg\scripts\buildsystems\vcpkg.cmake
```