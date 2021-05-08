//!-----------------------------------------------------
//! @file : Unit.h
//! @brief : 盤面を動く駒
//! @date : 2020/05/28
//!-----------------------------------------------------


#ifndef BR_UNIT_H
#define BR_UNIT_H


#include "Actor.h"

#include <Mof.h>

#include "UnitStateComponent.h"
#include "UnitMoveComponent.h"
#include "UnitAttackComponent.h"
#include "UnitFusionComponent.h"
#include "AIComponent.h"
#include "HpComponent.h"
#include "UnitJobComponent.h"


namespace br {
class Unit : public br::Actor, public IUnitEvent {
    using super = br::Actor;
private:
    br::UnitStateComponent* _state;
    br::UnitMoveComponent* _move;
    br::UnitAttackComponent* _attack;
    br::UnitFusionComponent* _fusion;
    br::AIComponent* _ai;
    br::HpComponent* _hp;
    br::UnitJobComponent* _job; // br::UnitJobComponentを継承したクラスがセットされる
protected:
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Scene* scene) 現在のシーン
    //! @param : [in](UnitType type) ユニットの種類
    //! @return : none
    //!-----------------------------------------------------
    Unit(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Unit();

    virtual br::ActorState GetState(void) const override;
    virtual Mof::CVector2 GetPosition(void) const override;

    void SetTeam(const char* type);

    br::UnitType GetUnitType(void) const;
    def::Vector2i GetGridPosition(void);

    const char* GetName(void) const;
    const char* GetTeam(void);
    //!-----------------------------------------------------
    //! @brief : 行動可能かどうか取得
    //! @param : [in](void) none
    //! @return : 行動可能であればtrueを返す
    //!-----------------------------------------------------
    bool IsActive(void);

    void SetActive(const bool state);
    void SetJobComponent(br::UnitJobComponent* sub);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : コンポーネントのポインタ
    //!-----------------------------------------------------
    br::UnitStateComponent* GetStateComponent(void) const;
    br::UnitMoveComponent* GetMoveComponent(void) const;
    br::UnitAttackComponent* GetAttackComponent(void) const;
    br::UnitJobComponent* GetJobComponent(void) const;

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](br::Tile* ptr) none
    //! @return : 移動目的地の設定
    //!-----------------------------------------------------
    void SetMoveDestination(br::Tile* ptr);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](Unit* ptr) none
    //! @return : 攻撃対象の設定
    //!-----------------------------------------------------
    void SetAttackTarget(br::Unit* ptr);
    //!-----------------------------------------------------
    //! @brief : MoveComponentのCancelを実行できるようにする
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void MoveRegisterCancel(void);
    //!-----------------------------------------------------
    //! @brief : Attack()を実行できるようにする
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void AttackStart(void);
    //!-----------------------------------------------------
    //! @brief : Fusion()を実行できるようにする
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void FusionStart(void);
    //!-----------------------------------------------------
    //! @brief : Heal()を実行できるようにする
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void HealStart(void);


    //!-----------------------------------------------------
    //! @brief : AIComponentのUpdateを実行できるようにする
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void AIStart(void);
    bool IsAIInput(void);

    //!-----------------------------------------------------
    //! @brief : 攻撃をされる
    //! @param : [in](int damage) HP減少値
    //! @return : none
    //!-----------------------------------------------------
    void Damege(int damage);
    //!-----------------------------------------------------
    //! @brief : 回復をされる
    //! @param : [in](int value) HP増加値
    //! @return : none
    //!-----------------------------------------------------
    void Heal(int value);



    //!-----------------------------------------------------
    //! @brief : 死にかけの味方と隣接しているかどうか 今はただ隣接していればOK
    //! @param : [in](void) none
    //! @return : しているならture;
    //!-----------------------------------------------------
    bool AdjacentPinchUnit(void);
    //!-----------------------------------------------------
    //! @brief : 敵が攻撃範囲いるかどうか
    //! @param : [in](void) none
    //! @return : いるならture;
    //!-----------------------------------------------------
    bool CanAttackEnemy(void);
    //!-----------------------------------------------------
    //! @brief : 体力が減っているかどうか
    //! @param : [in](void) none
    //! @return : ピンチならtureを返す;
    //!-----------------------------------------------------
    bool IsPinch(void);

    virtual bool Initialize(const br::ActorBaseState& base) override;
    //!-----------------------------------------------------
    //! @brief : 更新
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Update(void) override;
    virtual bool Render(Mof::CVector2 scroll) override;
};
}
#endif // !BR_UNIT_H