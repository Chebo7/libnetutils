cmake_minimum_required(VERSION 3.30)
project(libnetutils VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_SHARED_LIBS "Build shared library" ON)

add_library(netutils
    src/IPv4/Ipv4NetworkInterfaces.cpp
    src/IPv6/Ipv6NetworkInterfaces.cpp
    src/IPv4/Ipv4InterfaceAddress.cpp
    src/IPv6/Ipv6InterfaceAddress.cpp
    src/IPv4/Ipv4MacAddress.cpp
    src/IPv6/Ipv6MacAddress.cpp
    src/IPv4/Ipv4NetMask.cpp
    src/Socket/SmartSocket.cpp
    
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
    PUBLIC_HEADER "include/netutils/IPv4/Ipv4NetworkInterfaces.hpp;include/netutils/IPv6/Ipv6NetworkInterfaces.hpp;include/netutils/IPv4/Ipv4InterfaceAddress.hpp;include/netutils/IPv6/Ipv6InterfaceAddress.hpp;include/netutils/IPv4/Ipv4MacAddress.hpp;include/netutils/IPv6/Ipv6MacAddress.hpp;include/netutils/IPv4/Ipv4NetMask.hpp;include/netutils/Socket/SmartSocket.hpp"
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