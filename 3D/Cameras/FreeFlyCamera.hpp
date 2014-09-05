#ifndef FREEFLYCAMERA_HPP
#define FREEFLYCAMERA_HPP

#include <cmath>

#include <Utils/Logger.hpp>
#include "../Graphics/InputManager.hpp"

#include "Camera.hpp"

namespace Graphics{
namespace D3{

    class FreeFlyCamera : public Camera
    {
        public:
            FreeFlyCamera(glm::vec3 position, glm::vec3 lookAt = glm::vec3(0.0, 0.0, 0.0), glm::vec3 up = glm::vec3(0.0, 1.0, 0.0));
            ~FreeFlyCamera();

            virtual void manage();
        private:
            void vectorFromAngles();
            InputManager& InputMgr;

            glm::vec3 _forward, _left;

            float _speed, _sensitivity, _theta, _phi;
    };

}
}

#endif // FREEFLYCAMERA_HPP
