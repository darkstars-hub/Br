//!-----------------------------------------------------
//! @file : UnitStatus.h
//! @brief : ユニットが持つ攻撃力などのパラメータ
//!          JobComponentから値を受け取りUnitStateComponentが持つ
//!          現在このゲームはレベルアップがなく
//!          キャラクターもいないので値をセットするのはJobComponentのみ
//! @date : 2020/07/13
//!-----------------------------------------------------


#ifndef BR_UNIT_STATUS_H
#define BR_UNIT_STATUS_H


namespace br {
class UnitStatus{
private:
    int _attack;
    int _defence;
    int _magic_attack;
    int _magic_defence;
    int _hit;
    int _avoid;
    class HpComponent* _hp;
public:
    UnitStatus();
    ~UnitStatus();

    void SetData(int attack, int defence, int magic_attack, int magic_defence, int hit, int avoid);
    void SetHp(HpComponent* component);
    
    int GetHpMax(void);
    int GetHp(void);
    int GetAttack(void);
    int GetDefence(void);
    int GetMagicAttack(void);
    int GetMagicDefence(void);
    int GetHit(void);
    int GetAvoid(void);
};
}
#endif // !BR_UNIT_STATUS_H