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
    kType_Default, /*Ĭ������*/
    kType_Info, /*��Ϣ*/
    kType_Time, /*ʱ��*/
    kType_Blank, /*�հ�*/
    kType_Notice, /*��ʾ*/
    kType_ErrorMsg, /*������Ϣ*/
    kType_WarningMsg /*������Ϣ*/
  };

public:
  static void Init(int level = 0x7); // Ĭ��ȫ����ӡ
  
  /*DefaultMsg Notice Info ������kLevelInfo����ȼ�*/
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
