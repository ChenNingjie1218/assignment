#include <csignal>

#include "client.h"
void signalHandler(int signum) {
  if (signum == SIGINT) {
    exit(0);
  }
}
int main(int argc, char **argv) {
  signal(SIGINT, signalHandler);
  TestClient Testclient(5000, "127.0.0.1");
  Testclient.Run();
  return 0;
}