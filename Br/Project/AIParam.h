//!-----------------------------------------------------
//! @file : AIParam.h
//! @brief :  このパラメータを持っているエネミーユニットが
//!           攻撃対象を選択するときに参照する入力情報
//! @date : 2020/07/22
//!-----------------------------------------------------


#ifndef BR_AI_PARAM_H
#define BR_AI_PARAM_H


#include <vector>

//#include "Unit.h"


namespace br {
class AIParam {
private:
    //! 考えてる人
    //br::Unit* _owner;
    class Unit* _owner;
    //! エネミーがプレイヤーを狙うときの優先度（重み）
    //int _weight;
    //! 攻撃対象となりうるプレイヤーユニットのポインタ
    //std::vector<br::Unit*> _targets;
    //! エネミーがプレイヤーを狙うときの優先度（重み）
    //std::vector<std::pair<br::Unit*, int>> _weights;
    std::vector<std::pair<class Unit*, int>> _weights;
    //! ユニット情報
    //class UnitAIManager* _ai_manager;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Unit* _owner) 考えている人
    //! @return : none
    //!-----------------------------------------------------
    AIParam();
    AIParam(class Unit* owner);
    ~AIParam();

    //!-----------------------------------------------------
    //! @brief : 攻撃対象とするユニット
    //! @param : [in](void) none
    //! @return : 重みが最大のユニット
    //!-----------------------------------------------------
    //br::Unit* GetTargetUnit(void);
    class Unit* GetTargetUnit(void);

    //!-----------------------------------------------------
    //! @brief : 重み情報を初期化（リセット）する
    //! @param : [in](std::vector<br::Unit*>& players) none
    //! @return : none
    //!-----------------------------------------------------
    //void Initialize(std::vector<br::Unit*>& players);
    //void Initialize(std::vector<class Unit*>& players);
    
    //!-----------------------------------------------------
    //! @brief : 狙うかもしれないユニットを追加する
    //! @param : [in](br::Unit* player) プレイヤーユニット
    //! @return : none
    //!-----------------------------------------------------
    //void AddUnit(br::Unit* player);
    void AddUnit(class Unit* player);
    //!-----------------------------------------------------
    //! @brief : 重み情報を追加する
    //! @param : [in](br::Unit* player) このユニットに対して
    //! @param : [in](int value) 重みの値
    //! @return : none
    //!-----------------------------------------------------
    void AddWeight(class Unit* player, int value);
};
}
#endif // !BR_AI_PARAM_H