#pragma once
#include <functional>
#include <iostream>
#include <sstream>

// A simple internal helper to redirect raw output to a callback
class LogStreamBuffer : public std::stringbuf {
public:
  using Callback = std::function<void(const std::string &)>;

  LogStreamBuffer(Callback cb) : m_callback(cb) {}

  virtual int sync() override {
    std::string s = this->str();
    if (!s.empty()) {
      if (m_callback)
        m_callback(s);
      this->str("");
    }
    return 0;
  }

private:
  Callback m_callback;
};
