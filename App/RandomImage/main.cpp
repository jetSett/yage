#include <iostream>
#include <random>
#include <ctime>
#include <Graphics/Resources/Image.hpp>
#include <ResourcesMgr/MediaManager.hpp>
#include <Graphics/Loaders/ImagesLoader.hpp>
#include <2D/Renderer.hpp>
#include <2D/Texture.hpp>
#include <Memory/NewInc.hpp>


using namespace std;

using namespace Graphics;

using namespace D2;

std::default_random_engine eng;
std::uniform_int_distribution<unsigned char> a(0, 255);

void randomize(std::vector<unsigned char>& tab){
    for(unsigned int i = 0; i<tab.size(); ++i){
        tab[i] = a(eng);
    }
}

int main()
{
    Logger::setLogger(new DebugLogger);

    eng.seed(time(nullptr));

    WindowsManager::getInstance().createWindow("test", 800, 640);

    Window2DPtr win = Renderer::getInstance().initialize(WindowsManager::getInstance().getWindow("test"));

    const unsigned int size = 200*160*4;

    std::vector<unsigned char> tab(size);

    randomize(tab);
    Image img1(glm::ivec2(200, 160), PXF_A8R8G8B8, (&tab[0]));
    SmartPtr<Texture> tex1 = new Texture(img1, win->getRenderer());
    ShapePtr sh = new Shape(tex1, {0, 0, 800, 640});
    win->addShape(sh);

    while(InputManager::getInstance().stillRunning()){
        Renderer::getInstance().update();
        InputManager::getInstance().updateEvent();
        if(InputManager::getInstance().isPressedSinceDelay(SDL_SCANCODE_ESCAPE))
            InputManager::getInstance().terminate();

        if(InputManager::getInstance().isPressedSinceDelay(SDL_SCANCODE_SPACE)){
            randomize(tab);
            Image img2(glm::ivec2(200, 160), PXF_A8R8G8B8, (&tab[0]));
            tex1->update(img2, win->getRenderer());
        }
    }

    WindowsManager::destroy();
    InputManager::destroy();
    Renderer::destroy();

    Logger::destroy();

     return 0;
}
