#ifndef MYSUPERBLOCK_H
#define MYSUPERBLOCK_H
#include <bitset>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>

class MySuperBlock {
 public:
  MySuperBlock();
  ~MySuperBlock() = default;

  int allocate();
  // void free();
  void allocate_block(uint16_t block_number);
  void free_block(uint16_t block_number);

  uint16_t get_free_block_count() const;
  uint32_t get_size() const;
  uint16_t get_block_count() const;

  //序列化
  void serialize(std::fstream& fs) const;

  //反序列化
  void deserialize(std::fstream& fs);

 private:
  void update_free_block_count();

  std::bitset<127> bitmap_;    //该文件系统的位图表
  uint16_t block_count_;       //该文件系统的分片总数
  uint32_t size_;              //该文件系统的块大小
  uint16_t free_block_count_;  //该文件系统空闲块数
};
#endif