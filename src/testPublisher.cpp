
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "zmq_ntl.cpp"



int main(int argc, char *argv[])
{
	ZMQ_NTL ntl("../config/pubsub.yaml", true);
  
  while(true)
  ntl.send("HelloWorld");

	return 0;
}

