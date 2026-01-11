#pragma once

namespace NetUtils {
namespace Socket {
class SmartSocket {
private:
  int fd = 0;

public:
  SmartSocket(int domain, int type, int protocol);
  SmartSocket(const SmartSocket &) = default;
  SmartSocket(SmartSocket &&) = default;
  SmartSocket &operator=(const SmartSocket &) = default;
  SmartSocket &operator=(SmartSocket &&) = default;
  ~SmartSocket();

  operator int() const;

  int getFd() { return fd; }
};
} // namespace Socket
} // namespace NetUtils