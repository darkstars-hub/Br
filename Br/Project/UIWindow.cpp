#include "UIWindow.h"

#include "Game.h"
#include "Stage.h"
#include "ActorManager.h"
#include "UnitManager.h"
#include "UnitStateComponent.h"
#include "UnitCompatibility.h"


void br::UIWindow::RenderTurn(void) {
    //auto turn = _game->GetTurn().c_str();
    Mof::CRectangle rect;
    int size = def::kUIWindowOffset;
    if (_game->GetTurn() == def::kPlayerTeam) {
        rect = Mof::CRectangle(0.0f, 0.0f, size, size);
    } // if
    else if (_game->GetTurn() == def::kEnemyTeam) {
        rect = Mof::CRectangle(0.0f, size, size, size * 2);
    } // else if
    auto r = _game->GetResourceManager();
    auto tex = r->GetTexture("Resource/textures/turn160.png");


    auto window = ::g_pFramework->GetWindow();
    auto pos = Mof::CVector2(window->GetWidth() - size, 0.0f);
    tex->Render(pos.x, pos.y, rect);
}

void br::UIWindow::RenderTileInfomation(void) {
    if (!_tile) {
        return;
    } // if
    ::CGraphicsUtilities::RenderString(
        500.0f, 100.0f,
        "名前 = %s  地形コスト = %d ",
        //tile->GetName().c_str(),
        _tile->GetName(),
        _tile->GetCost());
}

void br::UIWindow::RenderUnitInfomation(void) {
    if (!_unit) {
        return;
    } // id
    ::CGraphicsUtilities::RenderString(
        0.0f, 20.0f,
        "名前 = %s \n\
HP = %d / %d 移動可能数 = %d\n\
攻撃 = %d 防御 = %d\n\
魔攻 = %d 魔防 = %d\n\
命中 = %d 回避 = %d",
        _unit->GetName(),
        _unit->GetStateComponent()->GetHp()->GetValue(),
        _unit->GetStateComponent()->GetHp()->GetMaxValue(),
        _unit->GetStateComponent()->GetMoveCount(),
        _unit->GetStateComponent()->GetStatus()->GetAttack(),
        _unit->GetStateComponent()->GetStatus()->GetDefence(),
        _unit->GetStateComponent()->GetStatus()->GetMagicAttack(),
        _unit->GetStateComponent()->GetStatus()->GetMagicDefence(),
        _unit->GetStateComponent()->GetStatus()->GetHit(),
        _unit->GetStateComponent()->GetStatus()->GetAvoid());
}

void br::UIWindow::RenderCompatibility(void) {
    int size = def::kUIWindowOffset;
    float width = ::g_pFramework->GetWindow()->GetWidth();
    float height = ::g_pFramework->GetWindow()->GetHeight();

    if (auto r = _resource_manager.lock()) {
        auto tex = r->GetTexture("Resource/textures/unit_compatibility.png");
        auto rect = Mof::CRectangle(0.0f, 0.0f, 160.0f, 160.0f);

        // 逆の相性表を表示
        if (br::UnitCompatibility::GetInstance().IsReverse()) {
            rect.Translation(Mof::CVector2(160.0f, 0.0f));
        } // if
        tex->Render(width - rect.GetWidth(),
                    height - rect.GetHeight(),
                    rect);
    } // if
}

br::UIWindow::UIWindow() :
    _game(nullptr),
    _cursor(nullptr),
    _tile(nullptr),
    _unit(nullptr),
    _compatibility_texture(),
    _resource_manager() {
}

br::UIWindow::~UIWindow() {
}

void br::UIWindow::SetGame(br::Game* ptr) {
    this->_game = ptr;


    _resource_manager = _game->GetResourceManager();
}

void br::UIWindow::SetCursor(br::Cursor* cursor) {
    this->_cursor = cursor;
}

Mof::CVector2 br::UIWindow::GetOffset(void) const {
    return Mof::CVector2(0.0f,
                         def::kUIWindowOffset);
}

def::Vector2i br::UIWindow::GetOffsetCount(void) const {
    auto v = def::Vector2i();
    v.x = def::kUIWindowOffsetCount;
    v.y = def::kUIWindowOffsetCount;
    v.col = def::kUIWindowOffsetCount;
    v.row = def::kUIWindowOffsetCount;
    return v;
}

void br::UIWindow::Update(void) {
    auto pos = ut::ToGridPos(_game->GetCursor()->GetPosition());
    _tile = _game->GetStage()->GetTile(pos);
    auto units = _game->GetActorManager()->GetUnitManager()->GetUnits();
    int size = def::kChipSize;

    _unit = nullptr;
    for (auto unit : units) {
        auto p = ut::ToGridPos(unit->GetPosition());
        if (pos == p && // 死んでいないユニット
            unit->GetState() != br::ActorState::Dead) {
            _unit = unit;
            break;
        } // if
    } // for
}

void br::UIWindow::Render(void) {
    int size = def::kUIWindowOffset;
    int color = MOF_ARGB(150, 200, 200, 0);
    float width = ::g_pFramework->GetWindow()->GetWidth();
    float height = ::g_pFramework->GetWindow()->GetHeight();
    ::CGraphicsUtilities::RenderFillRect(
        width - size,
        0.0f,
        width,
        height,
        color);
    ::CGraphicsUtilities::RenderFillRect(
        0.0f,
        0.0f,
        width,
        size,
        color);

    this->RenderTurn();
    this->RenderTileInfomation();
    this->RenderUnitInfomation();
    this->RenderCompatibility();
}