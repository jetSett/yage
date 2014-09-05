#ifndef ENTITY_H
#define ENTITY_H

#include <ResourcesMgr/MediaManager.hpp>
#include <2D/Shape.hpp>
#include <2D/Window2D.hpp>

class Entity
{
    public:
        Entity(const std::string& tex, Graphics::D2::Window2D* wnd);
        virtual ~Entity();
        virtual void update() = 0;
        void rend();
        void setPosition(int x, int y);
    protected:
       Graphics::D2::TexturePtr _texture;
        Graphics::D2::Window2D* _wnd;
        int _x, _y;
};

#endif // ENTITY_H
