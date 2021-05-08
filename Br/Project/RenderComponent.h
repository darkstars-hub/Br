//!-----------------------------------------------------
//! @file : RenderComponent.h
//! @brief : Actor�����`��@�\�̊��N���X
//! @date : 2020/05/28
//!-----------------------------------------------------


#ifndef BR_RENDER_COMPONENT_H
#define BR_RENDER_COMPONENT_H


#include "Component.h"


namespace br {
class RenderComponent : public Component {
    using super = br::Component;
public:
        //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    RenderComponent(Actor* owner, int priority = 100);
    virtual ~RenderComponent();

    //!-----------------------------------------------------
    //! @brief : �`�悷�邩�ǂ���
    //! @param : [in](void) none
    //! @return : ����ꍇtrue
    //!-----------------------------------------------------
    bool IsRender(void) override;

    virtual bool Initialize(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;
    virtual bool Release(void) override;
};
}
#endif // !BR_RENDER_COMPONENT_H