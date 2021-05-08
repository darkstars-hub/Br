//!-----------------------------------------------------
//! @file : CursorMoveComponent.h
//! @brief : �J�[�\�������ړ��@�\
//! @date : 2020/05/30
//!-----------------------------------------------------


#ifndef BR_CURSOR_MOVE_COMPONENT_H
#define BR_CURSOR_MOVE_COMPONENT_H


#include "UpdateComponent.h"

#include <Mof.h>

#include "Helper.h"
#include "Cursor.h"
#include "Tile.h"


namespace br {
class CursorMoveComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    Cursor* _cursor;
    DirectionWait* _wait;
    //! �I�����j�b�g�̈ړ��\�͈͂̊O�ֈړ����悤�Ƃ���ƈ���������
    bool _stop;
    //int _inner_range_count;
    //const int _inner_range_count_max;

    //!-----------------------------------------------------
    //! @brief : �����ʈړ�����
    //! @param : [in](br::Scene* scene) ���݂̃V�[��
    //! @param : [in](Mof::CVector2& pos) ���̒l�͕ύX�����
    //! @return : none
    //!-----------------------------------------------------
    void Move(const def::Vector2i m, Mof::CVector2& pos);
	void Move(br::Direction dir, Mof::CVector2& pos);
    void MoveOnAttackMode(Mof::CVector2& pos);

    //!-----------------------------------------------------
    //! @brief : ���ݎw�������Ă���Tile
    //! @param : [in](br::Actor* actor) ��������Actor
    //! @param : [in](br::Scene* scene) ���݂̃V�[��
    //! @return : ���A�����Ă���Tile
    //!-----------------------------------------------------
    br::Tile* GetSelectedTile(br::Actor* actor, br::Scene* scene);
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    CursorMoveComponent(Actor* owner, int priority = 100);
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](none)
    //! @return : none
    //!-----------------------------------------------------
    virtual ~CursorMoveComponent();

    //!-----------------------------------------------------
    //! @brief : �|�C���^�̐ݒ�
    //! @param : [in](class Cursor* ptr) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetCursor(br::Cursor* ptr);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](bool b) �~�܂�
    //! @return : none
    //!-----------------------------------------------------
    void SetStop(bool b);
    //!-----------------------------------------------------
    //! @brief : �|�C���^�̐ݒ�
    //! @param : [in](DirectionWait _wait) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void RegisterWait(DirectionWait* wait);
     //!-----------------------------------------------------
    //! @brief : �|�C���^�̐ݒ�
    //! @param : [in](Mof::CVector2* scroll) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    //void RegisterScroll(Mof::CVector2* scroll);

    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll);

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_CURSOR_MOVE_COMPONENT_H