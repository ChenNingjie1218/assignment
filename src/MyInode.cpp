#include "MyInode.h"

MyInode::MyInode() {
  time_t create_time = time(NULL);
  set_ctime(create_time);
  set_mtime(create_time);
  set_i_block_count(0);
  set_i_size(0);
}

int MyInode::read_file(uint64_t offset) {
  if (offset < i_size_)
    return i_block_[offset / (64 * 1024 * 1024)];
  else
    return -1;
}

void MyInode::write_file(int block) { i_block_[i_block_count_++] = block; }

time_t MyInode::get_ctime() const { return i_ctime_; }

time_t MyInode::get_mtime() const { return i_mtime_; }

uint64_t MyInode::get_size() const { return i_size_; }

void MyInode::set_i_size(uint64_t size) { i_size_ = size; }

void MyInode::set_ctime(time_t ctime) { i_ctime_ = ctime; }

void MyInode::set_mtime(time_t mtime) { i_mtime_ = mtime; }

void MyInode::set_i_block_count(uint16_t count) { i_block_count_ = count; }

void MyInode::serialize(std::fstream &fs) const {
  fs.write(reinterpret_cast<const char *>(&i_size_), sizeof(i_size_));
  fs.write(reinterpret_cast<const char *>(&i_ctime_), sizeof(i_ctime_));
  fs.write(reinterpret_cast<const char *>(&i_mtime_), sizeof(i_mtime_));
  fs.write(reinterpret_cast<const char *>(&i_block_count_),
           sizeof(i_block_count_));
  fs.write(reinterpret_cast<const char *>(i_block_.data()),
           sizeof(uint32_t) * i_block_.size());
}
void MyInode::deserialize(std::fstream &fs) {
  fs.read(reinterpret_cast<char *>(&i_size_), sizeof(i_size_));
  fs.read(reinterpret_cast<char *>(&i_ctime_), sizeof(i_ctime_));
  fs.read(reinterpret_cast<char *>(&i_mtime_), sizeof(i_mtime_));
  fs.read(reinterpret_cast<char *>(&i_block_count_), sizeof(i_block_count_));
  fs.read(reinterpret_cast<char *>(i_block_.data()),
          sizeof(uint32_t) * i_block_.size());
}

void MyInode::add_i_size(uint64_t increment) { i_size_ += increment; }

std::vector<uint32_t> MyInode::get_block_vector() const {
  std::vector<uint32_t> block_vector;
  for (uint16_t i = 0; i < i_block_count_; ++i) {
    block_vector.push_back(i_block_[i]);
  }
  return block_vector;
}

void MyInode::rewrite() {
  time_t modify_time = time(NULL);
  set_mtime(modify_time);
  set_i_block_count(0);
  set_i_size(0);
}