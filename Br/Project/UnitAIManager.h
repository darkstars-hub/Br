//!-----------------------------------------------------
//! @file : UnitAIManager.h
//! @brief : 敵ユニットのAIの制御をする
//! @date : 2020/06/20
//!-----------------------------------------------------


#ifndef BR_UNIT_AI_MANAGER_H
#define BR_UNIT_AI_MANAGER_H


#include <vector>

#include "Unit.h"
#include "UnitManager.h"
#include "AIParam.h"


namespace br {
class UnitAIManager {
private:
    UnitAIManager();
    ~UnitAIManager();

    std::vector<br::Unit*>* _players;
    std::vector<br::Unit*>* _enemies;
    //size_t _index;
public:
    static br::UnitAIManager& GetInstance();

    void SetUnits(std::vector<br::Unit*>* players,std::vector<br::Unit*>* enemies);
    const std::vector<br::Unit*>* GetPlayers(void);


    //!-----------------------------------------------------
    //! @brief : プレイヤーのLordユニットを探して取得
    //! @param : [in](void) none
    //! @return : いないならnullptrを返す
    //!-----------------------------------------------------
    br::Unit* SearchPlayerBoss(void);
    //!-----------------------------------------------------
    //! @brief : 最寄りのプレイヤーユニットを探して取得
    //! @param : [in](void) none
    //! @return : いないならnullptrを返す
    //!-----------------------------------------------------
    br::Unit* SearchNearestPlayer(Mof::CVector2 position);
    //!-----------------------------------------------------
    //! @brief : AIParamを参照して対象を取得
    //! @param : [in](br::AIParam& param) 重み情報
    //! @return : いないならnullptrを返す
    //!-----------------------------------------------------
    br::Unit* SearchTargetUnit(br::AIParam& param);

    bool Update(void);

    //!-----------------------------------------------------
    //! @brief : AIParamにプレイヤーユニットを追加する
    //! @param : [out](br::AIParam& param) パラメータ
    //! @return : none
    //!-----------------------------------------------------
    void PlayerSetTo(br::AIParam& param);
};
}
#endif // !BR_UNIT_AI_MANAGER_H