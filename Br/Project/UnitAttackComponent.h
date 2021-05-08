//!-----------------------------------------------------
//! @file : UnitAttackComponent.h
//! @brief : Unitが持つ攻撃する機能
//! @date : 2020/06/16
//!-----------------------------------------------------


#ifndef BR_UNIT_ATTACK_COMPONENT_H
#define BR_UNIT_ATTACK_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "Helper.h"
#include "Tile.h"
#include "SelectableComponent.h"
#include "UnitStateComponent.h"
#include "UnitMoveComponent.h"
#include "RangeRenderComponent.h"
#include "MotionComponent.h"


namespace br {
class UnitAttackComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! 現在攻撃可能な範囲内にいる敵
    class Unit* _target;
    //! 現在攻撃可能な範囲内にいる敵
    std::vector<class Unit*> _targets;
    //! 選択情報取得
    br::SelectableComponent* _select;
    //! 状態取得
    br::UnitStateComponent* _state;
    //! 範囲を参照してもらう
    br::RangeRenderComponent* _range_render;
    //! モーションを変更する
    br::MotionComponent* _motion;
    //! 攻撃範囲　範囲情報は後でRangeRenderComponent*に渡す
    std::vector<br::Tile*> _range;
    //! 移動範囲を参照する
    br::UnitMoveComponent* _move;
    //! 攻撃中
    //bool _is_attack;
    //! 攻撃アニメーションの時間
    int _action_count;
    //! 攻撃アニメーションの時間の最大値
    int _action_count_max;
    //! 攻撃アニメーション開始前のユニットの位置
    Mof::CVector2 _prev_position;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : non
    //!-----------------------------------------------------
    UnitAttackComponent(Actor* owner, int priority = 100);
    virtual ~UnitAttackComponent();

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](Unit* ptr) none
    //! @return : 攻撃対象の設定
    //!-----------------------------------------------------
    void SetTarget(class Unit* ptr);
    const std::vector<br::Tile*>& GetRange(void) const;

    //!-----------------------------------------------------
    //! @brief : 攻撃中かどうか
    //! @param : [in](void) none
    //! @return : そうであればtrueを返す
    //!-----------------------------------------------------
    //bool IsAttack(void);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    bool OnCursor(void);
    bool OnEnter(void);
    bool OnCancel(void);
    bool OnEnd(void);


    //!-----------------------------------------------------
    //! @brief : Attack時の処理を実行できるようにする
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void RegisterAttack(void);
    void AttackRangeClear(void);
    void ToAttackMode(void);
    //!-----------------------------------------------------
    //! @brief : 攻撃可能範囲を計算する
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void ReConputeRange(void);

    //!-----------------------------------------------------
    //! @brief : 現在の位置から攻撃可能な範囲に居るユニット達を_targetsに入れる
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Start(void);
    //!-----------------------------------------------------
    //! @brief : 対象のユニットに攻撃する
    //! @param : [in](br::Unit* target) 対象の
    //! @return : none
    //!-----------------------------------------------------
    void Attack(void);
    //void Attack(br::Unit& target);
    //!-----------------------------------------------------
    //! @brief : 指定のユニットが攻撃可能範囲内にいるか調べる
    //! @param : [in](br::Unit* target) ユニット
    //! @return : 攻撃できるならtrueを返す
    //!-----------------------------------------------------
    bool CanAttack(br::Unit* target);
    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_UNIT_ATTACK_COMPONENT_H