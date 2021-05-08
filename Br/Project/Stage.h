//!-----------------------------------------------------
//! @file : Stage.h
//! @brief : ������Ֆ� �P���P�́u�ӂ��v������̂ŁA���ۂɂ�2��2�s���Ȃ�
//! @date : 2020/05/30
//!-----------------------------------------------------


#ifndef BR_STAGE_H
#define BR_STAGE_H


#include "Actor.h"

#include <memory>
#include <vector>
#include <Mof.h>
#include "../include/rapidjson/document.h"

#include "Helper.h"
#include "Common.h"
#include "Tile.h"


namespace br {
class Stage : public br::Actor {
    using super = br::Actor;
private:
    //! �X�e�[�W��̒n�`
    std::vector<br::Tile*> _tiles;
    //! �񁖍s
    Mof::Vector2 _tile_count;
    //! �^�C���̎�ނ̔ԍ� ������Q�Ƃ�Tile�͍쐬�����
    std::vector<int> _tile_id;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Scene* scene) ���݂̃V�[��
    //! @return : none
    //!-----------------------------------------------------
    Stage(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Stage();

    virtual br::ActorState GetState(void) const override;
    virtual Mof::CVector2 GetPosition(void) const override;

    //!-----------------------------------------------------
    //! @brief : �Ή�����^�C�����擾
    //! @param : [in](int col) ��
    //! @param : [in](int row) �s
    //! @param : [in](br::Direction = br::Direction::None) �^�C���̗אڕ���
    //! @return : ���̈ʒu�ɂ���^�C���̃|�C���^
    //!-----------------------------------------------------
    br::Tile* GetTile(int col, int row, br::Direction = br::Direction::CountMax);
    br::Tile* GetTile(def::Vector2i position, br::Direction = br::Direction::CountMax);
    //!-----------------------------------------------------
    //! @brief : �񐔂ƍs�����擾
    //! @param : [in](void) none 
    //! @return : �񐔂ƍs�����i�[���ꂽMof::CVector2
    //!-----------------------------------------------------
    Mof::CVector2 GetTileCount(void) const;

    //!-----------------------------------------------------
    //! @brief : �ǂݍ���
    //! @param : [in](const char* path) �p�X
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Load(const char* path) override;
    
    //!-----------------------------------------------------
    //! @brief : ������
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Initialize(const br::ActorBaseState& base) override;
    //!-----------------------------------------------------
    //! @brief : �X�V
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;
    //!-----------------------------------------------------
    //! @brief : ���
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Release(void) override;
};
}
#endif // !BR_STAGE_H