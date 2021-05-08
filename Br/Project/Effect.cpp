#include "Effect.h"


br::Effect::Effect(br::Scene* scene) :
    super(scene),
    _motion(nullptr),
    _texture(nullptr),
    _is_show(false) {

    super::_base.type = br::ActorType::Effect;
    _motion = new br::MotionComponent(this, 50);
    _texture = new br::TextureComponent(this, 90);
}

br::Effect::~Effect() {
    super::Release();
    MOF_SAFE_DELETE(_motion);
    MOF_SAFE_DELETE(_texture);
}

br::ActorState br::Effect::GetState(void) const {
    return super::_base.state;
}

Mof::CVector2 br::Effect::GetPosition(void) const {
    return super::_base.position;
}

bool br::Effect::IsEndMotion(void) {
    return _motion->IsEndMotion();
}

const char* br::Effect::GetName(void) const {
    return super::_base.name;
}

bool br::Effect::Initialize(const br::ActorBaseState& base) {
    //auto r = _scene->GetResourceManager();
    //auto path = "Resource/sprites/miss_effect/miss_effect.sprite";
    //_motion->MakeAnimation(r, path);
    //_texture->SetTexture(r->GetSpritePart(path)->GetTexture());
    super::Initialize(base);
    return true;
}

bool br::Effect::Update(void) {
    if (!_is_show) {
        return false;
    } // if

    super::Update();
    if (_motion->IsEndMotion()) {
    //    super::_base.state = br::ActorState::Dead;
        _is_show = false;
    } // if
    return true;
}

bool br::Effect::Render(Mof::CVector2 scroll) {
    if (!_is_show) {
        return false;
    } // if
    super::Render(scroll);
    return true;
}

void br::Effect::Start(const char* path, Mof::CVector2 position, const char* name) {
    this->_is_show = true;

    auto r = _scene->GetResourceManager();
    //auto path = "Resource/sprites/miss_effect/miss_effect.sprite";
    _motion->MakeAnimation(r, path);
    _texture->SetTexture(r->GetSpritePart(path)->GetTexture());

    super::_base.position = position;
    super::_base.name = name;
}