#include "DamageCalculator.h"

#include "UnitCompatibility.h"


int br::DamageCalculator::Calculation(const br::Unit& attacker, const br::Unit& target) {
	auto u0 = attacker.GetUnitType();
	auto u1 = target.GetUnitType();
	// ‘Š«QÆ
	auto c = br::UnitCompatibility::GetInstance().Compatibility(u0, u1);

	int a;
	int d;
	if (attacker.GetUnitType() == br::UnitType::Wizard) {
		a = attacker.GetStateComponent()->GetStatus()->GetMagicAttack();
		d = target.GetStateComponent()->GetStatus()->GetMagicDefence();
	} // if
	else {
		a = attacker.GetStateComponent()->GetStatus()->GetAttack();
		d = target.GetStateComponent()->GetStatus()->GetDefence();
	} // else


	int ret = a - d;
	if (c == br::UnitCompatibility::Effective::SuperEffective) {
		ret *= 1.5;
	} // if
	else if (c == br::UnitCompatibility::Effective::NotVeryEffective) {
		ret /= 1.5;
	} // else if

	return ret;
}

br::DamageCalculatorResult br::DamageCalculator::CalculationResult(const br::Unit& attacker, const br::Unit& target) {
	auto ret = br::DamageCalculatorResult();

	auto u0 = attacker.GetUnitType();
	auto u1 = target.GetUnitType();
	//// ‘Š«QÆ
	//
	//int a = attacker.GetStateComponent()->GetStatus()->GetAttack();
	//int d = target.GetStateComponent()->GetStatus()->GetDefence();
	auto c = br::UnitCompatibility::GetInstance().Compatibility(u0, u1);

	ret.value = this->Calculation(attacker, target);
	ret.effective = c;
	ret.hit =
		attacker.GetStateComponent()->GetStatus()->GetHit() -
		target.GetStateComponent()->GetStatus()->GetAvoid();
	return ret;
}