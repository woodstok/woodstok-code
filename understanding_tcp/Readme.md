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

1.Blocking syn from client

    iptables -A INPUT -s 192.168.100.51 -p tcp --tcp-flags SYN SYN -j DROP

###Blocking and logging the packets

####Create a custom chain with a new name.

    iptables -N logdrop
    iptables -A logdrop -j LOG --log-prefix "IPTables-Dropped: " --log-level 4
    iptables -A logdrop -j DROP    

####Instead of DROP, use logdrop chain instead
  
    iptables -A INPUT -s 192.168.100.51 -p tcp --tcp-flags SYN SYN -j logdrop

    
