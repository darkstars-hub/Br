#include "GameOverMenu.h"

#include "MenuMessenger.h"
#include "ActorManager.h"
#include "UnitManager.h"
#include "GameOverMenuMessage.h"


br::GameOverMenu::GameOverMenu(br::Scene* scene) :
    super(scene),
    back(),
    _retry(),
    _retire(),
    _game(nullptr) {
            //あいうえおかきくけこさしすせそたちつてと20
            //なにぬねのはひふへほまみむめもやいゆえよ40
            //らりるれろわいうえを...
    back = { 34, 19, 60, 42 };
    _retry = { 41, 19, 40, 1 };
    _retire = { 41, 15, 1, 0 };
}

void br::GameOverMenu::Decide(void) {
    _items.at(_index).Excute();
    this->Hide();
}

void br::GameOverMenu::Cancel(void) {
//    _target->onCancel();
//    _target = nullptr;
 //   this->Hide();
}

void br::GameOverMenu::Show(br::MenuMessage* e) {
    auto m = dynamic_cast<br::GameOverMenuMessage*>(e);
    _ASSERT_EXPR(m, L"メニューが表示できない");

    // メンバの設定
    this->_is_show = true;
    super::_textures.Load(_scene->GetResourceManager());
    this->_game = m->game;
    this->_actor_manager = m->actor_manager;
    this->_stage = m->stage;
    this->_cursor = m->cursor;

    // メニューのアイテム追加
    _items.push_back(br::MenuItem(_retry, &_textures, [&]() {
        _stage->Release();
        _actor_manager->Release();
        _stage->Initialize({});
        _actor_manager->Initialize();
//        _cursor->Initialize({});
        _game->ChangeTurn(def::kPlayerTeam);
        return true; }, this));
    _items.push_back(br::MenuItem(_retire, &_textures, 
                                  [&]() { 
        _game->ChangeScene(); 
        return true; }, this));

    // 表示位置設定
    // 表示位置はウインドウの中心にする
    auto rect = this->GetBackRect();
    auto window_center = Mof::CVector2(def::kWindowWidth * 0.5f,
                                       def::kWindowHeight * 0.5f);
    _position.x = window_center.x - rect.GetWidth() * 0.5f;
    _position.y = window_center.y - rect.GetHeight() * 0.5f;
    auto pos = super::_position;
    for (auto& v : _items) {
        v.SetPosition(pos);
        pos.y += br::_text_size;
    } // for
    _index = 0;
    _items.at(_index).SetSelect(true);
}

void br::GameOverMenu::Hide(void) {
    this->_is_show = false;
    _index = 0;
    _items.clear();

    _scene->GetMenu()->Hide();
}