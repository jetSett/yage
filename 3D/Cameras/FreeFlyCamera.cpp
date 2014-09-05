#include "FreeFlyCamera.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    FreeFlyCamera::FreeFlyCamera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up) : Camera(position, lookAt, up),
    InputMgr(InputManager::getInstance()){
        _phi = 0;
        _theta = 0;
        _sensitivity = 0.4;
        _speed = 0.2;
        vectorFromAngles();
    }

    FreeFlyCamera::~FreeFlyCamera(){}

    void FreeFlyCamera::manage(){
        if(InputMgr.hasMouseMoved()){
            _theta -= InputMgr.getPointerXRel()*_sensitivity;
            _phi -= InputMgr.getPointerYRel()*_sensitivity;
        }
        if(InputMgr.isPressed(SDL_SCANCODE_DOWN))
            _position -= /*(float)InputMgr.getTimeStep()**/_speed*_forward;
        if(InputMgr.isPressed(SDL_SCANCODE_UP))
            _position += /*(float)InputMgr.getTimeStep()**/_speed*_forward;
        if(InputMgr.isPressed(SDL_SCANCODE_RIGHT))
            _position -= /*(float)InputMgr.getTimeStep()**/_speed*_left;
        if(InputMgr.isPressed(SDL_SCANCODE_LEFT))
            _position += /*(float)InputMgr.getTimeStep()**/_speed*_left;


        vectorFromAngles();
    }

    void FreeFlyCamera::vectorFromAngles(){
        if(_phi>89)
            _phi = 89;
        else if(_phi < -89)
            _phi = -89;

        double phiRad = _phi*M_PI/180;
        double thetRad = _theta*M_PI/180;

        double cp = std::cos(phiRad);
        double sp = std::sin(phiRad);
        double ct = std::cos(thetRad);
        double st = std::sin(thetRad);
        if(_up.x == 1){
            _forward.x = sp;
            _forward.y = cp*ct;
            _forward.z = cp*st;
        }else if(_up.y == 1){
            _forward.x = cp*st;
            _forward.y = sp;
            _forward.z = cp*ct;
        }else{
            _forward.x = cp*ct;
            _forward.y = cp*st;
            _forward.z = sp;
        }

        _left = glm::cross(_up, _forward);
        _left = glm::normalize(_left);
        _lookAt = _position + _forward;
    }

}
}
