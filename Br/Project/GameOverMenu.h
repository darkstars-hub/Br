//!-----------------------------------------------------
//! @file : GameOverMenuMessage.h
//! @brief : ゲームオーバーメニュー
//! @date : 2020/07/11
//!-----------------------------------------------------


#ifndef BR_GAME_OVER_MENU_H
#define BR_GAME_OVER_MENU_H


#include "Menu.h"

#include "Game.h"
#include "ActorManager.h"
#include "Stage.h"
#include "Cursor.h"


namespace br {
class GameOverMenu : public br::Menu {
    using super = br::Menu;
private:
    //! std::vector<Mof::CRectangle> _texts　のインデックス
    std::vector<size_t> back;
    std::vector<size_t> _retry;
    std::vector<size_t> _retire;

    br::Game* _game;
    br::ActorManager* _actor_manager;
    br::Stage* _stage;
    br::Cursor* _cursor;
public:
    GameOverMenu(br::Scene* scene);
    //virtual void Show(class Unit* ptr) override;

    void Decide(void)override;
    void Cancel(void) override;

    void Show(br::MenuMessage* e) override;
    void Hide(void) override;
};
}
#endif // !BR_GAME_OVER_MENU_H