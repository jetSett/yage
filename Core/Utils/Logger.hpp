#ifndef LOGGER_HPP_INCLUDED
#define LOGGER_HPP_INCLUDED

#include <string>
#include <sstream>
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>

#include "Exceptions.hpp"

class Logger{
public:
    virtual ~Logger(){
    }

    static void setLogger(Logger* log);

    static void destroy();

    static Logger& Log();
    template <class T> Logger& operator<<(const T& toLog){
        std::ostringstream oss;
        oss << toLog;
        write(oss.str());
        return Log();
    }

private:
    virtual void write(std::string mess) = 0;

    static Logger* _log;

protected:
    std::string getCurrentTime() const;
    std::string getCurrentDate() const;
};

class DebugLogger : public Logger{
private:
    virtual void write(std::string mess){
        std::cout << mess << std::endl;
    }
};

class FileLogger : public Logger{
public:
    FileLogger(const std::string& file = "Out.log");
    ~FileLogger();
private:
    virtual void write(std::string mess){
        _file << getCurrentTime() << " : " << mess << "\n" << std::flush;
    }

    std::ofstream _file;
};

#endif // LOGGER_HPP_INCLUDED
