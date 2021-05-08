#include "ActorFactory.h"

#include "Helper.h"
#include "Common.h"
#include "Cursor.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "UnitTextureComponent.h"
#include "AIComponent.h"
#include "UnitStateComponent.h"
#include "SelectableComponent.h"
#include "MotionComponent.h"
#include "UnitMoveComponent.h"
#include "UnitAttackComponent.h"
#include "UnitSightComponent.h"
#include "UnitFusionComponent.h"
#include "RangeRenderComponent.h"
#include "PathRenderComponent.h"
#include "PathComponent.h"
#include "RangeComponent.h"
#include "HpComponent.h"
#include "LordComponent.h"
#include "CavalryComponent.h"
#include "LightCavalryComponent.h"
#include "ArcherComponent.h"
#include "HopliteComponent.h"
#include "HeavyCavalryComponent.h"
#include "ChariotComponent.h"
#include "HunterComponent.h"
#include "SniperComponent.h"
#include "GeneralComponent.h"
#include "HealerComponent.h"
#include "WizardComponent.h"
#include "UnitHealComponent.h"
#include "StageTable.h"
#include "ArcherMoveComponent.h"


br::Component* br::ActorFactory::CreateComponent(br::ComponentType type, int priority) {
    br::Component* component = nullptr;
    switch (type) {
        case br::ComponentType::SelectableComponent:
            component = new br::SelectableComponent(nullptr, priority);
            break;
        case br::ComponentType::MotionComponent:
            component = new br::MotionComponent(nullptr, priority);
            break;
        case br::ComponentType::AttackComponent:
            break;
        case br::ComponentType::TextureComponent:
            break;
        case br::ComponentType::SpriteComponent:
            break;
        case br::ComponentType::PathRenderComponent:
            component = new br::PathRenderComponent(nullptr, priority);
            break;
        case br::ComponentType::RangeRenderComponent:
            component = new br::RangeRenderComponent(nullptr, priority);
            break;
        case br::ComponentType::CursorMoveComponent:
            break;
        case br::ComponentType::UnitTextureComponent:
            component = new br::UnitTextureComponent(nullptr, priority);
            break;
        case br::ComponentType::UnitStateComponent:
            component = new br::UnitStateComponent(nullptr, priority);
            break;
        case br::ComponentType::UnitMotionComponent:
            break;
        case br::ComponentType::UnitMoveComponent:
            component = new br::UnitMoveComponent(nullptr, priority);
            break;
        case br::ComponentType::UnitAttackComponent:
            component = new br::UnitAttackComponent(nullptr, priority);
            break;
        case br::ComponentType::UnitSightComponent:
            component = new br::UnitSightComponent(nullptr, priority);
            break;
        case br::ComponentType::UnitFusionComponent:
            component = new br::UnitFusionComponent(nullptr, priority);
            break;
        case br::ComponentType::UnitJobComponent:
            break;
        case br::ComponentType::LordComponent:
            component = new br::LordComponent(nullptr, priority);
            break;
        case br::ComponentType::CavalryComponent:
            component = new br::CavalryComponent(nullptr, priority);
            break;
        case br::ComponentType::ArcherComponent:
            component = new br::ArcherComponent(nullptr, priority);
            break;
        case br::ComponentType::HopliteComponent:
            component = new br::HopliteComponent(nullptr, priority);
            break;
        case br::ComponentType::LightCavalryComponent:
            component = new br::LightCavalryComponent(nullptr, priority);
            break;
        case br::ComponentType::HeavyCavalryComponent:
            component = new br::HeavyCavalryComponent(nullptr, priority);
            break;
        case br::ComponentType::ChariotComponent:
            component = new br::ChariotComponent(nullptr, priority);
            break;
        case br::ComponentType::HunterComponent:
            component = new br::HunterComponent(nullptr, priority);
            break;
        case br::ComponentType::GeneralComponent:
            component = new br::GeneralComponent(nullptr, priority);
            break;
        case br::ComponentType::SniperComponent:
            component = new br::SniperComponent(nullptr, priority);
            break;
        case br::ComponentType::HpComponent:
            component = new br::HpComponent(nullptr, priority);
            break;
        case br::ComponentType::AIComponent:
            component = new br::AIComponent(nullptr, priority);
            break;
        case br::ComponentType::PathComponent:
            component = new br::PathComponent(nullptr, priority);
            break;
        case br::ComponentType::RangeComponent:
            component = new br::RangeComponent(nullptr, priority);
            break;
        case br::ComponentType::ArcherMoveComponent:
            component = new br::ArcherMoveComponent(nullptr, priority);
            break;
        case br::ComponentType::HealerComponent:
            component = new br::HealerComponent(nullptr, priority);
            break;
		case br::ComponentType::UnitHealComponent:
			component = new br::UnitHealComponent(nullptr, priority);
			break;
		case br::ComponentType::WizardComponent:
			component = new br::WizardComponent(nullptr, priority);
			break;
        default:
            break;
    } // switch
    return component;
}

