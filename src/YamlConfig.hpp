#ifndef YAMLCONFIG_H
#define YAMLCONFIG_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "yaml-cpp/yaml.h"

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

  struct Connection {
    std::string name;
    std::vector<Port> ports;
    Connector connector;
  };
  
  void operator >>(const YAML::Node& node, Port& port);

  void operator >>(const YAML::Node& node, Connector& connector);

  void operator >>(const YAML::Node& node, Connection& connection);

class YamlConfig {
public:

  YamlConfig();

  ~YamlConfig();

  void parse(std::string configfile);

  
  
  Connection connectionVar;



private:



};

#endif