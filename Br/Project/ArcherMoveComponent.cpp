#include "ArcherMoveComponent.h"

#include "MenuMessenger.h"
#include "UnitCommandMenu.h"
#include "UnitCommandMenuMessage.h"
#include "BezierCurve.h"


/*
float InterpolationAnim(float AnimTime, br::AnimData prev, br::AnimData next, int cnt = 2) {
    int phase;
    for (phase = 1; phase < cnt; phase++) {
        if (AnimTime < next.time) {
            break;
        } // if
    } // for
    phase = MOF_MIN(phase, cnt - 1);

    float nt = AnimTime - prev.time;
    float at = next.time - prev.time;
    float t = nt / at; // 配合率
    t = MOF_CLIPING(t, 0.0f, 1.0f);

    t = 0.5f - 0.5f * MOF_COS(MOF_MATH_PI * t);
// 補間
    float from = prev.value;
    float to = next.value;
    return from + (to - from) * t;
}
*/

Mof::CRectangle br::ArcherMoveComponent::GetDestinationRect(void) const {
    auto tile_pos = super::_destination->GetPosition();
    auto tile_rect = Mof::CRectangle(
        tile_pos.x, tile_pos.y,
        tile_pos.x + def::kChipSize, tile_pos.y + def::kChipSize);
    // できるだけ小さく
    float size = def::kChipSize * 0.5f - 1;
    //tile_rect.Expansion(-size);
    return tile_rect;
}

Mof::CRectangle br::ArcherMoveComponent::GetOwnerRect(void) const {
    auto pos = super::_owner->GetPosition();
    auto rect = Mof::CRectangle(
        pos.x, pos.y,
        pos.x + def::kChipSize, pos.y + def::kChipSize);
    // できるだけ小さく
    float size = def::kChipSize * 0.5f - 1;
    //rect.Expansion(-size);
    return rect;
}

br::ArcherMoveComponent::ArcherMoveComponent(Actor* owner, int priority) :
    super(owner, priority),
    _time(0.0f),
//    _time_max(60) 
_is_jump(false),
_jump_max(32.0f) {
}

br::ArcherMoveComponent::~ArcherMoveComponent() {
}

bool br::ArcherMoveComponent::IsArrived(void) const {
    return this->GetOwnerRect().CollisionRect(this->GetDestinationRect());
}

bool br::ArcherMoveComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool br::ArcherMoveComponent::Update(void) {
    auto pos = super::_owner->GetPosition();
    //ut::Zero(_move);

    if (!_select->IsUnderCursor() && !_select->IsSelected()) {
        if (!_is_move) {
            _range->Clear();
            _path->Clear();
            _motion->SetState("wait");
        } // if
    } // if

    if (_is_move) { // 今いる地点の次の地点へ
        if (!this->IsArrived()) {
            auto control1 = Mof::CVector2(super::_owner->GetPosition());
            auto control3 = Mof::CVector2(_destination->GetPosition());
            auto min_ = Mof::CVector2(
                control1.x < control3.x ? control1.x : control3.x,
                control1.y < control3.y ? control1.y : control3.y);
            auto control2 = Mof::CVector2(
                (control1.x + control3.x) * 0.5f,
                (control1.y + control3.y) * 0.5f - def::kChipSize * 3);
            std::vector<float> data_x; data_x.reserve(3);
            std::vector<float> data_y; data_y.reserve(3);
            data_x.push_back(control1.x); data_y.push_back(control1.y);
            data_x.push_back(control2.x); data_y.push_back(control2.y);
            data_x.push_back(control3.x); data_y.push_back(control3.y);

            _time += ::CUtilities::GetFrameSecond();
            if (1.0f <= _time) { _time = 1.0f; }
            auto bezier = br::BezierCurve();
            pos.x = bezier.InterpolationAnimData(_time, data_x);
            pos.y = bezier.InterpolationAnimData(_time, data_y);
            /*
              // ジャンプする（仮）
            auto dest = _destination->GetPosition();
            auto pos = super::_owner->GetPosition();
            if (!_is_jump) {
                _is_jump = true;
                _move.y -= (std::fabs(std::fabs(dest.x) - std::fabs(pos.x))) / 2;
                if (dest.y < pos.y) {
                    _move.y -= dest.y < pos.y;
                } // if
                else {
                    _move.y += dest.y < pos.y;
                } // else
            } // if

            // 60フレームで移動する
            if (dest.x > pos.x) {
                _move.x += std::fabs(std::fabs(dest.x) - std::fabs(pos.x)) / 60.0f;
            } // if
            else if (dest.x < pos.x) {
                _move.x -= std::fabs(std::fabs(dest.x) - std::fabs(pos.x)) / 60.0f;
            } // else if
            float gravity = 2.0f;
            _move.y += gravity;
            */
        } // if
          //if (this->IsArrived()) {
        else {
            _is_move = false;
            _is_jump = false;
            // 位置を修正する
            ut::Zero(_move);
            pos = _destination->GetPosition();

            // メニューを表示
            // メニューが消えたらendEvent
            auto unit = dynamic_cast<br::Unit*>(super::_owner);
            if (unit->GetTeam() == def::kPlayerTeam) {
                super::_owner->SetPosition(pos);
                auto e = br::UnitCommandMenuMessage();
                e.target = unit;
                auto m = super::_owner->GetScene()->GetMenu();
                m->Show<br::UnitCommandMenu>(&e);
            } // if
        } // else
    } // if

    //_move *= _speed;
    pos += _move;
    super::_owner->SetPosition(pos);
    return true;
}

void br::ArcherMoveComponent::MoveStart(void) {
    super::MoveStart();
    _time = 0.0f;

    //auto data = br::AnimData();
   //data.time = 0.0f;
   //data.value = super::_owner->GetPosition().y;
   //_current_data = data;
}

br::Component* br::ArcherMoveComponent::Clone(void) {
    auto ptr = new br::ArcherMoveComponent(nullptr, _priority);
    return ptr;
}
