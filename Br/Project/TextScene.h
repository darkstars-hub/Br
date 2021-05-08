//!-----------------------------------------------------
//! @file : TextScene.h
//! @brief : �Q�[���N���A���
//! @date : 2020/07/08
//!-----------------------------------------------------


#ifndef BR_TEXT_SCENE_H
#define BR_TEXT_SCENE_H


#include "Scene.h"

#include <Mof.h>

#include "TextSystem.h"
#include "TextSceneInfomation.h"
#include "LoadSceneInfomation.h"


namespace br {
class TextScene : public br::Scene {
    using super = br::Scene;
private:
    //! �w�i�摜
    Mof::CTexture _back_texture;
    //! �e�L�X�g���̓V�X�e��
    br::TextSystem _text_system;
    //! TextScene�̓��͏��
    br::TextSceneInfomation _infomation;

    void UpdateScene(void);
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    TextScene();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~TextScene();

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
    //! @brief : ���̃V�[����LoadScene�̎���LoadScene���K�v�ȏ���Ԃ�
    //! @param : [in](void) none
    //! @return : ���[�h�V�[���̏��
    //!-----------------------------------------------------
//    br::LoadSceneInfomation GetLoadSceneInfomation(void) override;
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
#endif // !BR_TEXT_SCENE_H