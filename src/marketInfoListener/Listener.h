#pragma once
#include <string>

class Listener {
public:
    virtual ~Listener(){}
    /* start to listen to incoming data */
    virtual void startListening() = 0;
    /* send the message/request to the connected server */
    virtual void sendRequest(std::string) = 0;
private:
    /* set up callback/thread to react to incoming data */
    virtual void setHandlers() = 0;
};
