#include "ReverseGuage.h"

#include "UnitCompatibility.h"


br::ReverseGuage::ReverseGuage() :
    _value_max(100),
    _value(100) {
}

br::ReverseGuage::~ReverseGuage() {
}

void br::ReverseGuage::SetResourceManager(std::weak_ptr<br::ResourceManager> r) {
    this->_resource_manager = r;
}

bool br::ReverseGuage::IsMax(void) {
    return _value == _value_max;
}

void br::ReverseGuage::Add(int value) {
    _value += value;
    if (_value_max < _value) {
        _value = _value_max;
    } // if
}

bool br::ReverseGuage::Use(void) {
    if (this->IsMax()) {
        br::UnitCompatibility::GetInstance().Reverse();
        this->Add(-_value_max);
        return true;
    } // if
    else {
        return false;
    } // else
}

//void br::ReverseGuage::Render(Mof::CVector2 position) {
void br::ReverseGuage::Render(void) {
    float x = 600.0f;
    auto position = Mof::CVector2(x, 0.0f);
    if (auto r = _resource_manager.lock()) {
        ::CGraphicsUtilities::RenderString(x, 10.0f, "リバースゲージ");
        auto rect = Mof::CRectangle(x, 40.0f, x + _value * 2, 80.0f);

        int color = _value == _value_max ?
            MOF_ARGB(255, 255, 0, 0) :
            MOF_ARGB(155, 255, 0, 0);
        ::CGraphicsUtilities::RenderFillRect(rect, color);
        //auto tex = r->GetTexture("");
        //tex->Render(position.x, position.y);
    } // if
}