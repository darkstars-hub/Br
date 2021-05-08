//!-----------------------------------------------------
//! @file : UnitSightComponent.h
//! @brief : Unit�����U������@�\
//! @date : 2020/06/16
//!-----------------------------------------------------


#ifndef BR_UNIT_SIGHT_COMPONENT_H
#define BR_UNIT_SIGHT_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "Helper.h"
#include "Tile.h"
#include "SelectableComponent.h"
#include "Range.h"
#include "RangeRenderComponent.h"
#include "UnitMoveComponent.h"
#include "UnitAttackComponent.h"


namespace br {
class UnitSightComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
 //  //! ���ݍU���\�Ȕ͈͓��ɂ���G
 //  class Unit* _target;
 //  //! ���ݍU���\�Ȕ͈͓��ɂ���G
 //  std::vector<class Unit*> _targets;
 //  //! ��Ԏ擾
 //  br::UnitStateComponent* _state;

    //! ����
    int _sight_count;
    //! ���E�͈̔́@�͈͏��͌��RangeRenderComponent*�ɓn��
    std::vector<br::RangeDataPointer> _range;
    //! �͈͂��Q�Ƃ��Ă��炤
    br::RangeRenderComponent* _range_render;
    //! �ړ��͈͂��Q�Ƃ���
    br::UnitMoveComponent* _move;
    //! �U���͈͂��Q�Ƃ���
    br::UnitAttackComponent* _attack;
    //! �I�����擾
    br::SelectableComponent* _select;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : non
    //!-----------------------------------------------------
    UnitSightComponent(Actor* owner, int priority = 100);
    virtual ~UnitSightComponent();

    std::vector<br::RangeDataPointer>* GetRange(void);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    bool OnCursor(void);
    bool OnSelect(void);
    bool OnEnter(void);
    bool OnCancel(void);
    bool OnEnd(void);

    virtual br::Component* Clone(void) override;

    //!-----------------------------------------------------
    //! @brief : �ړ����ݒ肷��
    //! @param : [in](bool remove = true) �ړ��E�U���͈͂���菜��
    //! @return : none
    //!-----------------------------------------------------
    void ReConputeRange(bool remove = true);
};
}
#endif // !BR_UNIT_SIGHT_COMPONENT_H