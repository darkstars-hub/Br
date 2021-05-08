//!-----------------------------------------------------
//! @file : AIPatrol.h
//! @brief : AIComponent�����G���j�b�g�̏��񂵂Ă�����
//! @date : 2020/07/02
//!-----------------------------------------------------


#ifndef BR_AI_PATROL_H
#define BR_AI_PATROL_H


#include "AIState.h"

#include "Helper.h"
#include "Tile.h"

namespace br {
class AIPatrol : public br::AIState {
    using super = br::AIState;
private:
    //!-----------------------------------------------------
    //! @brief : ���݂̕������Q�Ƃ��Đi�ރ^�C�����v�Z����
    //! @param : [in](br::Tile* origin) ��_
    //! @param : [out](br::Direction front) �����Ă������
    //! @return : �i�ރ^�C��
    //!-----------------------------------------------------
    class Tile* Analyze(br::Tile& origin, br::Direction* front);
public:
    AIPatrol(class AIComponent* owner);

    virtual void ParamAddTo(class AIParam& param) override;

    virtual void Start(void) override;
    virtual void DecideTarget(class Unit* out) override;
    virtual void DecideDestination(class Tile* out)override;
    virtual class Unit* ConputeTarget(void) override;
    virtual class Tile* ConputeDestination(void) override;
    const char* GetName() const override;
};
}
#endif // !BR_AI_PATROL_H