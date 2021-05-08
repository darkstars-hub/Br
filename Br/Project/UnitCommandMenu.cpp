#include "UnitCommandMenu.h"

#include "MenuMessenger.h"
#include "ActorManager.h"
#include "UnitManager.h"
#include "UnitCommandMenuMessage.h"
#include "BattleSystemForecast.h"
#include "ReverseGuage.h"


br::UnitCommandMenu::UnitCommandMenu(br::Scene* scene) :
    super(scene),
    _target(nullptr) {
    _wait = { 15, 1, 6 };
    _attack = { 15, 15, 5, 2 };
    _fusion = { 36, 2, 9, 60, 2 };
    _back = { 34, 19, 60, 42 };
    _turn_end = { 15, 62, 47, 11, 56, 2, 41, 57, 2 };
    _reverse = { 25, 47, 18, 47 };
    _heal = { 5, 1, 27, 7 };
}

void br::UnitCommandMenu::Decide(void) {
    _items.at(_index).Excute();
    this->Hide();
}

void br::UnitCommandMenu::Cancel(void) {
    _target->onCancel();
    _target = nullptr;
    this->Hide();
}

void br::UnitCommandMenu::Show(br::MenuMessage* e) {
    auto m = dynamic_cast<br::UnitCommandMenuMessage*>(e);
    _ASSERT_EXPR(m, L"メニューが表示できない");

    // パラメータのセット
    this->_is_show = true;
    this->_target = m->target;
    _textures.Load(_scene->GetResourceManager());

    // 待機コマンド
    auto w = br::MenuItem(_wait, &_textures, [&]() { return _target->onEnd(); }, this);
    _items.push_back(w);
    // 攻撃コマンド
    if (this->_target->CanAttackEnemy()) {
        auto a = br::MenuItem(_attack, &_textures,
                              [&]() {
            dynamic_cast<br::Game*>(_scene)->GetBattleSystemForeCast()->Show(_target, nullptr);
            _target->AttackStart();
            return true; }, this);
        _items.push_back(a);
    } // if
    // 合体コマンド
    if (this->_target->AdjacentPinchUnit() || this->_target->IsPinch()) {
        auto f = br::MenuItem(_fusion, &_textures, [&]() {
            _target->FusionStart();
            return true; }, this);
        _items.push_back(f);
    } // if
    // リーダーユニットなら相性反転コマンド実行
    if (this->_target->GetUnitType() == br::UnitType::Lord) {
        auto re = br::MenuItem(_reverse, &_textures, [&]() {
            dynamic_cast<br::Game*>(_scene)->GetReverseGuage()->Use();
            _target->onEnd();
            return true; }, this);
        _items.push_back(re);
    } // if

    if (this->_target->GetUnitType() == br::UnitType::Healer) {
        auto heal = br::MenuItem(_heal, &_textures, [&]() {
//            dynamic_cast<br::Game*>(_scene)->GetReverseGuage()->Use();
//            dynamic_cast<br::Game*>(_scene)->GetBattleSystemForeCast()->Show(_target, nullptr);
//            _target->AttackStart();
//            _target->FusionStart();
            _target->HealStart();
       //     _target->onEnd();
            return true; }, this);
        _items.push_back(heal);
    } // if

    // 戻るコマンド
    auto b = br::MenuItem(_back, &_textures, [&]() {
        this->Cancel();
        return true; }, this);
    _items.push_back(b);

    // 表示位置はウインドウの中心にする
    auto rect = this->GetBackRect();
    auto window_center = Mof::CVector2(def::kWindowWidth * 0.5f,
                                       def::kWindowHeight * 0.5f);
    _position.x = window_center.x - rect.GetWidth() * 0.5f;
    _position.y = window_center.y - rect.GetHeight() * 0.5f;
    // 位置の設定
    auto pos = _position;
    for (auto& v : _items) {
        v.SetPosition(pos);
        pos.y += 32;
    } // for
    // 選択しているモノの初期位置は一番上にする
    _index = 0;
    _items.at(_index).SetSelect(true);
}

void br::UnitCommandMenu::Hide(void) {
    this->_is_show = false;
    _index = 0;
    _items.clear();
    // 処理終了
    _scene->GetMenu()->Hide();
}