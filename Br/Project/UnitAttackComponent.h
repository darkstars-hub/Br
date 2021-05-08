//!-----------------------------------------------------
//! @file : UnitAttackComponent.h
//! @brief : Unit�����U������@�\
//! @date : 2020/06/16
//!-----------------------------------------------------


#ifndef BR_UNIT_ATTACK_COMPONENT_H
#define BR_UNIT_ATTACK_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "Helper.h"
#include "Tile.h"
#include "SelectableComponent.h"
#include "UnitStateComponent.h"
#include "UnitMoveComponent.h"
#include "RangeRenderComponent.h"
#include "MotionComponent.h"


namespace br {
class UnitAttackComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! ���ݍU���\�Ȕ͈͓��ɂ���G
    class Unit* _target;
    //! ���ݍU���\�Ȕ͈͓��ɂ���G
    std::vector<class Unit*> _targets;
    //! �I�����擾
    br::SelectableComponent* _select;
    //! ��Ԏ擾
    br::UnitStateComponent* _state;
    //! �͈͂��Q�Ƃ��Ă��炤
    br::RangeRenderComponent* _range_render;
    //! ���[�V������ύX����
    br::MotionComponent* _motion;
    //! �U���͈́@�͈͏��͌��RangeRenderComponent*�ɓn��
    std::vector<br::Tile*> _range;
    //! �ړ��͈͂��Q�Ƃ���
    br::UnitMoveComponent* _move;
    //! �U����
    //bool _is_attack;
    //! �U���A�j���[�V�����̎���
    int _action_count;
    //! �U���A�j���[�V�����̎��Ԃ̍ő�l
    int _action_count_max;
    //! �U���A�j���[�V�����J�n�O�̃��j�b�g�̈ʒu
    Mof::CVector2 _prev_position;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : non
    //!-----------------------------------------------------
    UnitAttackComponent(Actor* owner, int priority = 100);
    virtual ~UnitAttackComponent();

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](Unit* ptr) none
    //! @return : �U���Ώۂ̐ݒ�
    //!-----------------------------------------------------
    void SetTarget(class Unit* ptr);
    const std::vector<br::Tile*>& GetRange(void) const;

    //!-----------------------------------------------------
    //! @brief : �U�������ǂ���
    //! @param : [in](void) none
    //! @return : �����ł����true��Ԃ�
    //!-----------------------------------------------------
    //bool IsAttack(void);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    bool OnCursor(void);
    bool OnEnter(void);
    bool OnCancel(void);
    bool OnEnd(void);


    //!-----------------------------------------------------
    //! @brief : Attack���̏��������s�ł���悤�ɂ���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void RegisterAttack(void);
    void AttackRangeClear(void);
    void ToAttackMode(void);
    //!-----------------------------------------------------
    //! @brief : �U���\�͈͂��v�Z����
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void ReConputeRange(void);

    //!-----------------------------------------------------
    //! @brief : ���݂̈ʒu����U���\�Ȕ͈͂ɋ��郆�j�b�g�B��_targets�ɓ����
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Start(void);
    //!-----------------------------------------------------
    //! @brief : �Ώۂ̃��j�b�g�ɍU������
    //! @param : [in](br::Unit* target) �Ώۂ�
    //! @return : none
    //!-----------------------------------------------------
    void Attack(void);
    //void Attack(br::Unit& target);
    //!-----------------------------------------------------
    //! @brief : �w��̃��j�b�g���U���\�͈͓��ɂ��邩���ׂ�
    //! @param : [in](br::Unit* target) ���j�b�g
    //! @return : �U���ł���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool CanAttack(br::Unit* target);
    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_UNIT_ATTACK_COMPONENT_H