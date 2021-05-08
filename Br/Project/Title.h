//!-----------------------------------------------------
//! @file : Title.h
//! @brief : タイトル
//! @date : 2020/05/28
//!-----------------------------------------------------


#ifndef BR_TITLE_H
#define BR_TITLE_H


#include "Scene.h"

#include <vector>

#include <Mof.h>

#include "TextSceneInfomation.h"
#include "LoadSceneInfomation.h"


namespace br {
class Title : public br::Scene {
    using super = br::Scene;
private:
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Title();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~Title();
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
    //! @brief : 次のシーンがTextSceneの時にTextSceneが必要な情報を返す
    //! @param : [in](void) none
    //! @return : テキストシーンの情報
    //!-----------------------------------------------------
private:
    br::TextSceneInfomation GetTextSceneInfomation(void);
public:
    //!-----------------------------------------------------
    //! @brief : 次のシーンがLoadSceneの時にLoadSceneが必要な情報を返す
    //! @param : [in](void) none
    //! @return : ロードシーンの情報
    //!-----------------------------------------------------
//    br::LoadSceneInfomation GetLoadSceneInfomation(void) override;
    std::shared_ptr<br::SceneInfomation> GetNextSceneInfomation(void) override;
    
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
#endif // !BR_TITLE_H