#include "MenuMessenger.h"

#include "Unit.h"


br::MenuMessenger::MenuMessenger(br::Scene* scene) :
    _scene(scene),
    _menu(nullptr),
    _is_delete(false) {
}

br::MenuMessenger::~MenuMessenger() {
    if (_menu) {
        _menu->Release();
    } // if
    MOF_SAFE_DELETE(_menu);
}

bool br::MenuMessenger::IsMenuShow(void) {
    if (_menu && _menu->IsShow()) {
        return true;;
    } // if

    return false;;
}

void br::MenuMessenger::Hide(void) {
    if (!_menu) {
        return;
    } // if
    _is_delete = true;
}

void br::MenuMessenger::Input(void) {
    if (_menu != nullptr) {
        _menu->Input();
    } // if
}

void br::MenuMessenger::Update(void) {
    if (_menu && _is_delete) {
        MOF_SAFE_DELETE(_menu);
     } // if
    
    if (_menu) {
        _menu->Update();
    } // if
}

void br::MenuMessenger::Render(void) {
    if (_menu) {
        _menu->Render();
    } // if
}

void br::MenuMessenger::Release(void) {
    _scene = nullptr;
}