//!-----------------------------------------------------
//! @file : UpdateComponent.h
//! @brief : Actor�����X�V�@�\�̊��N���X
//! @date : 2020/05/30
//!-----------------------------------------------------


#ifndef BR_UPDATE_COMPONENT_H
#define BR_UPDATE_COMPONENT_H


#include "Component.h"


namespace br {
class UpdateComponent : public Component {
    using super = br::Component;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    UpdateComponent(Actor* owner, int priority = 100);
    virtual ~UpdateComponent();

    bool IsUpdate(void) override;

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
};
}
#endif // !BR_UPDATE_COMPONENT_H