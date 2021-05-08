#include "Component.h"


br::Component::Component(br::Actor* owner, int priority) :
    _owner(owner),
    _priority(priority),
    _type(ComponentType::Component) {
    if (_owner) {
        _owner->AddComponent(this);
    } // if
}

br::Component::~Component() {
}

void br::Component::SetOwner(br::Actor* ptr) {
    this->_owner = ptr;
}

br::Actor* br::Component::GetOwner(void) const {
    return this->_owner;
}

int br::Component::GetPriority(void) const {
    return this->_priority;
}

br::ComponentType br::Component::GetType(void) const {
    return this->_type;
}

bool br::Component::IsUpdate(void) {
    return false;
}

bool br::Component::IsRender(void) {
    return false;
}

bool br::Component::Input(void) {
    return true;
}

bool br::Component::Initialize(void) {
    _ASSERT_EXPR(_owner, L"コンポーネントのアクターが登録されていません");
    return true;
}

bool br::Component::Release(void) {
    return true;
}