//!-----------------------------------------------------
//! @file : ArcherMoveComponent.h
//! @brief : Unit�����ړ��@�\
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_ARCHER_MOVE_COMPONENT_H
#define BR_ARCHER_MOVE_COMPONENT_H


#include "UnitMoveComponent.h"

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
class ArcherMoveComponent : public br::UnitMoveComponent {
    using super = br::UnitMoveComponent;
private:
    float _time;
//    float _time_max;
//    AnimData _current_data;
    bool _is_jump;
    float _jump_max;

    Mof::CRectangle GetDestinationRect(void) const;
    Mof::CRectangle GetOwnerRect(void) const;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    ArcherMoveComponent(Actor* owner, int priority = 100);
    virtual ~ArcherMoveComponent();


    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ���j�b�g�������Ă������
    //!-----------------------------------------------------
    //br::Direction GetDirection(void) const;

    
    //!-----------------------------------------------------
    //! @brief : �ڕW�n�_�ɓ����������ǂ���
    //! @param : [in](void) none
    //! @return : �����Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    virtual bool IsArrived(void) const override;
    
    virtual bool Initialize(void) override;
    virtual bool Update(void) override;

    virtual void MoveStart(void) override;
    
    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_UNIT_MOVE_COMPONENT_H