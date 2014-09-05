#include "Logger.hpp"
#include "../Memory/NewInc.hpp"
Logger* Logger::_log = nullptr;

Logger& Logger::Log(){
    assert(_log != nullptr);
    return *_log;
}

void Logger::setLogger(Logger* log){
    if(_log){
        delete _log;
    }
    _log = log;
}

void Logger::destroy(){
    delete _log;
    _log = nullptr;
}

std::string Logger::getCurrentTime() const{
    char sTime[24];
    std::time_t cTime = std::time(nullptr);
    std::strftime(sTime, sizeof(sTime), "%H:%M:%S", std::localtime(&cTime));
    return sTime;
}
std::string Logger::getCurrentDate() const{
    char sTime[24];
    std::time_t cTime = std::time(nullptr);
    std::strftime(sTime, sizeof(sTime), "%d/%m/%Y", std::localtime(&cTime));
    return sTime;
}

FileLogger::FileLogger(const std::string& file) : _file(file){
    if(!_file){
        throw LoadingFailed(file);
    }
    _file << "Log started : " << getCurrentDate() << " " << getCurrentTime() << std::endl;
    _file << "================================" << std::endl;
}

FileLogger::~FileLogger(){
    _file << "================================" << std::endl;
    _file << "Log closed at " << getCurrentTime() << std::endl;
}
