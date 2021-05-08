//!-----------------------------------------------------
//! @file : BattleSystemForecast.h
//! @brief : BattleSystemを実行する前に表示される戦闘結果の予測
//!          攻撃コマンドを選択すると対象に攻撃した場合の結果が表示される
//!         　プレイヤーが攻撃相手を選択する時のみ表示する
//! @date : 2020/07/20
//!-----------------------------------------------------


#ifndef BR_BATTLE_SYSTEM_FORECAST_H
#define BR_BATTLE_SYSTEM_FORECAST_H


#include <Mof.h>

//#include "Unit.h"
namespace br {
class BattleSystemForecast {
private:
    //! 表示フラグ
    bool _is_show;
    //! 攻撃する側
    class Unit* _attacker;
    //! 攻撃される側
    class Unit* _target;
    //! 表示位置
    Mof::CVector2 _position;
public:
    BattleSystemForecast();
    ~BattleSystemForecast();


    
    //!-----------------------------------------------------
    //! @brief :セッター
    //! @param : [in](class Unit* ptr) 攻撃される側
    //! @return : none
    //!-----------------------------------------------------
    void SetTarget(class Unit* ptr);
    //!-----------------------------------------------------
    //! @brief :セッター
    //! @param : [in](Mof::CVector2 position) 表示位置
    //! @return : none
    //!-----------------------------------------------------
    void SetPosition(Mof::CVector2 position);

    //!-----------------------------------------------------
    //! @brief : 表示中であるかどうか
    //! @param : [in](void) none
    //! @return : 表示中である場合true
    //!-----------------------------------------------------
    bool IsShow(void);
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Render(void);


    //!-----------------------------------------------------
    //! @brief : 表示する
    //! @param : [in](class Unit* attacker) 攻撃する側
    //! @param : [in](class Unit* target) 攻撃される側
    //! @return : none
    //!-----------------------------------------------------
    void Show(class Unit* attacker, class Unit* target);
//    void Show(void);

    //!-----------------------------------------------------
    //! @brief : 表示終了
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Hide(void);
};
}
#endif // !BR_BATTLE_SYSTEM_FORECAST_H