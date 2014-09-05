#ifndef PARTICLEGENERATOR_HPP
#define PARTICLEGENERATOR_HPP

#include <vector>

#include "Renderer.hpp"
#include "RenderableObject.hpp"

namespace Graphics{
namespace D3{

class ParticleGenerator : public RenderableObject
{
    struct Particle{
        bool active = true;
        double life = 1.0;
        double fade;
        double larg = 0.3;
        float r, g, b;
        double x = 0, y = 0, z = 0;
        double xi, yi, zi;
        double xg = 0, yg = -0.01, zg = 0;
    };
    struct CarreParticleVertex{
        float px, py;
        Color c;
    };
    public:
        ParticleGenerator(int count);
        ~ParticleGenerator();
        virtual void rend();
    protected:
        void updatePosition();
        std::vector<Particle> _particles;
        std::vector<Buffer<CarreParticleVertex>> _buffers;
        DeclarationPtr _declaration;
};

}
}

#include "ParticleGenerator.tcc"

#endif // PARTICLEGENERATOR_HPP
