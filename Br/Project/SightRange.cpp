#include "SightRange.h"

void br::SightRange::Search(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
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
    move--; // Ž‹ŠE‚ÍlEƒ‚ƒm‚ÉŽÕ‚ç‚ê‚È‚¢
    //move -= tile->GetCost();
    if (move <= 0) {
       // add->_bound = true;
    } // if
    if (0 <= move) {
        range.push_back(add);
        this->SearchAdjacents(tile, move, range);
    } // if
}

void br::SightRange::SearchAdjacents(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
    if (move <= 0) {
        return;
    } // if
    for (auto a : tile->GetAdjacents()) {
        if (a != nullptr) {
            this->Search(a, move, range);
        } // if
    } // for
}

void br::SightRange::ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
    this->SearchAdjacents(tile, move, range);

    std::sort(range.begin(), range.end());
    range.erase(std::unique(range.begin(), range.end()), range.end());
}