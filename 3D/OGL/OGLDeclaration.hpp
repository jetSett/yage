#ifndef OGLDECLARATION_HPP
#define OGLDECLARATION_HPP

#include <vector>

#include "../Declaration.hpp"

namespace Graphics{
namespace D3{

    class OGLDeclaration : public Declaration
    {
        public:
            struct Element{
                ElementUsage usage;
                ElementType type;
                unsigned int offset;
            };
            typedef std::vector<Element> ElementArray;
            typedef std::vector<ElementArray> ElementMatrix;

            OGLDeclaration();
            virtual ~OGLDeclaration();

            void addElement(unsigned int stream, const Element& elem);

            const ElementArray& getStreamElements(unsigned int stream) const;
        private:
            ElementMatrix _elements;
    };
}
}

#endif // OGLDECLARATION_HPP
