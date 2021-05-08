//!-----------------------------------------------------
//! @file : UnitAIManager.h
//! @brief : �G���j�b�g��AI�̐��������
//! @date : 2020/06/20
//!-----------------------------------------------------


#ifndef BR_UNIT_AI_MANAGER_H
#define BR_UNIT_AI_MANAGER_H


#include <vector>

#include "Unit.h"
#include "UnitManager.h"
#include "AIParam.h"


namespace br {
class UnitAIManager {
private:
    UnitAIManager();
    ~UnitAIManager();

    std::vector<br::Unit*>* _players;
    std::vector<br::Unit*>* _enemies;
    //size_t _index;
public:
    static br::UnitAIManager& GetInstance();

    void SetUnits(std::vector<br::Unit*>* players,std::vector<br::Unit*>* enemies);
    const std::vector<br::Unit*>* GetPlayers(void);


    //!-----------------------------------------------------
    //! @brief : �v���C���[��Lord���j�b�g��T���Ď擾
    //! @param : [in](void) none
    //! @return : ���Ȃ��Ȃ�nullptr��Ԃ�
    //!-----------------------------------------------------
    br::Unit* SearchPlayerBoss(void);
    //!-----------------------------------------------------
    //! @brief : �Ŋ��̃v���C���[���j�b�g��T���Ď擾
    //! @param : [in](void) none
    //! @return : ���Ȃ��Ȃ�nullptr��Ԃ�
    //!-----------------------------------------------------
    br::Unit* SearchNearestPlayer(Mof::CVector2 position);
    //!-----------------------------------------------------
    //! @brief : AIParam���Q�Ƃ��đΏۂ��擾
    //! @param : [in](br::AIParam& param) �d�ݏ��
    //! @return : ���Ȃ��Ȃ�nullptr��Ԃ�
    //!-----------------------------------------------------
    br::Unit* SearchTargetUnit(br::AIParam& param);

    bool Update(void);

    //!-----------------------------------------------------
    //! @brief : AIParam�Ƀv���C���[���j�b�g��ǉ�����
    //! @param : [out](br::AIParam& param) �p�����[�^
    //! @return : none
    //!-----------------------------------------------------
    void PlayerSetTo(br::AIParam& param);
};
}
#endif // !BR_UNIT_AI_MANAGER_H