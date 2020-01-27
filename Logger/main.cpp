#include <iostream>
#include "Logger.h"

//void Test() {
//  for (int i = 0; i < 256; i++) {
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
//                            i);
//    std::cout << "Hello 你好" << i << std::endl;
//  }
//}

int main()
{
  Logger::Init(Logger::kLevelError | Logger::kLevelInfo | Logger::kLevelWarning); // 
  Logger::Info("Info:信息");
  Logger::Notice("Notice:提示 %d", 123);
  Logger::DefaultMsg("Default:默认");
  Logger::Error("Error:错误 %s","No such file ...");
  Logger::Warning("Warning:警告");
  //Test();
  std::cout << "Hello World!\n";
}