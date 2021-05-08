//!-----------------------------------------------------
//! @file : Common.h
//! @brief : ÉQÅ[ÉÄì‡Ç≈ã§í Ç∑ÇÈÇ‡ÇÃ
//! @date : 2020/05/28
//!-----------------------------------------------------


#ifndef BR_COMMON_H_
#define BR_COMMON_H_


namespace br {
enum class Direction {
    Up,
    Down,
    Left,
    Right,
    CountMax,
};
enum class ComponentType {
    Component = 0,
    UpdateComponent = 1,
    RenderComponent = 2,

    SelectableComponent = 3,
    MotionComponent = 4,
    AttackComponent = 5,

    TextureComponent = 6,
    SpriteComponent = 7,
    PathRenderComponent = 8,
    RangeRenderComponent = 9,

    CursorMoveComponent = 10,

    UnitTextureComponent = 11,
    UnitStateComponent = 12,
    UnitMotionComponent = 13,
    UnitMoveComponent = 14,
    UnitAttackComponent = 15,
    UnitSightComponent = 16,
    UnitFusionComponent = 17,

    UnitJobComponent = 18,
    LordComponent = 19,
    CavalryComponent = 20,
    ArcherComponent = 21,
    HopliteComponent = 22,
    LightCavalryComponent = 23,
    HeavyCavalryComponent = 24,
    ChariotComponent = 25,
    HunterComponent = 26,
    GeneralComponent = 27,
    SniperComponent = 28,

    HpComponent = 29,
    AIComponent = 30,
    PathComponent = 31,
    RangeComponent = 32,

    ArcherMoveComponent = 33,


    HealerComponent = 34,
    UnitHealComponent = 35,
	WizardComponent = 36,
};
enum class TeamType {
    Player,
    Enemy
};
enum class UnitType {
    Lord = 0,
    Cavalry = 1,
    Archer = 2,
    Hoplite = 3,
    Chariot = 4,
    LightCavalry = 5,
    HeavyCavalry = 6,
    Sniper = 7,
    Hunter = 8,
    General = 9,
    Healer = 10,
	Wizard= 11,
    CountMax
};
}
#endif // !BR_COMMON_H_