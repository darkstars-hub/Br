#include "HpComponent.h"

#include "ResourceManager.h"
#include "Helper.h"


br::HpComponent::HpComponent(Actor* owner, int priority) :
    super(owner, priority),
    _value_max(10),
    _value(_value_max),
    _is_show(true),
    _textrue(),
    _render_rect(Mof::CRectangle(0.0f, 0.0f, 8.0f, 8.0f)),
    _render_offset(8.0f) {
    super::_type = ComponentType::HpComponent;
}

br::HpComponent::~HpComponent() {
}

void br::HpComponent::SetShow(bool show) {
    this->_is_show = show;
}

void br::HpComponent::SetMaxHp(int value) {
    this->_value_max = value;
}

void br::HpComponent::SetHp(int value) {
    this->_value = value;
}

int br::HpComponent::GetValue(void)const {
    return this->_value;
}

int br::HpComponent::GetMaxValue(void) const {
    return this->_value_max;
}

void br::HpComponent::Damege(int value) {
    _value -= value;
    if (_value <= 0) {
        _value = 0;
    } // if
}

void br::HpComponent::Heal(int value) {
    _value += value;
    if (_value_max <= _value) {
        _value = _value_max;
    } // if
}

bool br::HpComponent::Initialize(void) {
    _textrue = super::_owner->GetScene()
        ->GetResourceManager()->GetTexture("Resource/textures/hp.png");
    return true;
}

bool br::HpComponent::Update(void) {
    return true;
}

bool br::HpComponent::Render(Mof::CVector2 scroll) {
    if (auto r = _textrue.lock()) {
        auto pos = super::_owner->GetPosition();

        // 1 * ♡ = 10 * HP
        int vm = _value_max / 10;
        int v = _value / 10;
        // 真ん中にくるようにする
        pos.x += def::kChipSize * 0.5f;
        pos.x -= (_render_offset * 0.5f) * vm;
        pos.y += def::kChipSize - r->GetHeight();
        // 描画
        for (int i = 0; i < vm; i++) {
            auto rect = _render_rect;
            if (v - i <= 0) {
                rect.Translation(Mof::CVector2(_render_offset, 0.0f));
            } // if
            r->Render(pos.x - scroll.x, pos.y - scroll.y, rect);
            pos.x += _render_offset;
        } // for
    } // if
    return true;
}

br::Component* br::HpComponent::Clone(void) {
    auto ptr = new br::HpComponent(nullptr, _priority);
    return ptr;
}