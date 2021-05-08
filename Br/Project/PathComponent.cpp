#include "PathComponent.h"

#include "UnitPath.h"


br::PathComponent::PathComponent(Actor* owner, int priority)
    :super(owner, priority),
    _path(),
    _path_render(nullptr) {
}

br::PathComponent::~PathComponent() {
}

const std::vector<br::PathDataPointer>& br::PathComponent::GetPath(void) const {
    return this->_path;
}

br::PathDataPointer br::PathComponent::GetElement(std::size_t index) {
    return _path.at(index);
}

bool br::PathComponent::IsArrived(size_t index) const {
    return index >= _path.size() - 1;
}

void br::PathComponent::Clear(void) {
    _path.clear();
}

void br::PathComponent::Conpute(br::Tile* tile, br::Tile* destination) {
    _path.clear();
//    AStar alg;
    br::UnitPath alg;
    alg.ConputePath(tile, destination, _path);
    _path_render->SetPath(&_path);
}

bool br::PathComponent::CheckTargetTile(const std::vector<br::RangeDataPointer>& range, br::Tile* target)const {
    if (range.empty()) {
        return false;
    } // i

    for (auto t : range) {
        if (t->_tile->Equal(target)) {
            return true;
        } // if
    } // for
    return false;
}

bool br::PathComponent::Initialize(void) {
    _path_render = _owner->GetComponent<br::PathRenderComponent>();
    return true;
}

bool br::PathComponent::Update(void) {
    return true;
}

bool br::PathComponent::Render(Mof::CVector2 scroll) {
    return true;
}

br::Component* br::PathComponent::Clone(void) {
    auto ptr = new br::PathComponent(nullptr, _priority);
    return ptr;
}