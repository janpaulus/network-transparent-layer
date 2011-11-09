
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "zmq_ntl.cpp"



int main(int argc, char *argv[])
{
	ZMQ_NTL ntl("../config/pubsub.yaml", true);
  
  while(true){
  ntl.send("HelloWorld");
  std::string data;
  ntl.receive(data);
  std::cout << data << std::endl;
  
  sleep(1);
  }

	return 0;
}

