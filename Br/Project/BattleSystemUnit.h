//!-----------------------------------------------------
//! @file : BattleSystemUnit.h
//! @brief : �o�g���V�X�e���̒��œ������j�b�g
//! @date : 2020/07/18
//!-----------------------------------------------------


#ifndef BR_BATTLE_SYSTEM_UNIT_H
#define BR_BATTLE_SYSTEM_UNIT_H


#include <vector>
#include <memory>

#include <Mof.h>

#include "Sprite.h"
#include "Unit.h"
#include "ResourceManager.h"


namespace br {
class BattleSystemUnit {
private:
    //! �o�g���V�X�e���œ������j�b�g
    br::Unit* _unit;
    //! �\���摜
    br::Sprite _sprite;
    //! �����ʒu
    Mof::CVector2 _position;
    //! �U�����ł��邩�ǂ����@�����łȂ��Ȃ�U������鑤
    bool _is_attacker;
    //! �L���b�V��
    std::weak_ptr<br::ResourceManager> _resource_manager;
    //! �A�j���[�V�����̎���
    float _time;
    float _time_max;
    //! �U������
    br::BattleSystemUnit* _target;

    //! �A�j���[�V�����̃R���g���[���|�C���g
    Mof::CVector2 _point1;
    Mof::CVector2 _point2;
    Mof::CVector2 _point3;
    std::vector<float> _control_x;
    std::vector<float> _control_y;

    //! �U���I���t���O
    bool _attack_end;

    //!-----------------------------------------------------
    //! @brief : �����ɂ���Sprite�Ƀf�[�^������
    //! @param : [in](br::UnitType type) ���j�b�g�^�C�v
    //! @param : [out](br::Sprite& out) �ǂݍ��ݐ�
    //! @return : none
    //!-----------------------------------------------------
    void SetSprite(br::UnitType type, br::Sprite& out);
public:
    BattleSystemUnit();
    ~BattleSystemUnit();

    //!-----------------------------------------------------
    //! @brief : �U�����I��������ǂ���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    bool AttackEnd(void);

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](bool b) �U�����ɂ���
    //! @return : none
    //!-----------------------------------------------------
    void SetAttacker(bool b);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](br::BattleSystemUnit* ptr) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    //void SetTarget(br::BattleSystemUnit* ptr);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](std::weak_ptr<br::ResourceManager>r) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetResourceManager(std::weak_ptr<br::ResourceManager>r);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �|�C���^
    //!-----------------------------------------------------
    br::Unit* GetUnit(void);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �\�����̉摜�̋�`
    //!-----------------------------------------------------
    Mof::CRectangle GetRectangle(void);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �\���ʒu
    //!-----------------------------------------------------
    Mof::CVector2 GetPosition(void) const;
    //!-----------------------------------------------------
    //! @brief : �U�����鑤�ł��邩�ǂ���
    //! @param : [in](void) none
    //! @return : �U�����鑤�ł���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsAttacker(void) const;
    //!-----------------------------------------------------
    //! @brief : �U������鑤�ł��邩�ǂ���
    //! @param : [in](void) none
    //! @return : �U�����鑤�łȂ��Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsTarget(void) const;
    //!-----------------------------------------------------
    //! @brief : br::Sprite::IsEndMotion�̃��b�p�[
    //! @param : [in](void) none
    //! @return : ���[�V�������I������Ȃ�Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsEndMotion(void);
    //!-----------------------------------------------------
    //! @brief : �Ώۂ��U���͈͂ɓ����Ă��邩�m�F����
    //! @param : [in](BattleSystemUnit& target) �����Ώ�
    //! @return : �U���\�Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool CanAttakck(BattleSystemUnit& target);


    //!-----------------------------------------------------
    //! @brief : ������
    //! @param : [in](br::Unit* unit) ����郆�j�b�g
    //! @param : [in](Mof::CVector2 position) �����ʒu
    //! @param : [in](bool attacker) �U�����ł���Ȃ�true
    //! @param : [in](br::BattleSystemUnit* ptr) �U������
    //! @return : none
    //!-----------------------------------------------------
//    void Initialize(br::Unit* unit, Mof::CVector2 position, bool attacker);
    void Initialize(br::Unit* unit, Mof::CVector2 position, bool attacker, br::BattleSystemUnit* target);
    //!-----------------------------------------------------
    //! @brief : �X�V
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Update(void);
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Render(void);
    //!-----------------------------------------------------
    //! @brief : �A�j���[�V�����ɕK�v�ȃf�[�^�̍쐬
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void MakeControlPoint(void);
};
}
#endif // !BR_BATTLE_SYSTEM_UNIT_H