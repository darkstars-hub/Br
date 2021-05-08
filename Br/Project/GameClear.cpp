#include "GameClear.h"

#include <Mof.h>

#include "Helper.h"
#include "ResourceManager.h"
#include "AudioSystem.h"


void br::GameClear::UpdateScene(void) {
    super::Fade();
}

br::GameClear::GameClear() :
    _texture(),
    _bgm() {
    super::_resource_manager = std::make_shared<br::ResourceManager>();
    super::_audio_system = std::make_shared<br::AudioSystem>();

    _texture.Load("Resource/textures/game_clear.png");
    _bgm.Load("Resource/bgm/game_maoudamashii_7_event08.mp3");
    _bgm.SetLoop(true);
    _bgm.Play();
}

br::GameClear::~GameClear() {
}

br::SceneId br::GameClear::GetSceneId(void) const {
    return br::SceneId::GameClear;
}

br::SceneId br::GameClear::GetNextScene(void) const {
    return br::SceneId::Title;
}

bool br::GameClear::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        super::ChangeScene();
   //     _is_end = true;
        return true;
    } // if

    return true;
}

bool br::GameClear::Initialize(std::shared_ptr<br::SceneInfomation> info) {
    return true;
}

bool br::GameClear::Update(void) {
    this->UpdateScene();
    _audio_system->Update();
    return true;
}

bool br::GameClear::Render(void) {
    ::CGraphicsUtilities::RenderString(
        400.0f, 400.0f,
        "Game Clear");

    _texture.Render(300.0f, 300.0f);
    super::RenderFade();
    return true;
}

bool br::GameClear::Release(void) {
    _texture.Release();
    _bgm.Release();
    return true;
}