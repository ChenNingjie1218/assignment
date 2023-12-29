#include "client.h"

#include <cstddef>
#include <fstream>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
// 构造函数
Client::Client(int serverport, const char* str_server_ip)
    : serverport_(serverport) {
  //存服务器的ip
  if (str_server_ip) {
    auto len = strlen(str_server_ip) + 1;
    str_server_ip_ = new char[len];
    strncpy((char*)str_server_ip_, str_server_ip, len);
  } else {
    str_server_ip_ = NULL;
  }
}

// 析构函数
Client::~Client() {
  if (str_server_ip_) {
    delete[] str_server_ip_;
  }
}

void Client::Run() {
  // 创建客户端套接字
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == client_socket) {
    std::cerr << "无法创建套接字" << strerror(errno) << std::endl;
    exit(-1);
  }

  // 准备服务器地址
  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  if (inet_pton(AF_INET, str_server_ip_, &server_address.sin_addr) != 1) {
    std::cout << "inet_pton error" << std::endl;
    close(client_socket);
    exit(-1);
  }
  server_address.sin_port = htons(serverport_);

  //连接到服务器
  if (connect(client_socket, (sockaddr*)&server_address,
              sizeof(server_address)) == -1) {
    std::cout << "连接失败：" << strerror(errno) << std::endl;
    close(client_socket);
    exit(-1);
  }

  std::cout << "连接服务器成功" << std::endl;

  ClientFunction(client_socket);
  //关闭socket
  close(client_socket);
}

// TestClient

TestClient::TestClient(int serverport, const char* str_server_ip)
    : Client(serverport, str_server_ip) {}

void TestClient::ClientFunction(int connected_socket) {
  const int buffer_size = 4 * 1024;
  char buf[buffer_size];
  std::vector<Task> tasks;  // 存下发的任务

  // Status my_status("请求任务", "v1.0");

  // 创建共享内存
  // key_t key = ftok("shared_memory_key", 1234);                // 生成唯一key
  int shmid = shmget(1234, sizeof(Status), 0666 | IPC_CREAT);  // 创建共享内存段
  if (shmid == -1) {
    // 处理共享内存创建/获取失败的情况
    std::cerr << "共享内存创建/获取失败" << std::endl;
    return;
  }
  Status* sharedStatus =
      static_cast<Status*>(shmat(shmid, nullptr, 0));  //连接到共享内存
  if (sharedStatus == reinterpret_cast<Status*>(-1)) {
    std::cerr << "共享内存链接失败" << std::endl;
  }
  strcpy(sharedStatus->status_, "请求任务");
  strcpy(sharedStatus->version_, "没有插件");
  while (1) {
    // 接收服务器指令
    memset(buf, 0, buffer_size);
    recv(connected_socket, buf, buffer_size, 0);
    std::cout << "客户端收到指令：" << buf << std::endl;
    std::string ask = buf;
    std::string answer;
    if (ask == std::string("状态")) {
      // 获取自身状态
      std::cout << "客户端发送自身状态..." << std::endl;
      // 发送状态
      memset(buf, 0, buffer_size);
      strncpy(buf, sharedStatus->status_, strlen(sharedStatus->status_));
      std::cout << "客户端的当前状态为：" << buf << std::endl;
      send(connected_socket, buf, buffer_size, 0);

      // 发送版本号
      memset(buf, 0, buffer_size);
      strncpy(buf, sharedStatus->version_, strlen(sharedStatus->version_));
      std::cout << "客户端的当前版本号为：" << buf << std::endl;
      send(connected_socket, buf, buffer_size, 0);
      std::string status = sharedStatus->status_;
      if (status == std::string("正在执行任务")) {
        // 发送执行情况
        memset(buf, 0, buffer_size);
        strncpy(buf, std::to_string(sharedStatus->finished_).c_str(),
                std::to_string(sharedStatus->finished_).length());
        send(connected_socket, buf, buffer_size, 0);
        memset(buf, 0, buffer_size);
        strncpy(buf, std::to_string(sharedStatus->sum_).c_str(),
                std::to_string(sharedStatus->sum_).length());
        send(connected_socket, buf, buffer_size, 0);
      }
    } else if (ask == std::string("下发任务")) {
      // 请求下发任务
      std::cout << "客户端接收任务" << std::endl;
      RecvTestTask(connected_socket, sharedStatus, tasks);

      // fork一个进程去执行任务
      strcpy(sharedStatus->status_, "正在执行任务");
      std::cout << "客户端执行任务" << std::endl;
      pid_t pid = fork();
      if (pid == -1) {
        std::cerr << "创建子进程失败！" << std::endl;
        return;
      } else if (pid == 0) {
        ExecuteTasks(sharedStatus, tasks);
      }

    } else if (ask == std::string("模块更新")) {
      std::cout << "客户端更新测试模块..." << std::endl;
      // 请求更新测试模块
      UpdateTestModule(connected_socket, sharedStatus);

    } else if (ask == std::string("任务迁移")) {
      std::cout << "客户端任务迁移..." << std::endl;
      SerializeTasks(tasks);
      break;
    } else if (ask == std::string("回收")) {
      std::cout << "客户端提交测试结果..." << std::endl;
      send(connected_socket, std::to_string(sharedStatus->sum_).c_str(),
           std::to_string(sharedStatus->sum_).length(), 0);
      send(connected_socket, sharedStatus->result, sharedStatus->sum_, 0);

      // 请求下一轮任务
      // strcpy(sharedStatus->status_, "请求任务");
    }
  }
  // 分离共享内存和删除共享内存段
  shmdt(sharedStatus);
  shmctl(shmid, IPC_RMID, nullptr);
}

