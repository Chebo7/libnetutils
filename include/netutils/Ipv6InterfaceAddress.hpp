#pragma once
#include <arpa/inet.h>
#include <cstring>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

namespace NetUtils {
std::string Ipv6InterfaceAddress(std::string interface);
}