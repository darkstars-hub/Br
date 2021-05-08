//!-----------------------------------------------------
//! @file : Range.h
//! @brief : �͈͌v�Z����
//! @date : 2020/06/06
//!-----------------------------------------------------


#ifndef BR_RANGE_H
#define BR_RANGE_H

#include "Path.h"

namespace br {

struct RangeData {
    //! ���̃^�C�����
    Tile* _tile = nullptr;
    //! ���� �ړ��͈͕\���p
    int _last_move = 0;
    //! �ړ��s�\�Ȓn�_�ɗאڂ��Ă���
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
    //! @brief : �ړ��\�͈͒T��
    //! @param : [in](br::Tile* tile) �J�n
    //! @param : [in](int move) �c��̈ړ��\��
    //! @param : [out](std::vector<br::Tile*>& path) �T���J�n�ʒu����I���ʒu�܂ł̌o�H
    //! @return : none
    //!-----------------------------------------------------
    virtual void ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& path) = 0;
};

class Range : public IRangeAlgorithm {
private:
protected:
    //!-----------------------------------------------------
    //! @brief : �ΏۂɈړ��ł��邩���ׂ�@���������ʂ�����
    //! @param : [in](br::Tile* tile) �Ώ�
    //! @param : [in](int move) �c��̈ړ��\��
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) �������ׂ��ʒu
    //! @return : none
    //!-----------------------------------------------------
    void Search(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range);
    //!-----------------------------------------------------
    //! @brief : �Ώۂɗאڂ���Tile���ړ��\�����ׂ�
    //! @param : [in](br::Tile* tile) �Ώ�
    //! @param : [in](int move) �c��̈ړ��\��
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) �������ׂ��ʒu
    //! @return : none
    //!-----------------------------------------------------
    void SearchAdjacents(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range);
public:
//protected:
    //!-----------------------------------------------------
    //! @brief : �ړ��\�͈͒T��
    //! @param : [in](br::Tile* tile) �J�n
    //! @param : [in](int move) �c��̈ړ��\��
    //! @param : [out](std::vector<br::RangeDataPointer*>& path) �͈�
    //! @return : none
    //!-----------------------------------------------------
    void ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) override;
};
}
#endif // !BR_ASTAR_H