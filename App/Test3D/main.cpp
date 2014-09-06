#include <glm/gtx/transform.hpp>
#include <3D/OPENGL2/OGL2Renderer.hpp>
#include <3D/Cameras/FreeFlyCamera.hpp>
#include <3D/CamerasManager.hpp>
#include <Memory/NewInc.hpp>
#include <3D/Loaders/MD2Loader.hpp>
#include <ResourcesMgr/MediaManager.hpp>
#include <Graphics/Loaders/ImagesLoader.hpp>

using namespace std;

using namespace Graphics;
using namespace D3;

struct Point{
    Point(float xa, float ya, float za) : x(xa), y(ya), z(za){}
    float x, y, z;
    Color c = D3::Renderer::getInstance().convertColor(Color::Red);
};

int main()
{
    Logger::setLogger(new DebugLogger);
    Renderer::setInstance(new D3::OGL2Renderer);

    WindowsManager::getInstance().createWindow("W1", 800, 640, SDL_WINDOW_OPENGL);
    WindowPtr win = WindowsManager::getInstance().getWindow("W1");

    Renderer::getInstance().initialize(win);
    Point p[] = {
        Point(-1.0f,-1.0f,-1.0f), // triangle 1 : début
        Point(-1.0f,-1.0f, 1.0f),
        Point(-1.0f, 1.0f, 1.0f), // triangle 1 : fin
        Point(1.0f, 1.0f,-1.0f), // triangle 2 : début
        Point(-1.0f,-1.0f,-1.0f),
        Point(-1.0f, 1.0f,-1.0f), // triangle 2 : fin
        Point(1.0f,-1.0f, 1.0f),
        Point(-1.0f,-1.0f,-1.0f),
        Point(1.0f,-1.0f,-1.0f),
        Point(1.0f, 1.0f,-1.0f),
        Point(1.0f,-1.0f,-1.0f),
        Point(-1.0f,-1.0f,-1.0f),
        Point(-1.0f,-1.0f,-1.0f),
        Point(-1.0f, 1.0f, 1.0f),
        Point(-1.0f, 1.0f,-1.0f),
        Point(1.0f,-1.0f, 1.0f),
        Point(-1.0f,-1.0f, 1.0f),
        Point(-1.0f,-1.0f,-1.0f),
        Point(-1.0f, 1.0f, 1.0f),
        Point(-1.0f,-1.0f, 1.0f),
        Point(1.0f,-1.0f, 1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(1.0f,-1.0f,-1.0f),
        Point(1.0f, 1.0f,-1.0f),
        Point(1.0f,-1.0f,-1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(1.0f,-1.0f, 1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(1.0f, 1.0f,-1.0f),
        Point(-1.0f, 1.0f,-1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(-1.0f, 1.0f,-1.0f),
        Point(-1.0f, 1.0f, 1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(-1.0f, 1.0f, 1.0f),
        Point(1.0f,-1.0f, 1.0f)
    };

    auto buf = D3::Renderer::getInstance().createVertexBuffer(35, 0, p);
    D3::DeclarationElement el[] = {
        {0, ELT_USAGE_POSITION, ELT_TYPE_FLOAT3},
        {0, ELT_USAGE_DIFUSE, ELT_TYPE_COLOR}
    };
    auto decl = D3::Renderer::getInstance().createVertexDeclaration(el);

    glm::mat4 proj = glm::perspective(70.0f, (float)(800/640), 0.1f, 1000.0f);

    MediaManager::getInstance().registerLoader(new MD2Loader, ".md2");
    MediaManager::getInstance().registerLoader(new ImagesLoader, ".pcx");

    D3::Renderer::getInstance().setMatrix(MAT_PROJECTION, proj);

    D3::CamerasManager::getInstance().addCamera("Cam1", new D3::FreeFlyCamera(glm::vec3(10.0, -10.0, 0.0)));

    win->captureCursor(true);

    InputManager::getInstance().addTerminateKey(SDL_SCANCODE_ESCAPE);
{

    ResourcePtr<Model> mod = MediaManager::getInstance().loadMediaFromFile<Model>("SINK.md2");

    while(InputManager::getInstance().stillRunning()){
        InputManager::getInstance().updateEvent();
        D3::CamerasManager::getInstance().update();

        Renderer::getInstance().beginScene();
            D3::Renderer::getInstance().setDeclaration(decl);
            D3::Renderer::getInstance().setVertexBuffer(0, buf);
            D3::Renderer::getInstance().drawPrimitives(PT_TRIANGLELIST, 0, 11);

            D3::Renderer::getInstance().pushMatrix(MAT_MODELVIEW);
            mod->rend();
            D3::Renderer::getInstance().popMatrix(MAT_MODELVIEW);

        Renderer::getInstance().endScene();
    }
}

    ResourceManager::destroy();
    MediaManager::destroy();
    D3::CamerasManager::destroy();
    Renderer::destroy();
    InputManager::destroy();
    WindowsManager::destroy();
    Logger::destroy();
    return 0;
}
