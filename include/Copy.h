#ifndef COPY_H
#define COPY_H
#include <unistd.h>

#include <cstdint>
#include <iostream>
#include <thread>
#include <vector>

#include "MyPipe.h"
#include "Reader.h"
#include "Writer.h"

void Work(int num_thread);

#endif