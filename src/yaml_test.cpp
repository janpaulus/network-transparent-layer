#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Port {
  std::string id;
  std::string synchronization;
  int buffersize;
  std::string address;
};

struct Connection {
  std::string id;
  std::string transport;
  std::string distribution;
  std::string interaction;
};

void operator >> (const YAML::Node& node, Port& port) {
   node["id"] >> port.id;
   node["synchronization"] >> port.synchronization;
   node["buffersize"] >> port.buffersize;
   node["address"] >> port.address;
}

void operator >> (const YAML::Node& node, Connection& con) {
   node["id"] >> con.id;
   node["tranport"] >> con.transport;
   node["distribution"] >> con.distribution;
   node["interaction"] >> con.interaction;
   const YAML::Node& portnode = node["port"];
   for(unsigned i=0; i<portnode.size(); i++) {
      portnode[i] >> con.port;
   }
}

int main()
{
   std::ifstream fin("../config/pubsub.yaml");
   YAML::Parser parser(fin);
   YAML::Node doc;
   parser.GetNextDocument(doc);
 
   for(unsigned i=0;i<doc.size();i++) {
      Connection connection;
      doc[i] >> connection;
      std::cout << connection.transport.protocol << "\n";
   }

   
   return 0;
}
