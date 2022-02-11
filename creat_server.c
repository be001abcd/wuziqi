
#include"creat_server.h"

struct Info{
	const char  *nickname ;
	const char  *server_address;
	const char  *role ;
	int nigiri_number ;
}info;

const char  *nickname = NULL;
const char  *server_address = NULL;
const char  *role = NULL;
int nigiri_number = 0;

const char  *message = NULL;
const char  *msg = NULL;



void thread(int client_sockfd,const char  *message){
        int lenth;
        long int address = (long) &info;
        while(1){
        read(client_sockfd,&lenth,4);
        message = (char *) malloc(lenth);
        read(client_sockfd, message, lenth);
        sleep(5);
        if (message != NULL) {
            printf("from <%ld> message = %s \n", address, message);
            free(lenth);
            free(message);
        } else {
            printf("no message!\n");
            exit(1);
        }}
        /*while(1)
        {
            read(client_sockfd,&lenth,4);
            msg = (char *) malloc(lenth);
            read(client_sockfd, msg, lenth);

            if (msg != NULL) {
                printf("from <%ld> message = %s \n", address, msg);
            } else {
                printf("no message!\n");
                exit(1);
        }*/

};

void get_thread(client_sockfd){
        thread(client_sockfd,message);
};

long int create_server() {
	int client_sockfd = 0;
	//初始化客户端fd

    int nigiri_number = 0;


    //初始化5个变量、昵称、链接地址、选择执棋、系统信息
	
  	/*delete the socket file*/
    	unlink("gobang-server.socket");
	//删除原先的socket文件
    
    	int server_sockfd = socket(AF_UNIX,SOCK_STREAM,0);

	//创建sockfd函数，返回类型为int，是一个描述符，创建唯一标识的sockfd
	//函数原型int  socket(int protofamily, int type, int protocol);//返回sockfd
	//AF_UNIX:protofamily中的一员，代表着协议域，又称为协议族（family）。常用的协议族有，AF_INET(IPV4)、AF_INET6(IPV6)、AF_LOCAL（或称AF_UNIX，Unix域socket）、AF_ROUTE
    	//SOCK_STREAM:指定socket类型。常用的socket类型有，SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET
    	//server_sockfd =0:指定协议。常用的协议有，IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等，它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议，如果等于零则选择默认协议
	if(server_sockfd == 0 )
	{
		printf("socket 创建失败！\n");
	}else{
		printf("gobang server v1.1\n");
	}

	/*create a socket*/
 	 struct sockaddr_un server_addr;

	//UNIX域下的结构体，一个const struct sockaddr *指针，指向要绑定给sockfd的协议地址。这个地址结构根据地址创建socket时的地址协议族的不同而不同，如unix对应的是：
	 #if 0
	struct sockaddr_un { 
  	 sa_family_t sun_family;               /* AF_UNIX */ 
    	char        sun_path[UNIX_PATH_MAX];  /* pathname */ 
	};
	#endif

   	 server_addr.sun_family = AF_UNIX;
	//绑定linux系统
	
   	 strcpy(server_addr.sun_path,"gobang-server.socket");
	
	//gobang-server.socket是具体的通信所用到的socket文件，如果传输成功，打印出来create server
	if(server_addr.sun_path != NULL)
	{
	 printf("create server\n");
	}else{
	printf("error file create!\n");
	}	
    	/*bind with the local file*/
	struct sockaddr_un client_addr;
	//bind函数要用到的地址结构体

    	socklen_t len= sizeof(client_addr);
	//地址长度socklen_t len
	//通常服务器在启动的时候都会绑定一个众所周知的地址（如ip地址+端口号），用于提供服务，客户就可以通过它来接连服务器,unix
	//unix要给一个绝对路径名提供给socket
	//这就是bind（绑定）的作用，这个函数是一个有返回值的函数，

  	int bind_ = bind(server_sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	//通常返回值为0，代表随机搜索可以使用的端口号,参数是server端的sockfd、地址族、地址长度

	if(bind_ != 0)
	{
		printf("bind error\n");
		exit(0);
	}

	    /*listen*/
	//listen函数在一般在调用bind之后-调用accept之前调用，它的函数返回值是：返回：0──成功， -1──失败
	//参数是server的sockfd和最大监听数
	int listen_ = listen(server_sockfd,5);
	if(listen_ != 0)
	{
		printf("listen error!\n");
		exit(0);
	}else{
		printf("server waiting\n");
	}
  
	//一个持续进行读操作的一个while循环，循环中有一个判断，如果nickname和server_adress和role都不为空则退出循环
	//把三个值写到结构体里面，然后create_server函数返回的是结构体首地址的一个long int值
     	while(1)
  	{
        	/*accept a connection*/
        	client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_addr,&len);
        if (client_sockfd == 0) {
            printf("accept error!\n");
        } else {
            struct Info info = {NULL,NULL,NULL};
            long int address = (long) &info;
            int lenth;
            read(client_sockfd,&lenth,4);
            nickname = (char *) malloc(lenth);
            read(client_sockfd, nickname, lenth);
            info.nickname = nickname;

            if (nickname != NULL) {
                printf("from <%ld> nickname = %s \n", address, info.nickname);
            } else {
                printf("no nickname!\n");
                exit(1);
            }

            read(client_sockfd,&lenth,4);
            server_address = (char *) malloc(lenth);
            read(client_sockfd, server_address, lenth);
            info.server_address = server_address;

            if (server_address != NULL) {
                printf("from <%ld> server_address = %s \n", address, info.server_address);
            } else {
                printf("no server_address!\n");
                exit(1);
            }

            read(client_sockfd,&lenth,4);
            role = (char *) malloc(lenth);
            read(client_sockfd, role, lenth);
            info.role = role;

            if (role != NULL) {
                printf("from <%ld> role = %s \n", address, info.role);
            } else {
                printf("no role!\n");
                exit(1);
            }

            read(client_sockfd,&lenth,4);
            nigiri_number = (char *) malloc(lenth);
            read(client_sockfd, &nigiri_number, lenth);
            info.nigiri_number = nigiri_number;

            if (nigiri_number != 0) {
                printf("from <%ld> nigiri_number = %d \n", address, info.nigiri_number);
            } else {
                printf("no nigiri_number!\n");
                exit(1);
            }
        }
	//accept函数首先会阻塞等待客户端连接，然后连接成功后会产生一个新的套接字和客户端通信，所以返回值就是client_sockfd
	//在这里开一个新的线程，专门来进行读操作，读写操作要先传递一个长度，然后根据具体的长度进行开辟空间操作
        pthread_t tid;
        int ptid = pthread_create(&tid,NULL,get_thread,client_sockfd);

        if (ptid == 0)
        {
            printf("pthread is ok\n");
        }else{
            printf("pthread is error!\n");
            break;
        }


        	}

   	 }
   




