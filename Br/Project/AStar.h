//!-----------------------------------------------------
//! @file : AStar.h
//! @brief : パス計算部分
//! @date : 2020/06/06
//!-----------------------------------------------------


#ifndef BR_ASTAR_H
#define BR_ASTAR_H

#include	"Path.h"

namespace br {

struct AStarData : public PathData {
    //! 調査済みフラグ
    bool is_closed = false;
    //! 調査予定フラグ
    bool is_open = false;
    //! 探索地点からのコスト  計算時に入れる
    int from_start = 0;
    //! ヒューリスティックコスト 計算時に入れる
    float heuristic = 0.0f;

    AStarData(br::Tile* tile) {
        _tile = tile;
        is_closed = false;
        is_open = false;
        parent.reset();
        from_start = 0;
        heuristic = 0;
    }
};
using AStarDataPointer = std::shared_ptr<AStarData>;

class AStar : public IPathAlgorithm {
public:
    //!-----------------------------------------------------
    //! @brief : 経路探索
    //! @param : [in](br::Tile* tile) 開始
    //! @param : [in](br::Tile* destination) 対象
    //! @param : [out](std::vector<br::Tile*>& path) 探索開始位置から終了位置までの経路
    //! @return : 到達可能できるならtrue
    //!-----------------------------------------------------
    virtual bool ConputePath(br::Tile* tile, br::Tile* destination, std::vector<br::PathDataPointer>& path) override;
private:
protected:
    //!-----------------------------------------------------
    //! @brief : 経路生成
    //! @param : [in](br::Tile* tile) 親を持ったTile
    //! @param : [in](std::vector<AStarDataPointer>& list) 探索リスト
    //! @param : [out](std::vector<br::Tile*>& path) 親までの経路
    //! @return : none
    //!-----------------------------------------------------
    void GeneratePath(br::AStarDataPointer tile, std::vector<AStarDataPointer>& list, std::vector<br::PathDataPointer>& path);
    //!-----------------------------------------------------
    //! @brief : タイルをオープンリストの先頭に挿入し AStar情報を設定する
    //! @param : [in](br::Tile* tile) 先頭に挿入するTile
    //! @param : [in](br::Tile* parent) 先頭に挿入するTileの親(前のタイル=current)
    //! @param : [in](br::Tile* destination) 目標地点
    //! @param : [out](std::vector<br::Tile*>& open_list) オープンリスト
    //! @return : none
    //!-----------------------------------------------------
    void InsertOpenList(br::AStarDataPointer tile, br::AStarDataPointer parent,
                        br::Tile* destination, std::vector<br::AStarDataPointer>& open_list);
    //!-----------------------------------------------------
    //! @brief : ヒューリスティック計算
    //! @param : [in](Tile* tile) 位置
    //! @param : [in](Tile* destination) 対象
    //! @return : ヒューリスティック
    //!-----------------------------------------------------
    //int ConputeHeuristic(br::AStarDataPointer position, br::Tile* destination);
    float ConputeHeuristic(br::AStarDataPointer position, br::Tile* destination);
};

}
#endif // !BR_ASTAR_H