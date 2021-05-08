//!-----------------------------------------------------
//! @file : Unit.h
//! @brief : �Ֆʂ𓮂���
//! @date : 2020/05/28
//!-----------------------------------------------------


#ifndef BR_UNIT_H
#define BR_UNIT_H


#include "Actor.h"

#include <Mof.h>

#include "UnitStateComponent.h"
#include "UnitMoveComponent.h"
#include "UnitAttackComponent.h"
#include "UnitFusionComponent.h"
#include "AIComponent.h"
#include "HpComponent.h"
#include "UnitJobComponent.h"


namespace br {
class Unit : public br::Actor, public IUnitEvent {
    using super = br::Actor;
private:
    br::UnitStateComponent* _state;
    br::UnitMoveComponent* _move;
    br::UnitAttackComponent* _attack;
    br::UnitFusionComponent* _fusion;
    br::AIComponent* _ai;
    br::HpComponent* _hp;
    br::UnitJobComponent* _job; // br::UnitJobComponent���p�������N���X���Z�b�g�����
protected:
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Scene* scene) ���݂̃V�[��
    //! @param : [in](UnitType type) ���j�b�g�̎��
    //! @return : none
    //!-----------------------------------------------------
    Unit(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Unit();

    virtual br::ActorState GetState(void) const override;
    virtual Mof::CVector2 GetPosition(void) const override;

    void SetTeam(const char* type);

    br::UnitType GetUnitType(void) const;
    def::Vector2i GetGridPosition(void);

    const char* GetName(void) const;
    const char* GetTeam(void);
    //!-----------------------------------------------------
    //! @brief : �s���\���ǂ����擾
    //! @param : [in](void) none
    //! @return : �s���\�ł����true��Ԃ�
    //!-----------------------------------------------------
    bool IsActive(void);

    void SetActive(const bool state);
    void SetJobComponent(br::UnitJobComponent* sub);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �R���|�[�l���g�̃|�C���^
    //!-----------------------------------------------------
    br::UnitStateComponent* GetStateComponent(void) const;
    br::UnitMoveComponent* GetMoveComponent(void) const;
    br::UnitAttackComponent* GetAttackComponent(void) const;
    br::UnitJobComponent* GetJobComponent(void) const;

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](br::Tile* ptr) none
    //! @return : �ړ��ړI�n�̐ݒ�
    //!-----------------------------------------------------
    void SetMoveDestination(br::Tile* ptr);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](Unit* ptr) none
    //! @return : �U���Ώۂ̐ݒ�
    //!-----------------------------------------------------
    void SetAttackTarget(br::Unit* ptr);
    //!-----------------------------------------------------
    //! @brief : MoveComponent��Cancel�����s�ł���悤�ɂ���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void MoveRegisterCancel(void);
    //!-----------------------------------------------------
    //! @brief : Attack()�����s�ł���悤�ɂ���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void AttackStart(void);
    //!-----------------------------------------------------
    //! @brief : Fusion()�����s�ł���悤�ɂ���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void FusionStart(void);
    //!-----------------------------------------------------
    //! @brief : Heal()�����s�ł���悤�ɂ���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void HealStart(void);


    //!-----------------------------------------------------
    //! @brief : AIComponent��Update�����s�ł���悤�ɂ���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void AIStart(void);
    bool IsAIInput(void);

    //!-----------------------------------------------------
    //! @brief : �U���������
    //! @param : [in](int damage) HP�����l
    //! @return : none
    //!-----------------------------------------------------
    void Damege(int damage);
    //!-----------------------------------------------------
    //! @brief : �񕜂������
    //! @param : [in](int value) HP�����l
    //! @return : none
    //!-----------------------------------------------------
    void Heal(int value);



    //!-----------------------------------------------------
    //! @brief : ���ɂ����̖����Ɨאڂ��Ă��邩�ǂ��� ���͂����אڂ��Ă����OK
    //! @param : [in](void) none
    //! @return : ���Ă���Ȃ�ture;
    //!-----------------------------------------------------
    bool AdjacentPinchUnit(void);
    //!-----------------------------------------------------
    //! @brief : �G���U���͈͂��邩�ǂ���
    //! @param : [in](void) none
    //! @return : ����Ȃ�ture;
    //!-----------------------------------------------------
    bool CanAttackEnemy(void);
    //!-----------------------------------------------------
    //! @brief : �̗͂������Ă��邩�ǂ���
    //! @param : [in](void) none
    //! @return : �s���`�Ȃ�ture��Ԃ�;
    //!-----------------------------------------------------
    bool IsPinch(void);

    virtual bool Initialize(const br::ActorBaseState& base) override;
    //!-----------------------------------------------------
    //! @brief : �X�V
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Update(void) override;
    virtual bool Render(Mof::CVector2 scroll) override;
};
}
#endif // !BR_UNIT_H