Advanced Operating System Project 2-part 2
RPC remote calls
Shuyi Zhao
OCT 29, 2012
DR. Ajay Katangur

1. checklist:
Makefile
rpctime.x
rpctime_client.c
rpctime_server.c

2.compilation
a. rpcgen -C -a rpctime.x      generate the makefile
b. make                         generate 2 executables named rpctime_server and rpctime_client. OtherS: .o files are intermedian files
                                make clean: clean executables

3.run:
use remote machine penguin.tamucc.edu and clst.tamucc.edu
Server Side (clst.tamucc.edu or penguin.taumcc)
$ rpctime_server &

Client Side (penguin.tamucc.edu)
$ rpctime_client clst.tamucc.edu n(the number of arguments)