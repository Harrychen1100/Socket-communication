#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>//for sockaddr_in
#include <arpa/inet.h>//for socket
#define UDPSRVPORTA 21318
int main()
{
	 int fd=socket(AF_INET,SOCK_DGRAM,0);
	 if(fd==-1)
	 {
	 perror("socket create error!\n");
	 exit(-1);
	 }
	 //printf("socket fd=%d\n",fd);


	 struct sockaddr_in addr;
	 addr.sin_family=AF_INET;
	 addr.sin_port=htons(UDPSRVPORTA);
	 addr.sin_addr.s_addr=inet_addr("127.0.0.1");




	 int r;
	 r=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	 if(r==-1)
	 {
	 printf("Bind error!\n");
	 close(fd);
	 exit(-1);
	 }
	 printf("The Server A is up and running using UDP on port %d.\n",UDPSRVPORTA);
 
	 char recvbuf[1024];
	 char sedbuf[1024];
	 struct sockaddr_in addr_aws;
	 socklen_t aws_len;
	 aws_len=sizeof(addr_aws);

	 while(1)
	 {
		float number;
	 	r=recvfrom(fd,recvbuf,sizeof(recvbuf),0,(struct sockaddr*)&addr_aws, &aws_len);
	 	if(r>0)
	 	{
	 	  recvbuf[r]=0;
	 	  //printf("The message received for %s is :%s\n",inet_ntoa(addr_aws.sin_addr),recvbuf);
		  number=atof(recvbuf);
		  printf("The Server A received input <%f>\n",number);
		  number= number*number;
		  printf("The Server A calculated square: <%f>\n",number);
		  sprintf(sedbuf,"%f",number);

		  r=sendto(fd,sedbuf,sizeof(sedbuf),0,(struct sockaddr*)&addr_aws,sizeof(addr_aws));
		  if(r>0)
		  {
			printf("The server A finishing seding the output to AWS\n");
		  }
	 	}
	 	else
	 	{
		   printf("Receive error!\n");
	 	   break;
	 	}
	 }
	 close(fd);
	 return 0;
}
