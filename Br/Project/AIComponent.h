//!-----------------------------------------------------
//! @file : AIComponent.h
//! @brief : �GUnit�����s������@�\
//! @date : 2020/06/16
//!-----------------------------------------------------


#ifndef BR_AI_COMPONENT_H
#define BR_AI_COMPONENT_H


#include "UpdateComponent.h"

#include <string>
#include <unordered_map>

#include "UnitStateComponent.h"
#include "UnitMoveComponent.h"
#include "UnitAttackComponent.h"
#include "UnitSightComponent.h"
#include "PathComponent.h"
#include "RangeComponent.h"
#include "Tile.h"
#include "Scene.h"
#include "AIParam.h"

namespace br {
class AIComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    bool _input;
    class Unit* _target;
    br::Tile* _target_tile;

    br::UnitStateComponent* _state;
    br::UnitMoveComponent* _move;
    br::UnitAttackComponent* _attack;
    br::UnitSightComponent* _sight;
    br::PathComponent* _path;
    br::RangeComponent* _range;

    bool _move_flag;
    bool _attack_flag;
    bool _end_flag;

    std::unordered_map<std::string, class AIState*> _state_map;
    class AIState* _current_state;
    br::AIParam _ai_param;

    //!-----------------------------------------------------
    //! @brief : �W�I��ݒ肷��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    //void DecideTarget(void);
    //!-----------------------------------------------------
    //! @brief : �ڕW�n�_��ݒ肷��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    //br::Tile* ConputeTargetTile(void);


    //!-----------------------------------------------------
    //! @brief : ���̋@�\�̏��������邩�ǂ���
    //! @param : [in](void) none
    //! @return : ����Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsExcute(void);
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    AIComponent(Actor* owner, int priority = 100);
    virtual ~AIComponent();

    //!-----------------------------------------------------
    //! @brief : �X�V�t���O�̃Z�b�g
    //! @param : [in](bool flag) �t���O
    //! @return : none
    //!-----------------------------------------------------
    void Start(void);
    void End(void);
    bool IsInput(void) const;

    br::Scene* GetScene(void);
    class Unit* GetUnit(void);
    class Unit* GetTargetUnit(void);
    
    br::UnitStateComponent* GetUnitState(void);
    br::PathComponent* GetPath(void);
    br::RangeComponent* GetRange(void);
    br::UnitMoveComponent* GetMove(void);
    br::UnitAttackComponent* GetAttack(void);
    br::UnitSightComponent* GetSight(void);
    void ChangeState(const std::string& name);

    
    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;
    virtual bool Release(void) override;

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_AI_COMPONENT_H