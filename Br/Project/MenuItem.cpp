#include "MenuItem.h"

#include "Menu.h"


//int br::MenuItem::_text_size = 32;
//std::vector<Mof::CRectangle> br::MenuItem::_texts;
//std::vector<size_t> br::MenuItem::wait;
//std::vector<size_t> br::MenuItem::attack;
//std::vector<size_t> br::MenuItem::fusion;
//std::vector<size_t> br::MenuItem::back;
//std::vector<size_t> br::MenuItem::turn_end;


Mof::CRectangle br::MenuItem::GetBackRect(void) {
    return Mof::CRectangle();
}

void br::MenuItem::BackRender(void) {
}

//void br::MenuItem::Setup(void) {
    //‚ ‚¢‚¤‚¦‚¨‚©‚«‚­‚¯‚±‚³‚µ‚·‚¹‚»‚½‚¿‚Â‚Ä‚Æ20
    //‚È‚É‚Ê‚Ë‚Ì‚Í‚Ð‚Ó‚Ö‚Ù‚Ü‚Ý‚Þ‚ß‚à‚â‚¢‚ä‚¦‚æ40
    //‚ç‚è‚é‚ê‚ë‚í‚¢‚¤‚¦‚ð...
   // int col = 13; int row = 5; int size = _text_size; int offset = 6;
   // for (int x = 0; x < col; x++) {
   //     for (int y = 0; y < row; y++) {
   //         auto rect = Mof::CRectangle(
   //             x * size,
   //             y * size + y * offset,
   //             x * size + size,
   //             y * size + size + y * offset);
   //         _texts.push_back(rect);
   //     } // for
   // } // for
//    wait = { 15, 1, 6 };
//    attack = { 15, 15, 5, 2 };
//    fusion = { 36, 2, 9, 60, 2 };
//    back = { 34, 19, 60, 42 };
//    turn_end = { 15, 62, 47, 11, 56, 2, 41, 57, 2 };
//}

br::MenuItem::MenuItem(
    std::vector<size_t> indices, br::MenuTextures* textures, std::function<bool(void)>action, br::Menu* owner) :
    _position(),
    _text_indices(indices),
    _texture(textures->_text),
    _action(action),
    _selected(false),
    _owner(owner) {

    int col = 13; int row = 5; int size = _text_size; int offset = 6;
    for (int x = 0; x < col; x++) {
        for (int y = 0; y < row; y++) {
            auto rect = Mof::CRectangle(
                x * size,
                y * size + y * offset,
                x * size + size,
                y * size + size + y * offset);
            _texts.push_back(rect);
        } // for
    } // for
}

void br::MenuItem::Excute(void) {
    _action();
}

void br::MenuItem::SetPosition(Mof::CVector2 position) {
    this->_position = position;
}

void br::MenuItem::SetSelect(bool b) {
    this->_selected = b;
}

std::vector<size_t>& br::MenuItem::GetIndices(void) {
    return this->_text_indices;
}

void br::MenuItem::Render(void) {
    if (auto tex = _texture.lock()) {
        auto rect = Mof::CRectangle(_position.x,
                                    _position.y,
                                    _position.x + _owner->GetBackRect().GetWidth(),
                                    _position.y + _text_size);
        if (_selected) {
            ::CGraphicsUtilities::RenderFillRect(
                rect, MOF_ARGB(255, 0, 255, 255));
        } // if
        else {
            ::CGraphicsUtilities::RenderFillRect(
                rect, MOF_ARGB(255, 0, 255, 0));
        } // else

        auto offset = Mof::CVector2();
        for (auto i : _text_indices) {
            tex->Render(
                _position.x + offset.x,
                _position.y + offset.y,
                _texts.at(i));
            offset.x += _text_size;
        } // for
    } // if
}