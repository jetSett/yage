#include <ResourcesMgr/ResourceManager.hpp>
#include "Game.hpp"
#include "Engines/GraphicsEngine.hpp"
#include "Engines/SoundEngine.hpp"
#include "Engines/GameEngine.hpp"

#include <Graphics/Loaders/ImagesLoader.hpp>
#include <3D/Loaders/MD2Loader.hpp>
#include <3D/Loaders/ShadersLoader.hpp>
#include <Sounds/Loaders/SoundLoaders.hpp>
#include <Memory/NewInc.hpp>

Game::Game()
{
    Logger::setLogger(new DebugLogger);

    initMediaMgr();

    Graphics::D3::Renderer::setInstance(new Graphics::D3::OGL2Renderer);
    _engines["graphics"] = new GraphicsEngine(this);
    _engines["sound"] = new SoundEngine(this);
    _engines["game"] = new GameEngine(this);

    REGISTER_RECEIVER(&Game::stopReceiver);
}

Game::~Game()
{
    _engines.clear();
    ResourceManager::destroy();
    MediaManager::destroy();
    Logger::destroy();
}

void Game::initMediaMgr(){
    MediaManager::getInstance().registerLoader(new ImagesLoader, ".jpg .png .tif .pcx .gif");
    MediaManager::getInstance().registerLoader(new MD2Loader, ".md2");
    MediaManager::getInstance().registerLoader(new SampleLoader, ".wav");
    MediaManager::getInstance().registerLoader(new StreamLoader, ".mp3");
    MediaManager::getInstance().registerLoader(new ShadersLoader(SHAD_PIX), ".pcg");
    MediaManager::getInstance().registerLoader(new ShadersLoader(SHAD_VERT), ".vcg");

    MediaManager::getInstance().addSearchPath("Data/Sounds");
    MediaManager::getInstance().addSearchPath("Data/Models");
    MediaManager::getInstance().addSearchPath("Data/Shaders");
    MediaManager::getInstance().addSearchPath("Data/Images");
}

void Game::run(){
    Logger::Log() << "Starting game (i've lost)";

    bool currentSt = _still_running;
    _mutex.unlock();

    while(currentSt){
        for(auto p : _engines){
            p.second->frame();
        }

        _mutex.lock();
        currentSt = _still_running;
        _mutex.unlock();
    }
    Logger::Log() << "End of game";
}

void Game::stop(){
    _mutex.lock();
    _still_running = false;
    _mutex.unlock();
}

void Game::messageTo(Message& m){
    if(m.s_data.find("To") != m.s_data.end()){
        std::string to = "";
        to = m.s_data["To"];
        m.s_data.erase("To");
        if(to == "game"){
            receiveMessage(m);
        }else if(_engines.find(to) != _engines.end()){
            _engines[to]->receiveMessage(m);
        }else{
            Logger::Log() << std::string("Unknown engine : ") + to;
        }
    }else{
        MessageReceiver::processMessage(m);
    }

}

void Game::processMessage(Message m){
    messageTo(m);
}

void Game::stopReceiver(Message&){
    stop();
}
