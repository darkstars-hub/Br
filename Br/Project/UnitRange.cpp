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

    if (0 <= move) { // ���ɒN�����̋���Ƃ���͍s��ɂł��Ȃ�
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
        // ���ׂ�^�C���̏�Ƀ��j�b�g������Ƃ��A
        if (unit && tile->GetOnUnit() && // ���̃��j�b�g���T���J�n�n�_�ɂ��郆�j�b�g�ƈႤ�`�[���Ȃ�ʂ�Ȃ�
            unit->GetTeam() != tile->GetOnUnit()->GetTeam()) {
            continue;
        } // if
        this->Search(a, move, range);
        if (move - a->GetCost() <= 0) { // �ړ��s�\�Ȓn�_�ɗאڂ��Ă���
            //(*(range.end() - 1))->_bound = true;
        } // if
    } // for
}

void br::UnitRange::ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) {
      // �擪�͒T���J�n�n�_
    _ASSERT_EXPR(range.empty(), L"��łȂ�");
    auto t = std::make_shared<RangeData>(tile);
    range.push_back(t);

    // ������Ƃ���͈ړ���ɂł���
    this->SearchAdjacents(tile, move, range);

    // range�̒��ɂ��������ʂȂ��̂�����
    std::sort(range.begin(), range.end());
    range.erase(std::unique(range.begin(), range.end()), range.end());
}