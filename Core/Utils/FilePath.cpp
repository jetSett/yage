#include "FilePath.hpp"
#include "Logger.hpp"

FilePath::FilePath(const char* name) : _name(name){
    normalize();
}

FilePath::FilePath(const std::string name) : _name(name){
    normalize();
}

bool FilePath::exist() const{
    std::ifstream file(_name.c_str());
    return file.is_open();
}

void FilePath::normalize(){
//    std::replace(_name.begin(), _name.end(), '/', '\\');
}

const std::string& FilePath::fullname() const{
    return _name;
}

std::string FilePath::filename() const{
    std::string::size_type pos = _name.find_last_of("\\/");
    if(pos != std::string::npos){
        return _name.substr(pos+1, std::string::npos);
    }else{
        return _name;
    }
}

std::string FilePath::shortFilename() const{
    return filename().substr(0, filename().find_last_of("."));
}

std::string FilePath::extension() const{
    std::string::size_type pos = _name.find_last_of(".");
    if(pos != std::string::npos){
        return _name.substr(pos+1, std::string::npos);
    }else{
        return _name;
    }
}
