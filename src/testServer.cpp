
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "zmq_ntl.cpp"



int main(int argc, char *argv[])
{
	ZMQ_NTL ntl("../config/pubsub.yaml", false);
  
  std::string data;
  while(true){
    ntl.receive(data);
    std::cout << data << std::endl;
    ntl.send(data);
  }
  
	return 0;
}

