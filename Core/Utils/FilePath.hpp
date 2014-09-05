#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <string>
#include <algorithm>
#include <fstream>

class FilePath{
public:
    FilePath(const std::string name = "unknown");
    FilePath(const char* name);
    bool exist() const;
    const std::string& fullname() const; //nom du fichier avec son chemin complet
    std::string filename() const; //nom du fichier sans chemin complet
    std::string shortFilename() const; //nom du fichier sans chemin et sans extension
    std::string extension() const;
private:
    void normalize();
    std::string _name;
};

#endif // FILE_H_INCLUDED
