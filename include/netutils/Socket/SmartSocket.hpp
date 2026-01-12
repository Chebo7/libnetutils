#pragma once

namespace NetUtils {
namespace Socket {
class SmartSocket {
private:
  int fd = 0;

public:
  SmartSocket(int domain, int type, int protocol);
  SmartSocket(const SmartSocket &) = delete;
  SmartSocket(SmartSocket &&) = delete;
  SmartSocket &operator=(const SmartSocket &) = delete;
  SmartSocket &operator=(SmartSocket &&) = delete;
  ~SmartSocket();

  operator int() const;

  int getFd() { return fd; }
};
} // namespace Socket
} // namespace NetUtils