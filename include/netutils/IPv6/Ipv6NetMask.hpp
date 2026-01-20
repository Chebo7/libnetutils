#pragma once
#include <arpa/inet.h>
#include <cstring>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>

namespace NetUtils {
namespace IPv6 {
std::string Ipv6NetMask(const std::string interface);
}
} // namespace NetUtils