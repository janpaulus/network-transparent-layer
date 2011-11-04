#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unicap.h>

//Client

int main(int argc, char *argv[])
{

	//create a requester type socket and connect through it server
	int requestNum = 0;
	void* context = zmq_init(1);
	void* requester = zmq_socket(context, ZMQ_REQ); 
	printf("Connecting to server \n");
	zmq_connect(requester, "tcp://*:5555");
	
	for (requestNum; requestNum != 100; requestNum++)
	{
		//define messages communicated
		zmq_msg_t request;
		zmq_msg_t reply;
    unsigned char *localImageBuffer; //need to copy incoming message data into this buffer
   
    //send a request message to the server through the socket
		zmq_msg_init_data(&request, "Hello", 6, NULL, NULL);
		zmq_send(requester, &request, 0);
		zmq_msg_close(&request);
		
		//receive reply message, through the socket
		zmq_msg_init(&reply);
		zmq_recv(requester, &reply, 0);
    memcpy(localImageBuffer, &reply, 614408);
    
		zmq_msg_close(&reply);
	}
		
	
	return 0; 
}
