#include <iostream>
#include "Logger.h"

//void Test() {
//  for (int i = 0; i < 256; i++) {
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
//                            i);
//    std::cout << "Hello ���" << i << std::endl;
//  }
//}

int main()
{
  Logger::Init(Logger::kLevelError | Logger::kLevelInfo | Logger::kLevelWarning); // 
  Logger::Info("Info:��Ϣ");
  Logger::Notice("Notice:��ʾ %d", 123);
  Logger::DefaultMsg("Default:Ĭ��");
  Logger::Error("Error:���� %s","No such file ...");
  Logger::Warning("Warning:����");
  //Test();
  std::cout << "Hello World!\n";
}