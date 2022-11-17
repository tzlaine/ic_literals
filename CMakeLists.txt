cmake_minimum_required(VERSION 3.22)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
project(ic_literals LANGUAGES CXX)

################################################## 
# C++ standard version selection
################################################## 
set(CXX_STD 23 CACHE STRING "Set to 14, 17, etc., to enable C++14, C++17, etc.")
message("-- Using -std=c++${CXX_STD}")


##################################################
# Sanitizers
##################################################
set(USE_ASAN false CACHE BOOL "Set to true to enable -fsanitize=address when building tests.") 
set(USE_UBSAN false CACHE BOOL "Set to true to enable -fsanitize=undefined when building tests.")
if (USE_ASAN AND USE_UBSAN)
    message(FATAL_ERROR "USE_ASAN and USE_UBSAN must not be enabled at the same time")
elseif (USE_ASAN)
    set(compile_flags -fsanitize=address)
    set(link_flags -fsanitize=address)
    message("-- Using -fsanitize=address") 
elseif (USE_UBSAN)
    set(compile_flags -fsanitize=undefined)
    set(link_flags -fsanitize=undefined)
    message("-- Using -fsanitize=undefined")
endif()

##################################################
# Dependencies
##################################################
set(boost_components)

include(dependencies)

set(boost_lib)
if (Boost_INCLUDE_DIR)
  set(boost_lib Boost::boost)
endif()


##################################################
# library
##################################################
add_library(ic_literals INTERFACE)
target_include_directories(ic_literals
  INTERFACE
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
set_property(TARGET ic_literals PROPERTY CXX_STANDARD ${CXX_STD})
if (link_flags)
    target_link_libraries(ic_literals PUBLIC ${link_flags})
    target_compile_options(ic_literals PUBLIC ${compile_flags})
endif ()
if (NOT MSVC)
  target_compile_options(ic_literals INTERFACE -Wno-literal-suffix)
endif ()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
  DESTINATION "include")

##################################################
# Tests and examples
##################################################
add_subdirectory(test)
add_subdirectory(example)
