//!-----------------------------------------------------
//! @file : UnitSightComponent.h
//! @brief : Unitが持つ攻撃する機能
//! @date : 2020/06/16
//!-----------------------------------------------------


#ifndef BR_UNIT_SIGHT_COMPONENT_H
#define BR_UNIT_SIGHT_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "Helper.h"
#include "Tile.h"
#include "SelectableComponent.h"
#include "Range.h"
#include "RangeRenderComponent.h"
#include "UnitMoveComponent.h"
#include "UnitAttackComponent.h"


namespace br {
class UnitSightComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
 //  //! 現在攻撃可能な範囲内にいる敵
 //  class Unit* _target;
 //  //! 現在攻撃可能な範囲内にいる敵
 //  std::vector<class Unit*> _targets;
 //  //! 状態取得
 //  br::UnitStateComponent* _state;

    //! 視力
    int _sight_count;
    //! 視界の範囲　範囲情報は後でRangeRenderComponent*に渡す
    std::vector<br::RangeDataPointer> _range;
    //! 範囲を参照してもらう
    br::RangeRenderComponent* _range_render;
    //! 移動範囲を参照する
    br::UnitMoveComponent* _move;
    //! 攻撃範囲を参照する
    br::UnitAttackComponent* _attack;
    //! 選択情報取得
    br::SelectableComponent* _select;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : non
    //!-----------------------------------------------------
    UnitSightComponent(Actor* owner, int priority = 100);
    virtual ~UnitSightComponent();

    std::vector<br::RangeDataPointer>* GetRange(void);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    bool OnCursor(void);
    bool OnSelect(void);
    bool OnEnter(void);
    bool OnCancel(void);
    bool OnEnd(void);

    virtual br::Component* Clone(void) override;

    //!-----------------------------------------------------
    //! @brief : 移動先を設定する
    //! @param : [in](bool remove = true) 移動・攻撃範囲を取り除く
    //! @return : none
    //!-----------------------------------------------------
    void ReConputeRange(bool remove = true);
};
}
#endif // !BR_UNIT_SIGHT_COMPONENT_H