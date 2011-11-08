#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

	void *context;
	void *subscriber;

	context = zmq_init(1);
	subscriber = zmq_socket(context, ZMQ_SUB);
	zmq_connect(subscriber, "tcp://*:5556");
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
