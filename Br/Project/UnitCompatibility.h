//!-----------------------------------------------------
//! @file : UnitCompatibility.h
//! @brief : ユニットタイプごとにある相性のテーブル
//! @date : 2020/06/22
//!-----------------------------------------------------


#ifndef BR_UNIT_COMPATIBILITY_MANAGER_H
#define BR_UNIT_COMPATIBILITY_MANAGER_H


#include "Common.h"


namespace br {
class UnitCompatibility {
public:
    enum class Effective {
        NormalEffective, // 通常の相性
        SuperEffective, // 効果はバツグンだ
        NotVeryEffective, // 効果はいまひとつのようだ
    };
    bool _reverse;
private:
    UnitCompatibility();
    ~UnitCompatibility();
public:
    static br::UnitCompatibility& GetInstance();

    bool IsReverse(void);
    void Reverse(void);
    br::UnitCompatibility::Effective Compatibility(
        br::UnitType attacker, br::UnitType target);
};
}
#endif // !BR_UNIT_COMPATIBILITY_MANAGER_H