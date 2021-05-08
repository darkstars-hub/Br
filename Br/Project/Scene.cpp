#include "Scene.h"

#include "MenuMessenger.h"
#include "ResourceManager.h"
#include "AudioSystem.h"
#include "Cursor.h"
#include "Menu.h"
#include "TextSceneInfomation.h"
#include "LoadSceneInfomation.h"
#include "SelectInfomation.h"


br::Scene::Scene() :
    _is_end(false),
    _resource_manager(),
    _next_resource(),
    _audio_system(),
    _next_audio(),
    _world(nullptr),
    _cursor(nullptr),
    _menu_messenger(nullptr),
    _actor_manager(nullptr),
    _effect_manager(nullptr),
    _is_change(),
    _alpha(255) {
    _next_resource = std::make_shared<br::ResourceManager>();
    _next_audio = std::make_shared<br::AudioSystem>();
}

br::Scene::~Scene() {
    _resource_manager->Release();
    _resource_manager.reset();
    _audio_system->Release();
    _audio_system.reset();
}

void br::Scene::AcquireResource(const std::shared_ptr<br::ResourceManager> r,
                                const std::shared_ptr<br::AudioSystem> a) {
    this->_resource_manager = r;
    this->_audio_system = a;
}

std::shared_ptr<br::ResourceManager> br::Scene::GetResourceManager(void) const {
    return this->_resource_manager;
}
std::shared_ptr<br::ResourceManager> br::Scene::GetNextResourceManager(void) const {
    return this->_next_resource;
}

std::shared_ptr<br::AudioSystem> br::Scene::GetAudioSystem(void) const {
    return this->_audio_system;
}
std::shared_ptr<br::AudioSystem> br::Scene::GetNextAudioSystem(void) const {
    return this->_next_audio;
}

br::Stage* br::Scene::GetStage(void) const {
    return this->_world;
}

br::Cursor* br::Scene::GetCursor(void) const {
    return this->_cursor;
}

br::MenuMessenger* br::Scene::GetMenu(void) const {
    return this->_menu_messenger;
}

br::ActorManager* br::Scene::GetActorManager(void) const {
    return this->_actor_manager;
}

br::EffectManager* br::Scene::GetEffectManager(void) const {
    return this->_effect_manager;
}

bool br::Scene::IsEnd(void) const {
    return this->_is_end;
}

std::shared_ptr<br::SceneInfomation> br::Scene::GetNextSceneInfomation(void) {
    return std::shared_ptr<br::SceneInfomation>();
}

bool br::Scene::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
        std::exit(0);
    } // if

    return true;
}


void br::Scene::RenderFade(void) {
    auto rect = Mof::CRectangle(0.0f, 0.0, def::kWindowWidth, def::kWindowHeight);
    ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(_alpha, 0, 0, 0));
}

void br::Scene::Fade(void) {
    std::lock_guard<std::mutex> lock(_mutex);

    if (!_is_change && _alpha >= 0) {
        _alpha -= 10;
        if (_alpha <= 0) {
            _alpha = 0;
        } // if
    } // if
    if (_is_change) {
        if (_alpha < 255) {
            _alpha += 10;
        } // if
        if (_alpha >= 255) {
            _alpha = 255;
        } // if
    } // if


    if (_is_change && _alpha >= 255) {
        this->_is_end = true;
    } // if
}

void br::Scene::ChangeScene(void) {
    std::lock_guard<std::mutex> lock(_mutex);
    _is_change = true;
}

bool br::Scene::IsChange(void) {
    std::lock_guard<std::mutex> lock(_mutex);
    return _is_change;
}