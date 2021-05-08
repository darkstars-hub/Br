#include "Actor.h"

#include <iterator>

#include "Component.h"


br::Actor::Actor(br::Scene* scene) :
    _components(),
    _update_components(),
    _render_components(),
    _scene(scene),
    _base() {
}

br::Actor::~Actor() {
}

br::Scene* br::Actor::GetScene(void) const {
    return this->_scene;
}

void br::Actor::SetPosition(const Mof::CVector2 position) {
    this->_base.position = position;
}

void br::Actor::AddComponent(Component* component) {
    int priority = component->GetPriority();
    auto it = _components.begin();
    auto it_end = _components.end();
    for (; it != it_end; ++it) {
        if (priority < (*it)->GetPriority()) {
            break;
        } // if
    } // for
    _components.insert(it, component);
}

void br::Actor::AddUpdateComponent(Component* component) {
    int priority = component->GetPriority();
    auto it = _update_components.begin();
    auto it_end = _update_components.end();
    for (; it != it_end; ++it) {
        if (priority < (*it)->GetPriority()) {
            break;
        } // if
    } // for
    _update_components.insert(it, component);
}

void br::Actor::AddRenderComponent(Component* component) {
    int priority = component->GetPriority();
    auto it = _render_components.begin();
    auto it_end = _render_components.end();
    for (; it != it_end; ++it) {
        if (priority < (*it)->GetPriority()) {
            break;
        } // if
    } // for
    _render_components.insert(it, component);
}

void br::Actor::RemoveComponent(Component* component) {
    if (component->IsUpdate()) {
        auto it = std::find(
            _update_components.begin(),
            _update_components.end(),
            component);
        if (it != _update_components.end()) {
            _update_components.erase(it);
        } // if
    } // if
    if (component->IsRender()) {
        auto it = std::find(
            _render_components.begin(),
            _render_components.end(),
            component);
        if (it != _render_components.end()) {
            _render_components.erase(it);
        } // if
    } // if
    auto it = std::find(
        _components.begin(),
        _components.end(),
        component);
    if (it != _components.end()) {
        MOF_SAFE_DELETE(*it);
        _components.erase(it);
    } // if
}

void br::Actor::RemoveUpdateComponent(Component* component) {
    auto it = std::find(
        _update_components.begin(),
        _update_components.end(),
        component);
    if (it != _update_components.end()) {
        _update_components.erase(it);
    } // if
}

void br::Actor::RemoveRenderComponent(Component* component) {
    auto it = std::find(
        _render_components.begin(),
        _render_components.end(),
        component);
    if (it != _render_components.end()) {
        _render_components.erase(it);
    } // if
}

bool br::Actor::Load(const char* path) {
    return true;
}

bool br::Actor::Input(void) {
    return true;
}

bool br::Actor::Initialize(const br::ActorBaseState& base) {
    _base = base;
    for (auto com : _components) {
        com->Initialize();
    } // for

    auto com_sort = [&](std::vector<br::Component*>& com) {
        std::sort(com.begin(),
                  com.end(),
                  [](br::Component* l, br::Component* r) {
            return l->GetPriority() < r->GetPriority();
        });
    };
    com_sort(_components);
    com_sort(_update_components);
    com_sort(_render_components);
    return true;
}

bool br::Actor::Update(void) {
    for (auto com : _update_components) {
        com->Update();
    } // for
    return true;
}

bool br::Actor::Render(Mof::CVector2 scroll) {
    for (auto com : _render_components) {
        com->Render(scroll);
    } // for
    return true;
}

bool br::Actor::Release(void) {
    for (auto c : _components) {
        c->Release();
        MOF_SAFE_DELETE(c);
    } // for
    return true;
}

void br::Actor::Construct(std::shared_ptr<br::Builder> bl) {
    std::transform(bl->_components.begin(),
                   bl->_components.end(),
                   std::back_inserter(_components), [](
                       br::Component* c) {
        return c->Clone();
    });
    //コンポーネントを更新と描画に仕分け
    std::copy_if(_components.begin(),
                 _components.end(),
                 std::back_inserter(_update_components),
                 [](br::Component* c) {
        return c->IsUpdate();
    });
    std::copy_if(_components.begin(),
                 _components.end(),
                 std::back_inserter(_render_components),
                 [](br::Component* c) {
        return c->IsRender();
    });

    for (auto c : _components) {
        c->_owner = this;
      //  c->Initialize();
    } // for
}