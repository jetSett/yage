#include <iostream>
#include <Graphics/WindowsManager.hpp>
#include <2D/Window2D.hpp>
#include <2D/Renderer.hpp>

#include <ResourcesMgr/MediaManager.hpp>
#include <Graphics/Loaders/ImagesLoader.hpp>

#include "Player.hpp"

#include <Memory/NewInc.hpp>

using namespace std;

using namespace Graphics;

class Pool{
public:
    Pool(){
    }
    void update(){
    }
};

class EntitiesMgr{
public:
    EntitiesMgr(D2::Window2DPtr wnd) : _wnd(wnd){
    }
    void addEntity(Entity* e){
        _ent.push_back(e);
    }

    void update(){
        for(Entity* e : _ent){
            e->update();
        }
    }

    void rend(){
        _wnd->clearShape();
        for(Entity* e : _ent){
            e->rend();
        }
        _wnd->update();
    }
private:
    std::list<SmartPtr<Entity>> _ent;
    D2::Window2DPtr _wnd;
};

int main()
{
    MemManaging::MemoryManager::instance().setLoggingLevel(MemManaging::LOW);
    Logger::setLogger(new DebugLogger);
    MediaManager::getInstance().registerLoader(new ImagesLoader, ".jpg .png");

    InputManager::getInstance().addTerminateKey(SDL_SCANCODE_ESCAPE);

    WindowsManager::getInstance().createWindow("Main", 800, 800);
    D2::Window2DPtr win = D2::Renderer::getInstance().initialize(WindowsManager::getInstance().getWindow("Main"));

    Player* p = new Player("player.jpg", win);
    p->setPosition(20, 20);

    EntitiesMgr ent(win);
    ent.addEntity(p);

    while(InputManager::getInstance().stillRunning()){
        InputManager::getInstance().updateEvent();
        ent.update();
        ent.rend();
    }

    InputManager::destroy();
    MediaManager::destroy();
    D2::Renderer::destroy();
    WindowsManager::destroy();
    Logger::destroy();
    return 0;
}
