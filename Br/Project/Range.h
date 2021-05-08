//!-----------------------------------------------------
//! @file : Range.h
//! @brief : 範囲計算部分
//! @date : 2020/06/06
//!-----------------------------------------------------


#ifndef BR_RANGE_H
#define BR_RANGE_H

#include "Path.h"

namespace br {

struct RangeData {
    //! 元のタイル情報
    Tile* _tile = nullptr;
    //! 足跡 移動範囲表示用
    int _last_move = 0;
    //! 移動不可能な地点に隣接している
    //bool _bound = false;

    RangeData(br::Tile* tile) {
        _tile = tile;
        _last_move = 0;
    }
};
using RangeDataPointer = std::shared_ptr<RangeData>;

class IRangeAlgorithm {
public:
    //!-----------------------------------------------------
    //! @brief : 移動可能範囲探索
    //! @param : [in](br::Tile* tile) 開始
    //! @param : [in](int move) 残りの移動可能数
    //! @param : [out](std::vector<br::Tile*>& path) 探索開始位置から終了位置までの経路
    //! @return : none
    //!-----------------------------------------------------
    virtual void ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& path) = 0;
};

class Range : public IRangeAlgorithm {
private:
protected:
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
    void SearchAdjacents(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range);
public:
//protected:
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
#endif // !BR_ASTAR_H