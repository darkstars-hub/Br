//!-----------------------------------------------------
//! @file : Load.h
//! @brief : ���[�h��
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
    //! �e�N�X�`���̉�]�p�x
    int _angle_count;
    //! ���̒l���ő�l�ɂȂ��_angle_count���P�オ��
    int _wait_count;
    //! _wait_count�̍ő�l
    const int _wait_count_max;

    ////! �ǂݍ��݂����s����
    std::thread _thread;

    br::SceneId _next_scene;
    //! ���̓f�[�^
    br::LoadSceneInfomation _infomation;

    //std::weak_ptr<Mof::CTexture> _logo_texture;
    std::unique_ptr<Mof::CTexture> _logo_texture;
    //std::weak_ptr<Mof::CTexture> _loading_texture;
    std::unique_ptr<Mof::CTexture> _loading_texture;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    //Load();
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](const char* resource_manager) ResourceManager�œǂݍ��ރp�X
    //! @param : [in](const char* audio_system) AudioSystem�œǂݍ��ރp�X
    //! @return : none
    //!-----------------------------------------------------
    //Load(const char* resource_manager, const char* audio_system);
    Load();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~Load();


    //!-----------------------------------------------------
    //! @brief : �J�ڂ�����Id��ݒ肷��
    //! @param : [in](br::SceneId scene) �V�[����ID
    //! @return : none
    //!-----------------------------------------------------
    //void SetNextScene(br::SceneId scene);
    //!-----------------------------------------------------
    //! @brief : ���̃V�[����Id���擾����
    //! @param : [in](void) none
    //! @return : ���̃V�[����Id
    //!-----------------------------------------------------
    br::SceneId GetSceneId(void) const override;
    //!-----------------------------------------------------
    //! @brief : �J�ڂ�����Id���擾����
    //! @param : [in](void) none
    //! @return : �J�ڂ�����Id
    //!-----------------------------------------------------
    br::SceneId GetNextScene(void) const override;
    //!-----------------------------------------------------
    //! @brief : ���̃V�[����TextScene�̎���TextScene���K�v�ȏ���Ԃ�
    //! @param : [in](void) none
    //! @return : �e�L�X�g�V�[���̏��
    //!-----------------------------------------------------
    br::TextSceneInfomation GetTextSceneInfomation(void);
//    br::SelectInfomation GetSelectInfomation(void) override;
    std::shared_ptr<br::SceneInfomation> GetNextSceneInfomation(void) override;


    //!-----------------------------------------------------
    //! @brief : ����
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Input(void) override;

    //!-----------------------------------------------------
    //! @brief : ������
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Initialize(std::shared_ptr<br::SceneInfomation> info) override;
    //!-----------------------------------------------------
    //! @brief : �X�V
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Render(void) override;
    //!-----------------------------------------------------
    //! @brief : ���
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Release(void) override;
};
}
#endif // !BR_LOAD_H