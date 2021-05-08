#include "ActorManager.h"

#include "Helper.h"
#include "Common.h"
#include "Cursor.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "UnitStateComponent.h"
#include "SelectableComponent.h"
#include "MotionComponent.h"
#include "UnitMoveComponent.h"
#include "RangeRenderComponent.h"
#include "PathRenderComponent.h"
#include "CavalryComponent.h"
#include "StageTable.h"


br::ActorManager::ActorManager(br::Scene* scene) :
    _scene(scene),
    _game(dynamic_cast<br::Game*>(scene)),
    _factory(_scene),
    _unit_manager(scene) {
}

br::ActorManager::~ActorManager() {
}

br::UnitManager* br::ActorManager::GetUnitManager(void) {
    return &this->_unit_manager;
}

bool br::ActorManager::Load(const char* path) {
    if (auto format = std::strstr(path, ".unit_initial_coordinate"); !format) {
        return false;
    } // if
    if (!ut::LoadJsonDocument(path, _unit_doc)) {
        return false;
    } // if
    return true;
}

bool br::ActorManager::Input(void) {
    _unit_manager.Input();
    return true;
}

bool br::ActorManager::Initialize(void) {

    { // プレイヤーユニット配置
        const auto& players = _unit_doc["players"];
        _ASSERT_EXPR(players.IsArray(),
                     L"players type is not array");
        for (int i = 0; i < players.Size(); i++) {
            if (!players[i].HasMember("type") || !players[i]["type"].IsInt() ||
                !players[i].HasMember("name") || !players[i]["name"].IsString() ||
                !players[i].HasMember("x") || !players[i]["x"].IsInt() ||
                !players[i].HasMember("y") || !players[i]["y"].IsInt()) {
                break;
            } // if

            const auto& type = players[i]["type"];
            const auto& name = players[i]["name"];
            const auto& x = players[i]["x"];
            const auto& y = players[i]["y"];

            auto base = br::ActorBaseState();
            base.name = name.GetString();
            base.position = Mof::CVector2(x.GetInt() * def::kChipSize,
                                          y.GetInt() * def::kChipSize);
            base.type = br::ActorType::Unit;
            auto a = _factory.Create<br::Unit>(def::kUnitKeys.at((br::UnitType)type.GetInt()), base);
            a->SetTeam(def::kPlayerTeam);
            _unit_manager.AddUnit(a);
        } // for
    }
    { // エネミーユニット配置
        const auto& enemies = _unit_doc["enemies"];
        _ASSERT_EXPR(enemies.IsArray(),
                     L"enemies type is not array");
        for (int i = 0; i < enemies.Size(); i++) {
            if (!enemies[i].HasMember("type") || !enemies[i]["type"].IsInt() ||
                !enemies[i].HasMember("name") || !enemies[i]["name"].IsString() ||
                !enemies[i].HasMember("x") || !enemies[i]["x"].IsInt() ||
                !enemies[i].HasMember("y") || !enemies[i]["y"].IsInt()) {
                break;
            } // if

            const auto& type = enemies[i]["type"];
            const auto& name = enemies[i]["name"];
            const auto& x = enemies[i]["x"];
            const auto& y = enemies[i]["y"];

            auto base = br::ActorBaseState();
            base.name = name.GetString();
            base.position = Mof::CVector2(x.GetInt() * def::kChipSize,
                                          y.GetInt() * def::kChipSize);
            base.type = br::ActorType::Unit;
            auto a = _factory.Create<br::Unit>(def::kUnitKeys.at((br::UnitType)type.GetInt()), base);
            a->SetTeam(def::kEnemyTeam);
            _unit_manager.AddUnit(a);
        } // for
    }
    _unit_manager.Initialize();
    return true;
}

bool br::ActorManager::Update(void) {
    _unit_manager.Update();
    return true;
}

bool br::ActorManager::Render(Mof::CVector2 scroll) {
    _unit_manager.Render(scroll);
    return true;
}

bool br::ActorManager::Release(void) {
    _unit_manager.Release();
    _factory.Release();
    return true;
}