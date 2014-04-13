
/* 
 *
 *  GPL license 
 *    
 *  in this examples - i randomly picked up these ip address
 *         server ip address = 192.168.100.100
 *         server port       = 32000
 *         client ip address = 192.168.100.51
 *         client port       = 32089 
 *    so create alias interfaces in linux machine before executing these programs       
 *    as root user , enter below commands in a konsole
 *
 *          root$ ifconfig eth0:0 192.168.100.100 up      
 *          root$ ifconfig eth0:1 192.168.100.51  up
      
         Load iptables rules to drop syn-ack packet from server. So that server would be in syn-sent
         state. 
           root$ iptables -F 
           root$ iptables -A INPUT -s 192.168.100.100 -d 192.168.100.51 -p tcp --tcp-flags SYN,ACK,FIN,RST SYN,ACK -j DROP
         see the server state using ./server-state.sh script. You could see two server sockets ( listen_fd, conn_fd ) one in
         listen state and other in syn-state as expected 
          you could flush the iptables to send the syn-ack to client and terminate program gracefully 
            root $ iptables -F                                 
        
 *
 */
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
   int  listen_fd, conn_fd;  
   struct sockaddr_in serv_addr ,cli_addr;
   int cli_len , n = 0 ;
   char mesg[256]; 

   // create a TCP socket
   listen_fd=socket(AF_INET,SOCK_STREAM,0);

   bzero(&serv_addr,sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   // convert dotted ipaddress to unsigned int
   serv_addr.sin_addr.s_addr=inet_addr(SERVER_IP_ADDRESS);   
   serv_addr.sin_port=htons(SERVER_PORT);


   //bind the socket to the server:port
   if (bind(listen_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
   {
      perror("bind");
      exit(1);
   }

   //make the socket ready of incoming connections
   if(listen(listen_fd,10) == -1)
   {
      perror("listen");
      exit(1);
   }
  
   //we get a new socket_fd for use with send and recv
   //while listen_fd can be used to accept() more new connections(max 10)
   conn_fd = accept(listen_fd,(struct sockaddr *)&cli_addr, &cli_len);


   printf( "\nAccepted connection from %s:%d",inet_ntoa(cli_addr.sin_addr.s_addr),ntohs(cli_addr.sin_port));
   printf ( "\n************ Press any key to exit  \n ");
   getchar();
   close(conn_fd);
   close(listen_fd);

}
