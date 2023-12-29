#include "server.h"

#include <sys/types.h>

#include <cstring>
#include <ios>
#include <iterator>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

// 构造函数
Server::Server(int port, int length_of_queue_of_listen,
               const char *str_bound_ip)
    : port_(port), length_of_queue_of_listen_(length_of_queue_of_listen) {
  // 存绑定的ip
  if (str_bound_ip != NULL) {
    auto len = strlen(str_bound_ip) + 1;
    str_bound_ip_ = new char[len];
    strncpy((char *)str_bound_ip_, str_bound_ip, len);
  } else {
    str_bound_ip_ = NULL;
  }
}

// 析构函数
Server::~Server() {
  if (str_bound_ip_) {
    delete[] str_bound_ip_;
  }
}

void Server::Run() {
  // 创建服务器套接字
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == server_socket) {
    std::cerr << "无法创建套接字" << strerror(errno) << std::endl;
    exit(-1);
  }

  // 准备服务器地址
  sockaddr_in server_address;
  memset(&server_address, 0, sizeof(sockaddr_in));
  server_address.sin_family = AF_INET;
  //静态绑定IP，如果没有，则为本地IP
  if (NULL == str_bound_ip_) {
    server_address.sin_addr.s_addr = INADDR_ANY;
  } else {
    //如果有，则绑定
    if (inet_pton(AF_INET, str_bound_ip_, &server_address.sin_addr) != 1) {
      std::cout << "inet_pton error" << std::endl;
      close(server_socket);
      exit(-1);
    }
  }
  server_address.sin_port = htons(port_);

  // 绑定套接字
  if (bind(server_socket, (sockaddr *)&server_address, sizeof(server_address)) <
      0) {
    std::cerr << "绑定失败:" << strerror(errno) << std::endl;
    close(server_socket);
    exit(-1);
  }

  // 监听连接
  if (listen(server_socket, length_of_queue_of_listen_) < 0) {
    std::cerr << "监听失败" << strerror(errno) << std::endl;
    exit(-1);
  }

  while (1) {
    std::cout << "等待客户端连接..." << std::endl;
    // 接受客户端连接
    int client_socket;
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    client_socket = accept(server_socket, (struct sockaddr *)&clientAddress,
                           &clientAddressLength);
    if (client_socket < 0) {
      std::cerr << "接受连接失败：" << strerror(errno) << std::endl;
      exit(-1);
    }
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddress.sin_addr, ip_str, INET_ADDRSTRLEN);
    std::cout << "有客户端连接成功：" << ip_str << ":"
              << ntohs(clientAddress.sin_port) << std::endl;
    // int pid = fork();
    // // 子进程执行服务，主进程继续监听
    // if (pid == 0) {
    // 接收数据后提供的服务
    ServerFunction(client_socket);
    close(client_socket);
    // return;
    // }
  }
  close(server_socket);
}

// CenterServer
CenterServer::CenterServer(int port, int length_of_queue_of_listen,
                           const char *str_bound_ip)
    : Server(port, length_of_queue_of_listen, str_bound_ip) {}

void CenterServer::ServerFunction(int listen_socket) {
  const int buffer_size = 4 * 1024;
  char buf[buffer_size];
  std::string ask;
  while (1) {
    // 跟踪客户端的状态和任务执行情况
    std::cout << "正在跟踪客户端 " << listen_socket << " 的状态..."
              << std::endl;
    memset(buf, 0, buffer_size);
    ask = "状态";
    strncpy(buf, ask.c_str(), ask.length());
    send(listen_socket, buf, buffer_size, 0);
    // send(listen_socket, ask.c_str(), ask.length(), 0);

    // 获取客户端的状态
    memset(buf, 0, buffer_size);
    std::cout << "等待客户端状态..." << std::endl;
    recv(listen_socket, buf, buffer_size, 0);
    std::cout << "客户端 " << listen_socket << " 的状态为：" << buf
              << std::endl;
    std::string answer = buf;

    // 获取客户端的插件版本号
    memset(buf, 0, buffer_size);
    std::cout << "等待客户端插件版本..." << std::endl;
    recv(listen_socket, buf, buffer_size, 0);
    std::cout << "客户端 " << listen_socket << " 的插件版本为：" << buf
              << std::endl;
    std::string version = buf;

    // 检查插件版本
    std::ifstream fr;
    fr.open("server/config.txt", std::ios::in);
    if (fr) {
      std::string newest_version;
      fr >> newest_version;
      fr.close();
      if (newest_version != version) {
        ask = "模块更新";
        memset(buf, 0, buffer_size);
        strncpy(buf, ask.c_str(), ask.length());
        send(listen_socket, buf, buffer_size, 0);
        // send(listen_socket, ask.c_str(), ask.length(), 0);
        // 模块更新
        UpdateTestModule(listen_socket);
      }
    } else {
      std::cerr << "open config.txt error!" << std::endl;
      return;
    }

    if (answer == std::string("请求任务")) {
      ask = "下发任务";
      // send(listen_socket, ask.c_str(), ask.length(), 0);
      memset(buf, 0, buffer_size);
      strncpy(buf, ask.c_str(), ask.length());
      send(listen_socket, buf, buffer_size, 0);
      // 下发任务
      SendTestTask(listen_socket);
    } else if (answer == std::string("完成")) {
      // 获取结果
      ask = "回收";
      std::cout << "正在回收结果..." << std::endl;
      send(listen_socket, ask.c_str(), ask.length(), 0);
      memset(buf, 0, buffer_size);
      recv(listen_socket, buf, buffer_size, 0);
      int result_num = atoi(buf);
      std::cout << "收到任务结果数量：" << result_num << std::endl;
      bool result_buf[1000000];
      recv(listen_socket, result_buf, result_num, 0);
      for (int i = 0; i < result_num; ++i) {
        std::cout << "客户端 " << listen_socket << " 的任务 " << i + 1
                  << " 的结果为" << (result_buf[i] ? "成功" : "失败")
                  << std::endl;
      }

      // 让该客户端迁移任务
      ask = "任务迁移";
      send(listen_socket, ask.c_str(), buffer_size, 0);

    } else if (answer == std::string("正在执行任务")) {
      // 执行情况
      recv(listen_socket, buf, buffer_size, 0);
      std::string finished(buf);
      recv(listen_socket, buf, buffer_size, 0);
      std::string sum(buf);
      std::cout << "客户端" << listen_socket << "执行了 " << finished << " / "
                << sum << std::endl;
    }
    // 一分钟后再查询状态
    sleep(10);
  }
}

