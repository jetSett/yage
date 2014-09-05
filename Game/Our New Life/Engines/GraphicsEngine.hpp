#ifndef GRAPHICSENGINE_HPP
#define GRAPHICSENGINE_HPP

#include <glm/gtx/transform.hpp>

#include "Engine.hpp"


#include <3D/OPENGL2/OGL2Renderer.hpp>
#include <Graphics/WindowsManager.hpp>
#include <3D/CamerasManager.hpp>
#include <3D/SceneGraph.hpp>
#include <3D/Cameras/FreeFlyCamera.hpp>
#include <3D/Shader.hpp>
#include <ResourcesMgr/MediaManager.hpp>

class GraphicsEngine : public Engine
{

    public:
        GraphicsEngine(Game* p);
        virtual ~GraphicsEngine();

        virtual void frame();

        void addModel(Model*, const std::string& name, const std::string& parent);

    private:

        void loadModels();

        std::queue<Message> _modelToLoad;

        void addModelReceiver(Message&);

        Graphics::WindowPtr _activeWnd;
        Graphics::WindowsManager& WndMgr = Graphics::WindowsManager::getInstance();
        Graphics::InputManager& InputMgr = Graphics::InputManager::getInstance();
        Graphics::D3::CamerasManager& CamMgr = Graphics::D3::CamerasManager::getInstance();
        Graphics::D3::Renderer& Rend = Graphics::D3::Renderer::getInstance();
        Graphics::D3::SceneGraph& ScnGraph = Graphics::D3::SceneGraph::getInstance();
        MediaManager& MedMgr = MediaManager::getInstance();
};

#endif // GRAPHICSENGINE_HPP
