#include "wsServer.hpp"

namespace wsServer
{
    void init()
    {
        _inner::srv = std::make_unique<ix::WebSocketServer>(4000, "0.0.0.0");
        _inner::srv->setOnClientMessageCallback(_inner::routeClientMessage);

        if (!_inner::srv->listenAndStart())
        {
            throw std::runtime_error("Server is not working");
        }
    };

    namespace _inner
    {
        std::unique_ptr<ix::WebSocketServer> srv;

        std::thread sendThread;

        void routeClientMessage(
            const std::shared_ptr<ix::ConnectionState>& connectionState,
            const ix::WebSocket& webSocket,
            const ix::WebSocketMessagePtr& webSocketMessage)
        {
            switch (webSocketMessage->type)
            {
            case ix::WebSocketMessageType::Message:
                std::cout << "New message recived:" << std::endl << webSocketMessage->str << std::endl;
                break;
            case ix::WebSocketMessageType::Open:
                std::cout << "New connection opened" << std::endl;
                break;
            case ix::WebSocketMessageType::Close:
                std::cout << "Old connection closed" << std::endl;
                break;
            case ix::WebSocketMessageType::Error:
                std::cout << "Error" << std::endl;
                break;
            case ix::WebSocketMessageType::Ping:
                std::cout << "Ping" << std::endl;
                break;
            case ix::WebSocketMessageType::Pong:
                std::cout << "Pong" << std::endl;
                break;
            case ix::WebSocketMessageType::Fragment:
                std::cout << "Fragment" << std::endl;
                break;
            }
        }

        void sendMessage()
        {

        }
    }
}
