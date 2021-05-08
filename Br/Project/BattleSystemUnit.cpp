#include "BattleSystemUnit.h"

#include "BezierCurve.h"
#include "Stage.h"
#include "Tile.h"


void br::BattleSystemUnit::SetSprite(br::UnitType type, br::Sprite& out) {
    auto r = _resource_manager.lock();
    switch (type) {
        case br::UnitType::Lord:
            out.Load("Resource/sprites/lord/battle.sprite", *r);
            break;
        case br::UnitType::Cavalry:
            out.Load("Resource/sprites/cavalry/battle.sprite", *r);
            break;
        case br::UnitType::Archer:
            out.Load("Resource/sprites/archer/battle.sprite", *r);
            break;
        case br::UnitType::Hoplite:
            out.Load("Resource/sprites/hoplite/battle.sprite", *r);
            break;
        case br::UnitType::Chariot:
            out.Load("Resource/sprites/chariot/battle.sprite", *r);
            break;
        case br::UnitType::LightCavalry:
            out.Load("Resource/sprites/light_cavalry/battle.sprite", *r);
            break;
        case br::UnitType::HeavyCavalry:
            out.Load("Resource/sprites/heavy_cavalry/battle.sprite", *r);
            break;
        case br::UnitType::Sniper:
            out.Load("Resource/sprites/sniper/battle.sprite", *r);
            break;
        case br::UnitType::Hunter:
            out.Load("Resource/sprites/hunter/battle.sprite", *r);
            break;
		case br::UnitType::General:
			out.Load("Resource/sprites/general/battle.sprite", *r);
			break;
		case br::UnitType::Healer:
			out.Load("Resource/sprites/healer/battle.sprite", *r);
			break;
		case br::UnitType::Wizard:
			out.Load("Resource/sprites/wizard/battle.sprite", *r);
			break;
        default:
            break;
    } // switch
}


br::BattleSystemUnit::BattleSystemUnit() :
    _unit(nullptr),
    _sprite(),
    _position(),
    _is_attacker(false),
    _time(0.0f),
    _time_max(2.0f),
    _target(nullptr),
    _attack_end(false) {
}

br::BattleSystemUnit::~BattleSystemUnit() {
}

bool br::BattleSystemUnit::AttackEnd(void) {
    return this->_attack_end && _time >= _time_max;
}

/*
bool br::BattleSystemUnit::ArrivedTargetPoint(void) {
    return 1.0f <= _time;
}
*/

void br::BattleSystemUnit::SetAttacker(bool b) {
    this->_is_attacker = b;
}
/*
void br::BattleSystemUnit::SetTarget(br::BattleSystemUnit* ptr) {
    this->_target = ptr;
}
*/

void br::BattleSystemUnit::SetResourceManager(std::weak_ptr<br::ResourceManager> r) {
    this->_resource_manager = r;
}

br::Unit* br::BattleSystemUnit::GetUnit(void) {
    return this->_unit;
}

Mof::CRectangle br::BattleSystemUnit::GetRectangle(void) {
    return this->_sprite.GetSrcRect();
}

Mof::CVector2 br::BattleSystemUnit::GetPosition(void) const {
    return this->_position;
}

bool br::BattleSystemUnit::IsAttacker(void) const {
    return this->_is_attacker;
}

bool br::BattleSystemUnit::IsTarget(void) const {
    return !this->_is_attacker;
}



bool br::BattleSystemUnit::IsEndMotion(void) {
    return this->_sprite.IsEndMotion();
}

bool br::BattleSystemUnit::CanAttakck(BattleSystemUnit& target) {
    auto& range = _unit->GetStateComponent()->GetAttackRange();
    auto stage = _unit->GetScene()->GetStage();

    auto pos = _unit->GetGridPosition();
    for (auto v : range) {
        auto tile = stage->GetTile(pos.col + v.x, pos.row + v.y);
        if (tile->GetOnUnit() && tile->GetOnUnit() == target.GetUnit()) {
            return true;
        } // if
    } // for
    return false;
}

void br::BattleSystemUnit::Initialize(br::Unit* unit,
                                      Mof::CVector2 position,
                                      bool attacker,
                                      br::BattleSystemUnit* target) {
    _unit = unit;
    _position = position;
    _is_attacker = attacker;
    _target = target;
    _time = 0.0f;
    _attack_end = false;

    // 攻撃側がプレイヤーの場合
    if (unit->GetTeam() == def::kPlayerTeam) {
        _sprite.SetReverseX(true);
    } // if

    _sprite.Release();
    this->SetSprite(unit->GetUnitType(), _sprite);
    _sprite.ChangeMotionByName("attack");
}

void br::BattleSystemUnit::Update(void) {
    if (this->IsAttacker()) {
        _time += ::CUtilities::GetFrameSecond();
        auto t = _time / _time_max;
        if (1.0f <= t) t = 1.0f;

        br::BezierCurve bezier;
        _position.x = bezier.InterpolationAnimData(t, _control_x, br::EaseType::EaseInOut);
        _position.y = bezier.InterpolationAnimData(t, _control_y, br::EaseType::EaseInOut);


        // 初期位置に戻る
        if (_sprite.IsEndMotion()) {
            if (!_attack_end) {
                std::swap(_control_x.at(0), _control_x.at(2));
                std::swap(_control_y.at(0), _control_y.at(2));
                _time = 0.0f;
            } // if
            _attack_end = true;
        } // if

        _sprite.Update();
    } // if
}

void br::BattleSystemUnit::Render(void) {
    _sprite.Render(_position);

    if (_unit->GetTeam() == def::kPlayerTeam) {
        ::CGraphicsUtilities::RenderString(
            _position.x,
            _position.y,
            "プレイヤー");
    } // if
    else {
        ::CGraphicsUtilities::RenderString(
            _position.x,
            _position.y,
            "エネミー");
    } // else

    ::CGraphicsUtilities::RenderFillCircle(
        _position.x,
        _position.y,
        10,
        MOF_ARGB(255, 255, 255, 0)
    );
}

void br::BattleSystemUnit::MakeControlPoint(void) {
//    assert(initialized)
    // 初期化
    _control_x.clear();
    _control_y.clear();
    // アニメーション作成
    _point1 = _position;
    _point2 = Mof::CVector2(_position.x, _target->GetPosition().y);
    _point3 = _target->GetPosition();
    if (_unit->GetTeam() == def::kPlayerTeam) {
        _point3.x -= _target->GetRectangle().GetWidth();
    } // if
    else {
        _point3.x += _target->GetRectangle().GetWidth();
    } // else
    // データの追加
    _control_x.push_back(_point1.x);
    _control_x.push_back(_point2.x);
    _control_x.push_back(_point3.x);
    _control_y.push_back(_point1.y);
    _control_y.push_back(_point2.y);
    _control_y.push_back(_point3.y);
}