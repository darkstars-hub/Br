#include "AIState.h"

#include "AIParam.h"
#include "Unit.h"


br::AIState::AIState(AIComponent* owner) :
    _owner(owner) {
}
/*
void br::AIState::ParamAddTo(AIParam& param) {
//    param.AddWeight();
}
*/

br::Unit* br::AIState::ConputeTarget(br::AIParam& param) {
    return nullptr;
}
