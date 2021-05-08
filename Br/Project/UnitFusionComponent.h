//!-----------------------------------------------------
//! @file : UnitFusionComponent.h
//! @brief : Unit�����Z������@�\
//! @date : 2020/06/23
//!-----------------------------------------------------


#ifndef BR_UNIT_FUSION_COMPONENT_H
#define BR_UNIT_FUSION_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "Helper.h"
#include "SelectableComponent.h"
#include "UnitStateComponent.h"
#include "RangeRenderComponent.h"
#include "MotionComponent.h"


namespace br {
class UnitFusionComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! ���ݗZ���\�Ȕ͈͓��ɂ��閡��
    std::vector<class Unit*> _targets;
    //! �I�����擾
    br::SelectableComponent* _select;
    //! ��Ԏ擾
    br::UnitStateComponent* _state;
    //! �͈͂��Q�Ƃ��Ă��炤
    br::RangeRenderComponent* _range_render;
    //! ���[�V������ύX����
    br::MotionComponent* _motion;
    //! �Z���͈́@�͈͏��͌��RangeRenderComponent*�ɓn��
    std::vector<br::Tile*> _range;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    UnitFusionComponent(Actor* owner, int priority = 100);
    virtual ~UnitFusionComponent();

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    bool OnEnter(void);
    bool OnCancel(void);
    bool OnEnd(void);

    //!-----------------------------------------------------
    //! @brief : ���݂̗אڂ��Ă��閡�����j�b�g�B��_targets�ɓ����
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Start(void);
    //!-----------------------------------------------------
    //! @brief : �w��̃��j�b�g���Z���\�͈͓��ɂ��邩���ׂ�
    //! @param : [in](br::Unit* target) ���j�b�g
    //! @return : �Z���ł���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool CanFusion(br::Unit* target);
    //!-----------------------------------------------------
    //! @brief : �Ώۂ̃��j�b�g�ƍ��̂���
    //! @param : [in](br::Unit& target) �Ώ�
    //! @return : ����������true
    //!-----------------------------------------------------
    bool Fusion(br::Unit& target);
    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_UNIT_FUSION_COMPONENT_H