//!-----------------------------------------------------
//! @file : UnitMoveComponent.h
//! @brief : Unitが持つ移動機能
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_UNIT_MOVE_COMPONENT_H
#define BR_UNIT_MOVE_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "SelectableComponent.h"
#include "UnitStateComponent.h"
#include "RangeRenderComponent.h"
#include "PathRenderComponent.h"
#include "MotionComponent.h"
#include "PathComponent.h"
#include "RangeComponent.h"


namespace br {
class UnitMoveComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
protected:
    //! 動くべきかどうか
    bool _is_move;
    //! 移動中のパス番号
    int _move_no;
    //! 移動量
    Mof::CVector2 _move;
    //! 移動速度
    const Mof::CVector2 _speed;
    //! 選択情報取得
    br::SelectableComponent* _select;
    //! 状態取得
    br::UnitStateComponent* _state;
    //! 経路
    br::PathComponent* _path;
    //! 移動可能範囲
    br::RangeComponent* _range;
    //! モーションを変更する
    br::MotionComponent* _motion;
    //! 攻撃範囲を設定する
   class UnitAttackComponent* _attack;
   //! 視界を設定する
   class UnitSightComponent* _sight;
    //! 移動前の位置
    Mof::CVector2 _prev_position;
    //! 移動目的地
    br::Tile* _destination;
    //! ユニットが向いている方向
    br::Direction _front_direction;

    void ReConputeRange(void);
    void Move(br::Direction d);
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    UnitMoveComponent(Actor* owner, int priority = 100);
    virtual ~UnitMoveComponent();


    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](br::Tile* ptr) none
    //! @return : 移動目的地の設定
    //!-----------------------------------------------------
    void SetDestination(br::Tile* ptr);

    //!-----------------------------------------------------
    //! @brief : 移動可能範囲を渡す
    //! @param : [in](void) none
    //! @return : 移動可能範囲
    //!-----------------------------------------------------
    const std::vector<br::RangeDataPointer>& GetRange(void) const;

    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : ユニットが向いている方向
    //!-----------------------------------------------------
    br::Direction GetDirection(void) const;
    

    bool IsMove(void) const;

    //!-----------------------------------------------------
    //! @brief : 目標地点に到着したかどうか
    //! @param : [in](void) none
    //! @return : したならtrueを返す
    //!-----------------------------------------------------
    virtual bool IsArrived(void) const;
    //!-----------------------------------------------------
    //! @brief : 移動開始
    //! @param : [in](br::Actor* target) 行先
    //! @return : none
    //!-----------------------------------------------------
    //void MoveStart(br::Tile* target);
    //void MoveStart(const br::Actor& target);
    virtual void MoveStart(void);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    //!-----------------------------------------------------
    //! @brief : 各イベント時に呼ばれる
    //! @param : [in](void) none
    //! @return : true
    //!-----------------------------------------------------
    bool OnCursor(void);
    bool OnSelect(void);
    bool OnEnter(void);
    bool OnCancel(void);
    bool OnEnd(void);

    //!-----------------------------------------------------
    //! @brief : Cancel時の処理を実行できるようにする
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void RegisterCancel(void);

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_UNIT_MOVE_COMPONENT_H