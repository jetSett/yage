#include "MessageManaging.hpp"
#include <Memory/NewInc.hpp>

void MessageReceiver::processQueue(){
    while(!_queue.empty()){
        messageMutex.lock();
        Message m = _queue.front();
        _queue.pop();
        messageMutex.unlock();
        processMessage(m);
    }
}

MessageReceiver::MessageReceiver() : _still_running(true), messageReguler(&MessageReceiver::messagesManaging, this){

}

MessageReceiver::~MessageReceiver(){
    _still_running = false;
    messageReguler.join();
}

void MessageReceiver::receiveMessage(Message m){
    messageMutex.lock();
    _queue.push(m);
    messageMutex.unlock();
}

void MessageReceiver::registerReceiver(std::string name, std::function<void(Message&)> fun){
    name = name.substr(name.find_last_of(':')+1, name.size());
    name = name.substr(0, name.find("Receiver"));
    _receivers[name] = fun;
}

void MessageReceiver::processMessage(Message m){
    try{
        if(_receivers.find(m.name)!= _receivers.end()){
            _receivers[m.name](m);
        }else{
            throw BadIndex("Bad function called in the message : " + m.name);
        }
    }catch(const std::exception& e){
        Logger::Log() << e.what();
    }
}

void MessageReceiver::messagesManaging(){
    bool currentSt = _still_running;
    _mutex.unlock();
    while(currentSt){
        processQueue();
        _mutex.lock();
        currentSt = _still_running;
        _mutex.unlock();
    }
}

MessageSender::MessageSender(MessageReceiver* p) : _parent(p){
}

void MessageSender::sendMessage(Message m){
    _parent->receiveMessage(m);
}
