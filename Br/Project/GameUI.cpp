#include "GameUI.h"

#include "Game.h"


br::GameUI::GameUI() :
    _ui_window(),
    _text_system(),
    _reverse_guage(),
    _battle_forecast() {
}

br::GameUI::~GameUI() {
}

Mof::CVector2 br::GameUI::GetUIWindowOffset(void) {
    return  _ui_window.GetOffset();;
}

br::BattleSystemForecast* br::GameUI::GetBattleSystemForeCast(void) {
    return &this->_battle_forecast;
}

br::ReverseGuage* br::GameUI::GetReverseGuage(void) {
    return &this->_reverse_guage;
}

bool br::GameUI::IsTextSystemShow(void) {
    return this->_text_system.IsShow();
}

void br::GameUI::Input(void) {
    _text_system.Input();

    // テスト用相性反転
    if (::g_pInput->IsKeyPush(MOFKEY_C)) {
        _reverse_guage.Use();
    } // if
   //if (::g_pInput->IsKeyPush(MOFKEY_X)) {
   //    _reverse_guage.Add(10);
   //} // if
   //if (::g_pInput->IsKeyPush(MOFKEY_G)) {
   //    _reverse_guage.Add(8);
   //} // if
}

void br::GameUI::Initialize(br::Game* game) {
    _ui_window.SetGame(game);
    _ui_window.SetCursor(game->GetCursor());
    _text_system.SetResourceManager(game->GetResourceManager());
    _text_system.Show(game->GetSelectInfomation().start_text_path);
    _reverse_guage.SetResourceManager(game->GetResourceManager());
}

void br::GameUI::Update(void) {
    if (_text_system.IsShow()) {
        _text_system.Update();
    } // if
    _ui_window.Update();
}

void br::GameUI::Render(bool battle_system_show) {
    // 戦闘結果予測表示
    if (_battle_forecast.IsShow()) {
        _battle_forecast.Render();
    } // if

    if (_text_system.IsShow()) {
        _text_system.Render();
    } // if

    if (!battle_system_show) {
        _ui_window.Render();
        _reverse_guage.Render();
    } // if

}

void br::GameUI::TextShow(const char* path, std::function<void(void)> lambda) {
    _text_system.Show(path, lambda);
}