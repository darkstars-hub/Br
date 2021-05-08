//!-----------------------------------------------------
//! @file : RenderComponent.h
//! @brief : Actorが持つ描画機能の基底クラス
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
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    RenderComponent(Actor* owner, int priority = 100);
    virtual ~RenderComponent();

    //!-----------------------------------------------------
    //! @brief : 描画するかどうか
    //! @param : [in](void) none
    //! @return : する場合true
    //!-----------------------------------------------------
    bool IsRender(void) override;

    virtual bool Initialize(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;
    virtual bool Release(void) override;
};
}
#endif // !BR_RENDER_COMPONENT_H