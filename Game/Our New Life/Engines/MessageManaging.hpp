#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP

#include <string>
#include <map>
#include <queue>

#include <thread>
#include <mutex>
#include <functional>

#include <glm/glm.hpp>

#include <Utils/Exceptions.hpp>
#include <Utils/Logger.hpp>

struct Message{
    std::string name;
    std::map<std::string, int> i_data;
    std::map<std::string, std::string> s_data;
    std::map<std::string, float> f_data;
    std::map<std::string, glm::vec3> v_data;
    std::map<std::string, glm::mat4> m_data;
};

class MessageReceiver
{
    public:
    virtual ~MessageReceiver();
    void processQueue();
    int getQueueSize(){
        return _queue.size();
    }
    void registerReceiver(std::string name, std::function<void(Message&)> fun);
    virtual void processMessage(Message);
    void receiveMessage(Message mess);
    protected:
        MessageReceiver();

        void messagesManaging();


        std::mutex messageMutex;
        std::queue<Message> _queue;
        std::map<std::string, std::function<void(Message&)>> _receivers;

        std::mutex _mutex;
        bool _still_running;

        std::thread messageReguler;
};

class MessageSender{
public:
    MessageSender(MessageReceiver* p);
    void sendMessage(Message m);
protected:
    MessageReceiver* _parent;
};


#define REGISTER_RECEIVER(fun) registerReceiver(#fun, std::function<void(Message&)>(std::bind(fun, this, std::placeholders::_1)));


#endif // MESSAGEBOX_HPP
