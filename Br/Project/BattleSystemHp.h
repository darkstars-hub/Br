//!-----------------------------------------------------
//! @file : BattleSystemHp.h
//! @brief : Unit���키���̕���̒���Hp��\������
//!          �_���[�W���󂯂�Unit��Hp������V��ł���l���m�F�ł���悤�ɂ���
//! @date : 2020/07/16
//!-----------------------------------------------------


#ifndef BR_BATTLE_SYSTEM_HP_H
#define BR_BATTLE_SYSTEM_HP_H


#include <memory>

#include <Mof.h>

#include "ResourceManager.h"
#include "Unit.h"


namespace br {
class BattleSystemHp {
private:
    int _damege_alpha;

    std::shared_ptr<Mof::CTexture> _hp_frame;
    std::shared_ptr<Mof::CTexture> _hp_green;
    std::shared_ptr<Mof::CTexture> _hp_red;

    Mof::CVector2 _offset;

    //! �ԃQ�[�W���P�t���[���Ɍ����
    const float _damage_decrase;
    float _last_hp;
    br::Unit* _unit_data;
    class BattleSystemUnit* _unit;
    br::HpComponent* _hp;
public:
    BattleSystemHp();
    ~BattleSystemHp();

    int GetAlpha(void) const;
    class BattleSystemUnit* GetUnit(void);

    void Initialize(std::weak_ptr<br::ResourceManager>r, class BattleSystemUnit* unit);
    void Update(void);
    void Render(Mof::CVector2 position, const br::Unit& attacker, const br::Unit& target);

    void IncrementAlpha(int abs);
    void DecrementAlpha(int value);
};
}
#endif // !BR_BATTLE_SYSTEM_HP_H