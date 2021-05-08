#include "Tile.h"

#include "Helper.h"
#include "StageTable.h"
#include "ResourceManager.h"
#include"ActorManager.h"
#include "TextureComponent.h"
#include "UnitManager.h"
#include "Unit.h"


br::Tile::Tile(br::Scene* scene, int type) :
    super(scene),
    _type(type),
    _name(),
    _cost(-1),
    _col(-1),
    _row(-1) {
    for (auto& a : _adjacents) {
        a = nullptr;
    } // for

    auto part = def::tile_table.at(_type);
   // super::_base.name = part.name;
    _name = part.name;
    _cost = part.cost;

    auto tex = new br::TextureComponent(this, 80);
    tex->SetTexture(_scene->GetResourceManager()->
                    GetTexture(part.path),
                    &part.render_rect);
}

br::Tile::~Tile() {
}

br::ActorState br::Tile::GetState(void) const {
    return super::_base.state;
}

Mof::CVector2 br::Tile::GetPosition(void) const {
    return super::_base.position;
}

br::Unit* br::Tile::GetOnUnit(void) {
    return super::GetScene()->GetActorManager()->GetUnitManager()->GetUnit(_col, _row);
}

def::Vector2i br::Tile::GetGridPosition(void) {
    return ut::ToGridPos(this->GetPosition());
}

const char* br::Tile::GetName(void) const {
    return this->_name;
    //return super::_base.name;
}

int br::Tile::GetCost(void) const {
    return this->_cost;
}

int br::Tile::GetCost(br::Unit* ptr) const {
    return this->_cost;
}

br::Tile::tile_array& br::Tile::GetAdjacents(void) {
    return this->_adjacents;
}
bool br::Tile::IsBlocked(void) {
    if (_type == 4) {
        return true;
    } // if
    return false;
}
bool br::Tile::IsBlocked(br::Unit* ptr) {
    if (_type == 4) {
        return true;
    } // if
    auto unit = this->GetOnUnit();
    if (unit && unit->GetTeam() != ptr->GetTeam()) {
        return true;
    } // if
    return false;
}

bool br::Tile::Initialize(const br::ActorBaseState& base) {
    super::Initialize(base);
    return true;
}

bool br::Tile::Update(void) {
    super::Update();

    _col = this->GetPosition().x / def::kChipSize;
    _row = this->GetPosition().y / def::kChipSize;
    return true;
}

void br::Tile::RegisterAdjacent(br::Direction direction, Tile* tile) {
    using Dir = br::Direction;
    switch (direction) {
        case br::Direction::Up:
            _adjacents.at(static_cast<int>(Dir::Up)) = tile;
            break;
        case br::Direction::Down:
            _adjacents.at(static_cast<int>(Dir::Down)) = tile;
            break;
        case br::Direction::Left:
            _adjacents.at(static_cast<int>(Dir::Left)) = tile;
            break;
        case br::Direction::Right:
            _adjacents.at(static_cast<int>(Dir::Right)) = tile;
            break;
        default:
            break;
    } // switch
}

bool br::Tile::Equal(br::Tile* r) {
    int size = def::kChipSize;
    auto a = this->GetPosition();
    auto b = r->GetPosition();
    return
        (int)a.x / size == (int)b.x / size &&
        (int)a.y / size == (int)b.y / size;
}

bool br::Tile::Render(Mof::CVector2 scroll) {
    super::Render(scroll);

    // ï\é¶Ç∑ÇÈÇ∆èdÇ≠Ç»ÇÈ
//#undef _DEBUG;
#ifndef _DEBUG
    auto size = def::kChipSize;
    auto pos = this->GetPosition();
    ::CGraphicsUtilities::RenderString(
        (pos - scroll).x + 8,
        (pos - scroll).y + 8,
        "%d", _cost);

    //! ó◊ê⁄èÛë‘ï\é¶
    for (int i = 0; i < static_cast<int>(br::Direction::CountMax); i++) {
        auto rect = Mof::CRectangle(pos.x, pos.y, pos.x + size, pos.y + size);
        rect.Translation(-scroll);
        rect.Expansion(-12, -12);

        if (_adjacents.at(i)) {
            auto dir = static_cast<br::Direction>(i);
            auto off = Mof::CVector2(); int val = def::kChipSize / 2;
            switch (dir) {
                case br::Direction::Up:
                    off.y -= val;
                    rect.Translation(off);
                    ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(99, 255, 0, 255));
                    break;
                case br::Direction::Down:
                    off.y += val;
                    rect.Translation(off);
                    ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(99, 255, 0, 255));
                    break;
                case br::Direction::Left:
                    off.x -= val;
                    rect.Translation(off);
                    ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(99, 255, 0, 255));
                    break;
                case br::Direction::Right:
                    off.x += val;
                    rect.Translation(off);
                    ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(99, 255, 0, 255));
                    break;
                case br::Direction::CountMax:
                    break;
                default:
                    break;
            }
        } // if
    } // for
#endif // _DEBUG
    return true;
}