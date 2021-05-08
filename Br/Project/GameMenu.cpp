#include "GameMenu.h"

#include "MenuMessenger.h"
#include "ActorManager.h"
#include "UnitManager.h"
#include "GameMenuMessage.h"

br::GameMenu::GameMenu(br::Scene* scene) :
    super(scene),
    back(),
    turn_end(),
    _retire() {
    back = { 34, 19, 60, 42 };
    turn_end = { 15, 62, 47, 11, 56, 2, 41, 57, 2 };
    _retire = { 41, 15, 1, 0 };
}

void br::GameMenu::Decide(void) {
    _items.at(_index).Excute();
    this->Hide();
}

void br::GameMenu::Cancel(void) {
    this->Hide();
}

void br::GameMenu::Show(br::MenuMessage* e) {
    auto m = dynamic_cast<br::GameMenuMessage*>(e);
    _ASSERT_EXPR(m, L"メニューが表示できない");

    this->_is_show = true;
    this->_game = m->game;
    this->_actor_manager = m->actor_manager;
    this->_stage = m->stage;
    this->_cursor = m->cursor;
    _textures.Load(_scene->GetResourceManager());

    using I = br::GameMenu;
    auto t = br::MenuItem(I::turn_end, &_textures, [&]() {
        _scene->GetActorManager()->GetUnitManager()->AllPlayerEnd(); return true; }, this);
    _items.push_back(t);

    //_items.push_back(br::MenuItem(_retry, &_textures, [&]() {
    //    _stage->Release();
    //    _actor_manager->Release();
    //    _stage->Initialize({});
    //    _actor_manager->Initialize();
    //    _cursor->Initialize({});
    //    _game->ChangeTurn(def::kPlayerTeam);
    //    return true; }, this));


    _items.push_back(br::MenuItem(_retire, &_textures,
                                  [&]() {
        _game->ChangeScene();
        return true; }, this));

    auto b = br::MenuItem(I::back, &_textures, [&]() { this->Cancel(); return true; }, this);
    _items.push_back(b);

    // 表示位置はウインドウの中心にする
    auto rect = this->GetBackRect();
    auto window_center = Mof::CVector2(def::kWindowWidth * 0.5f,
                                       def::kWindowHeight * 0.5f);
    _position.x = window_center.x - rect.GetWidth() * 0.5f;
    _position.y = window_center.y - rect.GetHeight() * 0.5f;

    auto pos = _position;
    for (auto& v : _items) {
        v.SetPosition(pos);
        pos.y += 32;
    } // for
    _index = 0;
    _items.at(_index).SetSelect(true);
}

void br::GameMenu::Hide(void) {
    this->_is_show = false;
    _index = 0;
    _items.clear();

    super::_scene->GetMenu()->Hide();
}