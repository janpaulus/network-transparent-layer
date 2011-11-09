#include <zmq.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "YamlConfig.hpp"


#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

int main(int argc, char *argv[])
{
	//created a context a publisher type socket
	void *context;
	void *publisher;
  YamlConfig config;
  config.parse("../config/pubsub.yaml");
  
  std::string pubAdress;
  pubAdress.append(config.connectionVar.connector.transport);
  pubAdress.append("://");
  pubAdress.append(config.connectionVar.ports[0].address);
  
  std::cout << pubAdress << std::endl;
	
//set a seed number
	srandom ((unsigned)time(NULL));
	
  int socket;
  
  if(config.connectionVar.connector.interaction == "pub-sub")
    socket = ZMQ_PUB;
  
	//prepare context
	context = zmq_init(1);
	publisher = zmq_socket(context, socket);
	zmq_bind(publisher, pubAdress.c_str());
	zmq_bind(publisher, "ipc:/weather");

	int k = 0;
	while(k<10000)
	{
		zmq_msg_t msg;

		int zipcode = 1000;
		int temperature = within(200)-20;
		int humidity = within(40)+5;
		
		//create of the given size 
		zmq_msg_init_size(&msg, 20);
		//fill in the message with values from 3 variables
		sprintf((char*)zmq_msg_data(&msg), "%d %d %d", zipcode, temperature, humidity);

		printf("Publishing %d %d %d \n",zipcode, temperature, humidity);
		zmq_send(publisher,&msg,0);
		zmq_msg_close(&msg);
		k++;
	}


	return 0;
}

