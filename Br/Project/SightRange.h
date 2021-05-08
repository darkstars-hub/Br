//!-----------------------------------------------------
//! @file : SightRange.h
//! @brief : ユニットの視界範囲計算部分
//! @date : 2020/07/02
//!-----------------------------------------------------


#ifndef BR_SIGHT_RANGE_H
#define BR_SIGHT_RANGE_H

#include "Range.h"
#include "Unit.h"


namespace br {
class SightRange : public IRangeAlgorithm {
private:
    //!-----------------------------------------------------
    //! @brief : 対象を視認できるか調べる　いくつか無駄がある
    //! @param : [in](br::Tile* tile) 対象
    //! @param : [in](int move) 残りの探索可能数
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) もう調べた位置
    //! @return : none
    //!-----------------------------------------------------
    void Search(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range);
    //!-----------------------------------------------------
    //! @brief : 対象に隣接するTileが探索可能か調べる
    //! @param : [in](br::Tile* tile) 対象
    //! @param : [in](int move) 残りの探索可能数
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) もう調べた位置
    //! @return : none
    //!-----------------------------------------------------
    void SearchAdjacents(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range);

    //!-----------------------------------------------------
    //! @brief : 探索できるか調べる　いくつか無駄がある
    //! @param : [in](br::Tile* tile) 対象
    //! @param : [in](int move) 残りの移動可能数
    //! @param : [in](br::Unit unit) 動く人
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) もう調べた位置
    //! @return : none
    //!-----------------------------------------------------
    //void Search(br::Tile* tile, int move, br::Unit* unit, std::vector<br::RangeDataPointer>& range);
    //!-----------------------------------------------------
    //! @brief : 対象に隣接するTileが移動可能か調べる
    //! @param : [in](br::Tile* tile) 対象
    //! @param : [in](int move) 残りの移動可能数
    //! @param : [in](br::Unit unit) 動く人
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) もう調べた位置
    //! @return : none
    //!-----------------------------------------------------
    //void SearchAdjacents(br::Tile* tile, int move, br::Unit* unit, std::vector<br::RangeDataPointer>& range);
public:
    void ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) override;
    //!-----------------------------------------------------
    //! @brief : 移動可能範囲探索
    //! @param : [in](br::Tile* tile) 開始
    //! @param : [in](int move) 残りの移動可能数
    //! @param : [in](br::Unit unit) 動く人
    //! @param : [out](std::vector<br::RangeDataPointer*>& path) 範囲
    //! @return : none
    //!-----------------------------------------------------
//    void ConputeRange(br::Tile* tile, int move, br::Unit* unit, std::vector<br::RangeDataPointer>& range);
};
}
#endif // !BR_SIGHT_H