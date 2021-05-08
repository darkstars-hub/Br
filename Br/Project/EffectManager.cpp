#include "EffectManager.h"

br::EffectManager::EffectManager(br::Scene* scene) :
    _effects(),
    _scene(scene) {
}

br::EffectManager::~EffectManager() {
}

std::shared_ptr<br::Effect> br::EffectManager::GetEffectByName(const char* name) {
    auto it = std::find_if(_effects.begin(),
                           _effects.end(),
                           [&](std::shared_ptr<br::Effect> e) {
        return e->GetName() == name;
    });
    // ������Ȃ��Ȃ�nullptr��Ԃ�;
    if (it == _effects.end()) {
        return nullptr;
    } // if
    return *it;
}

bool br::EffectManager::Update(void) {
    // �A�j���[�V�����̏I�������G�t�F�N�g�͍폜����
    _effects.erase(std::remove_if(_effects.begin(), _effects.end(), [](std::shared_ptr<br::Effect> e) {
        return e->GetState() == br::ActorState::Dead;
    }), _effects.end());

    for (auto e : _effects) {
        e->Update();
    } // for
    return true;
}
bool br::EffectManager::Render(Mof::CVector2 scroll) {
    for (auto e : _effects) {
        e->Render(scroll);
        //e->Render({});
    } // for
    return true;
}
bool br::EffectManager::Release(void) {
    return true;
}

void br::EffectManager::Start(const char* path, Mof::CVector2 position, const char* name) {
    auto effect = std::make_shared<br::Effect>(_scene);

    effect->Initialize({});
    effect->Start(path, position, name);
    //effect->Start("Resource/sprites/miss_effect/miss_effect.sprite", Mof::CVector2(200.0f, 200.0f));
    //_effects.emplace(std::make_pair(path, effect));
    _effects.push_back(effect);
}