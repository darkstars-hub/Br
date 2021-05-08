//!-----------------------------------------------------
//! @file : UnitManager.h
//! @brief : ユニット管理を受け持つ
//! @date : 2020/06/12
//!-----------------------------------------------------


#ifndef BR_UNIT_MANAGER_H
#define BR_UNIT_MANAGER_H


#include <vector>

#include "Helper.h"
#include "Scene.h"
#include "Game.h"
#include "Unit.h"
#include "Menu.h"
#include "ReverseGuage.h"


namespace br {
class UnitManager {
private:
    //! 現在のシーン
    br::Scene* _scene;
    br::Game* _game;
    //! 全てのユニット
    std::vector<br::Unit*> _units;
    //! 全てのプレイヤー
    std::vector<br::Unit*> _players;
    //! 全てのエネミー
    std::vector<br::Unit*> _enemies;
    //! 相性逆転ギミックのポインタ
    br::ReverseGuage* _reverse_guage;
public:
    UnitManager(br::Scene* scene);
    ~UnitManager();

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    //void SetReverseGuage(br::ReverseGuage* ptr);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](int col) 列
    //! @param : [in](int row) 行
    //! @return : none
    //!-----------------------------------------------------
    br::Unit* GetUnit(def::Vector2i pos);
    br::Unit* GetUnit(int col, int row);


    //!-----------------------------------------------------
    //! @brief : プレイヤーのリーダーユニットが死んでいるか確認する
    //! @param : [in](void) none
    //! @return : 死んでいるならtrueを返す    
    //!-----------------------------------------------------
    bool IsPlayerBossDead(void);
    //!-----------------------------------------------------
    //! @brief : 全ての敵が死んでいるか確認する
    //! @param : [in](void) none
    //! @return : 死んでいるならtrueを返す    
    //!-----------------------------------------------------
    bool IsAllEnemyDead(void);

    //!-----------------------------------------------------
    //! @brief : ユニットの追加
    //! @param : [in](br::Unit* unit) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void AddUnit(br::Unit* unit);
    //!-----------------------------------------------------
    //! @brief : プレイヤーのユニットを行動済みにする
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void AllPlayerEnd(void);

    std::vector<br::Unit*>& GetUnits(void);

    //!-----------------------------------------------------
    //! @brief : 受け取ったユニットが配列の何番目にあるか取得する
    //! @param : [in](br::Unit* unit) 調べるユニット
    //! @return : プレイヤーのユニットのインデックス
    //!-----------------------------------------------------
    int GetPlayerIndex(br::Unit* unit);
    //int GetIndex(br::Unit* unit,std::vector<br::Unit*> units);
    br::Unit* GetUnitAtIndex(size_t index);
    size_t GetPlayerUnitSize(void);

    //!-----------------------------------------------------
    //! @brief : 入力処理
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Input(void);
    //!-----------------------------------------------------
    //! @brief : 初期化
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Initialize(void);
    //!-----------------------------------------------------
    //! @brief : 更新
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Update(void);
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Render(Mof::CVector2 scroll);
    //!-----------------------------------------------------
    //! @brief : 解放処理
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Release(void);
};
}
#endif // !BR_UNIT_MANAGER_H