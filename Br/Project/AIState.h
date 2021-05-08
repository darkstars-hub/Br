//!-----------------------------------------------------
//! @file : AIState.h
//! @brief : AIComponentが持つ敵ユニットの状態
//!          行先や標的の決定もする
//! @date : 2020/07/02
//!-----------------------------------------------------


#ifndef BR_AI_STATE_H
#define BR_AI_STATE_H


namespace br {
class AIState {
protected:
    class AIComponent* _owner;
public:
    AIState(class AIComponent* owner);
    
    //!-----------------------------------------------------
    //! @brief : パラメータに値をセットする
    //! @param : [out](class AIParam& param) パラメータ
    //! @return : none
    //!-----------------------------------------------------
    virtual void ParamAddTo(class AIParam& param) = 0;
    
    //!-----------------------------------------------------
    //! @brief : 入力時に呼び出す
    //! @param : [out](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual void Start(void) = 0;
    //!-----------------------------------------------------
    //! @brief : 標的を設定する
    //! @param : [out](class Unit* out) 設定値
    //! @return : none
    //!-----------------------------------------------------
    virtual void DecideTarget(class Unit* out) = 0;
    //!-----------------------------------------------------
    //! @brief : 移動先を設定する
    //! @param : [out](class Tile* out) 設定値
    //! @return : none
    //!-----------------------------------------------------
    virtual void DecideDestination(class Tile* out) = 0;
    //!-----------------------------------------------------
    //! @brief : 標的を計算する
    //! @param : [out](viud) none
    //! @return : 出力
    //!-----------------------------------------------------
    virtual class Unit* ConputeTarget(void) = 0;
    virtual class Unit* ConputeTarget(AIParam& param);
    //!-----------------------------------------------------
    //! @brief : 移動先を計算する
    //! @param : [out](viud) none
    //! @return : 出力
    //!-----------------------------------------------------
    virtual class Tile* ConputeDestination(void) = 0;
    //!-----------------------------------------------------
    //! @brief : 名前の取得
    //! @param : [in](void) none
    //! @return : 名前
    //!-----------------------------------------------------
    virtual const char* GetName(void) const = 0;
};
}
#endif // !BR_AI_STATE_H