//!-----------------------------------------------------
//! @file : GameSystem.h
//! @brief : �Q�[���M�~�b�N�̕���
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
    //! �킢��\������
    br::BattleSystem _battle_system;
    //! ���̂�\������              
    br::FusionSystem _fusion_system;
    //! �퓬���ʗ\�z
    //br::BattleSystemForecast _battle_forecast; // ��ɏo������
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