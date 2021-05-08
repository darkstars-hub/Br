//!-----------------------------------------------------
//! @file : GameClear.h
//! @brief : ゲームクリア画面
//! @date : 2020/07/08
//!-----------------------------------------------------


#ifndef BR_GAME_CLEAR_H
#define BR_GAME_CLEAR_H


#include "Scene.h"

#include <Mof.h>


namespace br {
class GameClear : public br::Scene {
    using super = br::Scene;
private:
    Mof::CTexture _texture;
        //! BGM
    Mof::CSoundBuffer _bgm;
    void UpdateScene(void);
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    GameClear();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~GameClear();


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
#endif // !BR_GAME_CLEAR_H