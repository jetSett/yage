#include "Player.hpp"

#include <Memory/NewInc.hpp>

Player::Player(const std::string& tex, Graphics::D2::Window2D* wnd) : Entity(tex, wnd), _speed(5)
{

}

Player::~Player()
{
}

void Player::update(){
    if(InputMgr.isPressed(SDL_SCANCODE_W))
        _y-=_speed;
    if(InputMgr.isPressed(SDL_SCANCODE_S))
        _y+=_speed;
    if(InputMgr.isPressed(SDL_SCANCODE_A))
        _x-=_speed;
    if(InputMgr.isPressed(SDL_SCANCODE_D))
        _x+=_speed;
}
