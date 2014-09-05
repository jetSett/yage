#ifndef TILEMAP_H
#define TILEMAP_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <SDL2/SDL.h>

#include "Shape.hpp"

namespace Graphics{
namespace D2{

    template<class Tile>
    class TileMap
    {
        typedef std::function<ShapePtr(Tile, int, int, const TileMap<Tile>&)> ConvertFun;
        public:
            TileMap(const std::vector<std::vector<Tile>>& map, SDL_Rect viewSize, ConvertFun fun);
            ~TileMap();

            void rend(Window2DPtr);
            void update(int x, int y);
            void updateAll();

            void updateView(SDL_Rect view);

        private:
            const std::vector<std::vector<Tile>>& _map;
            std::vector<std::vector<ShapePtr>> _shapeMap;
            SDL_Rect _viewSize, _mapSize; // size in BLOCK !!!!!
            ConvertFun _convertFun;
    };

}
}

#include "TileMap.tcc"
#endif // TILEMAP_H
