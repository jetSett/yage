#include "Camera.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{
    void Camera::update(){
        manage();
        Rend.setLookAt(_position, _lookAt, _up);
    }

}
}
