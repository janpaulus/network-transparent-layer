#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Transport {
  std::string protocol;
  std::string hostname;
  int port;
};

struct Connection {
  std::string connection;
  int port;
  std::string connector;
  std::string interaction;
  Transport transport;
  std::string distribution;
};

void operator >> (const YAML::Node& node, Transport& transport) {
   node["protocol"] >> transport.protocol;
   node["hostname"] >> transport.hostname;
   node["port"] >> transport.port;
}

void operator >> (const YAML::Node& node, Connection& con) {
   node["connection"] >> con.connection;
   node["port"] >> con.port;
   node["connector"] >> con.connector;
   node["interaction"] >> con.interaction;
   node["distribution"] >> con.distribution;
   const YAML::Node& transportnode = node["transport"];
   for(unsigned i=0; i<transportnode.size(); i++) {
      transportnode[i] >> con.transport;
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
