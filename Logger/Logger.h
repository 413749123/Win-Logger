#pragma once

#include <Windows.h>

class Logger {
private:
  Logger();
  ~Logger();

public:
  static const int kLevelError = 0x1;
  static const int kLevelWarning = 0x2;
  static const int kLevelInfo = 0x4;

  enum Type {
    kType_Default, /*默认配置*/
    kType_Info, /*信息*/
    kType_Time, /*时间*/
    kType_Blank, /*空白*/
    kType_Notice, /*提示*/
    kType_ErrorMsg, /*错误信息*/
    kType_WarningMsg /*警告信息*/
  };

public:
  static void Init(int level = 0x7); // 默认全部打印
  
  /*DefaultMsg Notice Info 都属于kLevelInfo这个等级*/
  static void DefaultMsg(std::string msg);
  static void DefaultMsg(const char* format, ...);
  static void Notice(std::string msg);
  static void Notice(const char* format, ...);
  static void Info(std::string msg);
  static void Info(const char* format, ...);
  static void Warning(std::string msg);
  static void Warning(const char* format, ...);
  static void Error(std::string msg);
  static void Error(const char* format, ...);

private:
  static inline Logger *GetLogger() 
  {
    if (logger_ == nullptr) {
      logger_ = new Logger();
    }
    return logger_;
  }
  void WriteLine(std::string msg, Type type = kType_Default);
  void Write(std::string msg, Type type = kType_Default);
  void Out(std::string msg);

private:
  static Logger *logger_;
  
  int log_level_ = 0x7;
  HANDLE handle_out_;
  bool is_console_alloced_ = false;
};
