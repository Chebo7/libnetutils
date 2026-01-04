cmake_minimum_required(VERSION 3.30)
project(libnetutils VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_SHARED_LIBS "Build shared library" ON)

add_library(netutils
    src/Ipv4NetworkInterfaces.cpp
    src/Ipv6NetworkInterfaces.cpp
)

target_include_directories(netutils
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set_target_properties(netutils PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "include/netutils/Ipv4NetworkInterfaces.hpp;include/netutils/Ipv6NetworkInterfaces.hpp"
)

install(TARGETS netutils
    EXPORT netutils-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/netutils
)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT netutils-targets
    FILE netutils-config.cmake
    NAMESPACE netutils::
    DESTINATION lib/cmake/netutils
)