# Copyright Zach Laine 2022
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

###############################################################################
# Boost
###############################################################################
find_package(Boost 1.74.0 COMPONENTS ${boost_components})


###############################################################################
# GoogleTest
###############################################################################
#add_subdirectory(${CMAKE_SOURCE_DIR}/googletest-release-1.10.0)
#target_compile_definitions(gtest      PUBLIC GTEST_LANG_CXX11=1)
#target_compile_definitions(gtest_main PUBLIC GTEST_LANG_CXX11=1)
#target_include_directories(gtest      INTERFACE $<BUILD_INTERFACE:${CMAKE_HOME_DIRECTORY}/googletest-release-1.10.0/googletest/include>)
#target_include_directories(gtest_main INTERFACE $<BUILD_INTERFACE:${CMAKE_HOME_DIRECTORY}/googletest-release-1.10.0/googletest/include>)
