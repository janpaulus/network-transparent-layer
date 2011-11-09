
#include "YamlConfig.hpp"


  YamlConfig::YamlConfig() {
  }

  YamlConfig::~YamlConfig() {
  }

  void YamlConfig::parse(std::string configfile) {
    std::ifstream fin(configfile.c_str());
    YAML::Parser parser(fin);
    YAML::Node doc;
    parser.GetNextDocument(doc);

    for (unsigned i = 0; i < doc.size(); i++) {
      
      doc[i] >> connectionVar;
    }
  }

  void operator >>(const YAML::Node& node, Port& port) {
    node["id"] >> port.id;
    node["synchronization"] >> port.synchronization;
    node["buffersize"] >> port.buffersize;
    node["address"] >> port.address;
  }

  void operator >>(const YAML::Node& node, Connector& connector) {
    node["id"] >> connector.id;
    node["transport"] >> connector.transport;
    node["distribution"] >> connector.distribution;
    node["interaction"] >> connector.interaction;
  }

  void operator >>(const YAML::Node& node, Connection& connection) {
    node["connection"] >> connection.name;
    const YAML::Node& ports = node["ports"];
    for (unsigned i = 0; i < ports.size(); i++) {
      Port port;
      ports[i] >> port;
      connection.ports.push_back(port);
    }
    const YAML::Node& connectornode = node["connector"];
    for (unsigned i = 0; i < connectornode.size(); i++) {
      connectornode[i] >> connection.connector;
    }
  }
