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
    #lib/ApplicationServerManager.cpp
    #lib/I_AbstractNetworkAddressFactory.cpp
    #lib/I_ApplicationServer.cpp
    lib/I_ApplicationServerManager.cpp
    lib/I_Connection.cpp
    lib/I_Request.cpp
    lib/I_RequestHandler.cpp
    lib/I_ResourceLocation.cpp
    lib/I_Response.cpp
    lib/I_ResponseHandler.cpp
    #lib/I_SessionEvent.cpp
)

set(HEADERS
    #include/Zen/Enterprise/I_AbstractNetworkAddressFactory.hpp
    include/Zen/Enterprise/I_Address.hpp
    #include/Zen/Enterprise/I_ApplicationServer.hpp
    include/Zen/Enterprise/I_ApplicationServerManager.hpp
    include/Zen/Enterprise/I_Connection.hpp
    include/Zen/Enterprise/I_Request.hpp
    include/Zen/Enterprise/I_RequestHandler.hpp
    include/Zen/Enterprise/I_ResourceLocation.hpp
    include/Zen/Enterprise/I_SessionEvent.hpp
    include/Zen/Enterprise/I_Response.hpp
    include/Zen/Enterprise/I_ResponseHandler.hpp
    include/Zen/Enterprise/I_TimeoutHandler.hpp
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

install(TARGETS zen-enterprise DESTINATION /usr/local/bin)
install(DIRECTORY include DESTINATION /usr/local)
