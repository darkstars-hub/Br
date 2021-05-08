//!-----------------------------------------------------
//! @file : SightRange.h
//! @brief : ���j�b�g�̎��E�͈͌v�Z����
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
    //! @brief : �Ώۂ����F�ł��邩���ׂ�@���������ʂ�����
    //! @param : [in](br::Tile* tile) �Ώ�
    //! @param : [in](int move) �c��̒T���\��
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) �������ׂ��ʒu
    //! @return : none
    //!-----------------------------------------------------
    void Search(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range);
    //!-----------------------------------------------------
    //! @brief : �Ώۂɗאڂ���Tile���T���\�����ׂ�
    //! @param : [in](br::Tile* tile) �Ώ�
    //! @param : [in](int move) �c��̒T���\��
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) �������ׂ��ʒu
    //! @return : none
    //!-----------------------------------------------------
    void SearchAdjacents(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range);

    //!-----------------------------------------------------
    //! @brief : �T���ł��邩���ׂ�@���������ʂ�����
    //! @param : [in](br::Tile* tile) �Ώ�
    //! @param : [in](int move) �c��̈ړ��\��
    //! @param : [in](br::Unit unit) �����l
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) �������ׂ��ʒu
    //! @return : none
    //!-----------------------------------------------------
    //void Search(br::Tile* tile, int move, br::Unit* unit, std::vector<br::RangeDataPointer>& range);
    //!-----------------------------------------------------
    //! @brief : �Ώۂɗאڂ���Tile���ړ��\�����ׂ�
    //! @param : [in](br::Tile* tile) �Ώ�
    //! @param : [in](int move) �c��̈ړ��\��
    //! @param : [in](br::Unit unit) �����l
    //! @param : [out](std::vector<br::RangeDataPointer*>&range) �������ׂ��ʒu
    //! @return : none
    //!-----------------------------------------------------
    //void SearchAdjacents(br::Tile* tile, int move, br::Unit* unit, std::vector<br::RangeDataPointer>& range);
public:
    void ConputeRange(br::Tile* tile, int move, std::vector<br::RangeDataPointer>& range) override;
    //!-----------------------------------------------------
    //! @brief : �ړ��\�͈͒T��
    //! @param : [in](br::Tile* tile) �J�n
    //! @param : [in](int move) �c��̈ړ��\��
    //! @param : [in](br::Unit unit) �����l
    //! @param : [out](std::vector<br::RangeDataPointer*>& path) �͈�
    //! @return : none
    //!-----------------------------------------------------
//    void ConputeRange(br::Tile* tile, int move, br::Unit* unit, std::vector<br::RangeDataPointer>& range);
};
}
#endif // !BR_SIGHT_H