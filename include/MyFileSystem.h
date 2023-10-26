#ifndef MYFILESYSTEM_H
#define MYFILESYSTEM_H
#include <string.h>
#include <unistd.h>

#include <array>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "MyInode.h"
#include "MySuperBlock.h"

class MyFileSystem {
 public:
  MyFileSystem();
  ~MyFileSystem();
  /*格式化文件系统*/
  void format();
  /*显示文件列表*/
  void list_show(int type);
  /*写文件*/
  ssize_t write(int fd, const void* buf, size_t count);
  /*读文件*/
  ssize_t read(int fd, void* buf, size_t count);
  /*删除文件*/
  void remove(const char* pathname);
  /*打开文件*/
  int open(const char* pathname, int oflag);
  /*关闭文件*/
  int close(int filedes);

 private:
  /*创建文件*/
  int create(const char* pathname);
  /*刷新文件系统*/
  void fresh_my_filesystem();
  /*回写文件系统*/
  void write_my_filesystem();

  std::vector<MyInode> inodes_;                      // inode列表
  size_t count_inodes_;                              // inode数
  MySuperBlock super_block_;                         //超级块
  std::vector<std::array<char, 16>> name_to_inode_;  //名字对应id号
  std::fstream file_system_;                         //文件系统
  uint32_t offset;                                   //文件偏移量
};
#endif