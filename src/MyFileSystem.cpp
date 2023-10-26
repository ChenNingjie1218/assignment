#include "MyFileSystem.h"

#include <cstddef>
const char* FILESYSTEM_PATH = "../../doc/myfilesystem";
MyFileSystem::MyFileSystem() { fresh_my_filesystem(); };
MyFileSystem::~MyFileSystem() { write_my_filesystem(); }
// template <typename T>
// std::fstream& operator<<(std::fstream& os, const T& obj) {
//   os << obj;
//   return os;
// }

/*格式化文件系统*/
void MyFileSystem::format() {
  file_system_.open(FILESYSTEM_PATH,
                    std::ios::out | std::ios::in | std::ios::binary);
  MySuperBlock init_block;
  init_block.serialize(file_system_);
  file_system_.seekp(static_cast<std::streamoff>(32 * 1024 * 1024),
                     std::ios::beg);
  size_t init_count_inodes = 0;
  // file_system_ << init_count_inodes;
  file_system_.write(reinterpret_cast<const char*>(&init_count_inodes),
                     sizeof(init_count_inodes));
  file_system_.close();
  fresh_my_filesystem();
}

/*显示文件列表*/
void MyFileSystem::list_show(int type) {
  if (type == 1) {
    int index = 0;
    std::cout << "total " << inodes_.size() << std::endl;
    for (const auto& inode : inodes_) {
      struct tm* timeinfo;
      time_t modify_time = inode.get_mtime();
      timeinfo = localtime(&modify_time);
      std::array<char, 80> mtime;
      strftime(mtime.data(), sizeof(mtime), "%b %d %H:%M", timeinfo);

      std::cout << inode.get_size() << '\t' << mtime.data() << '\t'
                << name_to_inode_[index++].data() << std::endl;
    }
  } else {
    for (const auto& name : name_to_inode_) {
      std::cout << name.data() << '\t';
    }
    std::cout << std::endl;
  }
}

/*写文件*/
ssize_t MyFileSystem::write(int fd, const void* buf, size_t count) {
  uint32_t block_size = super_block_.get_size();
  size_t write_count = 0;
  while (write_count < count) {
    int block = super_block_.allocate();
    if (block == -1) {
      std::cout << "文件系统满了" << std::endl;
      return write_count;
    }
    inodes_[fd].write_file(block);
    file_system_.seekp((block + 1) * block_size, std::ios::beg);
    if (count - write_count < block_size) {
      file_system_.write(static_cast<const char*>(buf), count - write_count);
      inodes_[fd].add_i_size(count - write_count);
      return count;
    } else {
      file_system_.write(static_cast<const char*>(buf), block_size);
      inodes_[fd].add_i_size(block_size);
    }
    write_count += block_size;
  }
  return write_count;
}

/*读文件*/
ssize_t MyFileSystem::read(int fd, void* buf, size_t count) {
  const uint32_t block_size = super_block_.get_size();
  size_t read_count = 0;
  if (inodes_[fd].get_size() - offset < count) {
    count = inodes_[fd].get_size() - offset;
  }
  // char read_buf[block_size];
  while (read_count < count) {
    int block = inodes_[fd].read_file(offset);
    if (block == -1) {
      return read_count;
    }
    file_system_.seekg((block + 1) * block_size + offset % block_size,
                       std::ios::beg);
    if (count - read_count < block_size - offset % block_size) {
      file_system_.read(static_cast<char*>(buf) + read_count,
                        count - read_count);
    } else {
      file_system_.read(static_cast<char*>(buf) + read_count,
                        block_size - offset % block_size);
    }
    read_count += file_system_.gcount();
    offset += file_system_.gcount();
    if (!file_system_.gcount()) {
      return read_count;
    }
  }
  return read_count;
}

/*删除文件*/
void MyFileSystem::remove(const char* pathname) {
  int fd = -1;
  size_t len = strlen(pathname);
  int size = name_to_inode_.size();
  for (int i = 0; i < size; ++i) {
    if (!strncmp(pathname, name_to_inode_[i].data(), len)) {
      fd = i;
      break;
    }
  }
  if (fd != -1) {
    for (const auto& block : inodes_[fd].get_block_vector()) {
      super_block_.free_block(block);
    }
    name_to_inode_.erase(name_to_inode_.begin() + fd);
    inodes_.erase(inodes_.begin() + fd);
    count_inodes_--;
  } else {
    std::cout << "没有该文件" << std::endl;
  }
}

