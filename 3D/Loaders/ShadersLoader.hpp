#ifndef SHADERLOADER_INC
#define SHADERLOADER_INC

#include <ResourcesMgr/Loaders.hpp>
#include "../Resources/ShaderBase.hpp"

/// \todo mettre tout à niveau.
/// \warning ne PAS inclure/utiliser ce fichier

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
