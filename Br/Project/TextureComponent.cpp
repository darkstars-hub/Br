#include "TextureComponent.h"


br::TextureComponent::TextureComponent(br::Actor* owner, int priority) :
    super(owner, priority),
    _texture(),
    _rectangle(),
    _motion(nullptr) {
    super::_type = ComponentType::TextureComponent;
}

br::TextureComponent::~TextureComponent() {
}

void br::TextureComponent::SetTexture(std::weak_ptr<Mof::CTexture> texture,
                                      const Mof::Rectangle* rectangle) {
    if (auto r = texture.lock()) {
        this->_texture = texture;
        if (rectangle) {
            _rectangle = *rectangle;
        } // if
        else {
            _rectangle = Mof::CRectangle(
                0.0f,
                0.0f,
                r->GetWidth(),
                r->GetHeight());
        } // else
    } // if
}

void br::TextureComponent::SetMotionComponent(br::MotionComponent& c) {
    this->_motion = &c;
}

bool br::TextureComponent::Initialize(void) {
    super::Initialize();
    _motion = _owner->GetComponent<br::MotionComponent>();
    return true;
}

bool br::TextureComponent::Update(void) {
    return true;
}

bool br::TextureComponent::Render(Mof::CVector2 scroll) {
    if (auto r = _texture.lock()) {
        auto pos = super::_owner ->GetPosition();
        Mof::CRectangle rect = _rectangle;
        if (_motion) {
            rect = _motion->GetRenderRectangle();
        } // if
        {
#ifdef _DEBUG
            ::CGraphicsUtilities::RenderFillRect(
                CRectangle(pos.x - scroll.x,
                           pos.y - scroll.y,
                           pos.x + rect.GetWidth() - scroll.x,
                           pos.y + rect.GetHeight() - scroll.y),
                MOF_ARGB(99, 99, 99, 99));
#endif // _DEBUG
        }
        r->Render(pos.x - scroll.x,
                  pos.y - scroll.y,
                  rect);
    } // if
    return true;
}

bool br::TextureComponent::Release(void) {
    _texture.reset();
    return true;
}

br::Component* br::TextureComponent::Clone(void) {
    auto ptr = new br::TextureComponent(nullptr, _priority);
    ptr->_texture = this->_texture;
    ptr->_rectangle = this->_rectangle;
    return ptr;
}