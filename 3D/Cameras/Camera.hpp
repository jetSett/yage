#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include "../Renderer.hpp"

namespace Graphics{
namespace D3{

    class Camera
    {
        public:
            Camera(glm::vec3 position, glm::vec3 lookAt = glm::vec3(0.0, 0.0, 0.0), glm::vec3 up = glm::vec3(0.0, 0.0, 1.0)) :
            _position(position), _lookAt(lookAt), _up(up), Rend(Renderer::getInstance()){}
            virtual ~Camera(){}
            void update();
            virtual void manage() = 0;
        protected:
            glm::vec3 _position, _lookAt, _up;
            Renderer& Rend;
    };

}
}
#endif // CAMERA_HPP
