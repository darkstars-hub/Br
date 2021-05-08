#include "Stage.h"

#include "Helper.h"
#include "AudioSystem.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "Tile.h"


br::Stage::Stage(br::Scene* scene) :
    super(scene),
    _tiles() {
    auto a = _scene->GetAudioSystem();
    a->Play("Resource/bgm/stage0.mp3");
}

br::Stage::~Stage() {
}

br::ActorState br::Stage::GetState(void) const {
    return super::_base.state;
}

Mof::CVector2 br::Stage::GetPosition(void) const {
    return super::_base.position;
}

br::Tile* br::Stage::GetTile(int col, int row, br::Direction direction) {
    // 方向オフセット設定
    int x = 0; int y = 0;
    switch (direction) {
        case br::Direction::Up:
            y--;
            break;
        case br::Direction::Down:
            y++;
            break;
        case br::Direction::Left:
            x--;
            break;
        case br::Direction::Right:
            x++;
            break;
        default:
            break;
    } // switch


    auto tile = std::find_if(_tiles.begin(),
                             _tiles.end() - 1,
                             [&](auto& tile) {
        return
            (col == (tile->GetPosition().x / def::kChipSize) - x) &&
            (row == (tile->GetPosition().y / def::kChipSize) - y);
    });
    if (tile == _tiles.end()) {
        return nullptr;
    } // if

    return *tile;
}

br::Tile* br::Stage::GetTile(def::Vector2i position, br::Direction direction) {
    return this->GetTile(position.col, position.row, direction);
}

Mof::CVector2 br::Stage::GetTileCount(void) const {
    return this->_tile_count;
}


bool br::Stage::Load(const char* path) {
    //テキストファイルを開く
    FILE* fp = fopen(path, "rt");
    if (fp == NULL) {
        return false;
    }
    fseek(fp, 0, SEEK_END);
    long fSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);


    char* pBuffer = (char*)malloc(fSize + 1);
    fSize = fread(pBuffer, 1, fSize, fp);
    pBuffer[fSize] = '\0';
    char* pstr;

     //マップのチップ数
    pstr = strtok(pBuffer, ",");
    _tile_count.x = atoi(pstr);
    pstr = strtok(NULL, ",");
    _tile_count.y = atoi(pstr);

    //チップデータの読み込み
    for (int y = 0; y < _tile_count.y; y++) {
        for (int x = 0; x < _tile_count.x; x++) {
            pstr = strtok(NULL, ",");
            _tile_id.push_back(std::atoi(pstr));
        } // for
    } // for

    //ファイルを閉じる
    fclose(fp);
    free(pBuffer);
    return true;
}

bool br::Stage::Initialize(const br::ActorBaseState& base) {
    super::Initialize(base);

    for (int row = 0; row < _tile_count.y; row++) {
        for (int col = 0; col < _tile_count.x; col++) {
            auto tile = new Tile(_scene, _tile_id.at(row * _tile_count.x + col));
            
            auto base = br::ActorBaseState();
            base.position = Mof::CVector2(def::kChipSize * col,
                                          def::kChipSize * row);
            base.state = br::ActorState::Active;
            base.type = br::ActorType::Tile;
            tile->Initialize(base);
            _tiles.push_back(tile);
        } // for
    } // for
        // １＊１の「ふち」があるので、実際には2列2行少ない
    int space = 1;
    for (int y = 0 + space; y < _tile_count.y - space; y++) {
        for (int x = 0 + space; x < _tile_count.x - space; x++) {
            auto tile = _tiles.at(y * _tile_count.x + x);
            if (y > 0 + space) {
                tile->RegisterAdjacent(br::Direction::Up,
                                       _tiles.at((y - 1) * _tile_count.x + x));
            } // if
            if (y < _tile_count.y - 1 - space) {
                tile->RegisterAdjacent(br::Direction::Down,
                                       _tiles.at((y + 1) * _tile_count.x + x));
            } // if
            if (x > 0 + space) {
                tile->RegisterAdjacent(br::Direction::Left,
                                       _tiles.at(y * _tile_count.x + x - 1));
            } // if
            if (x < _tile_count.x - 1 - space) {
                tile->RegisterAdjacent(br::Direction::Right,
                                       _tiles.at(y * _tile_count.x + x + 1));
            } // if
        } // for
    } // for

    return true;
}

bool br::Stage::Update(void) {
    super::Update();
    for (auto actor : _tiles) {
        actor->Update();
    } // for
    return true;
}

bool br::Stage::Render(Mof::CVector2 scroll) {
    super::Render(scroll);
    auto tex = _scene->GetResourceManager()->GetTexture("Resource/textures/back_ground_stage.png");
    tex->Render(0.0f, 0.0f);
    for (auto actor : _tiles) {
        actor->Render(scroll);
    } // for
    return true;
}

bool br::Stage::Release(void) {
    super::Release();
    for (auto actor : _tiles) {
        actor->Release();
        MOF_SAFE_DELETE(actor);
    } // for
    _tiles.clear();
    return true;
}