#include "MyShell.h"
MyShell::MyShell() {
  init();
  help();
}
void MyShell::work() {
  std::string cmd;
  std::string option;
  std::string path_name;
  while (getline(std::cin, cmd)) {
    std::istringstream line(cmd);
    line >> option;
    if (option == std::string("read")) {
      line >> path_name;
      std::string dst_name;
      line >> dst_name;
      read_from_myfilesystem(path_name, dst_name);
    } else if (option == std::string("write")) {
      std::string src_name;
      line >> src_name;
      line >> path_name;
      write_to_myfilesystem(src_name, path_name);
    } else if (option == std::string("help")) {
      help();
    } else if (option == std::string("rm")) {
      line >> path_name;
      rm(path_name.c_str());
    } else if (option == std::string("format")) {
      format();
    } else if (option == std::string("exit")) {
      break;
    } else if (option == std::string("ls")) {
      std::string l;
      line >> l;
      if (l == std::string("-l")) {
        ls(1);
      } else {
        ls(0);
      }

    } else {
      std::cerr << "暂不支持该命令" << std::endl;
    }
  }
}

void MyShell::init() {
  op.clear();
  op["help"] = "帮助 eg:help";
  op["write"] = "写文件 eg:write src dst";
  op["read"] = "读文件 eg:read src dst";
  op["ls"] = "显式文件列表 eg:ls";
  op["rm"] = "删除文件 eg:rm filename";
  op["format"] = "格式化文件系统 eg:format";
}

/*帮助*/
void MyShell::help() {
  for (auto oneop : op) {
    std::cout << setiosflags(std::ios::left) << std::setw(15) << oneop.first
              << oneop.second << std::endl;
  }
}
/*删除*/
void MyShell::rm(const char *pathname) { file_system_.remove(pathname); }
/*读取*/
void MyShell::read_from_myfilesystem(std::string &pathname,
                                     std::string &dstname) {
  std::ofstream fw;
  fw.open(dstname, std::ios::out | std::ios::binary);
  if (fw) {
    int fd = file_system_.open(pathname.c_str(), std::ios::in);
    if (fd != -1) {
      std::array<char, 64 * 1024 * 1024> *buf =
          new std::array<char, 64 * 1024 * 1024>;
      int read_count = 0;
      while ((read_count =
                  file_system_.read(fd, buf->data(), 64 * 1024 * 1024)) > 0) {
        fw.write(buf->data(), read_count);
      }
      delete buf;
      file_system_.close(fd);
      fw.close();
#ifndef NDEBUG
      std::cout << "读完了" << std::endl;
#endif
    } else {
      std::cerr << pathname << "文件打开失败！" << std::endl;
    }
  } else {
    std::cerr << dstname << "文件打开失败！" << std::endl;
  }
}
/*写入*/
void MyShell::write_to_myfilesystem(std::string &srcname,
                                    std::string &pathname) {
  std::ifstream fr;
  fr.open(srcname, std::ios::in);
  if (fr) {
    int fd = file_system_.open(pathname.c_str(),
                               std::ios::in | std::ios::out | std::ios::binary);
    if (fd != -1) {
      std::array<char, 64 * 1024 * 1024> *buf =
          new std::array<char, 64 * 1024 * 1024>;
      while (!fr.eof()) {
        fr.read(buf->data(), 64 * 1024 * 1024);
        file_system_.write(fd, buf->data(), fr.gcount());
      }
      delete buf;
      file_system_.close(fd);
      fr.close();
#ifndef NDEBUG
      std::cout << "写完了" << std::endl;
#endif
    } else {
      std::cerr << pathname << "文件打开失败！" << std::endl;
    }
  } else {
    std::cerr << srcname << "文件打开失败！" << std::endl;
  }
}
/*查看文件列表*/
void MyShell::ls(int type) { file_system_.list_show(type); }
/*格式化文件系统*/
void MyShell::format() { file_system_.format(); }