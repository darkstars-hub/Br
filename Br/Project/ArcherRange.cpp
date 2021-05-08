#include "ArcherRange.h"


//////////////////////////////////////////////////////////////
//✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖
//✖✖✖✖✖〇✖〇✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖
//✖✖✖✖〇✖✖✖〇✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖
//✖✖✖✖✖✖駒✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖
//✖✖✖✖〇✖✖✖〇✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖
//✖✖✖✖✖〇✖〇✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖
//✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖
//////////////////////////////////////////////////////////////
std::vector<def::Vector2i> br::ArcherRange::_move_offset = {
   {-1, -2},
   {-2, -1},
   {-2, +1},
   {-1, +2},

   {+1, +2},
   {+2, +1},
   {+2, -1},
   {+1, -2}
};


void br::ArcherRange::ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
        // 今いるところは移動先にできる
    this->SearchMovePoints(tile, move, range);

    // rangeの中にいくつか無駄なものがある
    std::sort(range.begin(), range.end());
    range.erase(std::unique(range.begin(), range.end()), range.end());

    // 誰かいると行けない
    auto it = std::remove_if(range.begin(), range.end(), [&](br::RangeDataPointer p) {
        return p->_tile->GetOnUnit() && p->_tile != tile;
    });
    range.erase(it, range.end());
}

void br::ArcherRange::Search(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
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
    if (0 <= move) {
        range.push_back(add);
        this->SearchMovePoints(tile, move, range);
    } // if
}

void br::ArcherRange::SearchMovePoints(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
    if (move <= 0) {
        return;
    } // if
    //for (auto a : tile->GetAdjacents()) {
    for (auto v : _move_offset) {
        auto pos = ut::ToGridPos(tile->GetPosition());
        auto t = _stage->GetTile(pos.col + v.x, pos.row + v.y);
        if (t != nullptr) {
            this->Search(t, move, range);
        } // if
    } // for
}

br::ArcherRange::ArcherRange(br::Stage* ptr) :
    _stage(ptr) {
/*
    _move_offset = {
        {-1, -2},
        {-2, -1},
        {-2, +1},
        {-1, +2},

        {+1, +2},
        {+2, +1},
        {+2, -1},
        {+1, -2}
    };
*/
}
