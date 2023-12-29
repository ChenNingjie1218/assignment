#include <csignal>

#include "server.h"

void signalHandler(int signum) {
  if (signum == SIGINT) {
    exit(0);
  }
}

int main() {
  signal(SIGINT, signalHandler);
  CenterServer centerserver(5000);
  centerserver.Run();
  return 0;
}