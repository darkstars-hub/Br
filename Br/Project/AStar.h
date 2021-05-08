//!-----------------------------------------------------
//! @file : AStar.h
//! @brief : �p�X�v�Z����
//! @date : 2020/06/06
//!-----------------------------------------------------


#ifndef BR_ASTAR_H
#define BR_ASTAR_H

#include	"Path.h"

namespace br {

struct AStarData : public PathData {
    //! �����ς݃t���O
    bool is_closed = false;
    //! �����\��t���O
    bool is_open = false;
    //! �T���n�_����̃R�X�g  �v�Z���ɓ����
    int from_start = 0;
    //! �q���[���X�e�B�b�N�R�X�g �v�Z���ɓ����
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
    //! @brief : �o�H�T��
    //! @param : [in](br::Tile* tile) �J�n
    //! @param : [in](br::Tile* destination) �Ώ�
    //! @param : [out](std::vector<br::Tile*>& path) �T���J�n�ʒu����I���ʒu�܂ł̌o�H
    //! @return : ���B�\�ł���Ȃ�true
    //!-----------------------------------------------------
    virtual bool ConputePath(br::Tile* tile, br::Tile* destination, std::vector<br::PathDataPointer>& path) override;
private:
protected:
    //!-----------------------------------------------------
    //! @brief : �o�H����
    //! @param : [in](br::Tile* tile) �e��������Tile
    //! @param : [in](std::vector<AStarDataPointer>& list) �T�����X�g
    //! @param : [out](std::vector<br::Tile*>& path) �e�܂ł̌o�H
    //! @return : none
    //!-----------------------------------------------------
    void GeneratePath(br::AStarDataPointer tile, std::vector<AStarDataPointer>& list, std::vector<br::PathDataPointer>& path);
    //!-----------------------------------------------------
    //! @brief : �^�C�����I�[�v�����X�g�̐擪�ɑ}���� AStar����ݒ肷��
    //! @param : [in](br::Tile* tile) �擪�ɑ}������Tile
    //! @param : [in](br::Tile* parent) �擪�ɑ}������Tile�̐e(�O�̃^�C��=current)
    //! @param : [in](br::Tile* destination) �ڕW�n�_
    //! @param : [out](std::vector<br::Tile*>& open_list) �I�[�v�����X�g
    //! @return : none
    //!-----------------------------------------------------
    void InsertOpenList(br::AStarDataPointer tile, br::AStarDataPointer parent,
                        br::Tile* destination, std::vector<br::AStarDataPointer>& open_list);
    //!-----------------------------------------------------
    //! @brief : �q���[���X�e�B�b�N�v�Z
    //! @param : [in](Tile* tile) �ʒu
    //! @param : [in](Tile* destination) �Ώ�
    //! @return : �q���[���X�e�B�b�N
    //!-----------------------------------------------------
    //int ConputeHeuristic(br::AStarDataPointer position, br::Tile* destination);
    float ConputeHeuristic(br::AStarDataPointer position, br::Tile* destination);
};

}
#endif // !BR_ASTAR_H