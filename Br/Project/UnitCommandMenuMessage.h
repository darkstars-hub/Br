//!-----------------------------------------------------
//! @file : UnitCommandMenuMessage.h
//! @brief : ���j�b�g�̍s�����j���[�\���p�̃N���X
//! @date : 2020/07/11
//!-----------------------------------------------------


#ifndef BR_UNIT_COMMAND_MENU_MESSAGE_H
#define BR_UNIT_COMMAND_MENU_MESSAGE_H


#include "MenuMessage.h"

#include "Unit.h"


namespace br {
class UnitCommandMenuMessage : public br::MenuMessage {
    using super = br::MenuMessage;
public:
    br::Unit* target;
};
}
#endif // !BR_UNIT_COMMAND_MENU_MESSAGE_H