//!-----------------------------------------------------
//! @file : TextureComponent.h
//! @brief : Actor������Sprite�`��@�\
//! @date : 2020/05/30
//!-----------------------------------------------------


#ifndef BR_TEXTURE_COMPONENT_H
#define BR_TEXTURE_COMPONENT_H


#include "RenderComponent.h"

#include <memory>
#include <Mof.h>

#include "MotionComponent.h"


namespace br {
class TextureComponent : public br::RenderComponent {
    using super = br::RenderComponent;
private:
protected:
    //! �`��e�N�X�`��
    std::weak_ptr<Mof::CTexture> _texture;
    //! �`���`
    Mof::Rectangle _rectangle;
    //! �A�j���[�V�����f�[�^
    br::MotionComponent* _motion;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    TextureComponent(br::Actor* owner, int priority);
    virtual ~TextureComponent();

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](std::shared_ptr<Mof::CTexture> texture) �|�C���^
    //! @param : [in](const Mof::Rectangle* rectangle = 0) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetTexture(std::weak_ptr<Mof::CTexture> texture,
                    const Mof::Rectangle* rectangle = 0);
        //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](br::MotionComponent& c) �Q��
    //! @return : none
    //!-----------------------------------------------------
    void SetMotionComponent(br::MotionComponent& c);


    bool Initialize(void) override;
    bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Render(Mof::CVector2 scroll) override;
    bool Release(void) override;

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_TEXTURE_COMPONENT_H