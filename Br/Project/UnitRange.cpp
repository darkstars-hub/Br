#include "UnitRange.h"


void br::UnitRange::Search(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
    auto it = std::find_if(range.begin(), range.end(),
                           [&](RangeDataPointer ap) {return ap->_tile == tile; });
    RangeDataPointer add;
    if (it != range.end()) {
        add = *it;
        if (move <= add->_last_move) {
            return;
        } // if
    } // if
    else {
        add = std::make_shared<RangeData>(tile);
    }

    add->_last_move = move;
    move -= tile->GetCost();

    if (0 <= move) { // 既に誰かがの居るところは行先にできない
        if (add->_tile->GetOnUnit() == nullptr) {
            range.push_back(add);
        } // if
        this->SearchAdjacents(tile, move, range);
    } // if
}

void br::UnitRange::SearchAdjacents(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
    if (move <= 0) {
        return;
    } // if
    auto unit = (*range.begin())->_tile->GetOnUnit();
    for (auto a : tile->GetAdjacents()) {
        if (!a) {
            continue;
        } // if
        // 調べるタイルの上にユニットがいるとき、
        if (unit && tile->GetOnUnit() && // そのユニットが探索開始地点にいるユニットと違うチームなら通れない
            unit->GetTeam() != tile->GetOnUnit()->GetTeam()) {
            continue;
        } // if
        this->Search(a, move, range);
        if (move - a->GetCost() <= 0) { // 移動不可能な地点に隣接している
            //(*(range.end() - 1))->_bound = true;
        } // if
    } // for
}

void br::UnitRange::ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
      // 先頭は探索開始地点
    _ASSERT_EXPR(range.empty(), L"空でない");
    auto t = std::make_shared<RangeData>(tile);
    range.push_back(t);

    // 今いるところは移動先にできる
    this->SearchAdjacents(tile, move, range);

    // rangeの中にいくつか無駄なものがある
    std::sort(range.begin(), range.end());
    range.erase(std::unique(range.begin(), range.end()), range.end());
}