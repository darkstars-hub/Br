//!-----------------------------------------------------
//! @file : MenuMessage.h
//! @brief : メニュー表示用の基底クラス
//! @date : 2020/07/11
//!-----------------------------------------------------


#ifndef BR_MENU_MESSAGE_H
#define BR_MENU_MESSAGE_H


namespace br {
class MenuMessage {
public:
    MenuMessage() = default;
    virtual ~MenuMessage() = default;
};
}
#endif // !BR_MENU_MESSAGE_H