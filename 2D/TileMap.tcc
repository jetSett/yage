namespace Graphics{
namespace D2{
    template<class Tile>
    TileMap<Tile>::TileMap(const std::vector<std::vector<Tile>>& map, SDL_Rect viewSize, ConvertFun fun) : _map(map),
                                                                                    _viewSize(viewSize), _convertFun(fun){
        _mapSize = {map.size(), map[0].size()};
        _shapeMap.resize(_mapSize.x, std::vector<ShapePtr>(_mapSize.y, nullptr));
        updateAll();
    }

    template<class Tile>
    TileMap<Tile>::~TileMap(){
    }

    template<class Tile>
    void TileMap<Tile>::rend(Window2DPtr win){
        for(int x = _viewSize.x; x<_viewSize.w; ++x){
            for(int y = _viewSize.y; y<_viewSize.h; ++y){
                win->addShape(_shapeMap[x][y]);
            }
        }
    }

    template<class Tile>
    void TileMap<Tile>::updateAll(){
        for(int x = _viewSize.x; x<_viewSize.w; ++x){
            for(int y = _viewSize.y; y<_viewSize.h; ++y){
                update(x, y);
            }
        }
    }

    template<class Tile>
    void TileMap<Tile>::update(int x, int y){
        ShapePtr ptr = _convertFun(_map[x][y], x, y, *this);
        _shapeMap[x][y] = ptr;
    }

    template<class Tile>
    void TileMap<Tile>::updateView(SDL_Rect v){
        _viewSize = v;
    }
}
}
