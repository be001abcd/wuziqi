#include "create_client.h"
char * message = "okokok";
int lenth = 0;
long int create_client(const char * server_address, const char * nickname, const char * role , int nigiri_number){
    /*creat a socket*/
    int sockfd = socket(AF_UNIX,SOCK_STREAM,0);
//socket创建socket描述符，是唯一标识一个socket，是后续操作参数，其中的参数AF_UNIX是协议域、SOCK_STREAM是socket类型、0就是指定协议的位置，为0的时候自动选默认的
   if(sockfd == 0)
   {
   	printf("error , do  not create a socket! \n");
   }
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path,"/home/wyh/wzq111/server/cmake-build-debug/gobang-server.socket");

    /*connect to the server*/
    int result = connect(sockfd,(struct sockaddr*)&address,sizeof(address));
    //connect函数也是一个有返回值的函数，当返回值为-1则连接失败，，三个参数分别是客户端fd、socket地址、地址长度
    if(result==-1)
    {
        perror("connect failed:");
        exit(1);
    }

    /*exchange data*/
    //具体的读写操作在这里进行
  /* nickname = (char *)malloc(10);
   server_address = (char *)malloc(30);
   role = (char *)malloc(10);*/

   lenth = strlen(nickname);
    write(sockfd,&lenth,4);
    write(sockfd,nickname,lenth);


    lenth = strlen(server_address);
    write(sockfd,&lenth,4);
    write(sockfd,server_address,lenth);

    lenth = strlen(role);
    write(sockfd,&lenth,4);
    write(sockfd,role,lenth);

    lenth = 4;
    write(sockfd,&lenth,4);
    write(sockfd,&nigiri_number,lenth);


    lenth = strlen(message);
    write(sockfd,&lenth,4);
    write(sockfd,message,lenth);
    lenth = NULL;




    /*close the socket*/
    close(sockfd);

    return 0;
}
