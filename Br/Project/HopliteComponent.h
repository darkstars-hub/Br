//!-----------------------------------------------------
//! @file : HopliteComponent.h
//! @brief : 鎧Unitが持つ機能
//! @date : 2020/06/20
//!-----------------------------------------------------


#ifndef BR_HOPLITE_COMPONENT_H
#define BR_HOPLITE_COMPONENT_H


#include "UnitJobComponent.h"


namespace br {
class HopliteComponent : public UnitJobComponent {
    using super = br::UnitJobComponent;
private:
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    HopliteComponent(Actor* owner, int priority = 100);
    virtual ~HopliteComponent();

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
#endif // !BR_HOPLITE_COMPONENT_H