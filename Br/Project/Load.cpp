#include "Load.h"

#include <thread>
#include <Mof.h>

#include "Helper.h"
#include "ResourceManager.h"
#include "AudioSystem.h"


//br::Load::Load(br::LoadSceneInfomation& info) :
br::Load::Load() :
    super(),
    _angle_count(0),
    _wait_count(0),
    _wait_count_max(2),
    _thread(),
    _next_scene(br::SceneId::Game),
//    _infomation(info),
    _infomation(),
    _logo_texture(std::make_unique<Mof::CTexture>()),
    _loading_texture(std::make_unique<Mof::CTexture>()) {
}

br::Load::~Load() {
}
/*
void br::Load::SetNextScene(br::SceneId scene) {
    this->_next_scene = scene;
}
*/
br::SceneId br::Load::GetSceneId(void) const {
    return br::SceneId::Load;
}

br::SceneId br::Load::GetNextScene(void) const {
    return _infomation.next_scene;
}

br::TextSceneInfomation br::Load::GetTextSceneInfomation(void) {
    return _infomation.text_infomation;
}
/*
br::SelectInfomation br::Load::GetSelectInfomation(void) {
    return _infomation.select_infomation;
}
*/

std::shared_ptr<br::SceneInfomation> br::Load::GetNextSceneInfomation(void) {
    return _infomation.next_scene_info;
}

bool br::Load::Input(void) {
    return true;
}

bool br::Load::Initialize(std::shared_ptr<br::SceneInfomation> info) {
    _infomation = *std::dynamic_pointer_cast<br::LoadSceneInfomation>(info);

        // •\Ž¦‰æ‘œ‚¾‚¯æ‚É“Ç‚Ýž‚ñ‚Å‚¨‚­
    //_logo_texture = super::_resource_manager->GetTexture("Resource/textures/now_loading.png");
    _logo_texture->Load("Resource/textures/now_loading.png");
    //_loading_texture = super::_resource_manager->GetTexture("Resource/textures/loading.png");
    _loading_texture->Load("Resource/textures/loading.png");

    // “Ç‚Ýž‚Ý
    _thread = std::thread([&]() {
        this->_next_resource->Load(_infomation.resource_manager_data_path);
//         _resource_manager->Load(_infomation.resource_manager_data_path);
        this->_next_audio->Load(_infomation.audio_system_data_path);
//         _audio_system->Load(_infomation.audio_system_data_path);
    });
    return true;
}

bool br::Load::Update(void) {
    if (_next_resource->IsLoaded() && _next_audio->IsLoaded()) {
//    if (_resource_manager->IsLoaded() && _audio_system->IsLoaded()) {
        if (!super::IsChange()) {
            _thread.join();
            super::ChangeScene();
        } // if
    } // if
    else {
        if (_wait_count++ > _wait_count_max) {
            _wait_count = 0;
        } // if

        if (_wait_count == _wait_count_max) {
            if (_angle_count++ > 360) {
                _angle_count = 0;
            } // if
        } // if
    } // else
    super::Fade();
    return true;
}

bool br::Load::Render(void) {
    // “Ç‚Ýž‚Ý’†‚Ì”wŒi
    auto back = super::_resource_manager->GetTexture(_infomation.back_texture_path);
    if (back) {
        back->Render(0.0f, 0.0f);
    } // if

    // ‚®‚é‚®‚é‰ñ‚é‰æ‘œ‚ÆNowLoading‰æ‘œ
    _loading_texture->RenderRotate(500.0f, 300.0f, _angle_count, TEXTUREALIGNMENT_CENTERCENTER);
    _logo_texture->Render(400.0f, 600.0f);
    super::RenderFade();
    return true;
}

bool br::Load::Release(void) {
    _logo_texture->Release();
    _loading_texture->Release();
    return true;
}