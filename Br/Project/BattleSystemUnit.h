//!-----------------------------------------------------
//! @file : BattleSystemUnit.h
//! @brief : バトルシステムの中で動くユニット
//! @date : 2020/07/18
//!-----------------------------------------------------


#ifndef BR_BATTLE_SYSTEM_UNIT_H
#define BR_BATTLE_SYSTEM_UNIT_H


#include <vector>
#include <memory>

#include <Mof.h>

#include "Sprite.h"
#include "Unit.h"
#include "ResourceManager.h"


namespace br {
class BattleSystemUnit {
private:
    //! バトルシステムで動くユニット
    br::Unit* _unit;
    //! 表示画像
    br::Sprite _sprite;
    //! 初期位置
    Mof::CVector2 _position;
    //! 攻撃側であるかどうか　そうでないなら攻撃される側
    bool _is_attacker;
    //! キャッシュ
    std::weak_ptr<br::ResourceManager> _resource_manager;
    //! アニメーションの時間
    float _time;
    float _time_max;
    //! 攻撃相手
    br::BattleSystemUnit* _target;

    //! アニメーションのコントロールポイント
    Mof::CVector2 _point1;
    Mof::CVector2 _point2;
    Mof::CVector2 _point3;
    std::vector<float> _control_x;
    std::vector<float> _control_y;

    //! 攻撃終了フラグ
    bool _attack_end;

    //!-----------------------------------------------------
    //! @brief : 引数にしたSpriteにデータを入れる
    //! @param : [in](br::UnitType type) ユニットタイプ
    //! @param : [out](br::Sprite& out) 読み込み先
    //! @return : none
    //!-----------------------------------------------------
    void SetSprite(br::UnitType type, br::Sprite& out);
public:
    BattleSystemUnit();
    ~BattleSystemUnit();

    //!-----------------------------------------------------
    //! @brief : 攻撃し終わったかどうか
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    bool AttackEnd(void);

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](bool b) 攻撃側にする
    //! @return : none
    //!-----------------------------------------------------
    void SetAttacker(bool b);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](br::BattleSystemUnit* ptr) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    //void SetTarget(br::BattleSystemUnit* ptr);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](std::weak_ptr<br::ResourceManager>r) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetResourceManager(std::weak_ptr<br::ResourceManager>r);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : ポインタ
    //!-----------------------------------------------------
    br::Unit* GetUnit(void);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 表示中の画像の矩形
    //!-----------------------------------------------------
    Mof::CRectangle GetRectangle(void);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 表示位置
    //!-----------------------------------------------------
    Mof::CVector2 GetPosition(void) const;
    //!-----------------------------------------------------
    //! @brief : 攻撃する側であるかどうか
    //! @param : [in](void) none
    //! @return : 攻撃する側であるならtrueを返す
    //!-----------------------------------------------------
    bool IsAttacker(void) const;
    //!-----------------------------------------------------
    //! @brief : 攻撃される側であるかどうか
    //! @param : [in](void) none
    //! @return : 攻撃する側でないならtrueを返す
    //!-----------------------------------------------------
    bool IsTarget(void) const;
    //!-----------------------------------------------------
    //! @brief : br::Sprite::IsEndMotionのラッパー
    //! @param : [in](void) none
    //! @return : モーションが終わったならならtrueを返す
    //!-----------------------------------------------------
    bool IsEndMotion(void);
    //!-----------------------------------------------------
    //! @brief : 対象が攻撃範囲に入っているか確認する
    //! @param : [in](BattleSystemUnit& target) 反撃対象
    //! @return : 攻撃可能ならtrueを返す
    //!-----------------------------------------------------
    bool CanAttakck(BattleSystemUnit& target);


    //!-----------------------------------------------------
    //! @brief : 初期化
    //! @param : [in](br::Unit* unit) 内包するユニット
    //! @param : [in](Mof::CVector2 position) 初期位置
    //! @param : [in](bool attacker) 攻撃側であるならtrue
    //! @param : [in](br::BattleSystemUnit* ptr) 攻撃相手
    //! @return : none
    //!-----------------------------------------------------
//    void Initialize(br::Unit* unit, Mof::CVector2 position, bool attacker);
    void Initialize(br::Unit* unit, Mof::CVector2 position, bool attacker, br::BattleSystemUnit* target);
    //!-----------------------------------------------------
    //! @brief : 更新
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Update(void);
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Render(void);
    //!-----------------------------------------------------
    //! @brief : アニメーションに必要なデータの作成
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void MakeControlPoint(void);
};
}
#endif // !BR_BATTLE_SYSTEM_UNIT_H