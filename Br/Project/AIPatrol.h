//!-----------------------------------------------------
//! @file : AIPatrol.h
//! @brief : AIComponentが持つ敵ユニットの巡回している状態
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
    //! @brief : 現在の方向を参照して進むタイルを計算する
    //! @param : [in](br::Tile* origin) 基点
    //! @param : [out](br::Direction front) 向いている方向
    //! @return : 進むタイル
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