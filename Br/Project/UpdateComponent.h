//!-----------------------------------------------------
//! @file : UpdateComponent.h
//! @brief : Actorが持つ更新機能の基底クラス
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
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
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