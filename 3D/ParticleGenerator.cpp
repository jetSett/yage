#include "ParticleGenerator.hpp"
#include <Utils/Math.hpp>
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    ParticleGenerator::ParticleGenerator(int count){

        DeclarationElement decl[] = {
            {0, ELT_USAGE_POSITION, ELT_TYPE_FLOAT2},
            {0, ELT_USAGE_DIFUSE, ELT_TYPE_COLOR}
        };

        _declaration = Renderer::getInstance().createVertexDeclaration(decl);

        _particles.resize(count);
        _buffers.resize(count);
        int i = 0;
        for(Particle& p : _particles){

            p.r = RandGenerator::getInstance().rand(0, 1);
            p.g = RandGenerator::getInstance().rand(0, 1);
            p.b = RandGenerator::getInstance().rand(0, 1);

            p.xi = RandGenerator::getInstance().rand(-0.3, 0.3);
            p.yi = RandGenerator::getInstance().rand(-0.3, 0.3);
            p.zi = RandGenerator::getInstance().rand(-0.3, 0.3);

            p.fade = RandGenerator::getInstance().rand(0.001, 0.01);

            Color a;
            a.setFloats(p.r, p.g, p.b);

            CarreParticleVertex v[4] = {
                {0, 0, Renderer::getInstance().convertColor(a)},
                {0, (float)p.larg, Renderer::getInstance().convertColor(a)},
                {(float)p.larg, 0, Renderer::getInstance().convertColor(a)},
                {(float)p.larg, (float)p.larg, Renderer::getInstance().convertColor(a)}
            };
            _buffers[i] = Renderer::getInstance().createVertexBuffer(4, 0, v);
            i++;
        }
    }

    void ParticleGenerator::rend(){
        Renderer::getInstance().setDeclaration(_declaration);
        for(unsigned int i = 0; i<_particles.size(); ++i){
            Particle &p = _particles[i];
            Renderer::getInstance().translate(MAT_MODELVIEW, glm::vec3(p.x, p.y, p.z));

            Renderer::getInstance().setVertexBuffer(0, _buffers[i]);

            Renderer::getInstance().drawPrimitives(PT_TRIANGLESTRIP, 0, 2);

            Renderer::getInstance().translate(MAT_MODELVIEW, glm::vec3(-p.x, -p.y, -p.z));
        }
        updatePosition();
    }

    void ParticleGenerator::updatePosition(){
        for(Particle& p : _particles){
                if(p.life > 0){
                    p.x += p.xi;
                    p.y += p.yi;
                    p.z += p.zi;
                    p.xi += p.xg;
                    p.yi += p.yg;
                    p.zi += p.zg;
                    p.life -= p.fade;
                }else{
                    p.x = 0;
                    p.y = 0;
                    p.z = 0;
                    p.xi = RandGenerator::getInstance().rand(-0.3, 0.3);
                    p.yi = RandGenerator::getInstance().rand(-0.3, 0.3);
                    p.zi = RandGenerator::getInstance().rand(-0.3, 0.3);
                    p.fade = RandGenerator::getInstance().rand(0.001, 0.01);
                    p.life = 1;
                }
        }

    }

    ParticleGenerator::~ParticleGenerator(){}


}
}
