//!-----------------------------------------------------
//! @file : GameUI.h
//! @brief : �Q�[��������UI���X�V�E�`��
//! @date : 2020/08/03
//!-----------------------------------------------------


#ifndef BR_GAME_UI_H
#define BR_GAME_UI_H


#include <Mof.h>

#include "UIWindow.h"
#include "TextSystem.h"
#include "ReverseGuage.h"
#include "BattleSystemForecast.h"


namespace br {
class GameUI {
private:
    //! ���݂̏���\�������肷��
    br::UIWindow _ui_window;          
    //! �e�L�X�g��\������            
    br::TextSystem _text_system;  
    //! �������]�M�~�b�N
    br::ReverseGuage _reverse_guage;
    //! �퓬���ʗ\�z
    br::BattleSystemForecast _battle_forecast;
public:
    GameUI();
    ~GameUI();

    Mof::CVector2 GetUIWindowOffset(void);
    br::BattleSystemForecast* GetBattleSystemForeCast(void);
    br::ReverseGuage* GetReverseGuage(void);
    
    bool IsTextSystemShow(void);

    void Input(void);

    void Initialize(class Game* game);
    void Update(void);
    void Render(bool battle_system_show);

    void TextShow(const char* path, std::function<void(void)>lambda = []() {});
};
}
#endif // !BR_GAME_UI_H