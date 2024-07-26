#ifndef WSSOCKET_HPP
#define WSSOCKET_HPP

#include <memory>
#include <thread>
#include <chrono>
#include <iostream>

#include "ixwebsocket/IXWebSocketMessage.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "ixwebsocket/IXWebSocketServer.h"

#include "dataWraper.hpp"

namespace wsServer
{
    void init();

    namespace _inner
    {
        extern std::unique_ptr<ix::WebSocketServer> srv;

        extern std::thread sendThread;

        extern DataWraper<std::string> clientChatMessage;

        void routeClientMessage(const std::shared_ptr<ix::ConnectionState>&, const ix::WebSocket&, const ix::WebSocketMessagePtr&);
        [[noreturn]] void sendMessage();
    }
}


#endif