std::shared_ptr<br::Builder> br::ActorFactory::CreateBuilder(const char* path) {
    auto builder = std::make_shared<br::Builder>();
    //! テキスト情報
    rapidjson::Document document;
    ut::LoadJsonDocument(path, document);
    const auto& info = document["infomation"];
    _ASSERT_EXPR(info.IsArray(),
                 L"infomation type is not array");
    for (int i = 0; i < info.Size(); i++) {
        if (!info[i].HasMember("name") || !info[i]["name"].IsString() ||
            !info[i].HasMember("type") || !info[i]["type"].IsInt() ||
            !info[i].HasMember("priority") || !info[i]["priority"].IsInt()) {
            break;
        } // if
        // 値の設定
        auto type = static_cast<br::ComponentType>(info[i]["type"].GetInt());
        int priority = info[i]["priority"].GetInt();
        auto component = this->CreateComponent(type, priority);
        builder->AddComponent(component);
    } // if
    return builder;
}

br::ActorFactory::ActorFactory(br::Scene* scene) :
    _scene(scene) {

    auto r = _scene->GetResourceManager();
    this->AddBuilder(def::kUnitKeys.at(br::UnitType::Lord), 
                     this->CreateBuilder("Resource/builder/lord_builder.builder"));
    this->AddBuilder(def::kUnitKeys.at(br::UnitType::Cavalry), 
                     this->CreateBuilder("Resource/builder/cavalry_builder.builder"));
    this->AddBuilder(def::kUnitKeys.at(br::UnitType::Hoplite), 
                     this->CreateBuilder("Resource/builder/hoplite_builder.builder"));
    this->AddBuilder(def::kUnitKeys.at(br::UnitType::Archer),
                     this->CreateBuilder("Resource/builder/archer_builder.builder"));

    this->AddBuilder(def::kUnitKeys.at(br::UnitType::Chariot),
                     this->CreateBuilder("Resource/builder/chariot_builder.builder"));
    this->AddBuilder(def::kUnitKeys.at(br::UnitType::General),
                     this->CreateBuilder("Resource/builder/general_builder.builder"));
    this->AddBuilder(def::kUnitKeys.at(br::UnitType::HeavyCavalry),
                     this->CreateBuilder("Resource/builder/heavy_cavalry_builder.builder"));

    this->AddBuilder(def::kUnitKeys.at(br::UnitType::Hunter),
                     this->CreateBuilder("Resource/builder/hunter_builder.builder"));
    this->AddBuilder(def::kUnitKeys.at(br::UnitType::LightCavalry),
                     this->CreateBuilder("Resource/builder/light_cavalry_builder.builder"));
    this->AddBuilder(def::kUnitKeys.at(br::UnitType::Sniper),
                     this->CreateBuilder("Resource/builder/sniper_builder.builder"));

	this->AddBuilder(def::kUnitKeys.at(br::UnitType::Healer),
		this->CreateBuilder("Resource/builder/healer_builder.builder"));
	this->AddBuilder(def::kUnitKeys.at(br::UnitType::Wizard),
		this->CreateBuilder("Resource/builder/wizard_builder.builder"));


}

br::ActorFactory::~ActorFactory() {
}

bool br::ActorFactory::Release(void) {
    for (auto t : _type) {
        t.second->Release();
    } // for
    _type.clear();
    return true;
}
