
#include <zmq.hpp>
#include <string>
#include <vector>
#include "YamlConfig.hpp"

class ZMQ_NTL {
public:

  ZMQ_NTL(std::string configfile, bool isSender) {
    config.parse(configfile);
    if (isSender) {
      std::string commStarter;
      commStarter.append(config.connectionVar.connector.transport);
      commStarter.append("://");
      commStarter.append(config.connectionVar.ports[0].address);

      std::cout<< "commStarter : " << commStarter<< std::endl;
      if (config.connectionVar.connector.interaction == "pub-sub") {
        interaction = ZMQ_PUB;
      } else if (config.connectionVar.connector.interaction == "req-rep") {
        if (config.connectionVar.ports[0].synchronization == "blocking")
          interaction = ZMQ_REQ;
        else
          interaction = ZMQ_DEALER;
      } else if (config.connectionVar.connector.interaction == "push-pull") {
        interaction = ZMQ_PUSH;
      }

      context = new zmq::context_t(1);
      zmq_port = new zmq::socket_t(*context, interaction);
      zmq_port->bind(commStarter.c_str());
      std::cout<< "bind : " << commStarter <<std::endl;
      
    } else {
      
      std::string commPartner;
      commPartner.append(config.connectionVar.connector.transport);
      commPartner.append("://");
      commPartner.append(config.connectionVar.ports[1].address);
      

      if (config.connectionVar.connector.interaction == "pub-sub") {
        interaction = ZMQ_SUB;
      } else if (config.connectionVar.connector.interaction == "req-rep") {
        if (config.connectionVar.ports[0].synchronization == "blocking")
          interaction = ZMQ_REP;
        else
          interaction = ZMQ_ROUTER;
      } else if (config.connectionVar.connector.interaction == "push-pull") {
        interaction = ZMQ_PULL;
      }

      context = new zmq::context_t(1);
      zmq_port = new zmq::socket_t(*context, interaction);

      zmq_port->connect(commPartner.c_str());
      
      if (config.connectionVar.connector.interaction == "pub-sub") {
        zmq_port->setsockopt(ZMQ_SUBSCRIBE, "", 0);
        std::cout<< "commPartner : " << commPartner <<std::endl;
      }
      


    }

  };

  ~ZMQ_NTL() {
  };

  bool receive(std::string& data) {
    zmq::message_t message;
    bool returnvalue = zmq_port->recv(&message);
    data = static_cast<char*> (message.data());

    return returnvalue;
  };

  bool send(const std::string& data) {
    zmq::message_t message(data.size());
    memcpy(message.data(), data.c_str(), data.size()+1);
  //  std::cout << (char*)message.data() << std::endl;
    bool returnvalue = zmq_port->send(message);
    return returnvalue;
  };

private:
  zmq::context_t* context;
  zmq::socket_t* zmq_port;
  YamlConfig config;
  int interaction;
};


