#define MUTE
#include "GameOver.h"

#include <Mof.h>

#include "Helper.h"
#include "ResourceManager.h"
#include "AudioSystem.h"


void br::GameOver::UpdateScene(void) {
    super::Fade();
}

br::GameOver::GameOver() :
    _texture(),
    _bgm() {
    super::_resource_manager = std::make_shared<br::ResourceManager>();
    super::_audio_system = std::make_shared<br::AudioSystem>();

    _texture.Load("Resource/textures/game_over.png");
    _bgm.Load("Resource/bgm/game_maoudamashii_7_event01.mp3");
    _bgm.SetLoop(true);
#ifndef MUTE
    _bgm.Play();
#endif //!MUTE
}

br::GameOver::~GameOver() {
}

br::SceneId br::GameOver::GetSceneId(void) const {
    return br::SceneId::GameOver;
}

br::SceneId br::GameOver::GetNextScene(void) const {
    return br::SceneId::Title;
}

bool br::GameOver::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        super::ChangeScene();
        //_is_end = true;
        return true;
    } // if

    return true;
}

bool br::GameOver::Initialize(std::shared_ptr<br::SceneInfomation> info) {
    return true;
}

bool br::GameOver::Update(void) {
    this->UpdateScene();
    _audio_system->Update();
    return true;
}

bool br::GameOver::Render(void) {
    ::CGraphicsUtilities::RenderString(
        400.0f, 400.0f,
        "Game Over");
    _texture.Render(300.0f, 300.0f);

    super::RenderFade();
    return true;
}

bool br::GameOver::Release(void) {
    _texture.Release();
    _bgm.Release();
    return true;
}