#ifndef WSSOCKET_HPP
#define WSSOCKET_HPP

#include "ixwebsocket/IXWebSocketServer.h"

namespace wsServer
{
    void init();

    namespace _inner
    {
        extern std::unique_ptr<ix::WebSocketServer> srv;
    }
}


#endif
