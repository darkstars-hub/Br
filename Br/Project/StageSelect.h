//!-----------------------------------------------------
//! @file : StageSelect.h
//! @brief : ステージを選ぶ画面
//! @date : 2020/07/09
//!-----------------------------------------------------


#ifndef BR_STAGE_SELECT_H
#define BR_STAGE_SELECT_H


#include "Scene.h"

#include <vector>
#include <string>

#include <Mof.h>
#include "SelectInfomation.h"
#include "TextSceneInfomation.h"
#include "LoadSceneInfomation.h"

#include "SelectIcon.h"


namespace br {
class StageSelect : public br::Scene {
    using super = br::Scene;
private:
    //! 選択アイコンの位置
    Mof::CVector2 _icon_position;
    //! 選択アイコンのテクスチャ
    Mof::CTexture _select_icon;
    //! ステージ（一枚絵）の画像
    Mof::CTexture _stage_texture;
    //! マサラタウンの当たり判定
    br::SelectIcon _stage0;
    //! トキワシティの当たり判定
    br::SelectIcon _stage1;
    //! ニビシティの当たり判定
    br::SelectIcon _stage2;
    //! 海のステージの当たり判定
    br::SelectIcon _stage3;
    //! ラストステージの当たり判定
    br::SelectIcon _stage4;

    //! 選んだステージの名前
    const char* _stage_name;
    //! 選んだステージの情報
    const char* _stage_info;
    //! ゲームシーンに渡す選択したステージの情報
    br::SelectInfomation _infomation;
    //! BGM
    Mof::CSoundBuffer _bgm;
    //! 選択時効果音
    Mof::CSoundBuffer _select_sound;
    //! 決定時効果音
    Mof::CSoundBuffer _enter_sound;

    std::vector<std::string> _cleared_stage_string;

    //!-----------------------------------------------------
    //! @brief : 矩形の取得
    //! @param : [in](void) none
    //! @return : アイコンの大きさの矩形
    //!-----------------------------------------------------
    Mof::CRectangle GetIconRectangle(void);
    void UpdateScene(void);
    //!-----------------------------------------------------
    //! @brief : クリア済みか確認する
    //! @param : [in](const std::string path) ゲームステージのパス
    //! @return : クリアしているかどうか
    //!-----------------------------------------------------
    bool CheckCleared(const std::string& path);

    void Load(void);
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    StageSelect();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~StageSelect();


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
    //br::TextSceneInfomation GetTextSceneInfomation(void) override;
    //!-----------------------------------------------------
    //! @brief : 次のシーンがLoadSceneの時にLoadSceneが必要な情報を返す
    //! @param : [in](void) none
    //! @return : ロードシーンの情報
    //!-----------------------------------------------------
    //br::LoadSceneInfomation GetLoadSceneInfomation(void) override;
private:
    br::SelectInfomation GetSelectInfomation(void);
public:
    std::shared_ptr<br::SceneInfomation> GetNextSceneInfomation(void) ;


//    br::SelectInfomation GetInfomation(void) const;


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
#endif // !BR_STAGE_SELECT_H