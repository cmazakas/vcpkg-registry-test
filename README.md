# Boost Nightly Demo

Make sure vcpkg is installed.

Make a custom toolchain file similar to:
```cmake
# toolchain.cmake
# set various flags here, etc.

# make sure the vcpkg toolchain file is included in ours
# this is what makes the vcpkg.json work
include(/home/exbigboss/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake)
```

Build the demo!

```bash
cmake -B __build -S . -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake
cmake --build __build/
./__build/registry-test
```
