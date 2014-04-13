#Readme

##Commands for this tutorial

###Creating alias interfaces

    sudo ifconfig eth0:0 192.168.100.100 up
    sudo ifconfig eth0:1 192.168.100.51  up

###Monitoring server-state
*Note:This is already there as a file in server-state.sh*

    ss -a | awk '{ print "ip:port = " $4  "  State = " $1 }' | grep "192.168.100.100"
    ss -a | awk '{ print "ip:port = " $4  "  State = " $1 }' | grep "192.168.100.51"    

###Blocking packets with specific tcp flags

*Note: in the --tcp-flags switch, we supply two parameters.
1.mask - these are the flags that we examine.
2.comp - these are the flags that have to be set.  Flags are: SYN ACK FIN RST URG PSH ALL NONE.  
Hence the command `iptables -A FORWARD -p tcp --tcp-flags SYN,ACK,FIN,RST SYN` will only match packets with the SYN flag set, and the ACK, FIN and RST flags unset.  *

1.Blocking syn from client

    iptables -A INPUT -s 192.168.100.51 -p tcp --tcp-flags SYN SYN -j DROP

2.Blocking syn+ack from server
   
    iptables -A INPUT -s 192.168.100.100  -p tcp --tcp-flags SYN,ACK SYN,ACK -j DROP

###Blocking and logging the packets

####Create a custom chain with a new name.

    iptables -N logdrop
    iptables -A logdrop -j LOG --log-prefix "IPTables-Dropped: " --log-level 4
    iptables -A logdrop -j DROP    

####Instead of DROP, use logdrop chain instead
  
    iptables -A INPUT -s 192.168.100.51 -p tcp --tcp-flags SYN SYN -j logdrop

    
