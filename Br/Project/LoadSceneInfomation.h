//!-----------------------------------------------------
//! @file : LoadSceneInfomation.h
//! @brief : LoadSceneに渡す情報を内包する
//! @date : 2020/07/26
//!-----------------------------------------------------


#ifndef BR_LOAD_SCENE_INFOMATION_H
#define BR_LOAD_SCENE_INFOMATION_H


#include <string>
#include <memory>

#include "SceneInfomation.h"

#include "Scene.h"
#include "TextSceneInfomation.h"
#include "SelectInfomation.h"

namespace br {
struct LoadSceneInfomation : public br::SceneInfomation {
    //! ResourceManager::Loadに渡すパス
    const char* resource_manager_data_path = "";
    //! AudioSystem::Loadに渡すパス
    const char* audio_system_data_path = "";
    //! 遷移先のシーン
    br::SceneId next_scene = br::SceneId::GameOver;
    //! TextSceneに渡す情報
    br::TextSceneInfomation text_infomation;
    //! GameSceneに渡す情報
    br::SelectInfomation select_infomation;
    //! Load画面の背景画像のパス
    const char* back_texture_path = "";
    //! ロード後のシーン
    std::shared_ptr<br::SceneInfomation>next_scene_info;
    
};
}
#endif // !BR_LOAD_SCENE_INFOMATION_H
