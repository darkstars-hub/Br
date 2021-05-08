//!-----------------------------------------------------
//! @file : ArcherMoveComponent.h
//! @brief : Unitが持つ移動機能
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_ARCHER_MOVE_COMPONENT_H
#define BR_ARCHER_MOVE_COMPONENT_H


#include "UnitMoveComponent.h"

#include <vector>

#include <Mof.h>

#include "SelectableComponent.h"
#include "UnitStateComponent.h"
#include "RangeRenderComponent.h"
#include "PathRenderComponent.h"
#include "MotionComponent.h"
#include "PathComponent.h"
#include "RangeComponent.h"


namespace br {
class ArcherMoveComponent : public br::UnitMoveComponent {
    using super = br::UnitMoveComponent;
private:
    float _time;
//    float _time_max;
//    AnimData _current_data;
    bool _is_jump;
    float _jump_max;

    Mof::CRectangle GetDestinationRect(void) const;
    Mof::CRectangle GetOwnerRect(void) const;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    ArcherMoveComponent(Actor* owner, int priority = 100);
    virtual ~ArcherMoveComponent();


    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : ユニットが向いている方向
    //!-----------------------------------------------------
    //br::Direction GetDirection(void) const;

    
    //!-----------------------------------------------------
    //! @brief : 目標地点に到着したかどうか
    //! @param : [in](void) none
    //! @return : したならtrueを返す
    //!-----------------------------------------------------
    virtual bool IsArrived(void) const override;
    
    virtual bool Initialize(void) override;
    virtual bool Update(void) override;

    virtual void MoveStart(void) override;
    
    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_UNIT_MOVE_COMPONENT_H