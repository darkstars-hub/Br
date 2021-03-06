//!-----------------------------------------------------
//! @file : UnitFusionComponent.h
//! @brief : Unitが持つ融合する機能
//! @date : 2020/06/23
//!-----------------------------------------------------


#ifndef BR_UNIT_FUSION_COMPONENT_H
#define BR_UNIT_FUSION_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "Helper.h"
#include "SelectableComponent.h"
#include "UnitStateComponent.h"
#include "RangeRenderComponent.h"
#include "MotionComponent.h"


namespace br {
class UnitFusionComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! 現在融合可能な範囲内にいる味方
    std::vector<class Unit*> _targets;
    //! 選択情報取得
    br::SelectableComponent* _select;
    //! 状態取得
    br::UnitStateComponent* _state;
    //! 範囲を参照してもらう
    br::RangeRenderComponent* _range_render;
    //! モーションを変更する
    br::MotionComponent* _motion;
    //! 融合範囲　範囲情報は後でRangeRenderComponent*に渡す
    std::vector<br::Tile*> _range;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    UnitFusionComponent(Actor* owner, int priority = 100);
    virtual ~UnitFusionComponent();

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    bool OnEnter(void);
    bool OnCancel(void);
    bool OnEnd(void);

    //!-----------------------------------------------------
    //! @brief : 現在の隣接している味方ユニット達を_targetsに入れる
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Start(void);
    //!-----------------------------------------------------
    //! @brief : 指定のユニットが融合可能範囲内にいるか調べる
    //! @param : [in](br::Unit* target) ユニット
    //! @return : 融合できるならtrueを返す
    //!-----------------------------------------------------
    bool CanFusion(br::Unit* target);
    //!-----------------------------------------------------
    //! @brief : 対象のユニットと合体する
    //! @param : [in](br::Unit& target) 対象
    //! @return : 成功したらtrue
    //!-----------------------------------------------------
    bool Fusion(br::Unit& target);
    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_UNIT_FUSION_COMPONENT_H