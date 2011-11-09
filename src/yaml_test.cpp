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
  Port port1;
  Port port2;
};

void operator >> (const YAML::Node& node, Port& port) {
   node["id"] >> port.id;
   node["synchronization"] >> port.synchronization;
   node["buffersize"] >> port.buffersize;
   node["address"] >> port.address;
}

void operator >> (const YAML::Node& node, Connector& con) {
   node["id"] >> con.id;
   node["transport"] >> con.transport;
   node["distribution"] >> con.distribution;
   node["interaction"] >> con.interaction;
   const YAML::Node& portnode = node["port"];
   if(portnode.size() == 2){
      portnode[0] >> con.port1;
      portnode[1] >> con.port2;
   }else{
      throw std::runtime_error("Could not parse Connector!");
   }
}

int main()
{
   std::ifstream fin("../config/pubsub.yaml");
   YAML::Parser parser(fin);
   YAML::Node doc;
   parser.GetNextDocument(doc);
 
   for(unsigned i=0;i<doc.size();i++) {
      Connector connector;
      doc[i] >> connector;
      std::cout << connector.port1.synchronization << "\n";
   }

   
   return 0;
}
