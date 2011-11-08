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

struct Connector {
  std::string id;
  std::string transport;
  std::string distribution;
  std::string interaction;
};

struct Connection{
    std::vector<Port> ports;
 //   Connector       connector;
};


void operator >> (const YAML::Node& node, Port& port) {
   node["id"] >> port.id;
   node["synchronization"] >> port.synchronization;
   node["buffersize"] >> port.buffersize;
   node["address"] >> port.address;
}

void operator >> (const YAML::Node& node, Connector& connector) {
   node["id"] >> connector.id;
   node["tranport"] >> connector.transport;
   node["distribution"] >> connector.distribution;
   node["interaction"] >> connector.interaction;

}


void operator >> (const YAML::Node& node, Connection& connection) {
    const YAML::Node& ports = node["ports"];
    for(unsigned i=0;i<ports.size();i++) {
      Port port;
      ports[i] >> port;
      connection.ports.push_back(port);
    }
 //   node["connector"] >> connection.connector;
}


int main()
{
   std::ifstream fin("../config/pubsub.yaml");
   YAML::Parser parser(fin);
   YAML::Node doc;
   parser.GetNextDocument(doc);
 
   for(unsigned i=0;i<doc.size();i++) {
      Connection connectionVar;
      doc[i] >> connectionVar;
      std::cout << connectionVar.ports[0].id << "\n";
      std::cout << connectionVar.ports[0].address << "\n";
      std::cout << connectionVar.ports[0].buffersize << "\n";
   }

   
   return 0;
}
