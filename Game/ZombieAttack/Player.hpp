#ifndef PLAYER_H
#define PLAYER_H

#include <Graphics/InputManager.hpp>

#include "Entity.hpp"


class Player : public Entity
{
    public:
        Player(const std::string& tex, Graphics::D2::Window2D* wnd);
        ~Player();

        void update();
    private:
        int _speed;
        Graphics::InputManager& InputMgr = Graphics::InputManager::getInstance();
};

#endif // PLAYER_H
