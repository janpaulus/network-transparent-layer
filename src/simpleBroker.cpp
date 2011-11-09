//
//  Simple message queuing broker in C++
//  Same as request-reply broker but using QUEUE device
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include "zhelpers.hpp"

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    //  Socket facing clients
    zmq::socket_t frontend (context, ZMQ_DEALER);
    frontend.bind("tcp://127.0.0.1:5558");

    //  Socket facing services
    zmq::socket_t backend (context, ZMQ_ROUTER);
    zmq_bind (backend, "tcp://127.0.0.1:5556");

    //  Start built-in device
    zmq::device (ZMQ_QUEUE, frontend, backend);
    return 0;
}
