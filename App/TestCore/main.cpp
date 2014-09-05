#include <iostream>
#include <list>
#include <Utils/Logger.hpp>
#include <Memory/SmartPtr.hpp>
#include <Memory/NewInc.hpp>

using namespace std;

typedef SmartPtr<int> Intptr;

struct A{
    Intptr createInt(int i){
        Intptr a = new int(i);
        liste[i] = a;
        return liste[i];
    }
    std::map<int, Intptr> liste;
};

int main()
{
    Logger::setLogger(new DebugLogger);
    A a;
    Intptr ptr = a.createInt(42);
    Logger::destroy();
    return 0;
}
