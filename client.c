#include"create_client.h"
char * nickname = NULL;
char * server_address = NULL;
char * role = NULL;

int ch;
int main(int argc,char* argv[]) {
    while ((ch = getopt(argc, argv, "hn:s:bw")) != -1) {
        switch (ch) {
            case 'h':
                printf("hellogobang [option]...\n");
                printf("-n\tplayer's name.\n");
                printf("-s\tserver_address.\n");
                printf("-b|-w\tblack or white.\n");
                printf("-h\tThis information.\n");
                break;
            case 'n':
                nickname = optarg;
                break;
            case 's':
                server_address = optarg;
                break;
            case 'b':
                role = "black";
                break;
            case 'w':
                role = "white";
                break;
        }
    }
    if (optind == 2) {
        return 0;
    } else if ((server_address && nickname && role) == 0) {
        printf("You must have name server address and player. \n");
        return 0;
    }
	srand((unsigned)time(NULL));
	long int client_id =  create_client(server_address,nickname,role , rand()%100);
    printf("client_id = %ld",client_id);
 
}