#include <array>

#include <random>
#include <ctime>

#include <Utils/Logger.hpp>
#include <Graphics/WindowsManager.hpp>
#include <2D/Renderer.hpp>
#include <2D/Window2D.hpp>
#include <2D/TileMap.hpp>

using namespace std;

using namespace Graphics;
using namespace D2;

const int LARGEUR = 40;
const int HAUTEUR = 40;

const int PIX_TAILLE = 20;

enum State{
    ALIVE = 1, DEAD = 0
};

std::default_random_engine eng;
std::uniform_int_distribution<int> a(0, 1), b(0, LARGEUR-1), c(0, HAUTEUR-1);

typedef std::vector<std::vector<State>> grille;

grille grid(HAUTEUR, std::vector<State>(LARGEUR, DEAD));

Image alive(glm::ivec2(PIX_TAILLE, PIX_TAILLE), PXF_A8R8G8B8), dead(glm::ivec2(PIX_TAILLE, PIX_TAILLE), PXF_R8G8B8);

Window2DPtr win = nullptr;

int countNear(int x, int y){
    int n = 0;
    if(x != 0 and grid[x-1][y] == ALIVE) //gauche
        n++;
    if(y != 0 and grid[x][y-1] == ALIVE) //haut
        n++;
    if(x != LARGEUR-1 and grid[x+1][y] == ALIVE) //droit
        n++;
    if(y != HAUTEUR-1 and grid[x][y+1] == ALIVE) //bas
        n++;

    //dhg
    if((x!=0 and y != 0) and (grid[x-1][y-1] == ALIVE))
        n++;
    //dhd
    if((x!=LARGEUR-1 and y!=0) and (grid[x+1][y-1] == ALIVE))
        n++;

    //dbg
    if((x!=0 and y!=HAUTEUR-1) and (grid[x-1][y+1] == ALIVE))
        n++;

    //dbd
    if((x!=LARGEUR-1 and y!=HAUTEUR-1) and (grid[x+1][y+1] == ALIVE))
        n++;
    return n;
}

ShapePtr convert(State s, int x, int y, const TileMap<State>& tm){
    TexturePtr t = new Texture(s==ALIVE?alive:dead, win->getRenderer());
    Shape* sha = new Shape(t, {x*PIX_TAILLE, y*PIX_TAILLE, PIX_TAILLE, PIX_TAILLE});
    return sha;
}

void updateTab(){
    grille g = grid;
    for(int x = 0; x < LARGEUR; ++x){
        for(int y = 0; y<HAUTEUR; ++y){
            if(countNear(x, y) == 3){
                g[x][y] = ALIVE;
            }else{
                g[x][y] = DEAD;
            }
        }
    }
    grid = g;
}

void init(){
    for(int x = 0; x<PIX_TAILLE; ++x){
        for(int y = 0; y<PIX_TAILLE; ++y){
            alive.setPixel(x, y, Color::Blue);
            dead.setPixel(x, y, Color::White);
        }
    }
}

int main()
{
    MemManaging::MemoryManager::instance().setLoggingLevel(MemManaging::LOW);
    eng.seed(time(nullptr));
    Logger::setLogger(new DebugLogger);


    init();

    InputManager::getInstance().addTerminateKey(SDL_SCANCODE_ESCAPE);

    WindowsManager::getInstance().createWindow("Jeu de la vie", PIX_TAILLE*LARGEUR, PIX_TAILLE*HAUTEUR);
    win = Renderer::getInstance().initialize(WindowsManager::getInstance().getWindow("Jeu de la vie"));

    TileMap<State> tileMap(grid, {0, 0, HAUTEUR, LARGEUR}, &convert);

    //creation

    while(InputManager::getInstance().stillRunning()){
        if(InputManager::getInstance().isPressed(SDL_SCANCODE_SPACE))
            break;
        if(InputManager::getInstance().isPressed(SDL_BUTTON_LEFT)){
            int x = InputManager::getInstance().getPointerX();
            int y = InputManager::getInstance().getPointerY();
            x/=PIX_TAILLE;
            y/=PIX_TAILLE;
            grid[x][y] = grid[x][y]==ALIVE?DEAD:ALIVE;
            tileMap.update(x, y);
        }

        win->clearShape();
        tileMap.rend(win);

        Renderer::getInstance().update();
        InputManager::getInstance().updateEvent();
    }

    //jeu
    while(InputManager::getInstance().stillRunning()){

        win->clearShape();
        tileMap.rend(win);

        Renderer::getInstance().update();
        InputManager::getInstance().updateEvent();
        InputManager::getInstance().waitKey(SDL_SCANCODE_SPACE);
        updateTab();
        tileMap.updateAll();
    }

    InputManager::destroy();
    WindowsManager::destroy();
    Renderer::destroy();
    Logger::destroy();
    return 0;
}
