//!-----------------------------------------------------
//! @file : UnitStateComponent.h
//! @brief : Unit������{�I�ȋ@�\
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_UNIT_STATE_COMPONENT_H
#define BR_UNIT_STATE_COMPONENT_H


#include "UpdateComponent.h"

#include "Helper.h"
#include "Common.h"
#include "Tile.h"
#include "SelectableComponent.h"
#include "MotionComponent.h"
#include "UnitStatus.h"

namespace br {
enum class UnitMotionState {
    Up,
    Down,
    Left,
    Right,
    Wait,
    Attack,
    CountMax,
};
enum class UnitTeamType {
    Player,
    Enemy
};

class UnitMoveComponent;
class UnitStateComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! ���j�b�g�^�C�v
    br::UnitType _unit_type;
    //! �ړ��\��
    int _move_count;
    //! �I�����擾���邽��
    br::SelectableComponent* _select;
    //! �ړ��悪�Ó������肷��
    br::UnitMoveComponent* _move;
    //! �G���ǂ���
    const char* _team;
    //! �s���\���ǂ���
    bool _is_active;
    //! �U���͈� ���݂̈ʒu����̕ψ�
    std::vector<def::Vector2i> _attack_range;
    //! HP
    class HpComponent* _hp;
    //! �p�����[�^
    br::UnitStatus _status;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    UnitStateComponent(Actor* owner, int priority = 100);
    virtual ~UnitStateComponent();


    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �X�e�[�^�X�̃|�C���^
    //!-----------------------------------------------------
    br::UnitStatus* GetStatus(void);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ������Ă���^�C��
    //!-----------------------------------------------------
    br::Tile* GetCurrentTile(void);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �ړ��\��
    //!-----------------------------------------------------
    int GetMoveCount(void)const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �U���\�͈́@���݂̈ʒu����̕ψ�
    //!-----------------------------------------------------
    std::vector<def::Vector2i>& GetAttackRange(void);

    br::UnitType GetUnitType(void);
    void SetUnitType(br::UnitType type);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](const char* name) �����`�[�����O
    //! @return : none
    //!-----------------------------------------------------
    void SetTeam(const char* type);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](const bool state) �s��������false
    //! @return : none
    //!-----------------------------------------------------
    void SetActive(const bool state);



    void SetMoveCount(int count);
    void SetAttackRange(std::vector<def::Vector2i>& range);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �����`�[��
    //!-----------------------------------------------------
    const char* GetTeam(void);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �s���\���ǂ���
    //!-----------------------------------------------------
    bool IsActive(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : HP�擾
    //!-----------------------------------------------------
    class HpComponent* GetHp(void);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_UNIT_STATE_COMPONENT_H