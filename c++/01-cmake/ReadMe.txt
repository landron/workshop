
##################################################################################################
Purpose
    basic cpp project
        - cmake
        - cross-platform
        - cross-compiler

Prerequisites
    - cmake (3.13.0)
    - llvm + clang : http://llvm.org/builds/

Configurations
    1. Windows, MS Visual Studio Community 2017
        (needs Microsoft account)
        tested : 15.9.3

        How: just "Open in Visual Studio" from Explorer
        (CMake GUI should also work)

    2. Windows, Visual Studio 15 2017, vcpkg
        2.1 CMake GUI 3.13.0
            Generator "Visual Studio 15 2017 Win64"
            "Specify toolchain file for cross-compiling" : vcpkg/scripts/buildsystems/vcpkg.cmake

        2.2 "Open in Visual Studio" from Explorer (VS's cmake)
            see # https://vcpkg.readthedocs.io/en/latest/users/integration/
            (in "workshop\c++\01-cmake\02-vcpkg")

    3. Windows, Visual Studio 15 2017, llvm 8.0.0
       
        see https://github.com/arves100/llvm-vs2017-integration
            each llvm version has its own branch: 8 is missing as of 2019.03.

            dir "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\VC\VCTargets\Platforms\x64\PlatformToolsets"
                v141
                v141_clang_c2

            (home: it is F:!)

            add "LLVM-vs2017"
                with Toolset.props & Toolset.targets copied from Toolset-llvm-vs2017-x64

                Toolset.props:
                replace <ExecutablePath> with:
                    <was_ExecutablePath>$(LLVMInstallDir)\msbuild-bin;$(ExecutablePath)</was_ExecutablePath>
                    <CLToolExe>clang-cl.exe</CLToolExe>
                    <CLToolPath>$(LLVMInstallDir)\bin</CLToolPath>
                    <LibraryPath>$(LLVMInstallDir)\lib\clang\8.0.0\lib\windows;$(LibraryPath)</LibraryPath>   

        3.1 CMake GUI
            Generator "Visual Studio 15 2017 Win64"
            Optional toolset : LLVM-vs2017

            https://stackoverflow.com/questions/50883851/how-to-stop-gm-being-passed-to-clang-cl-exe-from-cmake


##################################################################################################
\todo
    -   http://llvm.org/builds/ : get clang-format

##################################################################################################
vcpkg

- sqlite3 choosed for samples
https://github.com/Microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md

##################################################################################################
Reference

        https://llvm.org/docs/GettingStartedVS.html
        https://stackoverflow.com/questions/38171878/how-do-i-tell-cmake-to-use-clang-on-windows
            ? -T"LLVM-vs2014"
            https://stackoverflow.com/questions/43464856/integrate-llvm-clang-4-x-x-5-x-x-6-x-x-into-visual-studio-2017
            https://github.com/arves100/llvm-vs2017-integration

            dir "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\VC\VCTargets\Platforms\x64\PlatformToolsets"
                v141
                v141_clang_c2

##################################################################################################