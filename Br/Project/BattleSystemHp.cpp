#include "BattleSystemHp.h"

#include "DamageCalculator.h"
#include "BattleSystemUnit.h"


br::BattleSystemHp::BattleSystemHp() :
    _damege_alpha(0),
    _hp_frame(),
    _hp_green(),
    _hp_red(),
    _offset(),
    _last_hp(0.0f),
    _unit(nullptr),
    _hp(nullptr),
    _damage_decrase(0.3f) {
}

br::BattleSystemHp::~BattleSystemHp() {
}

int br::BattleSystemHp::GetAlpha(void) const {
    return _damege_alpha;
}

br::BattleSystemUnit* br::BattleSystemHp::GetUnit(void) {
    return this->_unit;
}

void br::BattleSystemHp::Initialize(std::weak_ptr<br::ResourceManager> resource_manager,
                                    br::BattleSystemUnit* unit) {
    // メンバ初期化
    _unit = unit;
    _unit_data = unit->GetUnit();
    _hp = _unit_data->GetComponent<br::HpComponent>();
    _last_hp = _hp->GetValue();

    _damege_alpha = 0;

    // 使用画像の設定
    const char* path = "Resource/textures/battle_system/hp_frame.png";
    const char* path_r = "Resource/textures/battle_system/hp_red.png";
    const char* path_g = "Resource/textures/battle_system/hp_green.png";
    if (auto r = resource_manager.lock()) {
        _hp_frame = r->GetTexture(path);
        _hp_green = r->GetTexture(path_g);
        _hp_red = r->GetTexture(path_r);
    } // if
    _offset = Mof::CVector2(0.0f, -50.0f);
}

void br::BattleSystemHp::Update(void) {
    // Hpの値が変われば表示量を減らす
    if (_last_hp != _hp->GetValue()) {
        _last_hp -= _damage_decrase;

        if (_last_hp <= _hp->GetValue()) {
            _last_hp = _hp->GetValue();
        } // if
    } // if
}

void br::BattleSystemHp::Render(Mof::CVector2 position, const br::Unit& attacker, const br::Unit& target) {
    int color = MOF_ARGB(_damege_alpha, 255, 255, 255);
    br::DamageCalculator c;
    int value = c.Calculation(attacker, target);

    _hp_frame->Render(position.x + _offset.x,
                      position.y + _offset.y,
                      color);
    float hp = target.GetStateComponent()->GetHp()->GetValue();
    float hp_max = target.GetStateComponent()->GetHp()->GetMaxValue();
    auto rect_red = Mof::CRectangle(0.0f, 0.0f,
                                    _hp_red->GetWidth() * (_last_hp / hp_max),
                                    _hp_red->GetHeight());
    _hp_red->Render(position.x + _offset.x,
                    position.y + _offset.y,
                    rect_red,
                    color);
    auto rect_green = Mof::CRectangle(0.0f, 0.0f,
                                      _hp_green->GetWidth() * (hp / hp_max),
                                      _hp_green->GetHeight());
    _hp_green->Render(position.x + _offset.x,
                      position.y + _offset.y,
                      rect_green,
                      color);


    auto offset = _offset;
    offset.x += 40.0f;
    offset.y -= 40.0f;
    ::CGraphicsUtilities::RenderString(position.x + offset.x,
                                       position.y + offset.y,
                                       MOF_ARGB(_damege_alpha, 255, 0, 0),
                                       "%d", value);
}

void br::BattleSystemHp::IncrementAlpha(int abs) {
    _damege_alpha += abs;
    if (255 < _damege_alpha) {
        _damege_alpha = 255;
    } // if
}

void br::BattleSystemHp::DecrementAlpha(int abs) {
    _damege_alpha -= abs;
    if (_damege_alpha < 0) {
        _damege_alpha = 0;
    } // if
}