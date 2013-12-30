
/* Sample TCP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_IP_ADDRESS "192.168.100.100"
#define CLIENT_IP_ADDRESS "192.168.100.51"

#define SERVER_PORT 32000
#define CLIENT_PORT 32089


int main(int argc, char**argv)
{
   int sock_fd,n;
   struct sockaddr_in serv_addr,cli_addr;

   //If user specifies client port, use that 
   int client_port = CLIENT_PORT;
   if(argc==2){
      client_port = atoi(argv[1]);
   }


   // create a new TCP SOCKET
   sock_fd=socket(AF_INET,SOCK_STREAM,0);

   bzero(&serv_addr,sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   // convert dotted ipaddress to unsigned int
   serv_addr.sin_addr.s_addr=inet_addr(SERVER_IP_ADDRESS);
   serv_addr.sin_port=htons(SERVER_PORT);

   bzero(&cli_addr,sizeof(serv_addr));
   cli_addr.sin_family = AF_INET;
   cli_addr.sin_port=htons(client_port);
   cli_addr.sin_addr.s_addr = inet_addr(CLIENT_IP_ADDRESS);


   // bind the socket to client_ip:port
   if(bind(sock_fd,(struct sockaddr *)&cli_addr,sizeof(cli_addr))==-1)
   {
      perror("bind");
      exit(1);
   }

   // Connect to the server_ip:port
   if(connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1)
   {
      perror("connect");
      exit(1);
   }
 
   printf (" ****** Press any key to continue  " );
   getchar();

   close(sock_fd);

}
