//!-----------------------------------------------------
//! @file : UnitManager.h
//! @brief : ���j�b�g�Ǘ����󂯎���
//! @date : 2020/06/12
//!-----------------------------------------------------


#ifndef BR_UNIT_MANAGER_H
#define BR_UNIT_MANAGER_H


#include <vector>

#include "Helper.h"
#include "Scene.h"
#include "Game.h"
#include "Unit.h"
#include "Menu.h"
#include "ReverseGuage.h"


namespace br {
class UnitManager {
private:
    //! ���݂̃V�[��
    br::Scene* _scene;
    br::Game* _game;
    //! �S�Ẵ��j�b�g
    std::vector<br::Unit*> _units;
    //! �S�Ẵv���C���[
    std::vector<br::Unit*> _players;
    //! �S�ẴG�l�~�[
    std::vector<br::Unit*> _enemies;
    //! �����t�]�M�~�b�N�̃|�C���^
    br::ReverseGuage* _reverse_guage;
public:
    UnitManager(br::Scene* scene);
    ~UnitManager();

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    //void SetReverseGuage(br::ReverseGuage* ptr);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](int col) ��
    //! @param : [in](int row) �s
    //! @return : none
    //!-----------------------------------------------------
    br::Unit* GetUnit(def::Vector2i pos);
    br::Unit* GetUnit(int col, int row);


    //!-----------------------------------------------------
    //! @brief : �v���C���[�̃��[�_�[���j�b�g������ł��邩�m�F����
    //! @param : [in](void) none
    //! @return : ����ł���Ȃ�true��Ԃ�    
    //!-----------------------------------------------------
    bool IsPlayerBossDead(void);
    //!-----------------------------------------------------
    //! @brief : �S�Ă̓G������ł��邩�m�F����
    //! @param : [in](void) none
    //! @return : ����ł���Ȃ�true��Ԃ�    
    //!-----------------------------------------------------
    bool IsAllEnemyDead(void);

    //!-----------------------------------------------------
    //! @brief : ���j�b�g�̒ǉ�
    //! @param : [in](br::Unit* unit) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void AddUnit(br::Unit* unit);
    //!-----------------------------------------------------
    //! @brief : �v���C���[�̃��j�b�g���s���ς݂ɂ���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void AllPlayerEnd(void);

    std::vector<br::Unit*>& GetUnits(void);

    //!-----------------------------------------------------
    //! @brief : �󂯎�������j�b�g���z��̉��Ԗڂɂ��邩�擾����
    //! @param : [in](br::Unit* unit) ���ׂ郆�j�b�g
    //! @return : �v���C���[�̃��j�b�g�̃C���f�b�N�X
    //!-----------------------------------------------------
    int GetPlayerIndex(br::Unit* unit);
    //int GetIndex(br::Unit* unit,std::vector<br::Unit*> units);
    br::Unit* GetUnitAtIndex(size_t index);
    size_t GetPlayerUnitSize(void);

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
#endif // !BR_UNIT_MANAGER_H