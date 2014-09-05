#include "Entity.hpp"

#include <Memory/NewInc.hpp>

Entity::Entity(const std::string& tex, Graphics::D2::Window2D* wnd) : _wnd(wnd)
{
    Image* img = MediaManager::getInstance().loadMediaFromFile<Image>(tex);
    _texture = new Graphics::D2::Texture(*img, wnd->getRenderer());
    delete img;
}

Entity::~Entity()
{
}

void Entity::rend(){
    SmartPtr<Graphics::D2::Shape> s = new Graphics::D2::Shape(_texture, {_x, _y, 200, 200});
    _wnd->addShape(s);
}

void Entity::setPosition(int x, int y){
    _x = x;
    _y = y;
}
