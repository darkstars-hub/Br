//!-----------------------------------------------------
//! @file : GeneralComponent.h
//! @brief : ���R(���Z)Unit�����@�\
//! @date : 2020/07/14
//!-----------------------------------------------------


#ifndef BR_GENERAL_COMPONENT_H
#define BR_GENERAL_COMPONENT_H


#include "UnitJobComponent.h"


namespace br {
class GeneralComponent : public UnitJobComponent {
    using super = br::UnitJobComponent;
private:
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    GeneralComponent(Actor* owner, int priority = 100);
    virtual ~GeneralComponent();

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
#endif // !BR_GENERAL_COMPONENT_H