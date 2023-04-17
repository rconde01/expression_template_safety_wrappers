# Expression Template Safety Wrapper
This project is an experiment in avoiding accidental use of dangling references within expression templates. It is based on ideas from Daniel Withopf presented in his talk [Taking Static Type-safety to the Next Level: Physical Units for Matrices](https://www.youtube.com/watch?v=SLSTS-EvOx4&t=3968s) at CppNow 2022. Here it is applied to `Eigen` via wrapper classes but I'm interested in whether it would be possible/desirable to integrate the technique directly within `Eigen`. The key to making this technique work is `Ref-qualifers` which allow you to distinguish cases where a class is being used as r-value reference and an l-value reference.

```
-- src
   |
   main.cpp # The tests
   expression_template_safety_wrapper.hpp # The wrapper classes
```

Building/Testing on Windows with Conan 2/Visual Studio 2022 with Conan 2 in a virtual environment

```
REM enable the visual studio compiler
"C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

REM enable the virtual environment on which conan 2 is installed
C:\Users\MyUserName\Envs\conan2test\Scripts\activate.bat

REM Create the CMake toolchain file for our `conanfile.txt`
conan install . --output-folder=build

REM Configure CMake
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

REM Build the Source and run the tests
cmake --build . && ctest

```
