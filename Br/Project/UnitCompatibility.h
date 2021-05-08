//!-----------------------------------------------------
//! @file : UnitCompatibility.h
//! @brief : ���j�b�g�^�C�v���Ƃɂ��鑊���̃e�[�u��
//! @date : 2020/06/22
//!-----------------------------------------------------


#ifndef BR_UNIT_COMPATIBILITY_MANAGER_H
#define BR_UNIT_COMPATIBILITY_MANAGER_H


#include "Common.h"


namespace br {
class UnitCompatibility {
public:
    enum class Effective {
        NormalEffective, // �ʏ�̑���
        SuperEffective, // ���ʂ̓o�c�O����
        NotVeryEffective, // ���ʂ͂��܂ЂƂ̂悤��
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