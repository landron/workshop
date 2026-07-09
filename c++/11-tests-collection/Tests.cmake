# ctest -V: test compiling errors

set(CMAKE_REQUIRED_FLAGS "-std=c++23")

# NRVO is mandatory in C++ 17

add_test(
    # nrvo = Named Return Value Optimization
    NAME nrvo_should_fail
    COMMAND ${CMAKE_CXX_COMPILER}
            ${CMAKE_CURRENT_SOURCE_DIR}/cpp17/copy-elision/nrvo_fails.cpp
            -c
)
# set_tests_properties(nrvo_should_fail PROPERTIES WILL_FAIL TRUE)
# The test passes ONLY if it fails due to the deleted move constructor
set_tests_properties(nrvo_should_fail PROPERTIES 
    PASS_REGULAR_EXPRESSION "attempting to reference a deleted function|use of deleted function"
)

# slicing protection 1: through "protected" 

add_test(
    NAME slice_should_fail_1
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++26
            ${CMAKE_CURRENT_SOURCE_DIR}/01_slicing/protected/slice_fails_1.cpp
            -c
)
set_tests_properties(slice_should_fail_1 PROPERTIES 
    PASS_REGULAR_EXPRESSION "is protected within this context|declared protected here"
)
add_test(
    NAME slice_should_fail_2
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++26
            ${CMAKE_CURRENT_SOURCE_DIR}/01_slicing/protected/slice_fails_2.cpp
            -c
)
set_tests_properties(slice_should_fail_2 PROPERTIES 
    PASS_REGULAR_EXPRESSION "is protected within this context|declared protected here"
)
