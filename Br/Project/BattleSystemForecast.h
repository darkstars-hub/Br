//!-----------------------------------------------------
//! @file : BattleSystemForecast.h
//! @brief : BattleSystem�����s����O�ɕ\�������퓬���ʂ̗\��
//!          �U���R�}���h��I������ƑΏۂɍU�������ꍇ�̌��ʂ��\�������
//!         �@�v���C���[���U�������I�����鎞�̂ݕ\������
//! @date : 2020/07/20
//!-----------------------------------------------------


#ifndef BR_BATTLE_SYSTEM_FORECAST_H
#define BR_BATTLE_SYSTEM_FORECAST_H


#include <Mof.h>

//#include "Unit.h"
namespace br {
class BattleSystemForecast {
private:
    //! �\���t���O
    bool _is_show;
    //! �U�����鑤
    class Unit* _attacker;
    //! �U������鑤
    class Unit* _target;
    //! �\���ʒu
    Mof::CVector2 _position;
public:
    BattleSystemForecast();
    ~BattleSystemForecast();


    
    //!-----------------------------------------------------
    //! @brief :�Z�b�^�[
    //! @param : [in](class Unit* ptr) �U������鑤
    //! @return : none
    //!-----------------------------------------------------
    void SetTarget(class Unit* ptr);
    //!-----------------------------------------------------
    //! @brief :�Z�b�^�[
    //! @param : [in](Mof::CVector2 position) �\���ʒu
    //! @return : none
    //!-----------------------------------------------------
    void SetPosition(Mof::CVector2 position);

    //!-----------------------------------------------------
    //! @brief : �\�����ł��邩�ǂ���
    //! @param : [in](void) none
    //! @return : �\�����ł���ꍇtrue
    //!-----------------------------------------------------
    bool IsShow(void);
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Render(void);


    //!-----------------------------------------------------
    //! @brief : �\������
    //! @param : [in](class Unit* attacker) �U�����鑤
    //! @param : [in](class Unit* target) �U������鑤
    //! @return : none
    //!-----------------------------------------------------
    void Show(class Unit* attacker, class Unit* target);
//    void Show(void);

    //!-----------------------------------------------------
    //! @brief : �\���I��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Hide(void);
};
}
#endif // !BR_BATTLE_SYSTEM_FORECAST_H