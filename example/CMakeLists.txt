include_directories(${CMAKE_HOME_DIRECTORY})

macro(add_sample name)
    add_executable(${name} ${name}.cpp)
    target_compile_options(${name} PRIVATE -Wall)
    target_link_libraries(${name} ic_literals boost)
    set_property(TARGET ${name} PROPERTY CXX_STANDARD ${CXX_STD})
    if (clang_on_linux)
        target_link_libraries(${name} c++)
    endif ()
endmacro()

#add_sample(foo)
