
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
    - Windows, MS Visual Studio Community 2017
		(needs Microsoft account)
        tested : 15.9.3

        How: just "Open in Visual Studio" from Explorer
        (CMake GUI should also work)

    - Windows, Visual Studio 15 2017, llvm 8.0.0
		\wip

##################################################################################################
\todo
    -   http://llvm.org/builds/ : get clang-format

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
