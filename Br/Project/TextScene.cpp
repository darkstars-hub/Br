#include "TextScene.h"

#include <Mof.h>

#include "Helper.h"
#include "ResourceManager.h"
#include "AudioSystem.h"


void br::TextScene::UpdateScene(void) {
    super::Fade();
    if (!_text_system.IsShow()) {
        super::ChangeScene();
    } // if
}

br::TextScene::TextScene() :
    _back_texture(),
    _text_system(),
    _infomation() {
    super::_resource_manager = std::make_shared<br::ResourceManager>();
    super::_audio_system = std::make_shared<br::AudioSystem>();
}

br::TextScene::~TextScene() {
}

br::SceneId br::TextScene::GetSceneId(void) const {
    return br::SceneId::TextScene;
}

br::SceneId br::TextScene::GetNextScene(void) const {
    return br::SceneId::Load;
}

std::shared_ptr<br::SceneInfomation> br::TextScene::GetNextSceneInfomation(void) {
    auto ret = std::make_shared<br::LoadSceneInfomation>();
    ret->resource_manager_data_path =
        "Resource/scene/select_scene_resources.txt";
    ret->audio_system_data_path =
        "Resource/scene/select_scene_sounds.txt";
    ret->next_scene = this->_infomation.next_scene;
    ret->next_scene_info = std::make_shared<br::SelectInfomation>();
    return ret;
}

bool br::TextScene::Input(void) {
    _text_system.Input();
    return true;
}

bool br::TextScene::Initialize(std::shared_ptr<br::SceneInfomation> in) {
    this->_infomation = *std::dynamic_pointer_cast<br::TextSceneInfomation>(in);
    auto& info = this->_infomation;

    // 表示テキスト読み込み、表示
    _text_system.SetResourceManager(super::_resource_manager);

    _text_system.Show(info.text_path);
    // 背景読み込み
    _back_texture.Load(info.texture_path);
    // BGM読み込み、再生
    auto bgm = std::make_shared<Mof::CStreamingSoundBuffer>();
    bgm->Load(info.bgm_path);
    bgm->SetLoop(true);
    _audio_system->AddSound(info.bgm_path, bgm);
    _audio_system->Play(info.bgm_path);
    return true;
}

bool br::TextScene::Update(void) {
    this->UpdateScene();

    if (_text_system.IsShow()) {
        _text_system.Update();
    } // if

    _audio_system->Update();
    return true;
}

bool br::TextScene::Render(void) {
    _back_texture.Render(0.0f, 0.0f);
    if (_text_system.IsShow()) {
        _text_system.Render();
    } //if


    super::RenderFade();
    return true;
}

bool br::TextScene::Release(void) {
    _back_texture.Release();
    _text_system.Release();
    return true;
}