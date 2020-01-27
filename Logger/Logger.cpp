#include <iostream>
#include <string>
#include <Windows.h>
#include "Logger.h"

Logger *Logger::logger_ = nullptr;

Logger::Logger()
{
  is_console_alloced_ = AllocConsole();

  handle_out_ = GetStdHandle(STD_OUTPUT_HANDLE);
}

Logger::~Logger()
{
  if (is_console_alloced_) {
    FreeConsole();
  }
}

void Logger::Init(int level /*= 0x7*/)
{
  GetLogger()->log_level_ = level;
}

void Logger::DefaultMsg(std::string msg)
{
  if (!(GetLogger()->log_level_ & kLevelInfo)) return;
  GetLogger()->WriteLine(msg, kType_Default);
}
void Logger::DefaultMsg(const char * format, ...)
{
  if (!(GetLogger()->log_level_ & kLevelInfo)) return;
  char buf[16 * 1024] = { 0 };
  va_list ap;

  va_start(ap, format);
  vsprintf_s(buf, _countof(buf), format, ap);
  GetLogger()->WriteLine(buf, kType_Default);
  va_end(ap);
}

void Logger::Notice(std::string msg)
{
  if (!(GetLogger()->log_level_ & kLevelInfo)) return;
  GetLogger()->WriteLine(msg, kType_Notice);
}

void Logger::Notice(const char * format, ...)
{
  if (!(GetLogger()->log_level_ & kLevelInfo)) return;
  char buf[16 * 1024] = { 0 };
  va_list ap;

  va_start(ap, format);
  vsprintf_s(buf, _countof(buf), format, ap);
  GetLogger()->WriteLine(buf, kType_Notice);
  va_end(ap);
}

void Logger::Info(std::string msg)
{
  if (!(GetLogger()->log_level_ & kLevelInfo)) return;
  GetLogger()->WriteLine(msg, kType_Info);
}

void Logger::Info(const char * format, ...)
{
  if (!(GetLogger()->log_level_ & kLevelInfo)) return;
  char buf[16 * 1024] = { 0 };
  va_list ap;

  va_start(ap, format);
  vsprintf_s(buf, _countof(buf), format, ap);
  GetLogger()->WriteLine(buf, kType_Info);
  va_end(ap);
}

void Logger::Warning(std::string msg)
{
  if (!(GetLogger()->log_level_ & kLevelWarning)) return;
  GetLogger()->WriteLine(msg, kType_WarningMsg);
}

void Logger::Warning(const char * format, ...)
{
  if (!(GetLogger()->log_level_ & kLevelWarning)) return;
  char buf[16 * 1024] = { 0 };
  va_list ap;

  va_start(ap, format);
  vsprintf_s(buf, _countof(buf), format, ap);
  GetLogger()->WriteLine(buf, kType_WarningMsg);
  va_end(ap);
}

void Logger::Error(std::string msg)
{
  if (!(GetLogger()->log_level_ & kLevelError)) return;
  GetLogger()->WriteLine(msg, kType_ErrorMsg);
}

void Logger::Error(const char * format, ...)
{
  if (!(GetLogger()->log_level_ & kLevelError)) return;
  char buf[16 * 1024] = { 0 };
  va_list ap;

  va_start(ap, format);
  vsprintf_s(buf, _countof(buf), format, ap);
  GetLogger()->WriteLine(buf, kType_ErrorMsg);
  va_end(ap);
}

void Logger::WriteLine(std::string msg, Type type)
{
  //Write("[2020-01-20 15:19:00]", kType_Time);
  Write(msg, type);
  Out("\n");
}

void Logger::Write(std::string msg, Type type)
{
  // 不给值就是黑色
  static int FOREGROUND_WHITE = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
  static int BACKGROUND_WHITE = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE;
  switch (type)
  {
    case kType_Default:
      SetConsoleTextAttribute(handle_out_,
                              FOREGROUND_WHITE);
      break;
    case kType_Blank:
      SetConsoleTextAttribute(handle_out_,
                              FOREGROUND_INTENSITY |
                              BACKGROUND_INTENSITY);
      break;
    case kType_Info:
      SetConsoleTextAttribute(handle_out_,
                              FOREGROUND_WHITE |
                              BACKGROUND_BLUE |
                              FOREGROUND_INTENSITY);
      break;
    case kType_Time:
      SetConsoleTextAttribute(handle_out_,
                              BACKGROUND_WHITE |
                              BACKGROUND_INTENSITY);
      break;
    case kType_Notice:
      SetConsoleTextAttribute(handle_out_,
                              47);
      break;
    case kType_ErrorMsg:
      SetConsoleTextAttribute(handle_out_,
                              FOREGROUND_WHITE | FOREGROUND_INTENSITY |
                              BACKGROUND_RED);
      break;
    case kType_WarningMsg:
      SetConsoleTextAttribute(handle_out_,
                              FOREGROUND_WHITE | FOREGROUND_INTENSITY |
                              BACKGROUND_RED | BACKGROUND_GREEN);
      break;
    default:
      break;
  }
  
  Out(msg);
  SetConsoleTextAttribute(handle_out_,/*恢复默认配色*/
                          FOREGROUND_WHITE);
}

void Logger::Out(std::string msg)
{
  DWORD len = msg.length();
  WriteFile(handle_out_, msg.c_str(), len, &len, 0);
}
