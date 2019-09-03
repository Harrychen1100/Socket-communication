#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#define TCPSRVPORT 25318

#define UDPSRVPORTA 21318
#define UDPSRVPORTB 22318
#define UDPSRVPORTC 23318
#define UDPSRVPORT  24318

#define CONNECT_NUM 5
#define MAX_NUM 80
int main()
{
    int serverSock=-1,clientSock=-1;
    struct sockaddr_in serverAddr;

    serverSock=socket(AF_INET,SOCK_STREAM,0);
    if(serverSock<0)
    {
        printf("socket creation failed\n");
        exit(-1);
    }
    //printf("socket create successfully.\n");

    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons((u_short) TCPSRVPORT);
    serverAddr.sin_addr.s_addr=htons(INADDR_ANY);
    if(bind(serverSock,&serverAddr,sizeof(struct sockaddr_in))==-1)
    {
        printf("Bind error.\n");
        exit(-1);
    }
    //printf("Bind successful.\n");

    if(listen(serverSock,10)==-1)
    {
        printf("Listen error!\n");
    }
    printf("The AWS is up and running!\n");

    char revBuf[MAX_NUM]={0};
    char sedBuf[MAX_NUM]={0};
    char* delim=" ";
    char* Result=NULL;
    char* Type=NULL;
    char* Number=NULL;
    float result,result1,result2,result3,result4,result5,result6;
    while(1)
    {
        clientSock=accept(serverSock,NULL,NULL);
	
        while(1)
        {
            if(read(clientSock,revBuf,MAX_NUM)==-1)
            {
                printf("read error.\n");
            }
            else
            {
		 Result=strtok(revBuf,delim);
		 Type=Result;
		 //printf("Type:%s\n",Type);
		 while(Result != NULL)
		 {
		 	printf("Result:%s\n",Result);
			Result=strtok(NULL, delim);
			if(Result != NULL)
			{ 
				Number = Result;
				//printf("Number:%s\n",Number);
			}
   
		 }
            }
	    printf("The AWS received <%s> and function=<%s> from the client using TCP over port <%d>\n",Number,Type,TCPSRVPORT);
	    result1=atof(Number);
	    //aws->serverA
	    int fd=socket(AF_INET,SOCK_DGRAM,0);
	    if(fd==-1)
	    {
		 perror("socket create error!\n");
	 	 exit(-1);
	    }
	    printf("socket fd=%d\n",fd);
	    struct sockaddr_in addr_to_A,addr_to_B,addr_to_C;
	    addr_to_A.sin_family=AF_INET;
            addr_to_A.sin_port=htons(UDPSRVPORTA);
            addr_to_A.sin_addr.s_addr=inet_addr("127.0.0.1");
		
	    addr_to_B.sin_family=AF_INET;
            addr_to_B.sin_port=htons(UDPSRVPORTB);
            addr_to_B.sin_addr.s_addr=inet_addr("127.0.0.1");

	    addr_to_C.sin_family=AF_INET;
            addr_to_C.sin_port=htons(UDPSRVPORTC);
            addr_to_C.sin_addr.s_addr=inet_addr("127.0.0.1");


	    struct sockaddr_in addr_aws;
	    addr_aws.sin_family=AF_INET;
	    addr_aws.sin_port=htons(UDPSRVPORT);
	    addr_aws.sin_addr.s_addr=htons(INADDR_ANY);

	    struct sockaddr_in servera_1,serverb_1,serverc_1;
	    socklen_t servera_1length,serverb_1length,serverc_1length;
	    servera_1length=sizeof(servera_1);
	    serverb_1length=sizeof(serverb_1);
	    serverc_1length=sizeof(serverc_1);

	    int r;
	    r=bind(fd,(struct sockaddr*)&addr_aws,sizeof(addr_aws));
            if(r==-1)
	    {
	 	printf("Bind error!\n");
	 	close(fd);
	 	exit(-1);
	    }
	    //printf("Bind successfully.\n");
	    char udprecbuf1[1024];
	    //char udprecbuf2[1024];
            //char udprecbuf3[1024];
	    char udpsedbuf1[1024];
	    char udpsedbuf2[1024];
            strcpy(udpsedbuf1,Number);

	    if(sendto(fd,udpsedbuf1,sizeof(udpsedbuf1),0,(struct sockaddr*)&addr_to_A,sizeof(addr_to_A))==-1)
	    {
		printf("AWS send to server A\n");
            }	
	    else printf("The AWS sent <%s> to Backend-Server A\n",udpsedbuf1);
	    r=recvfrom(fd,udprecbuf1,sizeof(udprecbuf1),0,(struct sockaddr*)&servera_1,&servera_1length);//get X^2
	    printf("The AWS received <%s> Backend-Server A using UDP over port %d\n",udprecbuf1,UDPSRVPORTA);
	    result2=atof(udprecbuf1);
 	    strcpy(udpsedbuf2,udprecbuf1);
	    bzero(udprecbuf1,sizeof(udprecbuf1));

	    if(sendto(fd,udpsedbuf1,sizeof(udpsedbuf1),0,(struct sockaddr*)&addr_to_B,sizeof(addr_to_B))==-1)
	    {
		printf("AWS send to server B\n");
            }
	    else printf("The AWS sent <%s> to Backend-Server B\n",udpsedbuf1);
	    r=recvfrom(fd,udprecbuf1,sizeof(udprecbuf1),0,(struct sockaddr*)&serverb_1,&serverb_1length);//get X^3
	    printf("The AWS received <%s> Backend-Server B using UDP over port %d\n",udprecbuf1,UDPSRVPORTB);
	    result3=atof(udprecbuf1);
	    bzero(udprecbuf1,sizeof(udprecbuf1));

	    if(sendto(fd,udpsedbuf1,sizeof(udpsedbuf1),0,(struct sockaddr*)&addr_to_C,sizeof(addr_to_C))==-1)
	    {
		printf("AWS send to server C error\n");
            }
	    else printf("The AWS sent <%s> to Backend-Server C\n",udpsedbuf1);
	    r=recvfrom(fd,udprecbuf1,sizeof(udprecbuf1),0,(struct sockaddr*)&serverc_1,&serverc_1length);//get X^5
	    printf("The AWS received <%s> Backend-Server B using UDP over port %d\n",udprecbuf1,UDPSRVPORTC);	  
	    result5=atof(udprecbuf1);	    
	    bzero(udprecbuf1,sizeof(udprecbuf1));
            //bzero(udprecbuf2,sizeof(udprecbuf2));
	    //bzero(udprecbuf3,sizeof(udprecbuf3));
	    //To get X^4 and X^6 
	    
	    if(sendto(fd,udpsedbuf2,sizeof(udpsedbuf2),0,(struct sockaddr*)&addr_to_A,sizeof(addr_to_A))==-1)
	    {
		printf("The second time, AWS send to server A\n");
            }	
	    else printf("The AWS sent <%s> to Backend-Server A\n",udpsedbuf2);


	    r=recvfrom(fd,udprecbuf1,sizeof(udprecbuf1),0,(struct sockaddr*)&servera_1,&servera_1length);//get (X^2)^2
	    printf("The AWS received <%s> Backend-Server A using UDP over port %d\n",udprecbuf1,UDPSRVPORTA);
	    result4=atof(udprecbuf1);
	    bzero(udprecbuf1,sizeof(udprecbuf1));

	    if(sendto(fd,udpsedbuf2,sizeof(udpsedbuf2),0,(struct sockaddr*)&addr_to_B,sizeof(addr_to_B))==-1)
	    {
		printf("The second time, AWS send to server B\n");
            }
	    else printf("The AWS sent <%s> to Backend-Server B\n",udpsedbuf2); 
	    r=recvfrom(fd,udprecbuf1,sizeof(udprecbuf1),0,(struct sockaddr*)&serverb_1,&serverb_1length);//get (X^2)^3
	    printf("The AWS received <%s> Backend-Server B using UDP over port %d\n",udprecbuf1,UDPSRVPORTB);
	    result6=atof(udprecbuf1);

	    bzero(udprecbuf1,sizeof(udprecbuf1));
	    bzero(udpsedbuf1,sizeof(udpsedbuf1));
	    bzero(udpsedbuf2,sizeof(udpsedbuf2));
            //bzero(udprecbuf2,sizeof(udprecbuf2));
	    //bzero(udprecbuf3,sizeof(udprecbuf3));	
	    close(fd);
	    printf("Value of powers received by AWS:[%f,%f,%f,%f,%f,%f,]\n",result1,result2,result3,result4,result5,result6);
	    //aws->client
	    if(strcmp(revBuf,"QUIT")==0||strcmp(revBuf,"quit")==0)
            {
                strcpy(sedBuf,"Goodbye,my dear client!");
            }
            else
            {
		if(strcmp(revBuf,"DIV")==0||strcmp(revBuf,"div")==0)
                {
			result=1+result1+result2+result3+result4+result5+result6;
			sprintf(sedBuf,"%f",result);
		}
		if(strcmp(revBuf,"LOG")==0||strcmp(revBuf,"log")==0)
                {
			result=-result1-result2/2-result3/3-result4/4-result5/5-result6/6;
			sprintf(sedBuf,"%f",result);
		}
            }
	    printf("AWS calculate <%s> on <%s>:<%s>\n",Type,Number,sedBuf);
            if(write(clientSock,sedBuf,sizeof(sedBuf))==-1)
            {
                printf("Send error!\n");
            }
	    else printf("The AWS sent <%s> to client\n",sedBuf);
            if(strcmp(revBuf,"Bye")==0||strcmp(revBuf,"quit")==0)
            {
                break;
            }
            bzero(revBuf,sizeof(revBuf));
            bzero(sedBuf,sizeof(sedBuf));
        }
        close(clientSock);
    }
    close(serverSock);
    return 0;
}
