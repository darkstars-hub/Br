//!-----------------------------------------------------
//! @file : SniperComponent.h
//! @brief : 強弓Unitが持つ機能
//! @date : 2020/06/20
//!-----------------------------------------------------


#ifndef BR_SNIPER_COMPONENT_H
#define BR_SNIPER_COMPONENT_H


#include "UnitJobComponent.h"


namespace br {
class SniperComponent : public UnitJobComponent {
    using super = br::UnitJobComponent;
private:
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    SniperComponent(Actor* owner, int priority = 100);
    virtual ~SniperComponent();

    void RegisterType(void) override;
    bool Fusion(class Unit& target) override;

    bool Initialize(void) override;
    bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Render(Mof::CVector2 scroll);
    bool Release(void) override;

    br::Component* Clone(void) override;
};
}
#endif // !BR_SNIPER_COMPONENT_H