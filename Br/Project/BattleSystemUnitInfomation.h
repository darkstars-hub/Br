//!-----------------------------------------------------
//! @file : BattleSystemUnitInfomation .h
//! @brief : バトルシステムの中で動くユニット
//! @date : 2020/07/18
//!-----------------------------------------------------


#ifndef BR_BATTLE_SYSTEM_UNIT_INFOMATION_H
#define BR_BATTLE_SYSTEM_UNIT_INFOMATION_H


#include <Mof.h>

#include "BattleSystemUnit.h"


namespace br {
class BattleSystemUnitInfomation {
private:
    //! 情報の表示位置
    Mof::CVector2 _position;
    //! 表示矩形のサイズ
   const Mof::CVector2 _size;
    //! このユニットの情報を表示する
    br::BattleSystemUnit* _unit;
public:
    BattleSystemUnitInfomation();
    ~BattleSystemUnitInfomation();
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](br::BattleSystemUnit* ptr) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetUnit(br::BattleSystemUnit* ptr);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](Mof::CVector2 position) 表示位置
    //! @return : none
    //!-----------------------------------------------------
    void SetPosition(Mof::CVector2 position);

    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 表示矩形のサイズ
    //!-----------------------------------------------------
    Mof::CVector2 GetSize(void);


    //!-----------------------------------------------------
    //! @brief : セットしたユニットの情報の表示
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Render(void);
};
}
#endif // !BR_BATTLE_SYSTEM_UNIT_INFOMATION_H