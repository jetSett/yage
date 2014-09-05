#include "GraphicsEngine.hpp"
#include "../3D/Scene/ObjectNode.hpp"
#include "../3D/ModelObject.hpp"
#include <Memory/NewInc.hpp>

using namespace Graphics;
using namespace Graphics::D3;

GraphicsEngine::GraphicsEngine(Game* p) : Engine(p){
    REGISTER_RECEIVER(&GraphicsEngine::addModelReceiver);

    Rend = Renderer::getInstance();
    WndMgr.createWindow("active", 800, 600, SDL_WINDOW_OPENGL);
    _activeWnd = WndMgr.getWindow("active");
    Rend.initialize(_activeWnd);
    Rend.setBackgroudColor(Color::Red);
    Rend.showCursor(false);
	glm::mat4 proj = glm::perspective(70.0f, (float)(800/600), 0.1f, 1000.0f);
    Rend.setMatrix(MAT_PROJECTION, proj);

    CamMgr.addCamera("cam1", new FreeFlyCamera(glm::vec3(4, 4, 4)));
}

void GraphicsEngine::addModelReceiver(Message& m){
    _modelToLoad.push(m);
}

void GraphicsEngine::addModel(Model* m, const std::string& name, const std::string& parent){
    ResourcePtr<Model> ptr = m;
    ModelObject *obj = new ModelObject(ptr);
    ObjectNode * node = new ObjectNode(obj);
    ScnGraph.getNode(parent)->addChild(name, node);
}

void GraphicsEngine::loadModels(){
    while(!_modelToLoad.empty()){
        Message m = _modelToLoad.front();
        _modelToLoad.pop();
        std::string parent = m.s_data.find("parent") != m.s_data.end()?m.s_data["parent"]:ROOTSNNAME;
        std::string name = m.s_data["name"];

        Model* mod = MedMgr.loadMediaFromFile<Model>(name);
        addModel(mod, name, parent);
        if(m.v_data.find("Position") != m.v_data.end()){
            glm::vec3 pos = m.v_data["Position"];
            ScnGraph.getNode(name)->translate(pos.x, pos.y, pos.z);
        }
    }
}

GraphicsEngine::~GraphicsEngine()
{
    Renderer::destroy();
    WindowsManager::destroy();
    InputManager::destroy();
    CamerasManager::destroy();
    SceneGraph::destroy();
    Logger::Log() << "Destruct Graphics";
}

void GraphicsEngine::frame(){

    loadModels();

    InputMgr.updateEvent();

    CamMgr.update();

    Rend.beginScene();

        ScnGraph.update();

    Rend.endScene();



    if(!InputMgr.stillRunning() or InputMgr.isPressed(SDL_SCANCODE_ESCAPE)){
        Message m;
        m.name = "stop";
        sendMessage("game", m);
    }
    if(InputMgr.isPressedSinceDelay(SDL_SCANCODE_E)){
        Rend.showCursor(true);
        _activeWnd->captureCursor(!_activeWnd->isCursorCaptured());
    }
    if(InputMgr.isPressedSinceDelay(SDL_SCANCODE_SPACE)){
        Message m;
        m.name = "playSound";
        m.s_data["name"] = "pan.wav";
        sendMessage("sound", m);
    }

}
