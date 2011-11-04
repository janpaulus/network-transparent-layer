#include <zmq.h>
#include <unicap.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <SDL/SDL.h>
#include <signal.h>
#include <getopt.h>
#include <unistd.h>
#include <assert.h>

extern char *optarg;

typedef struct PeerMode 
{
    char ipaddress[30];
    char operationMode[15];
    char interactionMode[15];
} PeerMode;




int parseOptions(int argc, char *argv[], PeerMode *peerMode);


int main(int argc, char *argv[])
{
  
  PeerMode  *peerMode = (PeerMode*) malloc(sizeof(PeerMode));
  if(peerMode == NULL)
  {
    printf("ERROR ALLOCATING peer memory");
    exit(1);
  }
    
  if(parseOptions(argc, argv, peerMode) != 0)
  {
    printf("INVALID OPTION \n");
    exit(1);
  }
  
  void *context = zmq_init(1);
  void *frontEnd = zmq_socket(context, ZMQ_SUB);
  void *backEnd = zmq_socket(context, ZMQ_PUB);
  
  zmq_setsockopt(frontEnd, ZMQ_SUBSCRIBE, 0, 0);
  zmq_connect(frontEnd, "tcp://*:6666");
  zmq_bind(backEnd,"tcp://*:5556");
  
  zmq_device(ZMQ_FORWARDER, frontEnd, backEnd);
  

  zmq_term(context);      
  return 0;
}



//Processes command-line options given to the program
int parseOptions(int argc, char *argv[], struct PeerMode *peerMode)
{
  
  int nextOption = 0;
  const char* const shortOptions = "hi:m:p:"; //constant pointer to constant char
  const struct option longOptions[] = 
    {
      {"help", 0, NULL, 'h'},
      {"ipaddress", 1, NULL, 'i'},
      {"interactionmode", 1, NULL, 'm'},
      {"peermode", 1, NULL, 'p'},
      {NULL, 0, NULL, 0}
    };
  do
  {
    nextOption = getopt_long(argc, argv, shortOptions, longOptions, NULL);
    switch(nextOption)
    {
      case 'h':
        fprintf(stdout, 
                "-h or --help  Prints this message \n" 
                "-p <xxx> or --peermode <xxx> Set the peer behavior, 'producer' or 'subscriber'\n"
                "-i <xxx> or --ipaddress <xxx> Set ip end-point to <xxx>\n"
                "-m <xxx> or --mode <xxx> Set mode to <xxx>, 'pub-sub', 'req-rep'\n");
        break;
      case 'i':
        strcpy(peerMode->ipaddress, optarg);
        break;
      case 'm':
        strcpy(peerMode->interactionMode,optarg);
        break;
      case 'p':
        strcpy(peerMode->operationMode,optarg);
        break;
      default:
        continue;
    }
  } while(nextOption != -1);
  
  return 0; 
}
