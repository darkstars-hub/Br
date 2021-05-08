//!-----------------------------------------------------
//! @file : UnitTextureComponent.h
//! @brief : Unitが持つSprite描画機能
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
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
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