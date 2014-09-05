#include <glm/gtc/type_ptr.hpp>
#include "OGL2Renderer.hpp"
#include "OGL2Buffer.hpp"
#include "Window.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <Cg/cgGL.h>
#include <Memory/NewInc.hpp>


#define BUFFER_OFFSET(n) ((char*)NULL + (n))

namespace Graphics {
namespace D3{

    template<class T>
    inline void loadExtension(T& proc, const char* nom) {
        const unsigned char* unom = reinterpret_cast<const unsigned char*>(nom);
        if(!(proc = reinterpret_cast<T>(glXGetProcAddress(unom))))
            throw OGLException(std::string("wglGetProcAddress : ") + nom, "loadExtension");
    }

    #define LOAD_EXTENSION(nom) loadExtension(nom, #nom);

    #define CHECK_EXTENSION(nom) if(!checkExtension(nom)) throw OGLException(#nom, "checkExtension");

    OGL2Renderer::OGL2Renderer() {
        _extensions = "";
    }

    OGL2Renderer::~OGL2Renderer() {
        for(auto p : _contexts){
            SDL_GL_DeleteContext(p.second);
        }
    }

    void OGL2Renderer::checkCaps(){
        _capabilities[CAP_HW_MIPMAPPING] = checkExtension("GL_SGIS_generate_mipmap");
        _capabilities[CAP_DXT_COMPRESSION] = checkExtension("GL_ARB_texture_compression")
                                            && checkExtension("GL_EXT_texture_compression_s3tc");
        _capabilities[CAP_TEX_NON_POWER_2] = checkExtension("GL_ARB_texture_non_power_of_two");
    }

    void OGL2Renderer::initialize(WindowPtr ptr) {

        setContext();

        SDL_GLContext cont = SDL_GL_CreateContext(ptr->getSDLWindow());
        if(cont == 0){
            throw ExternError("SDL2 & Opengl", SDL_GetError());
        }
        _contexts[ptr->getTitle()] = cont;

        _extensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));

        loadExtensions();
        checkCaps();

        _vertexShadProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
        _pixelShadProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
        cgGLSetOptimalOptions(_vertexShadProfile);
        cgGLSetOptimalOptions(_pixelShadProfile);

        _vertexShadOptions[0] = nullptr;
        _pixelShadOptions[0] = nullptr;

        glEnable(GL_DEPTH_TEST);
//        glEnable(GL_CULL_FACE);
        glEnable(GL_STENCIL);
        glFrontFace(GL_CCW);

        glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
        glClearDepth(1.0f);
        glClearStencil(0x00);
        glShadeModel(GL_SMOOTH);

        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    }

    PFNGLBINDBUFFERARBPROC    OGL2Renderer::glBindBufferARB;
    PFNGLDELETEBUFFERSARBPROC OGL2Renderer::glDeleteBuffersARB;
    PFNGLGENBUFFERSARBPROC    OGL2Renderer::glGenBuffersARB;
    PFNGLBUFFERDATAARBPROC    OGL2Renderer::glBufferDataARB;
    PFNGLBUFFERSUBDATAARBPROC OGL2Renderer::glBufferSubDataARB;
    PFNGLGETBUFFERSUBDATAARBPROC OGL2Renderer::glGetBufferSubDataARB;
    PFNGLMAPBUFFERARBPROC OGL2Renderer::glMapBufferARB;
    PFNGLUNMAPBUFFERARBPROC OGL2Renderer::glUnmapBufferARB;
    PFNGLACTIVETEXTUREARBPROC OGL2Renderer::glActiveTextureARB;
    PFNGLCLIENTACTIVETEXTUREARBPROC OGL2Renderer::glClientActiveTextureARB;
    PFNGLCOMPRESSEDTEXIMAGE2DARBPROC OGL2Renderer::glCompressedTexImage2DARB;
    PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC OGL2Renderer::glCompressedTexSubImage2DARB;

