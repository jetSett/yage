#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../Game.hpp"

class Engine : public MessageReceiver, public MessageSender
{
    public:
        Engine(Game* parent) : MessageReceiver(), MessageSender(parent){}
        virtual ~Engine();
        virtual void frame() = 0;

        void sendMessage(std::string to, Message& m){
            m.s_data["To"] = to;
            MessageSender::sendMessage(m);
        }
    private:
};

#endif // ENGINE_HPP
