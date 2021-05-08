//!-----------------------------------------------------
//! @file : LightCavalryComponent.h
//! @brief : �|�R�nUnit�����@�\
//! @date : 2020/06/05
//!-----------------------------------------------------


#ifndef BR_LIGHT_CAVALRY_COMPONENT_H
#define BR_LIGHT_CAVALRY_COMPONENT_H


#include "UnitJobComponent.h"


namespace br {
class LightCavalryComponent : public UnitJobComponent {
    using super = br::UnitJobComponent;
private:
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    LightCavalryComponent(Actor* owner, int priority = 100);
    virtual ~LightCavalryComponent();

    void RegisterType(void) override;
    bool Fusion(class Unit& target) override;

    bool Initialize(void) override;
    bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Render(Mof::CVector2 scroll);
    bool Release(void) override;

    br::Component* Clone(void) override;
};
}
#endif // !BR_LIGHT_CAVALRY_COMPONENT_H