// 下发任务
void CenterServer::SendTestTask(const int &listen_socket) {
  std::ifstream fr;
  fr.open("server/config.txt", std::ios::in);
  if (fr) {
    std::string path;
    std::string no_use;
    // 过滤版本号
    getline(fr, no_use);
    // 过滤插件路径
    getline(fr, no_use);
    // 读取任务文件的路径
    getline(fr, path);
    fr.close();
    fr.open(path, std::ios::in);
    if (fr) {
      std::string mission((std::istreambuf_iterator<char>(fr)),
                          std::istreambuf_iterator<char>());
      rapidjson::Document doc;
      doc.Parse(mission.c_str());
      if (!doc.IsArray()) {
        std::cerr << "Error: Invalid JSON format. Expected an array."
                  << std::endl;
        return;
      }
      // 传递任务总数
      int size = doc.Size();
      std::string string_size = std::to_string(size);
      const int buffer_size = 4 * 1024;
      char buf[buffer_size];
      memset(buf, 0, buffer_size);
      strncpy(buf, string_size.c_str(), string_size.length());
      send(listen_socket, buf, buffer_size, 0);

      // 分发每个任务
      for (int i = 0; i < size; ++i) {
        const rapidjson::Value &obj = doc[i];
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        obj.Accept(writer);
        memset(buf, 0, buffer_size);
        strncpy(buf, buffer.GetString(), buffer.GetLength());
        send(listen_socket, buf, buffer_size, 0);
      }

      fr.close();
    } else {
      std::cerr << "open mission.json error!" << std::endl;
    }
  } else {
    std::cerr << "open config.txt error!" << std::endl;
  }
}

// 更新测试模块
void CenterServer::UpdateTestModule(const int &listen_socket) {
  // config.txt文件中配置插件的路径
  std::ifstream fr("server/config.txt", std::ios::in);
  if (fr) {
    // 测试模块的版本号
    std::string module_version;
    fr >> module_version;
    // 测试模块路径
    std::string module_path;
    fr >> module_path;

    fr.close();
    // 打开插件文件
    fr.open(module_path, std::ios::in | std::ios::binary);
    if (fr) {
      // 传输插件的版本号
      const int buffer_size = 4 * 1024;
      char buf[buffer_size];
      memset(buf, 0, buffer_size);
      strncpy(buf, module_version.c_str(), module_version.length());
      send(listen_socket, buf, buffer_size, 0);

      // 传输插件文件
      while (!fr.eof()) {
        memset(buf, 0, buffer_size);
        fr.read(buf, buffer_size);
        std::streamsize bytesRead = fr.gcount();
        if (!bytesRead) {
          // 读完了
          break;
        }
        // 先传一下尺寸
        send(listen_socket, std::to_string(bytesRead).c_str(), buffer_size, 0);
        // 传文件
        send(listen_socket, buf, bytesRead, 0);
      }
      // 文件传完了
      memset(buf, 0, buffer_size);
      send(listen_socket, buf, buffer_size, 0);
      std::cout << "服务器已发送完插件" << std::endl;
      fr.close();
    } else {
      std::cerr << "open module file error!" << std::endl;
    }

  } else {
    std::cerr << "open module config file error!" << std::endl;
  }
}