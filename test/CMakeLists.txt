include_directories(${CMAKE_HOME_DIRECTORY})

include(CTest)

enable_testing()

add_custom_target(
    check
    COMMAND ${CMAKE_CTEST_COMMAND} -j4 -C ${CMAKE_CFG_INTDIR}
)

add_custom_target(
    compile_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose -C ${CMAKE_CFG_INTDIR} -R compile_
)

set(warnings_flag)
if (NOT MSVC)
    set(warnings_flag -Wall)
endif ()

macro(add_test_executable name)
    set(local_name ${name})
    add_executable(${local_name} ${name}.cpp)
    target_compile_options(${local_name} PRIVATE ${warnings_flag})
    target_link_libraries(${local_name} ic_literals ${boost_lib} gtest gtest_main)
    if (MSVC)
        target_compile_options(${local_name} PRIVATE /source-charset:utf-8)
    endif ()
    set_property(TARGET ${local_name} PROPERTY CXX_STANDARD ${CXX_STD})
    add_test(${local_name} ${CMAKE_CURRENT_BINARY_DIR}/${local_name} --gtest_catch_exceptions=1)
    if (clang_on_linux)
        target_link_libraries(${local_name} c++)
    endif ()
endmacro()

#add_test_executable(foo)

macro(add_compile_test name)
    add_library(${name} STATIC EXCLUDE_FROM_ALL ${name}.cpp)
    target_compile_options(${name} PRIVATE ${warnings_flag})
    target_link_libraries(${name} ic_literals ${boost_lib})
    set_property(TARGET ${name} PROPERTY CXX_STANDARD ${CXX_STD})
    if (clang_on_linux)
        target_link_libraries(${name} c++)
    endif ()
    add_test(NAME ${name}_test COMMAND ${CMAKE_COMMAND} --build . --target ${name})
    message("added test")
endmacro()

macro(add_compile_fail_test name)
    add_compile_test(${name})
    set_tests_properties(${name} PROPERTIES WILL_FAIL TRUE)
endmacro()

add_compile_test(compile_test)
