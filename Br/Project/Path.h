//!-----------------------------------------------------
//! @file : Path.h
//! @brief : �p�X�v�Z����
//! @date : 2020/06/06
//!-----------------------------------------------------


#ifndef BR_PATH_H
#define BR_PATH_H


#include <Mof.h>
#include "Tile.h"

namespace br {

struct PathData {
    //! ���̃^�C�����
    Tile* _tile = nullptr;
    //! ���ǂ����o�H�̂P�O�̃^�C��(�e)
    std::weak_ptr<br::PathData> parent;
};
using PathDataPointer = std::shared_ptr<PathData>;

class IPathAlgorithm {
public:
    //!-----------------------------------------------------
    //! @brief : �o�H�T��
    //! @param : [in](br::Tile* tile) �J�n
    //! @param : [in](br::Tile* destination) �Ώ�
    //! @param : [out](std::vector<br::Tile*>& path) �T���J�n�ʒu����I���ʒu�܂ł̌o�H
    //! @return : ���B�\�ł���Ȃ�true
    //!-----------------------------------------------------
    virtual bool ConputePath(br::Tile* tile, br::Tile* destination, std::vector<br::PathDataPointer>& path) = 0;
};
}
#endif // !BR_PATH_H