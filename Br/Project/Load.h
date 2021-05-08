//!-----------------------------------------------------
//! @file : Load.h
//! @brief : ロード中
//! @date : 2020/05/31
//!-----------------------------------------------------


#ifndef BR_LOAD_H
#define BR_LOAD_H


#include "Scene.h"

#include <memory>
#include <thread>

#include <Mof.h>

#include "LoadSceneInfomation.h"
#include "TextSceneInfomation.h"


namespace br {
class Load : public br::Scene {
    using super = br::Scene;
private:
    //! テクスチャの回転角度
    int _angle_count;
    //! この値が最大値になると_angle_countが１上がる
    int _wait_count;
    //! _wait_countの最大値
    const int _wait_count_max;

    ////! 読み込みを実行する
    std::thread _thread;

    br::SceneId _next_scene;
    //! 入力データ
    br::LoadSceneInfomation _infomation;

    //std::weak_ptr<Mof::CTexture> _logo_texture;
    std::unique_ptr<Mof::CTexture> _logo_texture;
    //std::weak_ptr<Mof::CTexture> _loading_texture;
    std::unique_ptr<Mof::CTexture> _loading_texture;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    //Load();
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](const char* resource_manager) ResourceManagerで読み込むパス
    //! @param : [in](const char* audio_system) AudioSystemで読み込むパス
    //! @return : none
    //!-----------------------------------------------------
    //Load(const char* resource_manager, const char* audio_system);
    Load();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~Load();


    //!-----------------------------------------------------
    //! @brief : 遷移する先のIdを設定する
    //! @param : [in](br::SceneId scene) シーンのID
    //! @return : none
    //!-----------------------------------------------------
    //void SetNextScene(br::SceneId scene);
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
    br::TextSceneInfomation GetTextSceneInfomation(void);
//    br::SelectInfomation GetSelectInfomation(void) override;
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
#endif // !BR_LOAD_H