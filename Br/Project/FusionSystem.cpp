#include "FusionSystem.h"

#include "EffectManager.h"


void br::FusionSystem::SetSprite(br::UnitType type, br::Sprite& out) {
    auto r = _resource_manager;
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
        default:
            break;
    } // switch
}


br::FusionSystem::FusionSystem() :
    _is_show(false),
    _unit(nullptr),
    _target(nullptr),
    _back_path("Resource/textures/back_ground_9.png"),
    _unit_position(300.0f, 400.0f),
    _target_position(700.0f, 400.0f),
    _resource_manager(),
    _unit_sprite() {
}

br::FusionSystem::~FusionSystem() {
}

void br::FusionSystem::SetResourceManager(std::shared_ptr<br::ResourceManager> r) {
    this->_resource_manager = r;
}

bool br::FusionSystem::IsShow(void) {
    return this->_is_show;
}

void br::FusionSystem::Show(br::Unit* unit, br::Unit* target) {
    _ASSERT_EXPR(unit->GetTeam() == target->GetTeam(), L"“¯Žm“¢‚¿‚µ‚Ä‚Í‚¢‚¯‚È‚¢");
    this->_is_show = true;;
    _unit = unit;
    _target = target;

    _back_path = std::string("Resource/textures/back_ground_9.png");

    this->SetSprite(_unit->GetUnitType(), _unit_sprite);
    this->SetSprite(_target->GetUnitType(), _target_sprite);
    _unit_sprite.SetReverseX(true);
}

bool br::FusionSystem::Input(void) {
    return true;
}

bool br::FusionSystem::Update(void) {
    if (_unit_sprite.IsEndMotion() && _target_sprite.IsEndMotion()) {
        _is_show = false;

        auto com = _unit->GetComponent<br::UnitFusionComponent>();
        bool miss = com->Fusion(*_target);
//        auto unit = dynamic_cast<br::Unit*>(super::_owner);
        if (miss) {
            //auto e = _unit->GetScene()->GetEffectManager();
            //e->Start("Resource/sprites/miss_effect/miss_effect.sprite", _target->GetPosition());
        } // if
        _unit->onEnd();
    } // if

    _unit_sprite.Update();
    _target_sprite.Update();
    return true;
}

bool br::FusionSystem::Render(void) {
    auto r = _resource_manager;
    auto back = r->GetTexture(_back_path.c_str());
    back->Render(0.0f, 0.0f);

    _unit_sprite.Render(_unit_position);
    _target_sprite.Render(_target_position);
    return true;
}