//!-----------------------------------------------------
//! @file : UnitPath.h
//! @brief : ユニットのパス計算部分
//! @date : 2020/06/27
//!-----------------------------------------------------


#ifndef BR_UNIT_PATH_H
#define BR_UNIT_PATH_H


#include "AStar.h"


namespace br {
class UnitPath : public br::AStar {
    using super = br::AStar;
public:
    bool ConputePath(br::Tile* tile, br::Tile* destination, std::vector<br::PathDataPointer>& path) override;
};
}
#endif // !BR_UNIT_PATH_H