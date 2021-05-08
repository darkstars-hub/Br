#ifndef BR_UNIT_COMMAND_MENU_H
#define BR_UNIT_COMMAND_MENU_H


#include "Menu.h"

#include <vector>


namespace br {
class UnitCommandMenu : public br::Menu {
    using super = br::Menu;
private:
    br::Unit* _target;

     
    //! std::vector<Mof::CRectangle> _texts　のインデックス
     std::vector<size_t> _wait;
    //! std::vector<Mof::CRectangle> _texts　のインデックス
     std::vector<size_t> _attack;
    //! std::vector<Mof::CRectangle> _texts　のインデックス
     std::vector<size_t> _fusion;
    //! std::vector<Mof::CRectangle> _texts　のインデックス
     std::vector<size_t> _back;
    //! std::vector<Mof::CRectangle> _texts　のインデックス
     std::vector<size_t> _turn_end;
     //! std::vector<Mof::CRectangle> _texts　のインデックス
     std::vector<size_t> _reverse;
     //! std::vector<Mof::CRectangle> _texts　のインデックス
     std::vector<size_t> _heal;
public:
    UnitCommandMenu(br::Scene* scene);
    //virtual void Show(class Unit* ptr) override;

    void Decide(void)override;
    void Cancel(void) override;

    void Show(br::MenuMessage* e) override;
    void Hide(void) override;

};
}
#endif // !BR_UNIT_COMMAND_MENU_H