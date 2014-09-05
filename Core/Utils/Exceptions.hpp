#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <exception>
#include <string>
#include <sstream>

class PersoException : public std::exception{
public:
    const char* what() const throw(){
        return _mess.c_str();
    }
    PersoException(const std::string& mess) : _mess(mess){}
protected:
    std::string _mess;
};

class BadIndex : public PersoException{
public:
    BadIndex(const std::string& location) : PersoException(std::string("Error : Bad index on ") + location){}
};

class ExternError : public PersoException{
public:
    ExternError(const std::string& lib, const std::string mess) : PersoException(std::string("External Error ")
                                                                                 + lib +
                                                                                 std::string(" -> ") + mess){}
};

class ResourceError : public PersoException{
public:
    ResourceError(const std::string& mess, const std::string& resName) : PersoException(std::string("Ressource error on ") + resName + std::string(" -> ") + mess){}
};

class UnemplementedFunction : public PersoException{
public:
    UnemplementedFunction(const std::string& func) : PersoException(std::string("Unemplemented function : ") + func) {}
};

class LoadingFailed : public PersoException{
public:
    LoadingFailed(const std::string& file) : PersoException(std::string("Loading failed : ") + file){}
};

class BadDelete : public PersoException{
public:
    BadDelete(void* ptr, const std::string& file, int line) : PersoException(""){
        std::ostringstream oss;
        oss << "Bad delete : " << ptr << " | " << file << ":" << line;
        _mess = oss.str();
    }
};

#endif // EXCEPTIONS_H_INCLUDED
