//!-----------------------------------------------------
//! @file : Game.h
//! @brief : �Q�[������
//! @date : 2020/05/26
//!-----------------------------------------------------


#ifndef BR_GAME_H
#define BR_GAME_H


#include "Scene.h"

#include <Mof.h>

#include "Cursor.h"
#include "Menu.h"
#include "Camera.h"
#include "SelectInfomation.h"
#include "GameUI.h"
#include "GameSystem.h"


namespace br {
class Game : public br::Scene {
    using super = br::Scene;
private:
    //! �J����
    br::Camera _camera;
    //static 
    std::string _turn;

    //! �J�ڐ�̃V�[��
    br::SceneId _next_scene;
    //! �ǂݍ��ޏ��̍\����
    br::SelectInfomation _select_infomation;
    
    //! �Q�[����UI
    br::GameUI _ui;
    //! �Q�[���̃M�~�b�N
    br::GameSystem _system;

    //!-----------------------------------------------------
    //! @brief : �V�[����J�ڂ���K�v������Ȃ�J�ڐ��ݒ肷��
    //! @param : [in](void) none
    //! @return : �V�[����J�ڂ���K�v������Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool UpdateScene(void);
    //!-----------------------------------------------------
    //! @brief : �N���A�f�[�^���t�@�C���ɏ�������
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void WriteStageClearData(void);
public:
    //!-----------------------------------------------------
     //! @brief : �Q�b�^�[
     //! @param : [in](void) none
     //! @return : ���݂̃^�[�����擾
     //!-----------------------------------------------------
    std::string GetTurn(void);
     //!-----------------------------------------------------
     //! @brief : ���݂̃^�[����ύX����
     //! @param : [in](std::string str) �^�[���̖��O
     //! @return : none
     //!-----------------------------------------------------
    void ChangeTurn(const std::string& str);
	
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Game();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~Game();

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
    //! @brief : �O�̃V�[���őI�����������󂯎��
    //! @param : [in](br::SelectInfomation info) �ǂݍ��ޏ��̍\����
    //! @return : none
    //!-----------------------------------------------------
    void AcquireSelectData(br::SelectInfomation info);
    
    br::ReverseGuage* GetReverseGuage(void);
    br::BattleSystem* GetBattleSystem(void);
    br::BattleSystemForecast* GetBattleSystemForeCast(void);
    br::FusionSystem* GetFusionSystem(void);
    br::SelectInfomation GetSelectInfomation(void);

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
#endif // !BR_GAME_H