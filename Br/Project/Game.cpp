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
    // �N���A���̃e�L�X�g���o��
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
    // �v���C���[�̃��[�_�[���j�b�g�����S����
    // ���j���[���܂��o�Ă��Ȃ��Ƃ�
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
    // �f�o�b�O�p��ʑJ��
    if (::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        super::ChangeScene();
        return true;
    } // if

    _cursor->Input();
    // ���j���[���͏���
    if (_menu_messenger && _menu_messenger->IsMenuShow()) {
        _menu_messenger->Input();
        return true;
    } // if
    // UI���͏���
    if (_ui.IsTextSystemShow()) {
        _ui.Input();
        return true;
    } // if
    // �M�~�b�N���͏���
    if (_system.IsBattleSystemShow()) {
        _system.Input();
        return true;
    } // if
    // �Q�[�����͏���  
    _actor_manager->Input();
    return true;
}

bool br::Game::Initialize(std::shared_ptr<br::SceneInfomation> info) {
    _select_infomation = *std::dynamic_pointer_cast<br::SelectInfomation>(info);

    _ASSERT_EXPR(_select_infomation.select, L"�I����񂪓����Ă��܂���");
    // �Q�[������������
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

    // UI������
    _ui.Initialize(this);
    // �Q�[���V�X�e��������
    _system.Initialize(this);
    return true;
}

bool br::Game::Update(void) {
    // �߂�l���Q�[���̏�����������̂��̔��f�ɗ��p����
    auto end = this->UpdateScene();

    // �����̏������̓Q�[�������̍X�V�͂��Ȃ�
    if (_system.IsShow()) {
        end = true;
    } // if
    // �Q�[���V�X�e���̍X�V
    _system.Update();

    // �Q�[���X�V
    if (!end) {
        super::_cursor->Update();
        super::_world->Update();
        super::_actor_manager->Update();
    } // if

    // UI�X�V
    _ui.Update();
    // ���j���[�X�V
    if (_menu_messenger) {
        _menu_messenger->Update();
    } // if
    // ��ʌ��ʍX�V
    _effect_manager->Update();

    // �J�����X�V
    _camera.Update();
    // �����Ǘ����X�V�i�X�g���[�~���O�Đ��ׁ̈j
    _audio_system->Update();
    return true;
}

bool br::Game::Render(void) {
    // �`��
    //_audio_system->Render();
    auto scroll = _camera.GetScroll();
    auto offset = _ui.GetUIWindowOffset();

    // �Q�[���`��
    super::_world->Render(scroll - offset);
    super::_actor_manager->Render(scroll - offset);
    super::_cursor->Render(scroll - offset);

    // �Q�[���V�X�e���`��
    _system.Render();
    // UI�`��
    _ui.Render(_system.IsBattleSystemShow());
    // ���j���[�`��
    if (_menu_messenger) {
        _menu_messenger->Render();
    } // if
    // ��ʌ��ʕ\��
    _effect_manager->Render(scroll - offset);
    // ��ʑJ�ڌ��ʕ\��
    super::RenderFade();
    return true;
}

bool br::Game::Release(void) {
   // ���
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