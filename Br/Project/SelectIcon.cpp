#include "SelectIcon.h"

br::SelectIcon::SelectIcon(Mof::CRectangle rect) :
    _collision_rectangle(rect),
    _is_under(false),
    _sound_play(false) {
}

br::SelectIcon::~SelectIcon() {
}

void br::SelectIcon::SetUnder(bool b) {
    this->_is_under = b;
}

void br::SelectIcon::SetSoundPlay(bool b) {
    this->_sound_play = b;
}

bool br::SelectIcon::IsUnder(void) {
    return this->_is_under;
}

bool br::SelectIcon::IsSoundPlay(void) {
    return this->_sound_play;
}

bool br::SelectIcon::CollisionRectangle(Mof::CRectangle rect) {
    return _collision_rectangle.CollisionRect(rect);
}

void br::SelectIcon::RencerRect(int color) {
    ::CGraphicsUtilities::RenderFillRect(_collision_rectangle, color);
}