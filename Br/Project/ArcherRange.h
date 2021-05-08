//!-----------------------------------------------------
//! @file : ArcherRange.h
//! @brief : 弓ユニットの移動範囲
//! @date : 2020/06/23
//!-----------------------------------------------------


#ifndef BR_ARCHER_RANGE_H
#define BR_ARCHER_RANGE_H


#include "Range.h"
#include "Helper.h"
#include "Stage.h"


namespace br {
class ArcherRange : public IRangeAlgorithm {
private:
    static std::vector<def::Vector2i> _move_offset;
    br::Stage* _stage;

    //!-----------------------------------------------------
    //! @brief : 対象に移動できるか調べる　いくつか無駄がある
    //! @param : [in](br::Tile* tile) 対象
    //! @param : [in](int move) 残りの移動可能数
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) もう調べた位置
    //! @return : none
    //!-----------------------------------------------------
    void Search(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range);
    //!-----------------------------------------------------
    //! @brief : 対象に隣接するTileが移動可能か調べる
    //! @param : [in](br::Tile* tile) 対象
    //! @param : [in](int move) 残りの移動可能数
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) もう調べた位置
    //! @return : none
    //!-----------------------------------------------------
    void SearchMovePoints(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range);
public:
    ArcherRange(br::Stage* ptr);

    //!-----------------------------------------------------
    //! @brief : 移動可能範囲探索
    //! @param : [in](br::Tile* tile) 開始
    //! @param : [in](int move) 残りの移動可能数
    //! @param : [out](std::vector<br::RangeDataPointer*>& path) 範囲
    //! @return : none
    //!-----------------------------------------------------
    void ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) override;
};
}
#endif // !BR_ARCHER_RANGE_H