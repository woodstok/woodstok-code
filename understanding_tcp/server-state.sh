ss -a | awk '{ print "ip:port = " $4  "  State = " $1 }' | grep "192.168.100.100"
ss -a | awk '{ print "ip:port = " $4  "  State = " $1 }' | grep "192.168.100.51"
