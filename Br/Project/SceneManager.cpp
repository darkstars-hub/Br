#include "SceneManager.h"

#include "Title.h"
#include "TextScene.h"
#include "StageSelect.h"
#include "Load.h"
#include "Game.h"
#include "GameClear.h"
#include "GameOver.h"


br::SceneManager::SceneManager() :
    _current(),
    _next() {
}

br::SceneManager::~SceneManager() {
}

br::SceneManager& br::SceneManager::Singleton(void) {
    static br::SceneManager obj;
    return obj;
}

bool br::SceneManager::Input() {
    _current->Input();
    return true;
}
bool br::SceneManager::Initialize() {
    _current = std::make_shared<br::Title>();
    _current->Initialize(nullptr);
    return true;
}

bool br::SceneManager::Update() {

    if (_current->IsEnd()) {
        auto next = _current->GetNextScene();
        switch (_current->GetNextScene()) {
        case br::SceneId::Title:
            this->ChangeScene<br::Title>();
            break;
        case br::SceneId::TextScene:
            this->ChangeScene<br::TextScene>();
            break;
        case br::SceneId::StageSelect:
            this->ChangeScene<br::StageSelect>();
            break;
        case br::SceneId::Load:
            this->ChangeScene<br::Load>();
            break;
        case br::SceneId::Game:
            this->ChangeScene<br::Game>();
            break;
        case br::SceneId::GameClear:
            this->ChangeScene<br::GameClear>();
            break;
        case br::SceneId::GameOver:
            this->ChangeScene<br::GameOver>();
            break;
        default:
            break;
        } // switch
    } // if

    _current->Update();
    return true;
}

bool br::SceneManager::Render() {

    _current->Render();
    return true;
}

bool br::SceneManager::Release() {
    _current->Release();
    _current.reset();
    return true;
}
