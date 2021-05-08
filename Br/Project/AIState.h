//!-----------------------------------------------------
//! @file : AIState.h
//! @brief : AIComponent�����G���j�b�g�̏��
//!          �s���W�I�̌��������
//! @date : 2020/07/02
//!-----------------------------------------------------


#ifndef BR_AI_STATE_H
#define BR_AI_STATE_H


namespace br {
class AIState {
protected:
    class AIComponent* _owner;
public:
    AIState(class AIComponent* owner);
    
    //!-----------------------------------------------------
    //! @brief : �p�����[�^�ɒl���Z�b�g����
    //! @param : [out](class AIParam& param) �p�����[�^
    //! @return : none
    //!-----------------------------------------------------
    virtual void ParamAddTo(class AIParam& param) = 0;
    
    //!-----------------------------------------------------
    //! @brief : ���͎��ɌĂяo��
    //! @param : [out](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual void Start(void) = 0;
    //!-----------------------------------------------------
    //! @brief : �W�I��ݒ肷��
    //! @param : [out](class Unit* out) �ݒ�l
    //! @return : none
    //!-----------------------------------------------------
    virtual void DecideTarget(class Unit* out) = 0;
    //!-----------------------------------------------------
    //! @brief : �ړ����ݒ肷��
    //! @param : [out](class Tile* out) �ݒ�l
    //! @return : none
    //!-----------------------------------------------------
    virtual void DecideDestination(class Tile* out) = 0;
    //!-----------------------------------------------------
    //! @brief : �W�I���v�Z����
    //! @param : [out](viud) none
    //! @return : �o��
    //!-----------------------------------------------------
    virtual class Unit* ConputeTarget(void) = 0;
    virtual class Unit* ConputeTarget(AIParam& param);
    //!-----------------------------------------------------
    //! @brief : �ړ�����v�Z����
    //! @param : [out](viud) none
    //! @return : �o��
    //!-----------------------------------------------------
    virtual class Tile* ConputeDestination(void) = 0;
    //!-----------------------------------------------------
    //! @brief : ���O�̎擾
    //! @param : [in](void) none
    //! @return : ���O
    //!-----------------------------------------------------
    virtual const char* GetName(void) const = 0;
};
}
#endif // !BR_AI_STATE_H