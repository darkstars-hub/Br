//!-----------------------------------------------------
//! @file : AIParam.h
//! @brief :  ���̃p�����[�^�������Ă���G�l�~�[���j�b�g��
//!           �U���Ώۂ�I������Ƃ��ɎQ�Ƃ�����͏��
//! @date : 2020/07/22
//!-----------------------------------------------------


#ifndef BR_AI_PARAM_H
#define BR_AI_PARAM_H


#include <vector>

//#include "Unit.h"


namespace br {
class AIParam {
private:
    //! �l���Ă�l
    //br::Unit* _owner;
    class Unit* _owner;
    //! �G�l�~�[���v���C���[��_���Ƃ��̗D��x�i�d�݁j
    //int _weight;
    //! �U���ΏۂƂȂ肤��v���C���[���j�b�g�̃|�C���^
    //std::vector<br::Unit*> _targets;
    //! �G�l�~�[���v���C���[��_���Ƃ��̗D��x�i�d�݁j
    //std::vector<std::pair<br::Unit*, int>> _weights;
    std::vector<std::pair<class Unit*, int>> _weights;
    //! ���j�b�g���
    //class UnitAIManager* _ai_manager;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Unit* _owner) �l���Ă���l
    //! @return : none
    //!-----------------------------------------------------
    AIParam();
    AIParam(class Unit* owner);
    ~AIParam();

    //!-----------------------------------------------------
    //! @brief : �U���ΏۂƂ��郆�j�b�g
    //! @param : [in](void) none
    //! @return : �d�݂��ő�̃��j�b�g
    //!-----------------------------------------------------
    //br::Unit* GetTargetUnit(void);
    class Unit* GetTargetUnit(void);

    //!-----------------------------------------------------
    //! @brief : �d�ݏ����������i���Z�b�g�j����
    //! @param : [in](std::vector<br::Unit*>& players) none
    //! @return : none
    //!-----------------------------------------------------
    //void Initialize(std::vector<br::Unit*>& players);
    //void Initialize(std::vector<class Unit*>& players);
    
    //!-----------------------------------------------------
    //! @brief : �_����������Ȃ����j�b�g��ǉ�����
    //! @param : [in](br::Unit* player) �v���C���[���j�b�g
    //! @return : none
    //!-----------------------------------------------------
    //void AddUnit(br::Unit* player);
    void AddUnit(class Unit* player);
    //!-----------------------------------------------------
    //! @brief : �d�ݏ���ǉ�����
    //! @param : [in](br::Unit* player) ���̃��j�b�g�ɑ΂���
    //! @param : [in](int value) �d�݂̒l
    //! @return : none
    //!-----------------------------------------------------
    void AddWeight(class Unit* player, int value);
};
}
#endif // !BR_AI_PARAM_H