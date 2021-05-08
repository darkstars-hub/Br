//!-----------------------------------------------------
//! @file : LoadSceneInfomation.h
//! @brief : LoadScene�ɓn����������
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
    //! ResourceManager::Load�ɓn���p�X
    const char* resource_manager_data_path = "";
    //! AudioSystem::Load�ɓn���p�X
    const char* audio_system_data_path = "";
    //! �J�ڐ�̃V�[��
    br::SceneId next_scene = br::SceneId::GameOver;
    //! TextScene�ɓn�����
    br::TextSceneInfomation text_infomation;
    //! GameScene�ɓn�����
    br::SelectInfomation select_infomation;
    //! Load��ʂ̔w�i�摜�̃p�X
    const char* back_texture_path = "";
    //! ���[�h��̃V�[��
    std::shared_ptr<br::SceneInfomation>next_scene_info;
    
};
}
#endif // !BR_LOAD_SCENE_INFOMATION_H
