#ifndef SHADERLOADER_INC
#define SHADERLOADER_INC

#include <ResourcesMgr/Loaders.hpp>
#include "../Resources/ShaderBase.hpp"

class ShadersLoader : public Loader<ShaderBase>{
    public:
        ShadersLoader(ShaderType);
        ~ShadersLoader();
        virtual ShaderBase* loadFromFile(const std::string&);
        static void onError();
        private:
        ShaderType _type;
        CGcontext _context;
};

#endif // SHADERLOADER_INC
