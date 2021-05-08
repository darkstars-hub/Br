//!-----------------------------------------------------
//! @file : GameMenu.h
//! @brief : ゲームメニュー
//! @date : 2020/06/15
//!-----------------------------------------------------


#ifndef BR_GAME_MENU_H
#define BR_GAME_MENU_H


#include "Menu.h"

#include <vector>

#include "Game.h"
#include "ActorManager.h"
#include "Stage.h"
#include "Cursor.h"


namespace br {
class GameMenu : public br::Menu {
    using super = br::Menu;
private:
    //! std::vector<Mof::CRectangle> _texts　のインデックス
    std::vector<size_t> back;
   //! std::vector<Mof::CRectangle> _texts　のインデックス
    std::vector<size_t> turn_end;
   //! std::vector<Mof::CRectangle> _texts　のインデックス
    std::vector<size_t> _retire;

    br::Game* _game;
    br::ActorManager* _actor_manager;
    br::Stage* _stage;
    br::Cursor* _cursor;
public:
    GameMenu(br::Scene* scene);
    
    void Decide(void)override;
    void Cancel(void) override;

    void Show(br::MenuMessage* e) override;
    void Hide(void) override;

};
}
#endif // !BR_GAME_MENU_H