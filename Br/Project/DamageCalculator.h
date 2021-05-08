#ifndef BR_DAMAGE_CALCULATOR_H
#define BR_DAMAGE_CALCULATOR_H


#include "Unit.h"
#include "UnitCompatibility.h"

namespace br {
struct DamageCalculatorResult {
    int value = 0;
    int hit = 0;
    br::UnitCompatibility::Effective effective = 
        br::UnitCompatibility::Effective::NormalEffective;
};
class DamageCalculator {
public:
    int Calculation(const br::Unit& attacker,const br::Unit& target);
    br::DamageCalculatorResult CalculationResult(const br::Unit& attacker,const br::Unit& target);
};
}
#endif // !BR_DAMAGE_CALCULATOR_H