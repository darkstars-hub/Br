//!-----------------------------------------------------
//! @file : BattleSystemUnitInfomation .h
//! @brief : �o�g���V�X�e���̒��œ������j�b�g
//! @date : 2020/07/18
//!-----------------------------------------------------


#ifndef BR_BATTLE_SYSTEM_UNIT_INFOMATION_H
#define BR_BATTLE_SYSTEM_UNIT_INFOMATION_H


#include <Mof.h>

#include "BattleSystemUnit.h"


namespace br {
class BattleSystemUnitInfomation {
private:
    //! ���̕\���ʒu
    Mof::CVector2 _position;
    //! �\����`�̃T�C�Y
   const Mof::CVector2 _size;
    //! ���̃��j�b�g�̏���\������
    br::BattleSystemUnit* _unit;
public:
    BattleSystemUnitInfomation();
    ~BattleSystemUnitInfomation();
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](br::BattleSystemUnit* ptr) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetUnit(br::BattleSystemUnit* ptr);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](Mof::CVector2 position) �\���ʒu
    //! @return : none
    //!-----------------------------------------------------
    void SetPosition(Mof::CVector2 position);

    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �\����`�̃T�C�Y
    //!-----------------------------------------------------
    Mof::CVector2 GetSize(void);


    //!-----------------------------------------------------
    //! @brief : �Z�b�g�������j�b�g�̏��̕\��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Render(void);
};
}
#endif // !BR_BATTLE_SYSTEM_UNIT_INFOMATION_H