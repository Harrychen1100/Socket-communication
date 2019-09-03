#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#define SRVPORT 25318
#define CONNECT_NUM 5
#define MAX_NUM 1024
int main()
{
    int clientSock=-1;
    struct sockaddr_in serverAddr;

    clientSock=socket(AF_INET,SOCK_STREAM,0);
    if(clientSock<0)
    {
        printf("socket creation failed\n");
        exit(-1);
    }
    //printf("socket create successfully.\n");

    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons((u_short) SRVPORT);
    serverAddr.sin_addr.s_addr=htons(INADDR_ANY);
    if(connect(clientSock,&serverAddr,sizeof(struct sockaddr_in))<0)
    {
        printf("Connect error.\n");
        exit(-1);
    }
    printf("The client is up and running.\n");

    char sedBuf[MAX_NUM]={0};
    char revBuf[MAX_NUM]={0};
    char* delim=" ";
    char* Result=NULL;
    char* Type=NULL;
    char* Number=NULL;
    while(gets(sedBuf)!=-1)
    {
        if(write(clientSock,sedBuf,strlen(sedBuf))==-1)
        {
            printf("send error!\n");
        }

	Result=strtok(sedBuf,delim);
	Type=Result;
	//printf("Type:%s\n",Type);
	while(Result != NULL)
	{
 		//printf("Result:%s\n",Result);
		Result=strtok(NULL, delim);
		if(Result != NULL)
		{ 
			Number = Result;
			//printf("Number:%s\n",Number);
		}

	 }
        printf("The client sent <%s> and <%s> to AWS\n",Number,Type);
	
        
        if(read(clientSock,revBuf,MAX_NUM)==-1)
        {
            printf("rev error!\n");
        }
        printf("According to AWS <%s> on <%s>: <%s>\n",Type,Number,revBuf);
        if(strcmp(revBuf,"Goodbye,my dear client!")==0)
            break;
	bzero(sedBuf,sizeof(sedBuf));
        bzero(revBuf,sizeof(revBuf));
    }
    close(clientSock);
    return 0;
}
