//!-----------------------------------------------------
//! @file : UnitTextureComponent.h
//! @brief : Unit������Sprite�`��@�\
//! @date : 2020/06/14
//!-----------------------------------------------------


#ifndef BR_UNIT_TEXTURE_COMPONENT
#define BR_UNIT_TEXTURE_COMPONENT

#include "TextureComponent.h"

#include <Mof.h>
#include "UnitStateComponent.h"


namespace br {
class UnitTextureComponent : public br::TextureComponent {
    using super = br::TextureComponent;
private:
    const Mof::CVector2 _offset;
    br::UnitStateComponent* _state;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    UnitTextureComponent(br::Actor* owner, int priority);
    virtual ~UnitTextureComponent();
    
    bool Initialize(void) override;
    bool Render(Mof::CVector2 scroll) override;
    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_UNIT_TEXTURE_COMPONENT