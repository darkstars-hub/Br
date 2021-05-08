#include "Menu.h"

#include <locale>
#include <iostream>
#include "Helper.h"
#include "MenuMessenger.h"


size_t br::Menu::GetTextSize(void) const {
    return _text_size;
}

br::Menu::Menu(br::Scene* scene) :
    _scene(scene),
    _is_show(false),
    _position(),
    _index(0),
    _textures(){
}

br::Menu::~Menu() {
}

bool br::Menu::IsShow(void) {
    return this->_is_show;
}

Mof::CRectangle br::Menu::GetBackRect(void) {
    auto size = this->GetTextSize();
    int width = 0; int height = 0;
    for (auto& i : _items) {
        width = width < i.GetIndices().size() ? i.GetIndices().size() : width;
        height++;
    } // for
    return Mof::CRectangle(0.0, 0.0f, width * size, height * size);
}

Mof::CVector2 br::Menu::GetPosition(void) {
    return this->_position;
}

int br::Menu::GetIndex(void) {
    return this->_index;
}

bool br::Menu::Load(void) {
    _textures.Load(_scene->GetResourceManager());
    return true;
}

bool br::Menu::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        this->Decide();
        return true;
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_BACK)) {
        this->Cancel();
        return true;
    } // if

    if (::g_pInput->IsKeyPush(MOFKEY_UP)) {
        this->ShiftIndex(-1);
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_DOWN)) {
        this->ShiftIndex(1);
    } // if
    return true;
}

bool br::Menu::Update(void) {
    if (!_is_show) {
        return false;
    } // if
    return true;
}

bool br::Menu::Render(void) {
    if (!_is_show) {
        return false;
    } // if

    for (auto i : _items) {
        i.Render();
    } // for
    return true;
}

void br::Menu::ShiftIndex(const int count) {
    _items.at(_index).SetSelect(false);
    _index += count;
    _index = std::clamp(_index, 0, (int)_items.size() - 1);
    _items.at(_index).SetSelect(true);
}

void br::Menu::Release(void) {
    _textures.Release();
    _items.clear();
}