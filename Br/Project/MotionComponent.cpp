#include "MotionComponent.h"

#include "TextureComponent.h"


br::MotionComponent::MotionComponent(Actor* owner, int priority) :
    super(owner, priority),
    _motion(),
    _motion_state(),
    _motion_map(nullptr),
    _path(),
    _resource_manager() {
    super::_type = ComponentType::MotionComponent;
}

br::MotionComponent::~MotionComponent() {
}

void br::MotionComponent::SetState(const std::string& motion_name) {
    this->_motion_state = motion_name;
}

const std::string& br::MotionComponent::GetState(void) const {
    return this->_motion_state;
}

void br::MotionComponent::MakeAnimation(std::weak_ptr<br::ResourceManager>r, const char* path) {
    _motion.Release();
    _resource_manager = r;
    _path = std::string(path);
    if (auto rm = _resource_manager.lock()) {
        auto data = rm->GetSpritePart(_path);
        _motion.Create(data->GetAnimsAddress().data(), data->GetAnimsAddress().size());
        _motion_map = &data->GetMotionMapAddress();
    } // if
}

bool br::MotionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool br::MotionComponent::Update(void) {
    if (_motion_map->at(_motion.GetMotionNo()) != _motion_state) {
        _motion.ChangeMotionByName(_motion_state.c_str());
    } // if
    _motion.AddTimer(Mof::CUtilities::GetFrameSecond());
    return true;
}

bool br::MotionComponent::Render(Mof::CVector2 scroll) {
    return true;
}

Mof::CRectangle br::MotionComponent::GetRenderRectangle(void) {
    return this->_motion.GetSrcRect();
}

bool br::MotionComponent::IsEndMotion(void) {
    return _motion.IsEndMotion();
}

bool br::MotionComponent::ChangeMotionByName(const char* name) {
    return _motion.ChangeMotionByName(name);
}

int br::MotionComponent::GetMotionNo(void) {
    return this->_motion.GetMotionNo();
}

std::unordered_map<int, std::string>* br::MotionComponent::GetMotionMap(void) {
    return this->_motion_map;
}

br::Component* br::MotionComponent::Clone(void) {
    auto ptr = new br::MotionComponent(nullptr, _priority);
    ptr->MakeAnimation(_resource_manager, _path.c_str());
    return ptr;
}