Full Name: Haoliang Chen
USCID:     5885850318

Work: In this project, I build a communication system which can transmit the message through TCP and UDP. For the TCP, there
are 1 server,called AWS, and 1 client. For the UDP, there are 4 devices, one is AWS, and the other three are serverA, serverB,
and serverC.
In the project, the main function i realized is the once the client send function: LOG(or log) or DIV(or div) and with a number
range from 0 to 1 to the AWS, after AWS send the number to all three back-servers,and receive the calculate result, the client 
will receive the require calculate result.

code files: there are 5 code files, client.c, aws.c, serverA.c, serverB.c, serverC.c

client.c: In this files, it achieve the function that it can get the command from the user, which concludes <function> and <input>,
then it will send this message to the aws(server).And at last, it will receive the result, and will show the <function> and
<number>: result.

aws.c: In this files, it achieve the communication function in both TCP and UDP. As for TCP, it is the server of the TCP, it can receive
the message from client, and can send the calculated result back to client. As for UDP, the AWS can send the number need to be calculated
to three back-servers, and then get the result back. Finally, it will calculate as the function.

ServerA.c:It is one part of the UDP, it is responsible for calculating the square, once receive a number from the AWS, it will
calculate the square, and then return back the square value to AWS.

ServerB.c:It is one part of the UDP, it is responsible for calculating the cube, once receive a number from the AWS, it will
calculate the cube, and then return back the cube value to AWS.

ServerC.c:It is one part of the UDP, it is responsible for calculating the 5th power, once receive a number from the AWS, it will
calculate the 5th power, and then return back the value to AWS.



The format of the message is: function number.function can be "DIV"or"div"or"LOG"or"log".and number 
can be [0,1].

Idiosyncrasy: some time when built the TCP, there will be a blind error, at that time, may need to reopen the aws.o
and until the connection built.
reused code: 1)refer to the link https://www.cnblogs.com/yusenwu/p/4579167.html, to see how to build a tcp cnnection
	      2)use strtok() to segment the message refer https://www.cnblogs.com/Bob-tong/p/6610806.html