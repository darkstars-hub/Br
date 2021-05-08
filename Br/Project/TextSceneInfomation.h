//!-----------------------------------------------------
//! @file : TextSceneInfomation.h
//! @brief : TextSceneに渡す情報を内包する
//! @date : 2020/07/26
//!-----------------------------------------------------


#ifndef BR_TEXT_SCENE_INFOMATION_H
#define BR_TEXT_SCENE_INFOMATION_H


#include "SceneInfomation.h"
//#include "Scene.h"


namespace br {
struct TextSceneInfomation : public br::SceneInfomation {
    //! TextSystemに入力するデータのパス
    const char* text_path = "";
    //! 背景画像のパス
    const char* texture_path = "";
    //! BGMのパス
    const char* bgm_path = "";
    //! 遷移先のシーン
    br::SceneId next_scene = br::SceneId::GameOver;
};
}
#endif // !BR_TEXT_SCENE_INFOMATION_H