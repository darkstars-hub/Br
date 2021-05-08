//!-----------------------------------------------------
//! @file : TextSceneInfomation.h
//! @brief : TextScene�ɓn����������
//! @date : 2020/07/26
//!-----------------------------------------------------


#ifndef BR_TEXT_SCENE_INFOMATION_H
#define BR_TEXT_SCENE_INFOMATION_H


#include "SceneInfomation.h"
//#include "Scene.h"


namespace br {
struct TextSceneInfomation : public br::SceneInfomation {
    //! TextSystem�ɓ��͂���f�[�^�̃p�X
    const char* text_path = "";
    //! �w�i�摜�̃p�X
    const char* texture_path = "";
    //! BGM�̃p�X
    const char* bgm_path = "";
    //! �J�ڐ�̃V�[��
    br::SceneId next_scene = br::SceneId::GameOver;
};
}
#endif // !BR_TEXT_SCENE_INFOMATION_H