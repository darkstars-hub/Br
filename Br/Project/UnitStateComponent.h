//!-----------------------------------------------------
//! @file : UnitStateComponent.h
//! @brief : Unitが持つ基本的な機能
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_UNIT_STATE_COMPONENT_H
#define BR_UNIT_STATE_COMPONENT_H


#include "UpdateComponent.h"

#include "Helper.h"
#include "Common.h"
#include "Tile.h"
#include "SelectableComponent.h"
#include "MotionComponent.h"
#include "UnitStatus.h"

namespace br {
enum class UnitMotionState {
    Up,
    Down,
    Left,
    Right,
    Wait,
    Attack,
    CountMax,
};
enum class UnitTeamType {
    Player,
    Enemy
};

class UnitMoveComponent;
class UnitStateComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! ユニットタイプ
    br::UnitType _unit_type;
    //! 移動可能数
    int _move_count;
    //! 選択情報取得するため
    br::SelectableComponent* _select;
    //! 移動先が妥当か判定する
    br::UnitMoveComponent* _move;
    //! 敵かどうか
    const char* _team;
    //! 行動可能かどうか
    bool _is_active;
    //! 攻撃範囲 現在の位置からの変位
    std::vector<def::Vector2i> _attack_range;
    //! HP
    class HpComponent* _hp;
    //! パラメータ
    br::UnitStatus _status;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    UnitStateComponent(Actor* owner, int priority = 100);
    virtual ~UnitStateComponent();


    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : ステータスのポインタ
    //!-----------------------------------------------------
    br::UnitStatus* GetStatus(void);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 今乗っているタイル
    //!-----------------------------------------------------
    br::Tile* GetCurrentTile(void);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 移動可能数
    //!-----------------------------------------------------
    int GetMoveCount(void)const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 攻撃可能範囲　現在の位置からの変位
    //!-----------------------------------------------------
    std::vector<def::Vector2i>& GetAttackRange(void);

    br::UnitType GetUnitType(void);
    void SetUnitType(br::UnitType type);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](const char* name) 所属チーム名前
    //! @return : none
    //!-----------------------------------------------------
    void SetTeam(const char* type);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](const bool state) 行動したらfalse
    //! @return : none
    //!-----------------------------------------------------
    void SetActive(const bool state);



    void SetMoveCount(int count);
    void SetAttackRange(std::vector<def::Vector2i>& range);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 所属チーム
    //!-----------------------------------------------------
    const char* GetTeam(void);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 行動可能かどうか
    //!-----------------------------------------------------
    bool IsActive(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : HP取得
    //!-----------------------------------------------------
    class HpComponent* GetHp(void);

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
#endif // !BR_UNIT_STATE_COMPONENT_H