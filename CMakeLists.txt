cmake_minimum_required (VERSION 3.5)

# Using experimental C++ features, including c++14 and c++17.
set(CMAKE_CXX_FLAGS "-std=c++1z")

project(zenenterprise)

# Don't build in this directory
# mkdir ../zen-enterprise-build
# cd ../zen-enterprise-build
# cmake ../zen-enterprise
# make
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

find_package(Boost REQUIRED unit_test_framework)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(SOURCES
    lib/I_Connection.cpp
)

set(HEADERS
    include/Zen/Enterprise/I_Connection.hpp
)

add_definitions(-DZEN_ENTERPRISE_EXPORTS)
add_definitions(-DBOOST_TEST_DYN_LINK) 

add_library(zen-enterprise ${SOURCES})

enable_testing()

set(TEST_SOURCES
    test/memory.cpp
)

add_executable( zen-enterprise-tests ${TEST_SOURCES})

target_link_libraries( zen-enterprise-tests zen-enterprise
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test( tests zen-enterprise-tests)