// 下发任务
void TestClient::RecvTestTask(const int& listen_socket, Status* sharedStatus,
                              std::vector<Task>& tasks) {
  const int buffer_size = 4 * 1024;
  char buf[buffer_size];
  // 任务总数
  recv(listen_socket, buf, buffer_size, 0);
  sharedStatus->sum_ = atoi(buf);
  std::cout << "客户端收到任务总数：" << sharedStatus->sum_ << std::endl;
  tasks.clear();
  for (int i = 0; i < sharedStatus->sum_; ++i) {
    recv(listen_socket, buf, buffer_size, 0);

    // json格式读取
    rapidjson::Document doc;
    doc.Parse(buf);
    if (doc.HasParseError() || !doc.IsObject()) {
      std::cerr << "Failed to parse JSON object at line " << std::endl;
      return;
    }
    Task task(doc["a"].GetInt(), doc["b"].GetInt(), doc["expect"].GetInt());
    // 存任务
    tasks.push_back(task);
    std::cout << "第 " << i + 1 << " 个任务：" << buf << std::endl;
  }
}

// 执行任务
void TestClient::ExecuteTasks(Status* sharedStatus, std::vector<Task>& tasks) {
  std::ifstream fr;
  fr.open("client/config.txt", std::ios::in);
  if (fr) {
    std::string path;
    fr >> path;
    // 打开动态链接库
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (NULL == handle) {
      std::cout << "dlopen error" << std::endl;
      return;
    }

    // 映射动态库中的函数
    using Fun = Module* (*)();
    Fun create_obj = (Fun)dlsym(handle, "CreateObj");
    if (NULL == create_obj) {
      std::cout << "create_obj error" << std::endl;
      char* str = dlerror();
      std::cout << str << std::endl;
      return;
    }
    Module* obj = create_obj();
    int task_size = tasks.size();
    for (int i = 0; i < task_size; ++i) {
      // 使用动态库中的函数
      bool result = obj->Work(tasks[i]);
      sharedStatus->finished_ = i;
      sharedStatus->result[i] = result;
      sleep(5);
    }
    //别忘了释放动态内存
    delete obj;
    // 卸载动态链接库
    dlclose(handle);

    fr.close();
    strcpy(sharedStatus->status_, "完成");
    exit(0);
  } else {
    std::cerr << "open config.txt error!" << std::endl;
  }
}

// 更新测试模块
void TestClient::UpdateTestModule(const int& listen_socket,
                                  Status* sharedStatus) {
  // 读取插件路径
  std::ifstream fr;
  fr.open("client/config.txt", std::ios::in);
  if (fr) {
    std::string module_path;
    fr >> module_path;
    fr.close();
    std::ofstream fw;
    fw.open(module_path, std::ios::out | std::ios::binary);
    if (fw) {
      // 记录新的版本号
      std::string version;
      const int buffer_size = 4 * 1024;
      char buf[buffer_size];
      recv(listen_socket, buf, buffer_size, 0);
      version = buf;
      // 新的版本号
      std::cout << "获取到插件最新的版本号为：" << version << std::endl;

      while (1) {
        memset(buf, 0, buffer_size);
        recv(listen_socket, buf, buffer_size, 0);
        // std::cout << "客户端收到size：" << buf << std::endl;
        auto size = atoi(buf);
        if (size) {
          memset(buf, 0, buffer_size);
          recv(listen_socket, buf, size, 0);
          fw.write(buf, size);
        } else {
          break;
        }
      }
      fw.close();

      // 更新新的版本号状态
      std::cout << "已更新完当前插件，版本号为：" << version << std::endl;
      strcpy(sharedStatus->version_, version.c_str());
    } else {
      std::cerr << "open module file error!" << std::endl;
    }
  } else {
    std::cerr << "open config.txt error!" << std::endl;
  }
}

// 序列化任务
void TestClient::SerializeTasks(std::vector<Task>& tasks) {
  // 任务迁移
  std::ifstream fr;
  // 配置路径
  fr.open("client/serialize_config.txt", std::ios::in);
  if (fr) {
    std::string path;
    fr >> path;
    std::ofstream fw;
    fw.open(path, std::ios::out);
    if (fw) {
      int task_size = tasks.size();
      for (int i = 0; i < task_size; ++i) {
        // 任务转json存下来
        std::string new_json_str;
        rapidjson::Document doc;
        doc.SetObject();
        doc.AddMember("a", tasks[i].num1_, doc.GetAllocator());
        doc.AddMember("b", tasks[i].num2_, doc.GetAllocator());
        doc.AddMember("expect", tasks[i].expect_, doc.GetAllocator());
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        new_json_str = buffer.GetString();
        fw << new_json_str << std::endl;
      }
      fw.close();
    } else {
      std::cerr << "open serialize file error!" << std::endl;
    }
  } else {
    std::cerr << "open serialize_config.txt error!" << std::endl;
  }
}