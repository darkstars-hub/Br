//!-----------------------------------------------------
//! @file : ActorManager.h
//! @brief : Unitやらなんやらの配列を持つ
//! @date : 2020/06/05
//!-----------------------------------------------------


#ifndef BR_ACTOR_MANAGER_H
#define BR_ACTOR_MANAGER_H


#include <vector>

#include <Mof.h> 

#include "../include/rapidjson/document.h"

#include "Scene.h"
#include "Game.h"
#include "Unit.h"
#include "UnitManager.h"
#include "ActorFactory.h"
#include "Builder.h"


namespace br {
class ActorManager {
private:
    //! 現在のシーン
    br::Scene* _scene;
    //! ゲームシーン
    br::Game* _game;
    //! 管理しているユニット
    br::UnitManager _unit_manager;
    //! シーン上のすべてのゲームオブジェクト
    //std::vector<br::Actor*> _actors;
    //! ユニット情報
    rapidjson::Document _unit_doc;
    //! エネミー情報
    rapidjson::Document _enemy_doc;
    //! ユニット作成者
    br::ActorFactory _factory;
protected:
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Scene* scene) 現在のシーン
    //! @return : none
    //!-----------------------------------------------------
    ActorManager(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~ActorManager();

    //void SetGame(br::Game* ptr);
    br::UnitManager* GetUnitManager(void);

    //!-----------------------------------------------------
    //! @brief : 読み込み処理
    //! @param : [in](const char* path) 読み込むデータのパス
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Load(const char* path);
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
#endif // !BR_ACTOR_MANAGER_H