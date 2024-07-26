#include "wsServer.hpp"

namespace wsServer
{
    void init()
    {
        _inner::srv = std::make_unique<ix::WebSocketServer>();
        _inner::srv->setOnClientMessageCallback(_inner::routeClientMessage);

        if (!_inner::srv->listenAndStart())
        {
            throw std::runtime_error("Server is not working");
        }

        _inner::sendThread = std::thread(_inner::sendMessage);
    };

    namespace _inner
    {
        std::unique_ptr<ix::WebSocketServer> srv;

        std::thread sendThread;

        DataWraper<std::string> clientChatMessage;

        void routeClientMessage(
            const std::shared_ptr<ix::ConnectionState>& connectionState,
            const ix::WebSocket& webSocket,
            const ix::WebSocketMessagePtr& webSocketMessage)
        {
            switch (webSocketMessage->type)
            {
            case ix::WebSocketMessageType::Message:
                std::cout << "New message recived:" << std::endl << webSocketMessage->str << std::endl;
                _inner::clientChatMessage.push(webSocketMessage->str);
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

        [[noreturn]] void sendMessage()
        {
            while(true)
            {
                auto message = _inner::clientChatMessage.pop();
                for(const auto& client : _inner::srv->getClients())
                {
                    client->send(message);
                }
            }
        }
    }
}
