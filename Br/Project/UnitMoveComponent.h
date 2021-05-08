//!-----------------------------------------------------
//! @file : UnitMoveComponent.h
//! @brief : Unit�����ړ��@�\
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_UNIT_MOVE_COMPONENT_H
#define BR_UNIT_MOVE_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "SelectableComponent.h"
#include "UnitStateComponent.h"
#include "RangeRenderComponent.h"
#include "PathRenderComponent.h"
#include "MotionComponent.h"
#include "PathComponent.h"
#include "RangeComponent.h"


namespace br {
class UnitMoveComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
protected:
    //! �����ׂ����ǂ���
    bool _is_move;
    //! �ړ����̃p�X�ԍ�
    int _move_no;
    //! �ړ���
    Mof::CVector2 _move;
    //! �ړ����x
    const Mof::CVector2 _speed;
    //! �I�����擾
    br::SelectableComponent* _select;
    //! ��Ԏ擾
    br::UnitStateComponent* _state;
    //! �o�H
    br::PathComponent* _path;
    //! �ړ��\�͈�
    br::RangeComponent* _range;
    //! ���[�V������ύX����
    br::MotionComponent* _motion;
    //! �U���͈͂�ݒ肷��
   class UnitAttackComponent* _attack;
   //! ���E��ݒ肷��
   class UnitSightComponent* _sight;
    //! �ړ��O�̈ʒu
    Mof::CVector2 _prev_position;
    //! �ړ��ړI�n
    br::Tile* _destination;
    //! ���j�b�g�������Ă������
    br::Direction _front_direction;

    void ReConputeRange(void);
    void Move(br::Direction d);
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    UnitMoveComponent(Actor* owner, int priority = 100);
    virtual ~UnitMoveComponent();


    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](br::Tile* ptr) none
    //! @return : �ړ��ړI�n�̐ݒ�
    //!-----------------------------------------------------
    void SetDestination(br::Tile* ptr);

    //!-----------------------------------------------------
    //! @brief : �ړ��\�͈͂�n��
    //! @param : [in](void) none
    //! @return : �ړ��\�͈�
    //!-----------------------------------------------------
    const std::vector<br::RangeDataPointer>& GetRange(void) const;

    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ���j�b�g�������Ă������
    //!-----------------------------------------------------
    br::Direction GetDirection(void) const;
    

    bool IsMove(void) const;

    //!-----------------------------------------------------
    //! @brief : �ڕW�n�_�ɓ����������ǂ���
    //! @param : [in](void) none
    //! @return : �����Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    virtual bool IsArrived(void) const;
    //!-----------------------------------------------------
    //! @brief : �ړ��J�n
    //! @param : [in](br::Actor* target) �s��
    //! @return : none
    //!-----------------------------------------------------
    //void MoveStart(br::Tile* target);
    //void MoveStart(const br::Actor& target);
    virtual void MoveStart(void);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    //!-----------------------------------------------------
    //! @brief : �e�C�x���g���ɌĂ΂��
    //! @param : [in](void) none
    //! @return : true
    //!-----------------------------------------------------
    bool OnCursor(void);
    bool OnSelect(void);
    bool OnEnter(void);
    bool OnCancel(void);
    bool OnEnd(void);

    //!-----------------------------------------------------
    //! @brief : Cancel���̏��������s�ł���悤�ɂ���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void RegisterCancel(void);

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_UNIT_MOVE_COMPONENT_H