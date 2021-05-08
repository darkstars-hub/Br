//!-----------------------------------------------------
//! @file : ActorManager.h
//! @brief : Unit���Ȃ���̔z�������
//! @date : 2020/06/05
//!-----------------------------------------------------


#ifndef BR_ACTOR_MANAGER_H
#define BR_ACTOR_MANAGER_H


#include <vector>

#include <Mof.h> 

#include "../include/rapidjson/document.h"

#include "Scene.h"
#include "Game.h"
#include "Unit.h"
#include "UnitManager.h"
#include "ActorFactory.h"
#include "Builder.h"


namespace br {
class ActorManager {
private:
    //! ���݂̃V�[��
    br::Scene* _scene;
    //! �Q�[���V�[��
    br::Game* _game;
    //! �Ǘ����Ă��郆�j�b�g
    br::UnitManager _unit_manager;
    //! �V�[����̂��ׂẴQ�[���I�u�W�F�N�g
    //std::vector<br::Actor*> _actors;
    //! ���j�b�g���
    rapidjson::Document _unit_doc;
    //! �G�l�~�[���
    rapidjson::Document _enemy_doc;
    //! ���j�b�g�쐬��
    br::ActorFactory _factory;
protected:
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Scene* scene) ���݂̃V�[��
    //! @return : none
    //!-----------------------------------------------------
    ActorManager(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~ActorManager();

    //void SetGame(br::Game* ptr);
    br::UnitManager* GetUnitManager(void);

    //!-----------------------------------------------------
    //! @brief : �ǂݍ��ݏ���
    //! @param : [in](const char* path) �ǂݍ��ރf�[�^�̃p�X
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Load(const char* path);
    //!-----------------------------------------------------
    //! @brief : ���͏���
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Input(void);
    //!-----------------------------------------------------
    //! @brief : ������
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Initialize(void);
    //!-----------------------------------------------------
    //! @brief : �X�V
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Update(void);
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Render(Mof::CVector2 scroll);
    //!-----------------------------------------------------
    //! @brief : �������
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Release(void);
};
}
#endif // !BR_ACTOR_MANAGER_H