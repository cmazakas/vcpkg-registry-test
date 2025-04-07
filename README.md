# Boost Nightly Demo

Make sure vcpkg is installed.

Make a custom toolchain file similar to:
```cmake
# toolchain.cmake
cmake_policy(SET CMP0167 NEW) # for FindBoost.cmake deprecation warnings
include(/home/exbigboss/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake)
```

Build the demo!

```bash
cmake -B __build -S . -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake
cmake --build __build/
./__build/registry-test
```
