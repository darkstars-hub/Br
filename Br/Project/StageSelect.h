//!-----------------------------------------------------
//! @file : StageSelect.h
//! @brief : �X�e�[�W��I�ԉ��
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
    //! �I���A�C�R���̈ʒu
    Mof::CVector2 _icon_position;
    //! �I���A�C�R���̃e�N�X�`��
    Mof::CTexture _select_icon;
    //! �X�e�[�W�i�ꖇ�G�j�̉摜
    Mof::CTexture _stage_texture;
    //! �}�T���^�E���̓����蔻��
    br::SelectIcon _stage0;
    //! �g�L���V�e�B�̓����蔻��
    br::SelectIcon _stage1;
    //! �j�r�V�e�B�̓����蔻��
    br::SelectIcon _stage2;
    //! �C�̃X�e�[�W�̓����蔻��
    br::SelectIcon _stage3;
    //! ���X�g�X�e�[�W�̓����蔻��
    br::SelectIcon _stage4;

    //! �I�񂾃X�e�[�W�̖��O
    const char* _stage_name;
    //! �I�񂾃X�e�[�W�̏��
    const char* _stage_info;
    //! �Q�[���V�[���ɓn���I�������X�e�[�W�̏��
    br::SelectInfomation _infomation;
    //! BGM
    Mof::CSoundBuffer _bgm;
    //! �I�������ʉ�
    Mof::CSoundBuffer _select_sound;
    //! ���莞���ʉ�
    Mof::CSoundBuffer _enter_sound;

    std::vector<std::string> _cleared_stage_string;

    //!-----------------------------------------------------
    //! @brief : ��`�̎擾
    //! @param : [in](void) none
    //! @return : �A�C�R���̑傫���̋�`
    //!-----------------------------------------------------
    Mof::CRectangle GetIconRectangle(void);
    void UpdateScene(void);
    //!-----------------------------------------------------
    //! @brief : �N���A�ς݂��m�F����
    //! @param : [in](const std::string path) �Q�[���X�e�[�W�̃p�X
    //! @return : �N���A���Ă��邩�ǂ���
    //!-----------------------------------------------------
    bool CheckCleared(const std::string& path);

    void Load(void);
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    StageSelect();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~StageSelect();


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
    //br::TextSceneInfomation GetTextSceneInfomation(void) override;
    //!-----------------------------------------------------
    //! @brief : ���̃V�[����LoadScene�̎���LoadScene���K�v�ȏ���Ԃ�
    //! @param : [in](void) none
    //! @return : ���[�h�V�[���̏��
    //!-----------------------------------------------------
    //br::LoadSceneInfomation GetLoadSceneInfomation(void) override;
private:
    br::SelectInfomation GetSelectInfomation(void);
public:
    std::shared_ptr<br::SceneInfomation> GetNextSceneInfomation(void) ;


//    br::SelectInfomation GetInfomation(void) const;


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
#endif // !BR_STAGE_SELECT_H