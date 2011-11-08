#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


//Server

int main(int argc, char *argv[])
{
	void *context;
	void *responder;

	//initialize context and replier type socket
	// bind socket to a port with a given protocol
	context = zmq_init(1);
	responder = zmq_socket(context, ZMQ_REP);
	zmq_bind(responder, "tcp://*:5555");

	//main processing loop
	while(1)
	{
		//define messages communicated
		zmq_msg_t request;
		zmq_msg_t reply;
		
		//receive a request message from a client through the socket
		zmq_msg_init(&request);
		zmq_recv(responder, &request,0);
		printf ("Request %s\n", (char*)zmq_msg_data(&request));
		zmq_msg_close(&request);
		
		//send a reply message to a client through the socket
		zmq_msg_init_size(&reply, 6);
		memcpy((void*)zmq_msg_data(&reply), "world", 6);
		zmq_send(responder, &reply, 0);
		zmq_msg_close(&reply);
	}

	return 0;
}
