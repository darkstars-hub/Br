//!-----------------------------------------------------
//! @file : GameSystem.h
//! @brief : ゲームギミックの部分
//! @date : 2020/08/03
//!-----------------------------------------------------


#ifndef BR_GAME_SYSTEM_H
#define BR_GAME_SYSTEM_H


#include "BattleSystem.h"
#include "FusionSystem.h"
#include "BattleSystemForecast.h"


namespace br {
class GameSystem {
private:
    //! 戦いを表示する
    br::BattleSystem _battle_system;
    //! 合体を表示する              
    br::FusionSystem _fusion_system;
    //! 戦闘結果予想
    //br::BattleSystemForecast _battle_forecast; // 上に出せるやつ
public:
    GameSystem();
    ~GameSystem();

    br::BattleSystem* GetBattleSystem(void);
    br::FusionSystem* GetFusionSystem(void);
    //br::BattleSystemForecast* GetBattleSystemForeCast(void);
    bool IsShow(void);
    bool IsBattleSystemShow(void);
    void Input(void);
    void Initialize(class Game* game);
    void Update(void);
    void Render(void);
};
}
#endif // !BR_GAME_SYSTEM_H