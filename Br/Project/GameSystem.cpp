#include "GameSystem.h"
#include "Game.h"

br::GameSystem::GameSystem() :
    _battle_system(),
    _fusion_system()
    //_battle_forecast()
{
}

br::GameSystem::~GameSystem() {
}

br::BattleSystem* br::GameSystem::GetBattleSystem(void) {
    return &this->_battle_system;
}
/*
br::BattleSystemForecast* br::GameSystem::GetBattleSystemForeCast(void) {
    return &this->_battle_forecast;
}
*/

br::FusionSystem* br::GameSystem::GetFusionSystem(void) {
    return &this->_fusion_system;
}

bool br::GameSystem::IsShow(void) {
    return _battle_system.IsShow() || _fusion_system.IsShow();
}

bool br::GameSystem::IsBattleSystemShow(void) {
    return this->_battle_system.IsShow();
}

void br::GameSystem::Input(void) {
    _battle_system.Input();
}

void br::GameSystem::Initialize(br::Game* game) {
    _battle_system.Initialize(game->GetResourceManager());
    _fusion_system.SetResourceManager(game->GetResourceManager());
}

void br::GameSystem::Update(void) {
    // 戦闘画面表示
    if (_battle_system.IsShow()) {
        _battle_system.Update();
    } // if
    // 合体画面表示
    if (_fusion_system.IsShow()) {
        _fusion_system.Update();
    } // if
}

void br::GameSystem::Render(void) {
    // 戦闘結果予測表示
    //if (_battle_forecast.IsShow()) {
    //    _battle_forecast.Render();
    //} // if
    // 戦闘画面表示
    if (_battle_system.IsShow()) {
        _battle_system.Render();
    } // if
    // 合体画面表示
    if (_fusion_system.IsShow()) {
        _fusion_system.Render();
    } // if
}