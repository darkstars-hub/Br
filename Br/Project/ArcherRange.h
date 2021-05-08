//!-----------------------------------------------------
//! @file : ArcherRange.h
//! @brief : �|���j�b�g�̈ړ��͈�
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
    void SearchMovePoints(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range);
public:
    ArcherRange(br::Stage* ptr);

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
#endif // !BR_ARCHER_RANGE_H