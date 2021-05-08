//!-----------------------------------------------------
//! @file : Path.h
//! @brief : パス計算部分
//! @date : 2020/06/06
//!-----------------------------------------------------


#ifndef BR_PATH_H
#define BR_PATH_H


#include <Mof.h>
#include "Tile.h"

namespace br {

struct PathData {
    //! 元のタイル情報
    Tile* _tile = nullptr;
    //! たどった経路の１つ前のタイル(親)
    std::weak_ptr<br::PathData> parent;
};
using PathDataPointer = std::shared_ptr<PathData>;

class IPathAlgorithm {
public:
    //!-----------------------------------------------------
    //! @brief : 経路探索
    //! @param : [in](br::Tile* tile) 開始
    //! @param : [in](br::Tile* destination) 対象
    //! @param : [out](std::vector<br::Tile*>& path) 探索開始位置から終了位置までの経路
    //! @return : 到達可能できるならtrue
    //!-----------------------------------------------------
    virtual bool ConputePath(br::Tile* tile, br::Tile* destination, std::vector<br::PathDataPointer>& path) = 0;
};
}
#endif // !BR_PATH_H