/*打开文件*/
int MyFileSystem::open(const char* pathname, int oflag) {
  size_t len = strlen(pathname);
  for (std::vector<std::array<char, 16>>::iterator i = name_to_inode_.begin();
       i != name_to_inode_.end(); ++i) {
    if (len == strlen((*i).data()) &&
        strncmp(pathname, (*i).data(), len) == 0) {
      //默认写入已有文件就截断
      if (oflag & std::ios::out) {
        auto index = i - name_to_inode_.begin();
        for (const auto& block : inodes_[index].get_block_vector()) {
          super_block_.free_block(block);
        }
        inodes_[index].rewrite();
      }
      offset = 0;
      file_system_.open(FILESYSTEM_PATH,
                        std::ios::in | std::ios::out | std::ios::binary);
      return i - name_to_inode_.begin();
    }
  }
  if (name_to_inode_.size() < 127) {
    file_system_.open(FILESYSTEM_PATH,
                      std::ios::in | std::ios::out | std::ios::binary);
    return create(pathname);
  } else {
    return -1;
  }
}

/*创建文件*/
int MyFileSystem::create(const char* pathname) {
  MyInode inode;
  // struct tm* timeinfo;
  // time_t create_time = inode.get_ctime();
  // timeinfo = localtime(&create_time);
  std::array<char, 16> pathbuf;
  size_t size = std::min(strlen(pathname), pathbuf.size() - 1);
  std::strncpy(pathbuf.data(), pathname, size);
  pathbuf[size] = '\0';
  // strftime(pathbuf.data(), sizeof(pathbuf), "%Y-%m-%d", timeinfo);

  name_to_inode_.push_back(pathbuf);
  inodes_.push_back(inode);
  count_inodes_++;
  return name_to_inode_.size() - 1;
}

/*关闭文件*/
int MyFileSystem::close(int filedes) {
  file_system_.close();
  return 0;
}

/*刷新文件系统*/
void MyFileSystem::fresh_my_filesystem() {
  // file_system_.close();
  file_system_.open(FILESYSTEM_PATH,
                    std::ios::in | std::ios::out | std::ios::binary);
  if (file_system_.is_open()) {
    //读超级块
    super_block_.deserialize(file_system_);

    //读名字与inode号映射表
    int mapsize =
        super_block_.get_block_count() - super_block_.get_free_block_count();
    std::array<char, 16> filename;
    name_to_inode_.clear();
    for (int i = 0; i < mapsize; ++i) {
      file_system_.read(filename.data(), sizeof(filename));
      name_to_inode_.push_back(filename);
    }
    //读inode表
    file_system_.seekg(static_cast<std::streamoff>(32 * 1024 * 1024),
                       std::ios::beg);
    // file_system_ >> count_inodes_;
    file_system_.read(reinterpret_cast<char*>(&count_inodes_),
                      sizeof(count_inodes_));
    MyInode inode;
    inodes_.clear();
    for (size_t i = 0; i < count_inodes_; ++i) {
      inode.deserialize(file_system_);
      inodes_.push_back(inode);
    }
    file_system_.close();
  } else {
    std::cerr << "文件系统打开失败！" << std::endl;
  }
}

/*回写文件系统*/
void MyFileSystem::write_my_filesystem() {
  file_system_.open(FILESYSTEM_PATH,
                    std::ios::out | std::ios::in | std::ios::binary);
  if (file_system_) {
    //回写超级块
    super_block_.serialize(file_system_);
    //回写名字与inode映射
    for (const auto& name : name_to_inode_) {
      file_system_.write(name.data(), sizeof(name));
    }
    //回写inode表
    file_system_.seekp(static_cast<std::streamoff>(32 * 1024 * 1024),
                       std::ios::beg);
    // file_system_ << count_inodes_;
    file_system_.write(reinterpret_cast<const char*>(&count_inodes_),
                       sizeof(count_inodes_));
    for (const auto& inode : inodes_) {
      inode.serialize(file_system_);
    }
    file_system_.close();
  } else {
    std::cerr << "回写文件系统时，文件系统打开失败" << std::endl;
  }
}