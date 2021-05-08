//!-----------------------------------------------------
//! @file : Game.h
//! @brief : ゲーム部分
//! @date : 2020/05/26
//!-----------------------------------------------------


#ifndef BR_GAME_H
#define BR_GAME_H


#include "Scene.h"

#include <Mof.h>

#include "Cursor.h"
#include "Menu.h"
#include "Camera.h"
#include "SelectInfomation.h"
#include "GameUI.h"
#include "GameSystem.h"


namespace br {
class Game : public br::Scene {
    using super = br::Scene;
private:
    //! カメラ
    br::Camera _camera;
    //static 
    std::string _turn;

    //! 遷移先のシーン
    br::SceneId _next_scene;
    //! 読み込む情報の構造体
    br::SelectInfomation _select_infomation;
    
    //! ゲームのUI
    br::GameUI _ui;
    //! ゲームのギミック
    br::GameSystem _system;

    //!-----------------------------------------------------
    //! @brief : シーンを遷移する必要があるなら遷移先を設定する
    //! @param : [in](void) none
    //! @return : シーンを遷移する必要があるならtrueを返す
    //!-----------------------------------------------------
    bool UpdateScene(void);
    //!-----------------------------------------------------
    //! @brief : クリアデータをファイルに書き込む
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void WriteStageClearData(void);
public:
    //!-----------------------------------------------------
     //! @brief : ゲッター
     //! @param : [in](void) none
     //! @return : 現在のターンを取得
     //!-----------------------------------------------------
    std::string GetTurn(void);
     //!-----------------------------------------------------
     //! @brief : 現在のターンを変更する
     //! @param : [in](std::string str) ターンの名前
     //! @return : none
     //!-----------------------------------------------------
    void ChangeTurn(const std::string& str);
	
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Game();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~Game();

    //!-----------------------------------------------------
    //! @brief : このシーンのIdを取得する
    //! @param : [in](void) none
    //! @return : このシーンのId
    //!-----------------------------------------------------
    br::SceneId GetSceneId(void) const override;
    //!-----------------------------------------------------
    //! @brief : 遷移する先のIdを取得する
    //! @param : [in](void) none
    //! @return : 遷移する先のId
    //!-----------------------------------------------------
    br::SceneId GetNextScene(void) const override;

    //!-----------------------------------------------------
    //! @brief : 前のシーンで選択した情報を受け取る
    //! @param : [in](br::SelectInfomation info) 読み込む情報の構造体
    //! @return : none
    //!-----------------------------------------------------
    void AcquireSelectData(br::SelectInfomation info);
    
    br::ReverseGuage* GetReverseGuage(void);
    br::BattleSystem* GetBattleSystem(void);
    br::BattleSystemForecast* GetBattleSystemForeCast(void);
    br::FusionSystem* GetFusionSystem(void);
    br::SelectInfomation GetSelectInfomation(void);

    //!-----------------------------------------------------
    //! @brief : 入力
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Input(void) override;

    //!-----------------------------------------------------
    //! @brief : 初期化
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Initialize(std::shared_ptr<br::SceneInfomation> info) override;
    //!-----------------------------------------------------
    //! @brief : 更新
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Render(void) override;
    //!-----------------------------------------------------
    //! @brief : 解放
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Release(void) override;
};
}
#endif // !BR_GAME_H