#ifndef VRENDERER_H
#define VRENDERER_H

#include <cassert>

#include <SDL2/SDL.h>
#include <Cg/cg.h>

#include <glm/glm.hpp>

#include "Enums.hpp"
#include "../Graphics/WindowsManager.hpp"
#include "TextureBase.hpp"
#include "Buffer.hpp"
#include "Declaration.hpp"
#include "Resources/ShaderBase.hpp"


/// \namespace Graphics
/// \brief Contain all the 3D engine

namespace Graphics{
class Color;
namespace D3{

    /**
        \class Renderer
        \brief The main class of the engine
        Manage everything which has to be displayed, and set what will be displayed on the screen/window
    **/
    class Renderer {
    public:
        virtual ~Renderer(){
            InputManager::getInstance().terminate();
        }
        virtual void initialize(WindowPtr) = 0;
        virtual void beginScene() = 0;
        virtual void endScene() = 0;

        virtual void pushMatrix(MatrixType) = 0;
        virtual void popMatrix(MatrixType) = 0;
        virtual void translate(MatrixType, const glm::vec3&) = 0;
        virtual void scale(MatrixType, const glm::vec3&) = 0;
        virtual void rotate(MatrixType, const glm::vec4&) = 0;
        virtual void getMatrix(MatrixType, glm::mat4&) const = 0;
        virtual void setMatrix(MatrixType, const glm::mat4&) = 0;
        virtual void setMatrixMult(MatrixType, const glm::mat4&) = 0;

        virtual void setPerspective(float fov, float ratio, float near, float far) = 0;
        virtual void setLookAt(const glm::vec3&, const glm::vec3&, const glm::vec3&) = 0;
        virtual void setProjection(double l, double r, double b, double t) = 0;

        virtual void setBackgroudColor(const Color&) = 0;

        virtual TextureBase* createTexture(const std::string& name, const glm::ivec2 size, PixelFormat format, unsigned long flags) = 0;
        virtual void setTexture(unsigned int unit, const TextureBase* text) = 0;

        virtual ShaderBase* createShader(const std::string& name, CGprogram prog, ShaderType type) const = 0;
        virtual void setVertexShader(const ShaderBase* shad) = 0;
        virtual void setPixelShader(const ShaderBase* shad) = 0;

        template<class T>
        Buffer<T> createVertexBuffer(unsigned long size, unsigned long flags, const T* data) const{
            Buffer<T> buffer(createVB(size, sizeof(T), flags));
            if(data)
                buffer.fill(data, size);
            return buffer;
        }
        template<class T>
        Buffer<T> createIndexBuffer(unsigned long size, unsigned long flags, const T* data) const{
            Buffer<T> buffer(createIB(size, sizeof(T), flags));
            if(data)
                buffer.fill(data, size);
            return buffer;
        }

        template<class T>
        void setVertexBuffer(unsigned int stream, const Buffer<T>& buf,
                             unsigned long minVertex = 0, unsigned long maxVertex = 0){
            setVB(stream, buf.getBuffer(), sizeof(T), minVertex, maxVertex ? : buf.getCount()-1);
        }
        template<class T>
        void setIndexBuffer(const Buffer<T>& buf){
            setIB(buf.getBuffer(), sizeof(T));
        }

        virtual void setDeclaration(const Declaration* decl) = 0;

        template<std::size_t N>
        DeclarationPtr createVertexDeclaration(const DeclarationElement (&elem)[N]) const{
            return createDeclaration(elem, N);
        }

        void showCursor(bool s){
//            s?SDL_ShowCursor(SDL_TRUE):SDL_ShowCursor(SDL_FALSE);
        }

        virtual void drawPrimitives(PrimitiveType type, unsigned long first, unsigned long count) const = 0;
        virtual void drawIndexedPrimitives(PrimitiveType type, unsigned long first, unsigned long count) const = 0;

        static void destroy();

        static void setInstance(Renderer*);

        static Renderer& getInstance();

        virtual unsigned long convertColor(const Color&) const = 0;

        bool hasCapability(Capabilities);

        CGprofile getShaderProfile(ShaderType t) const {
            return t==SHAD_PIX?_pixelShadProfile:_vertexShadProfile;
        }
        const char* const* getShaderOptions(ShaderType t) const{
            return t==SHAD_PIX?_pixelShadOptions:_vertexShadOptions;
        }

    private:
        static Renderer* _instance;

    protected:
        virtual BufferBase* createVB(unsigned long size, unsigned long stride, unsigned long flags = 0) const = 0;

        virtual BufferBase* createIB(unsigned long size, unsigned long stride, unsigned long flags = 0) const  = 0;

        virtual DeclarationPtr createDeclaration(const DeclarationElement* first, std::size_t count) const = 0;

        virtual void setVB(unsigned int stream, const BufferBase* buf, unsigned long stride, unsigned long minVertex,
                           unsigned long maxVertex) = 0;
        virtual void setIB(const BufferBase* buf, unsigned long stride) = 0;

        virtual void checkCaps() = 0;

        std::map<Capabilities, bool> _capabilities;

        CGprofile _pixelShadProfile;
        CGprofile _vertexShadProfile;

        const char* _pixelShadOptions[2];
        const char* _vertexShadOptions[2];
    };


}
}

#endif // VRENDERER_H
