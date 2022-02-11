#ifndef _CREAT_SERVER_HINCLUDED_
#define _CREAT_SERVER_HINCLUDED_
#endif
#include<sys/types.h>
#include<sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "pthread.h"
extern long int create_server();