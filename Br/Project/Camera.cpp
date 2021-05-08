#include "Camera.h"

#include "Helper.h"
#include "Common.h"
#include "Cursor.h"
#include "Stage.h"


br::Camera::Camera(br::Scene* scene) :
    _scroll(),
    _scene(scene),
    _cursor(nullptr) {
}

br::Camera::~Camera() {
}

void br::Camera::SetCursor(Cursor* cursor) {
    this->_cursor = cursor;
}

void br::Camera::Initialize(void) {
    _scroll = Mof::CVector2();
}

void br::Camera::Update(void) {
    // UI�E�C���h�E����ʂ��߂Ă���l���������� UI�͏�E��L���^
    auto offset = def::kUIWindowOffset; // UI�E�C���h�E����ʂ��߂Ă���l
    //auto offset = 128; // UI�E�C���h�E����ʂ��߂Ă���l

    auto size = def::kChipSize;
    if (_cursor) {
        auto pos = _cursor->GetPosition() - _scroll;
        if (pos.y < 0 + def::kPadding) {
            _scroll.y -= def::kChipSize;
        } // if
        else if (def::kWindowHeight - size - def::kPadding - offset < pos.y) {
            _scroll.y += def::kChipSize;
        } // else if
        if (pos.x < 0 + def::kPadding) {
            _scroll.x -= def::kChipSize;
        } // if
        else if (def::kWindowWidth - size - def::kPadding - offset < pos.x) {
            _scroll.x += def::kChipSize;
        } // else if
    } // if
}

Mof::CVector2& br::Camera::GetScroll(void) {
    return this->_scroll;
}