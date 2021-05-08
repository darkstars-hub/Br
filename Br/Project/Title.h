//!-----------------------------------------------------
//! @file : Title.h
//! @brief : �^�C�g��
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
    //! @brief : �R���X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Title();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~Title();
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
private:
    br::TextSceneInfomation GetTextSceneInfomation(void);
public:
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
#endif // !BR_TITLE_H