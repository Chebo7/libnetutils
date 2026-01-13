#pragma once
#include <cerrno>
#include <cstring>
#include <linux/sockios.h>
#include <net/if.h>
#include <print>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>

namespace NetUtils {
namespace IPv4 {
int Ipv4IndexInterface(std::string interface);
}
} // namespace NetUtils