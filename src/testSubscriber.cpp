#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "YamlConfig.hpp"

int main(int argc, char *argv[])
{

	void *context;
	void *subscriber;

  YamlConfig config;
  config.parse("../config/pubsub.yaml");
  
  std::string subAdress;
  subAdress.append(config.connectionVar.connector.transport);
  subAdress.append("://");
  subAdress.append(config.connectionVar.ports[1].address);
  
  int socket;
  if(config.connectionVar.connector.interaction == "pub-sub")
    socket = ZMQ_SUB;
  
	context = zmq_init(1);
	subscriber = zmq_socket(context, socket);
	zmq_connect(subscriber, subAdress.c_str());
	zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, 0, 0);
	
	while(1)
	{
		int zipcode;
		int temperature;
		int humidity;
		
		//create and initialize an empty message. It will grow dynamically
		zmq_msg_t msg;
		zmq_msg_init(&msg);
		zmq_recv(subscriber, &msg,0);

		//read from msg (which is in the form of an array) to respective variables
		sscanf((char*)zmq_msg_data(&msg), "%d %d %d", &zipcode, &temperature, &humidity);

		printf("Printing %d %d %d\n", zipcode, temperature, humidity);
		zmq_msg_close(&msg);

	}


	return 0;
}
