#ifndef MYSHELL_H
#define MYSHELL_H
#include <iomanip>
#include <map>
#include <sstream>
#include <string>

#include "MyFileSystem.h"
class MyShell {
 public:
  MyShell();
  ~MyShell() = default;
  void work();

 private:
  //初始化
  void init();
  /*帮助*/
  void help();
  /*删除*/
  void rm(const char* pathname);
  /*读取*/
  void read_from_myfilesystem(std::string& pathname, std::string& dstpath);
  /*写入*/
  void write_to_myfilesystem(std::string& srcname, std::string& pathname);
  /*查看文件列表*/
  void ls(int type);
  /*格式化文件系统*/
  void format();

  MyFileSystem file_system_;              //我的文件系统
  std::map<std::string, std::string> op;  //操作及说明
};
#endif