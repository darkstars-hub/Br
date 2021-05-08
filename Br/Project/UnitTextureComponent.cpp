#include "UnitTextureComponent.h"

#include "Helper.h"


br::UnitTextureComponent::UnitTextureComponent(br::Actor* owner, int priority) :
    super(owner, priority),
    _offset(200.0f, 0.0f),
    _state(nullptr) {
    super::_type = ComponentType::UnitTextureComponent;
}

br::UnitTextureComponent::~UnitTextureComponent() {
}

bool br::UnitTextureComponent::Initialize(void) {
    super::Initialize();
    _state = super::_owner->GetComponent<br::UnitStateComponent>();
    return true;
}

bool br::UnitTextureComponent::Render(Mof::CVector2 scroll) {
    if (auto r = _texture.lock()) {
        auto pos = super::_owner->GetPosition();
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

        // 敵のテクスチャ座標に移動する
        if (_state->GetTeam() == def::kEnemyTeam) {
            rect.Translation(_offset);
        } // if

        auto c = Mof::CVector4(255.0f, 255.0f, 255.0f, 255.0f);
        if (!_state->IsActive()) {
            c.r = 155.0f; c.g = 155.0f; c.b = 155.0f;
        } // if

        r->Render(pos.x - scroll.x,
                  pos.y - scroll.y,
                  rect,
                  MOF_ARGB((int)c.a, (int)c.r, (int)c.g, (int)c.b));
    } // if
    return true;
}

br::Component* br::UnitTextureComponent::Clone(void) {
    auto ptr = new br::UnitTextureComponent(nullptr, _priority);
    ptr->_texture = this->_texture;
    ptr->_rectangle = this->_rectangle;
    return ptr;
}