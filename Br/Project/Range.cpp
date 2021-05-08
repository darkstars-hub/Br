#include "Range.h"

#include "Helper.h"

void br::Range::ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
//    先頭は探索開始地点
//    _ASSERT_EXPR(range.empty(),L"空でない");
//    auto t = std::make_shared<RangeData>(tile);
//    range.push_back(t);

    // 今いるところは移動先にできる
    this->SearchAdjacents(tile, move, range);

    // rangeの中にいくつか無駄なものがある
    std::sort(range.begin(), range.end());
    range.erase(std::unique(range.begin(), range.end()), range.end());

    // 誰かいると行けない
    //auto it = std::remove_if(range.begin(), range.end(), [&](br::RangeDataPointer p) {
    //    return p->_tile->GetOnUnit() && p->_tile != tile;
    //});
    //range.erase(it, range.end());
}

void br::Range::Search(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
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
    if (move <= 0) {
        //add->_bound = true;
    } // if
    if (0 <= move) {
        range.push_back(add);
        this->SearchAdjacents(tile, move, range);
    } // if
}

void br::Range::SearchAdjacents(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
    if (move <= 0) {
        return;
    } // if
    for (auto a : tile->GetAdjacents()) {
        if (a != nullptr) {
            this->Search(a, move, range);
        } // if
    } // for
}