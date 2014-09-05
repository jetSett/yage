#ifndef OGL2RENDERER_HPP_INCLUDED
#define OGL2RENDERER_HPP_INCLUDED

#include <Utils/Singleton.hpp>
#include <Utils/Logger.hpp>

#include "../OGL/OGLUtils.hpp"
#include "../OGL/OGLTexture.hpp"
#include "../OGL/OGLDeclaration.hpp"
#include "../OGL/OGLShader.hpp"

#include "../Renderer.hpp"


namespace Graphics{
namespace D3{

    class OGL2Renderer : public Renderer, public Singleton<OGL2Renderer>{
    friend class Singleton<OGL2Renderer>;
    public:
        OGL2Renderer();
        ~OGL2Renderer();

        virtual void initialize(WindowPtr);
        virtual void beginScene();
        virtual void endScene();

        virtual void pushMatrix(MatrixType);
        virtual void popMatrix(MatrixType);
        virtual void translate(MatrixType, const glm::vec3&);
        virtual void scale(MatrixType, const glm::vec3&);
        virtual void rotate(MatrixType, const glm::vec4&);
        virtual void getMatrix(MatrixType, glm::mat4&) const;

        virtual void setLookAt(const glm::vec3&, const glm::vec3&, const glm::vec3&);
        virtual void setPerspective(float fov, float ratio, float near, float far);
        virtual void setProjection(double l, double r, double b, double t);
        virtual void setMatrix(MatrixType, const glm::mat4&);
        virtual void setMatrixMult(MatrixType, const glm::mat4&);

        virtual void setBackgroudColor(const Color& c);

        virtual TextureBase* createTexture(const std::string& name, const glm::ivec2 size, PixelFormat format, unsigned long flags);
        virtual void setTexture(unsigned int unit, const TextureBase* text);


        virtual void setDeclaration(const Declaration* decl);

        virtual void drawPrimitives(PrimitiveType type, unsigned long first, unsigned long count) const;
        virtual void drawIndexedPrimitives(PrimitiveType type, unsigned long first, unsigned long count) const;

        virtual ShaderBase* createShader(const std::string& name, CGprogram prog, ShaderType type) const;
        virtual void setPixelShader(const ShaderBase* shad);
        virtual void setVertexShader(const ShaderBase* shad);


        void setContext();

        static PFNGLBINDBUFFERARBPROC    glBindBufferARB;
        static PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
        static PFNGLGENBUFFERSARBPROC    glGenBuffersARB;
        static PFNGLBUFFERDATAARBPROC    glBufferDataARB;
        static PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
        static PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB;
        static PFNGLMAPBUFFERARBPROC glMapBufferARB;
        static PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;
        static PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
        static PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
        static PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB;
        static PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC glCompressedTexSubImage2DARB;
//        static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
//        static PFNWGLCREATEPBUFFERARBPROC wglCreatePBufferARB;
//        static PFNWGLGETPBUFFERDCARBPROC wglGetPBufferDCARB;
//        static PFNWGLRELEASEPBUFFERDCARBPROC wglReleasePBufferARB;
//        static PFNWGLDESTROYPBUFFERARBPROC wglDestroyPBufferARB;
//        static PFNWGLQUERYPBUFFERARBPROC wglQueryPBufferARB;
    private:
        virtual void checkCaps();

        virtual BufferBase* createVB(unsigned long size, unsigned long stride, unsigned long flags) const;
        virtual BufferBase* createIB(unsigned long size, unsigned long stride, unsigned long flags) const;
        virtual DeclarationPtr createDeclaration(const DeclarationElement* first, std::size_t count) const;

        virtual void setVB(unsigned int stream, const BufferBase* buf, unsigned long stride, unsigned long minVertex, unsigned long maxVertex);
        virtual void setIB(const BufferBase* buf, unsigned long stride);

        unsigned long convertColor(const Color&) const;
        bool checkExtension(const std::string&);
        void loadExtensions();

        const OGLDeclaration* _currentDeclaration;
        unsigned int _indexStride;

        std::string _extensions;

        std::map<std::string, SDL_GLContext> _contexts;
    };
}
}

#endif // OGLRENDERER_HPP_INCLUDED
