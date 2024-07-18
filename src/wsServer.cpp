#include "wsServer.hpp"

namespace wsServer
{
    void init()
    {
        _inner::srv = std::make_unique<ix::WebSocketServer>(4000, "0.0.0.0");
        _inner::srv->makeBroadcastServer();

        if (!_inner::srv->listenAndStart())
        {
            throw std::runtime_error("Server is not working");
        }
    };

    namespace _inner
    {
        std::unique_ptr<ix::WebSocketServer> srv;
    }
}
