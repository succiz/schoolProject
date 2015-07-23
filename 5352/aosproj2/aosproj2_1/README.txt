Advanced Operating System Project 2-part 1
RPC remote calls
Shuyi Zhao
OCT 29, 2012
DR. Ajay Katangur

1. checklist:
Makefile
primefib.x
primefib_client.c
primefib_server.c

2.compilation
a. rpcgen -C -a primefib.x      generate the makefile
b. make                         generate 2 executables named primefib_server and primefib_client. OtherS: .o files are intermedian files
                                make clean: clean executables

3.run:
use remote machine penguin.tamucc.edu and clst.tamucc.edu
Server Side (clst.tamucc.edu)
$ primefib_server &

Client Side (penguin.tamucc.edu)
$ primefib_client clst.tamucc.edu n(the desired number)