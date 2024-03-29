
#include <zmq.hpp>
#include <string.h>

int main ()
{
    //  One I/O thread in the thread pool will do.
    zmq::context_t ctx (1);

    //  This client is a requester.
    zmq::socket_t s (ctx, ZMQ_REQ);

    //  Connect to the server.
    s.connect ("tcp://localhost:5555");

    // Send 20 requests and receive 20 replies.
    for (int i = 0; i != 20; i++) {

        //  Send the request. No point in filling the content in as server
        //  is a dummy and won't use it anyway.
        zmq::message_t request (10);
        memset (request.data (), 0, request.size ());
        s.send (request);

        //  Get the reply. 
        zmq::message_t reply;
        s.recv (&reply);
    }

    return 0;
}
