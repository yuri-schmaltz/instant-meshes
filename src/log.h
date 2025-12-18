/*
    log.h: Simple structured logging system
*/

#pragma once

#include <iostream>
#include <mutex>
#include <sstream>

enum class LogLevel { Debug, Info, Warn, Error };

class Log {
public:
  static Log &instance() {
    static Log instance;
    return instance;
  }

  template <typename... Args> void log(LogLevel level, Args... args) {
    std::lock_guard<std::mutex> lock(mMutex);
    std::ostringstream oss;
    switch (level) {
    case LogLevel::Debug:
      oss << "[DEBUG] ";
      break;
    case LogLevel::Info:
      oss << "[INFO]  ";
      break;
    case LogLevel::Warn:
      oss << "[WARN]  ";
      break;
    case LogLevel::Error:
      oss << "[ERROR] ";
      break;
    }
    print(oss, args...);
    oss << std::endl;

    // In the future, this could write to a file as well
    if (level == LogLevel::Error || level == LogLevel::Warn)
      std::cerr << oss.str();
    else
      std::cout << oss.str();
  }

private:
  Log() {}

  template <typename T, typename... Args>
  void print(std::ostringstream &oss, T first, Args... args) {
    oss << first;
    print(oss, args...);
  }

  template <typename T> void print(std::ostringstream &oss, T last) {
    oss << last;
  }

  void print(std::ostringstream &oss) {}

  std::mutex mMutex;
};

// Convenience macros
#define IM_DEBUG(...) Log::instance().log(LogLevel::Debug, __VA_ARGS__)
#define IM_INFO(...) Log::instance().log(LogLevel::Info, __VA_ARGS__)
#define IM_WARN(...) Log::instance().log(LogLevel::Warn, __VA_ARGS__)
#define IM_ERROR(...) Log::instance().log(LogLevel::Error, __VA_ARGS__)
