#include "Game.h"

#include "Helper.h"
#include "ResourceManager.h"
#include "AudioSystem.h"
#include "ActorManager.h"
#include "EffectManager.h"
#include "Stage.h"
#include "MenuMessenger.h"
#include "GameOverMenu.h"
#include "GameOverMenuMessage.h"


bool br::Game::UpdateScene(void) {
    super::Fade();

    auto um = super::_actor_manager->GetUnitManager();
    // クリア時のテキストを出す
    if (um->IsAllEnemyDead()) {
        if (!_system.IsShow() && !_ui.IsTextSystemShow()) {
            this->WriteStageClearData();
            //_next_scene = br::SceneId::GameClear;
            _next_scene = br::SceneId::StageSelect;
            if (_select_infomation.stage_data_path == "Resource/stage/stage4.txt") {
                _next_scene = br::SceneId::GameClear;
            } // if

            _ui.TextShow(_select_infomation.clear_text_path, [this]() {
                super::ChangeScene();
            });
        } // if
        return true;
    } // if
    // プレイヤーのリーダーユニットが死亡して
    // メニューがまだ出ていないとき
    if (um->IsPlayerBossDead()) {
        if (!_ui.IsTextSystemShow()) {
            _ui.TextShow("Resource/texts/player_boss_dead.text_system");
        } // if
        else if (!_menu_messenger->IsMenuShow() && !super::IsChange()) {
            _next_scene = br::SceneId::GameOver;
            auto m = new br::GameOverMenuMessage();
            m->game = this;
            m->actor_manager = _actor_manager;
            m->cursor = _cursor;
            m->stage = _world;
            _menu_messenger->Show<br::GameOverMenu>(m);
        } // else if
        return true;
    } // if
    return false;
}

void br::Game::WriteStageClearData(void) {
    std::ofstream os("Resource/stage/cleared_stage_paths.txt");
    os << _select_infomation.stage_data_path << std::endl;
}

std::string br::Game::GetTurn(void) {
    return _turn;
}

void br::Game::ChangeTurn(const std::string& str) {
    _turn = str;
}

br::Game::Game() :
    _camera(this),
    _turn(def::kPlayerTeam),
    _next_scene(br::SceneId::GameOver),
    _select_infomation(),
    _ui(),
    _system() {
}

br::Game::~Game() {
}

br::SceneId br::Game::GetSceneId(void) const {
    return br::SceneId::Game;
}

br::SceneId br::Game::GetNextScene(void) const {
    return this->_next_scene;
}

void br::Game::AcquireSelectData(br::SelectInfomation info) {
    _select_infomation = info;
}

br::ReverseGuage* br::Game::GetReverseGuage(void) {
    return this->_ui.GetReverseGuage();
}

br::BattleSystem* br::Game::GetBattleSystem(void) {
    return this->_system.GetBattleSystem();
}

br::BattleSystemForecast* br::Game::GetBattleSystemForeCast(void) {
    return _ui.GetBattleSystemForeCast();
}

br::FusionSystem* br::Game::GetFusionSystem(void) {
    return this->_system.GetFusionSystem();
}

br::SelectInfomation br::Game::GetSelectInfomation(void) {
    return this->_select_infomation;
}

bool br::Game::Input(void) {
    super::Input();
    // デバッグ用画面遷移
    if (::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        super::ChangeScene();
        return true;
    } // if

    _cursor->Input();
    // メニュー入力処理
    if (_menu_messenger && _menu_messenger->IsMenuShow()) {
        _menu_messenger->Input();
        return true;
    } // if
    // UI入力処理
    if (_ui.IsTextSystemShow()) {
        _ui.Input();
        return true;
    } // if
    // ギミック入力処理
    if (_system.IsBattleSystemShow()) {
        _system.Input();
        return true;
    } // if
    // ゲーム入力処理  
    _actor_manager->Input();
    return true;
}

bool br::Game::Initialize(std::shared_ptr<br::SceneInfomation> info) {
    _select_infomation = *std::dynamic_pointer_cast<br::SelectInfomation>(info);

    _ASSERT_EXPR(_select_infomation.select, L"選択情報が入っていません");
    // ゲーム部分初期化
    auto b = br::ActorBaseState(); b.position.x = 64.0f; b.position.y = 64.0f;
    super::_cursor = new br::Cursor(this, &_camera.GetScroll());
    super::_cursor->Initialize(b);
    super::_menu_messenger = new br::MenuMessenger(this);
    super::_world = new br::Stage(this);
    super::_world->Load(_select_infomation.stage_data_path);
    super::_world->Initialize({});
    super::_actor_manager = new br::ActorManager(this);
    super::_actor_manager->Load(_select_infomation.unit_data_path);
    super::_actor_manager->Initialize();
    super::_effect_manager = new br::EffectManager(this);
    _camera.SetCursor(super::_cursor);

    // UI初期化
    _ui.Initialize(this);
    // ゲームシステム初期化
    _system.Initialize(this);
    return true;
}

bool br::Game::Update(void) {
    // 戻り値をゲームの処理ををするのかの判断に利用する
    auto end = this->UpdateScene();

    // これらの処理中はゲーム部分の更新はしない
    if (_system.IsShow()) {
        end = true;
    } // if
    // ゲームシステムの更新
    _system.Update();

    // ゲーム更新
    if (!end) {
        super::_cursor->Update();
        super::_world->Update();
        super::_actor_manager->Update();
    } // if

    // UI更新
    _ui.Update();
    // メニュー更新
    if (_menu_messenger) {
        _menu_messenger->Update();
    } // if
    // 画面効果更新
    _effect_manager->Update();

    // カメラ更新
    _camera.Update();
    // 音声管理情報更新（ストリーミング再生の為）
    _audio_system->Update();
    return true;
}

bool br::Game::Render(void) {
    // 描画
    //_audio_system->Render();
    auto scroll = _camera.GetScroll();
    auto offset = _ui.GetUIWindowOffset();

    // ゲーム描画
    super::_world->Render(scroll - offset);
    super::_actor_manager->Render(scroll - offset);
    super::_cursor->Render(scroll - offset);

    // ゲームシステム描画
    _system.Render();
    // UI描画
    _ui.Render(_system.IsBattleSystemShow());
    // メニュー描画
    if (_menu_messenger) {
        _menu_messenger->Render();
    } // if
    // 画面効果表示
    _effect_manager->Render(scroll - offset);
    // 画面遷移効果表示
    super::RenderFade();
    return true;
}

bool br::Game::Release(void) {
   // 解放
    super::_world->Release();
    MOF_SAFE_DELETE(_world);
    super::_cursor->Release();
    MOF_SAFE_DELETE(_cursor);

    super::_actor_manager->Release();
    MOF_SAFE_DELETE(super::_actor_manager);
    super::_audio_system->Release();
    super::_resource_manager->Release();

    super::_effect_manager->Release();
    MOF_SAFE_DELETE(_effect_manager);

    MOF_SAFE_DELETE(_menu_messenger);

    return true;
}