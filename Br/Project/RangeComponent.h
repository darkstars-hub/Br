//!-----------------------------------------------------
//! @file : RangeComponent.h
//! @brief : Unitが持つ移動機能
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_RANGE_COMPONENT_H
#define BR_RANGE_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "SelectableComponent.h"
#include "UnitStateComponent.h"
#include "RangeRenderComponent.h"
#include "PathRenderComponent.h"
#include "MotionComponent.h"
#include "PathComponent.h"


namespace br {
class RangeComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! 範囲情報は後でRangeRenderComponent*に渡す
    std::vector<br::RangeDataPointer> _range;
    //! 範囲を参照してもらう
    br::RangeRenderComponent* _range_render;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    RangeComponent(Actor* owner, int priority = 100);
    virtual ~RangeComponent();

    //!-----------------------------------------------------
    //! @brief : 移動可能範囲を渡す
    //! @param : [in](void) none
    //! @return : 移動可能範囲
    //!-----------------------------------------------------
    const std::vector<br::RangeDataPointer>& GetRange(void) const;
    //!-----------------------------------------------------
    //! @brief : 移動可能範囲を計算する
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void ConputeRange(br::Tile* origin, int move);
    //!-----------------------------------------------------
    //! @brief : コンテナのクリア
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Clear(void);


    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;


    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_RANGE_COMPONENT_H