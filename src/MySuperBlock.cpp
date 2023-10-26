#include "MySuperBlock.h"

constexpr uint16_t max_block = 127;

constexpr uint32_t size_block = 64 * 1024 * 1024;  //文件系统分块大小

MySuperBlock::MySuperBlock() : block_count_(max_block), size_(size_block) {
  bitmap_.reset();
  update_free_block_count();
}

uint16_t MySuperBlock::allocate() {
  int size = bitmap_.size();
  for (int i = 0; i < size; ++i) {
    if (!bitmap_[i]) {
      allocate_block(i);
      return i;
    }
  }
  return -1;
}

void MySuperBlock::allocate_block(uint16_t block_number) {
  if (block_number >= 0 && block_number < max_block) {
    if (!bitmap_.test(block_number)) {
      bitmap_.set(block_number);
      update_free_block_count();
#ifndef NDEBUG
      std::cout << "分配块号：" << block_number << std::endl;
#endif
    } else {
      std::cerr << "分配错误！该块已经被分配!" << std::endl;
    }
  } else {
    std::cerr << "申请的块不合法！" << std::endl;
  }
}

void MySuperBlock::free_block(uint16_t block_number) {
  if (block_number >= 0 && block_number < max_block) {
    if (bitmap_.test(block_number)) {
      bitmap_.reset(block_number);
      update_free_block_count();
#ifndef NDEBUG
      std::cout << "回收块号:" << block_number << std::endl;
#endif
    } else {
      std::cerr << "释放错误！该块并没有被分配！" << std::endl;
    }
  } else {
    std::cerr << "释放的块不合法！" << std::endl;
  }
}

uint16_t MySuperBlock::get_free_block_count() const {
  return free_block_count_;
}

uint32_t MySuperBlock::get_size() const { return size_; }

uint16_t MySuperBlock::get_block_count() const { return block_count_; }

void MySuperBlock::update_free_block_count() {
  free_block_count_ = max_block - bitmap_.count();
}

//序列化
void MySuperBlock::serialize(std::fstream& fs) const {
  fs.seekp(0, std::ios::beg);
  unsigned long long bitsetdata = bitmap_.to_ullong();
  fs.write(reinterpret_cast<const char*>(&bitsetdata), sizeof(bitsetdata));
  fs.write(reinterpret_cast<const char*>(&block_count_), sizeof(block_count_));
  fs.write(reinterpret_cast<const char*>(&size_), sizeof(size_));
  fs.write(reinterpret_cast<const char*>(&free_block_count_),
           sizeof(free_block_count_));
}

//反序列化
void MySuperBlock::deserialize(std::fstream& fs) {
  fs.seekg(0, std::ios::beg);
  unsigned long long bitsetdata;
  fs.read(reinterpret_cast<char*>(&bitsetdata), sizeof(bitsetdata));
  bitmap_ = std::bitset<127>(bitsetdata);
  fs.read(reinterpret_cast<char*>(&block_count_), sizeof(block_count_));
  fs.read(reinterpret_cast<char*>(&size_), sizeof(size_));
  fs.read(reinterpret_cast<char*>(&free_block_count_),
          sizeof(free_block_count_));
}