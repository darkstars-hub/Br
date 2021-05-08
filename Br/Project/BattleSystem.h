//!-----------------------------------------------------
//! @file : BattleSystem.h
//! @brief : Unit���키���̕���
//! @date : 2020/07/13
//!-----------------------------------------------------


#ifndef BR_BATTLE_SYSTEM_H
#define BR_BATTLE_SYSTEM_H


#include <memory>
#include <string>

#include <Mof.h>

#include "Scene.h"
#include "ResourceManager.h"
//#include "Tile.h"
#include "Unit.h"
#include "Sprite.h"
#include "BattleSystemHp.h"
#include "BattleSystemUnit.h"
#include "BattleSystemUnitInfomation.h"
#include "TextSystem.h"


namespace br {
class BattleSystem {
private:
    br::Scene* _scene;
    //! �S�ẴA�N�V�������I�������Update�̒���false�ɂ���
    //! ��ʐ^�����Ńo�g����ʏI��
    bool _is_show;
    //! �\������e�N�X�`���̃p�X
    std::string _back_path;
    //! ���\�[�X�}�l�[�W���̃|�C���^
    std::weak_ptr<br::ResourceManager> _resource_manager;
    //! �U�����̍U���I���t���O
    bool _attacker_excuted;
    //! �t�F�[�h�C�����鎞�̃A���t�@�l
    int _in_alpha;
    //! �t�F�[�h�A�E�g���鎞�̃A���t�@�l
    int _out_alpha;


    //! �v���C���[��HP��\������
    br::BattleSystemHp _player_hp;
    //! �G�l�~�[��HP��\������
    br::BattleSystemHp _enemy_hp;
    //! �����œ����l�i�v���C���[�j
    br::BattleSystemUnit _player_unit;
    //! �����œ����l�i�G�l�~�[�j
    br::BattleSystemUnit _enemy_unit;
    //! ���j�b�g�̏��\��
    br::BattleSystemUnitInfomation _player_info;
    br::BattleSystemUnitInfomation _enemy_info;
    
    br::TextSystem _result_text;
    //! �U�����ꂽ���������Ă����甽���J�n����
    bool _counter_attack;
    //! �����i�U�����ꂽ�j���̔����I���t���O
    //bool _counter_excuted;
    //bool _is_change;

    br::BattleSystemUnit* GetAttackerUnit(void);
    br::BattleSystemUnit* GetTargetUnit(void);
    //!-----------------------------------------------------
    //! @brief : �o�g���V�X�e���̉�ʂɓ���Ƃ��̑J�ڌ��ʂ̍X�V
    //! @param : [in](void) none
    //! @return : Update�̏��������s���邩�ǂ���
    //!-----------------------------------------------------
    bool UpdateSystem(void);
    //!-----------------------------------------------------
    //! @brief : �J�ڌ��ʁi�t�F�[�h�A�E�g�̃A���t�@�l�j�̍X�V
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void UpdateFade(void);
    //!-----------------------------------------------------
    //! @brief : �o�g���V�X�e���̉�ʂɓ���Ƃ��̑J�ڌ��ʂ̕`��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void RenderFadeIn(void);
    //!-----------------------------------------------------
    //! @brief : �o�g���V�X�e���̉�ʂ���o��Ƃ��̑J�ڌ��ʂ̕`��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void RenderFadeOut(void);
    //!-----------------------------------------------------
    //! @brief : �J�ڌ��ʂ̕`��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void RenderFade(void);
    //!-----------------------------------------------------
    //! @brief : �̗͂�`��
    //! @param : [in](br::BattleSystemHp) Hp���
    //! @return : none
    //!-----------------------------------------------------
    void RenderHp(br::BattleSystemHp);
    //!-----------------------------------------------------
    //! @brief : �U�������̕����U��������������
    //! @param : [in](br::Unit* attacker) �U����
    //! @param : [in](br::Unit* target) ������
    //! @return : none
    //!-----------------------------------------------------
    void AttackSuccess(br::Unit* attacker, br::Unit* target);
    //!-----------------------------------------------------
    //! @brief : �U�������̕����U��������������
    //! @param : [in](br::Unit* attacker) �U����
    //! @param : [in](br::Unit* target) ������
    //! @return : none
    //!-----------------------------------------------------
    void AttackFailure(br::Unit* attacker, br::Unit* target);
public:
    BattleSystem();
    ~BattleSystem();

    //!-----------------------------------------------------
    //! @brief : �����o�̏�����
    //! @param : [in](std::weak_ptr<br::ResourceManager>r) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void Initialize(std::weak_ptr<br::ResourceManager>r);

    //!-----------------------------------------------------
    //! @brief : �\���t���O
    //! @param : [in](void) none
    //! @return : �\�����Ă����true��Ԃ�
    //!-----------------------------------------------------
    bool IsShow(void);
    //!-----------------------------------------------------
    //! @brief : BallteSystem���J�n����
    //! @param : [in](br::Unit* attacker) �U�����d�|�������̃|�C���^
    //! @param : [in](br::Unit* target) �U�����ꂽ���̃|�C���^
    //! @param : [in](br::Tile* filed) ���
    //! @return : none
    //!-----------------------------------------------------
    void Show(br::Unit* attacker, br::Unit* target);
   // void Show(br::Unit* attacker, br::Unit* target, br::Tile* back);

   
    //!-----------------------------------------------------
    //! @brief : ��������邩��
    //! @param : [in](void) none
    //! @return : true
    //!-----------------------------------------------------
    bool Input(void);
    //!-----------------------------------------------------
    //! @brief : �X�V �\���t���O�̐ݒ�
    //!          ��ʐ^�����i�t�F�[�h�A�E�g�̃A���t�@�l���Q�T�T�j�Ńo�g����ʏI��
    //! @param : [in](void) none
    //! @return : true
    //!-----------------------------------------------------
    bool Update(void);
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](void) none
    //! @return : true
    //!-----------------------------------------------------
    bool Render(void);
};
}
#endif // !BR_BATTLE_SYSTEM_H