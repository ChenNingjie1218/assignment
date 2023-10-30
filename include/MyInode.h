#ifndef MYINODE_H
#define MYINODE_H
#include <array>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <shared_mutex>
#include <vector>
class MyInode {
 public:
  MyInode();
  ~MyInode() = default;
  int read_file(uint64_t offset);
  void write_file(int block);
  time_t get_ctime() const;
  time_t get_mtime() const;
  uint64_t get_size() const;
  // std::shared_mutex& get_mutex();
  void serialize(std::fstream &fs) const;
  void deserialize(std::fstream &fs);
  void add_i_size(uint64_t increment);
  std::vector<uint32_t> get_block_vector() const;
  void rewrite();

 private:
  void set_ctime(time_t ctime);
  void set_mtime(time_t mtime);
  void set_i_block_count(uint16_t count);
  void set_i_size(uint64_t size);
  uint64_t i_size_;                    //文件大小
  time_t i_ctime_;                     //创建时间
  time_t i_mtime_;                     //修改时间
  uint16_t i_block_count_;             //文件占用块数
  std::array<uint32_t, 127> i_block_;  // block的块号
  // std::shared_mutex mutex_;            //文件的读写锁
};
#endif