//    PFNWGLCHOOSEPIXELFORMATARBPROC OGLRenderer::wglChoosePixelFormatARB;
//    PFNWGLCREATEPBUFFERARBPROC OGLRenderer::wglCreatePBufferARB;
//    PFNWGLGETPBUFFERDCARBPROC OGLRenderer::wglGetPBufferDCARB;
//    PFNWGLRELEASEPBUFFERDCARBPROC OGLRenderer::wglReleasePBufferARB;
//    PFNWGLDESTROYPBUFFERARBPROC OGLRenderer::wglDestroyPBufferARB;
//    PFNWGLQUERYPBUFFERARBPROC OGLRenderer::wglQueryPBufferARB;

    bool OGL2Renderer::checkExtension(const std::string& ext) {
        return _extensions.find(ext) != std::string::npos;
    }

    void OGL2Renderer::loadExtensions() {
        CHECK_EXTENSION("GL_ARB_vertex_buffer_object");
        CHECK_EXTENSION("GL_ARB_multitexture");

        LOAD_EXTENSION(glBindBufferARB);
        LOAD_EXTENSION(glDeleteBuffersARB);
        LOAD_EXTENSION(glGenBuffersARB);
        LOAD_EXTENSION(glBufferDataARB);
        LOAD_EXTENSION(glBufferSubDataARB);
        LOAD_EXTENSION(glGetBufferSubDataARB);
        LOAD_EXTENSION(glMapBufferARB);
        LOAD_EXTENSION(glUnmapBufferARB);
        LOAD_EXTENSION(glActiveTextureARB);
        LOAD_EXTENSION(glClientActiveTextureARB);
        LOAD_EXTENSION(glCompressedTexImage2DARB);
        LOAD_EXTENSION(glCompressedTexSubImage2DARB);
//        LOAD_EXTENSION(wglChoosePixelFormatARB);
//        LOAD_EXTENSION(wglCreatePBufferARB);
//        LOAD_EXTENSION(wglGetPBufferDCARB);
//        LOAD_EXTENSION(wglReleasePBufferARB);
//        LOAD_EXTENSION(wglDestroyPBufferARB);
//        LOAD_EXTENSION(wglQueryPBufferARB);
    }

    void OGL2Renderer::setContext(){
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    }

    void OGL2Renderer::pushMatrix(MatrixType t) {
        if(t >= MAT_TEXTURE_0)
            glActiveTextureARB(GL_TEXTURE0_ARB + t - MAT_TEXTURE_0);
        glMatrixMode(OGLEnum::Get(t));
        glPushMatrix();
    }

    void OGL2Renderer::popMatrix(MatrixType t) {
        if(t >= MAT_TEXTURE_0)
            glActiveTextureARB(GL_TEXTURE0_ARB + t - MAT_TEXTURE_0);
        glMatrixMode(OGLEnum::Get(t));
        glPopMatrix();
    }

    void OGL2Renderer::setMatrix(MatrixType t, const glm::mat4& mat){
        if(t >= MAT_TEXTURE_0)
            glActiveTextureARB(GL_TEXTURE0_ARB + t - MAT_TEXTURE_0);
        glMatrixMode(OGLEnum::Get(t));
        glLoadMatrixf(glm::value_ptr(mat));
    }

    void OGL2Renderer::setMatrixMult(MatrixType t, const glm::mat4& mat){
        if(t >= MAT_TEXTURE_0)
            glActiveTextureARB(GL_TEXTURE0_ARB + t - MAT_TEXTURE_0);
        glMatrixMode(OGLEnum::Get(t));
        glMultMatrixf(glm::value_ptr(mat));
    }

    void OGL2Renderer::rotate(MatrixType t, const glm::vec4& v){
        if(t >= MAT_TEXTURE_0)
            glActiveTextureARB(GL_TEXTURE0_ARB + t - MAT_TEXTURE_0);
        glMatrixMode(OGLEnum::Get(t));
        glRotated(v.x, v.y, v.z, v.w);
    }
    void OGL2Renderer::translate(MatrixType t, const glm::vec3& v){
        if(t >= MAT_TEXTURE_0)
            glActiveTextureARB(GL_TEXTURE0_ARB + t - MAT_TEXTURE_0);
        glMatrixMode(OGLEnum::Get(t));
        glTranslated(v.x, v.y, v.z);
    }

    void OGL2Renderer::scale(MatrixType t, const glm::vec3& v){
        if(t >= MAT_TEXTURE_0)
            glActiveTextureARB(GL_TEXTURE0_ARB + t - MAT_TEXTURE_0);
        glMatrixMode(OGLEnum::Get(t));
        glScaled(v.x, v.y, v.z);
    }

    void OGL2Renderer::getMatrix(MatrixType t, glm::mat4& m) const {
        if(t >= MAT_TEXTURE_0)
            glActiveTextureARB(GL_TEXTURE0_ARB + t - MAT_TEXTURE_0);
        float ptr[16];
        glGetFloatv(OGLEnum::Get(t), ptr);
        m = glm::mat4x4( ptr[0], ptr[1], ptr[2], ptr[3],
                         ptr[4], ptr[5], ptr[6], ptr[7],
                         ptr[8], ptr[9], ptr[10], ptr[11],
                          ptr[12], ptr[13], ptr[14], ptr[15]);
    }

    void OGL2Renderer::beginScene() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void OGL2Renderer::endScene() {
        const WindowsMap& map = WindowsManager::getInstance().getWindows();
        for(auto p : map){
            p.second->swapBuffer();
        }
    }

    unsigned long OGL2Renderer::convertColor(const Color& col) const{
        return col.toRBGA();
    }

    void OGL2Renderer::setPerspective(float fov, float ratio, float znear, float zfar){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov, ratio, znear, zfar);
    }

    void OGL2Renderer::setProjection(double l, double r, double b, double t){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(l, r, b, t);
    }

    void OGL2Renderer::setLookAt(const glm::vec3& eyes, const glm::vec3& center, const glm::vec3& up){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eyes.x, eyes.y, eyes.z, center.x, center.y, center.z, up.x, up.y, up.z);
    }

    TextureBase* OGL2Renderer::createTexture(const std::string& name, const glm::ivec2 size, PixelFormat format, unsigned long flags){
        unsigned int text;
        glGenTextures(1, &text);
        glBindTexture(GL_TEXTURE_2D, text);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        int nbMipmaps = flags & TEX_NOMIPMAP ? getMipLevels(size.x, size.y) : 0;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, nbMipmaps);

        if(nbMipmaps > 0 and hasCapability(CAP_HW_MIPMAPPING))
            glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);

        int w = size.x;
        int h = size.y;

        for(int i = 0; i <= nbMipmaps; ++i){
            glTexImage2D(GL_TEXTURE_2D, i, OGLEnum::Get(format).internal,
                         w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            if(w > 1) w /= 2;
            if(h > 1) h /= 2;
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        return new OGLTexture(name, size, format, nbMipmaps > 0, hasCapability(CAP_HW_MIPMAPPING), text);

    }

    void OGL2Renderer::setTexture(unsigned int unit, const TextureBase* text){
        glActiveTextureARB(GL_TEXTURE0_ARB + unit);
        const OGLTexture* oglText = static_cast<const OGLTexture*>(text);

        int a = oglText->getOGLTexture();

        if(text){
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, a);
        }else{
            glDisable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    BufferBase* OGL2Renderer::createVB(unsigned long size, unsigned long stride, unsigned long flags) const{
        unsigned int vb = 0;
        glGenBuffersARB(1, &vb);

        glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb);
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, size*stride, nullptr, OGLEnum::BufferFlag(flags));
        return new OGL2VertexBuffer(size, vb);
    }

    BufferBase* OGL2Renderer::createIB(unsigned long size, unsigned long stride, unsigned long flags) const{
        unsigned int vb = 0;
        glGenBuffersARB(1, &vb);

        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vb);
        glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, size*stride, nullptr, OGLEnum::BufferFlag(flags));
        return new OGL2IndexBuffer(size, vb);
    }

    DeclarationPtr OGL2Renderer::createDeclaration(const DeclarationElement* first, std::size_t count) const{
        OGLDeclaration* declaration = new OGLDeclaration;

        std::vector<int> offset(count, 0);
        for(const DeclarationElement* elt = first; elt<first+count; ++elt){
            OGLDeclaration::Element current;
            current.usage = elt->usage;
            current.type = elt->type;
            current.offset = offset[elt->stream];

            declaration->addElement(elt->stream, current);
            static const unsigned int size[] = {4, 8, 12, 16, 4};
            offset[elt->stream] += size[elt->type];
        }

        return declaration;
    }

    void OGL2Renderer::setVB(unsigned int stream, const BufferBase* buf, unsigned long stride,
                            unsigned long minVertex, unsigned long){
        const OGL2VertexBuffer* vertexBuffer = static_cast<const OGL2VertexBuffer*>(buf);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertexBuffer->getBuffer());

        static const unsigned int size[] ={1, 2, 3, 4, 4};
        static const unsigned int type[] = {GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE};

        const OGLDeclaration::ElementArray& streamDesc = _currentDeclaration->getStreamElements(stream);
        for(OGLDeclaration::Element elem : streamDesc){
            switch(elem.usage){
            case ELT_USAGE_POSITION:
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(size[elem.type], type[elem.type], stride, BUFFER_OFFSET(elem.offset+minVertex*stride));
                break;
            case ELT_USAGE_NORMAL:
                glEnableClientState(GL_NORMAL_ARRAY);
                glNormalPointer(type[elem.type], stride, BUFFER_OFFSET(elem.offset+minVertex*stride));
                break;
            case ELT_USAGE_DIFUSE:
                glEnableClientState(GL_COLOR_ARRAY);
                glColorPointer(size[elem.type], type[elem.type], stride, BUFFER_OFFSET(elem.offset+minVertex*stride));
                break;
            case ELT_USAGE_TEXCOORD0:
            case ELT_USAGE_TEXCOORD1:
            case ELT_USAGE_TEXCOORD2:
            case ELT_USAGE_TEXCOORD3:
                glActiveTextureARB(GL_TEXTURE0_ARB + (elem.usage-ELT_USAGE_TEXCOORD0));
                glEnable(GL_TEXTURE_2D);
                glClientActiveTextureARB(GL_TEXTURE0_ARB + (elem.usage-ELT_USAGE_TEXCOORD0));
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glTexCoordPointer(size[elem.type], type[elem.type], stride, BUFFER_OFFSET(elem.offset+minVertex*stride));
                break;
            }
        }
    }

    void OGL2Renderer::setIB(const BufferBase* buf, unsigned long stride){
        const OGL2IndexBuffer* indexBuffer = static_cast<const OGL2IndexBuffer*>(buf);
        glEnableClientState(GL_INDEX_ARRAY);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, indexBuffer->getBuffer());

        _indexStride = stride;
    }

    void OGL2Renderer::setDeclaration(const Declaration* decl){
        glColor4f(1, 1, 1, 1);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        for(int i = 0; i<4; ++i){
            glActiveTextureARB(GL_TEXTURE0_ARB + i);
            glDisable(GL_TEXTURE_2D);
        }
        _currentDeclaration = static_cast<const OGLDeclaration*>(decl);
    }

    void OGL2Renderer::drawPrimitives(PrimitiveType type, unsigned long first, unsigned long count) const{
        switch(type){
        case PT_LINELIST:
            glDrawArrays(GL_LINES, first, count*2);
            break;
        case PT_LINESTRIP:
            glDrawArrays(GL_LINE_STRIP, first, count+1);
            break;
        case PT_POINTLIST:
            glDrawArrays(GL_POINTS, first, count);
            break;
        case PT_TRIANGLEFAN:
            glDrawArrays(GL_TRIANGLE_FAN, first, count+1);
            break;
        case PT_TRIANGLELIST:
            glDrawArrays(GL_TRIANGLES, first, count*3);
            break;
        case PT_TRIANGLESTRIP:
            glDrawArrays(GL_TRIANGLE_STRIP, first, count+2);
            break;
        }
    }

    void OGL2Renderer::drawIndexedPrimitives(PrimitiveType type, unsigned long first, unsigned long count) const{

        unsigned long indiceType = (_indexStride == 2?GL_UNSIGNED_SHORT:GL_UNSIGNED_INT);
        const void* offset = BUFFER_OFFSET(first*_indexStride);

        switch(type){
        case PT_LINELIST:
            glDrawElements(GL_LINES, count*2, indiceType, offset);
            break;
        case PT_LINESTRIP:
            glDrawElements(GL_LINE_STRIP, count+1, indiceType, offset);
            break;
        case PT_POINTLIST:
            glDrawElements(GL_POINTS, count, indiceType, offset);
            break;
        case PT_TRIANGLEFAN:
            glDrawElements(GL_TRIANGLE_FAN, count+1, indiceType, offset);
            break;
        case PT_TRIANGLELIST:
            glDrawElements(GL_TRIANGLES, count*3, indiceType, offset);
            break;
        case PT_TRIANGLESTRIP:
            glDrawElements(GL_TRIANGLE_STRIP, count+2, indiceType, offset);
            break;
        }
    }

    ShaderBase* OGL2Renderer::createShader(const std::string& name, CGprogram prog, ShaderType type) const{
        return new OGLShader(name, prog, type);
    }

    void OGL2Renderer::setPixelShader(const ShaderBase* shad){
        const OGLShader* prog = static_cast<const OGLShader*>(shad);
        if(prog){
            if(prog->getType() == SHAD_VERT)
                throw PersoException("Bad type of shader loaded");
            cgGLLoadProgram(prog->getProgram());
            cgGLEnableProfile(_pixelShadProfile);
        }else{
            cgGLDisableProfile(_pixelShadProfile);
            cgGLUnbindProgram(_pixelShadProfile);
        }
    }

    void OGL2Renderer::setVertexShader(const ShaderBase* shad){
        const OGLShader* prog = static_cast<const OGLShader*>(shad);
        if(prog){
            if(prog->getType() == SHAD_PIX)
                throw PersoException("Bad type of shader loaded");
            cgGLLoadProgram(prog->getProgram());
            cgGLEnableProfile(_vertexShadProfile);
        }else{
            cgGLDisableProfile(_vertexShadProfile);
            cgGLUnbindProgram(_vertexShadProfile);
        }
    }

    void OGL2Renderer::setBackgroudColor(const Color& c){
        glClearColor(c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha());
    }

}
}
