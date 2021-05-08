//!-----------------------------------------------------
//! @file : MenuMessenger.h
//! @brief : メニューの表示、管理を受け持つ
//! @date : 2020/07/11
//!-----------------------------------------------------


#ifndef BR_MENU_MESSENGER_H
#define BR_MENU_MESSENGER_H


#include <vector>

#include "Scene.h"
#include "Menu.h"

namespace br {
class MenuMessenger {
private:
    br::Scene* _scene;
    br::Menu* _menu;

    bool _is_delete;
public:
    MenuMessenger(br::Scene* scene);
    ~MenuMessenger();

    bool IsMenuShow(void);
    template<typename T>
    void Show(br::MenuMessage* e) {
        _menu = new T(_scene);
        _menu->Show(e);
        _is_delete = false;
    }

    //void Show(class Unit* ptr);
    void Hide(void);

    void Input(void);
    void Update(void);
    void Render(void);
    void Release(void);
};
}
#endif // !BR_MENU_MESSENGER_H