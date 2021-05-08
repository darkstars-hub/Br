//!-----------------------------------------------------
//! @file : GameMenuMessage.h
//! @brief : ゲームメニュー表示用のクラス
//! @date : 2020/07/11
//!-----------------------------------------------------


#ifndef BR_GAME_MENU_MESSAGE_H
#define BR_GAME_MENU_MESSAGE_H


#include "MenuMessage.h"

#include "Game.h"
#include "ActorManager.h"
#include "Stage.h"
#include "Cursor.h"


namespace br {
class GameMenuMessage : public br::MenuMessage {
    using super = br::MenuMessage;
public:
    br::Game* game;
    br::ActorManager* actor_manager;
    br::Stage* stage;
    br::Cursor* cursor;
};
}
#endif // !BR_GAME_MENU_MESSAGE_H