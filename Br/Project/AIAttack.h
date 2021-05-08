//!-----------------------------------------------------
//! @file : AIAttack.h
//! @brief : AIComponent‚ª‚Â“Gƒ†ƒjƒbƒg‚ÌUŒ‚‚·‚éó‘Ô
//! @date : 2020/07/05
//!-----------------------------------------------------


#ifndef BR_AI_ATTACK_H
#define BR_AI_ATTACK_H


#include "AIState.h"


namespace br {
class AIAttack : public br::AIState {
    using super = br::AIState;
public:
    AIAttack(class AIComponent* owner);

    virtual void ParamAddTo(class AIParam& param) override;

    virtual class Unit* ConputeTarget(AIParam& param) override;

    virtual void Start(void) override;
    virtual void DecideTarget(class Unit* out) override;
    virtual void DecideDestination(class Tile* out)override;
    virtual class Unit* ConputeTarget(void) override;
    virtual class Tile* ConputeDestination(void) override;
    const char* GetName() const override;
};
}
#endif // !BR_AI_ATTACK_H