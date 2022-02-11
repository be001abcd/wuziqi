#ifndef _CREATE_CLIENT_HINCLUDED_
#define _CREATE_CLIENT_HINCLUDED_
#endif
#include<sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include<string.h>
extern long int create_client(const char * server_address, const char * nickname, const char * role , int nigiri_number);