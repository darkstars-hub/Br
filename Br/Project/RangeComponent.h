//!-----------------------------------------------------
//! @file : RangeComponent.h
//! @brief : Unit�����ړ��@�\
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_RANGE_COMPONENT_H
#define BR_RANGE_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "SelectableComponent.h"
#include "UnitStateComponent.h"
#include "RangeRenderComponent.h"
#include "PathRenderComponent.h"
#include "MotionComponent.h"
#include "PathComponent.h"


namespace br {
class RangeComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! �͈͏��͌��RangeRenderComponent*�ɓn��
    std::vector<br::RangeDataPointer> _range;
    //! �͈͂��Q�Ƃ��Ă��炤
    br::RangeRenderComponent* _range_render;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    RangeComponent(Actor* owner, int priority = 100);
    virtual ~RangeComponent();

    //!-----------------------------------------------------
    //! @brief : �ړ��\�͈͂�n��
    //! @param : [in](void) none
    //! @return : �ړ��\�͈�
    //!-----------------------------------------------------
    const std::vector<br::RangeDataPointer>& GetRange(void) const;
    //!-----------------------------------------------------
    //! @brief : �ړ��\�͈͂��v�Z����
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void ConputeRange(br::Tile* origin, int move);
    //!-----------------------------------------------------
    //! @brief : �R���e�i�̃N���A
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Clear(void);


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
#endif // !BR_RANGE_COMPONENT_H