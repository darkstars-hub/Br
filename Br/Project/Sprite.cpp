#include "Sprite.h"

#include "Helper.h"
#include "ResourceManager.h"


void br::SpritePart::LoadAnimation(const rapidjson::Document& document, ResourceManager& r) {
    if (!document.HasMember("images")) {
        return;
    } // if
    const auto& images = document["images"];
    _ASSERT_EXPR(images.IsArray(),
                 L"images type is not array");

    //auto k = images.Size();
    auto k = 1; // １種類とする
    for (size_t i = 0; i < k; i++) {
        auto uri = std::string();
        // uri
        if (images[i].HasMember("uri")) {
            const auto& uri_data = images[i]["uri"];
            _ASSERT_EXPR(uri_data.IsString(),
                         L"uri type is not string");
            uri = uri_data.GetString();

            _texture = r.GetTexture(_directory_path + uri);
        } // if
    } // for



    if (!document.HasMember("animations")) {
        return;
    } // if
    std::vector<Mof::SpriteAnimationCreatePattern> pattern_table;
    const auto& pattern_data = document["pattern"];
    _ASSERT_EXPR(pattern_data.IsArray(),
                 L"pattern type is not string");
    auto m = pattern_data.Size();
    for (size_t j = 0; j < m; j++) {
        auto pattern = Mof::SpriteAnimationCreatePattern();
        // frame
        if (pattern_data[j].HasMember("frame")) {
            const auto& frame = pattern_data[j]["frame"];
            _ASSERT_EXPR(frame.IsInt(),
                         L"frame type is not int");
            pattern.Wait = frame.GetInt();
        } // if
        // no
        if (pattern_data[j].HasMember("no")) {
            const auto& no = pattern_data[j]["no"];
            _ASSERT_EXPR(no.IsInt(),
                         L"no type is not int");
            pattern.No = no.GetInt();
        } // if
        // step
        if (pattern_data[j].HasMember("step")) {
            const auto& step = pattern_data[j]["step"];
            _ASSERT_EXPR(step.IsInt(),
                         L"step type is not int");
            pattern.Step = step.GetInt();
        } // if

        pattern_table.push_back(pattern);
    } // for



    if (!document.HasMember("animations")) {
        return;
    } // if
    const auto& animations_data = document["animations"];
    _ASSERT_EXPR(animations_data.IsArray(),
                 L"animations type is not array");

    auto n = animations_data.Size();

    for (size_t i = 0; i < n; i++) {
        auto anim = Mof::SpriteAnimationCreate();
        auto motion_key = std::string();
        // name
        if (animations_data[i].HasMember("name")) {

            const auto& name_data = animations_data[i]["name"];
            _ASSERT_EXPR(name_data.IsString(),
                         L"name type is not string");
            anim.Name = name_data.GetString();
            motion_key = std::string(name_data.GetString());
        } // if
        //_motion_map.emplace(motion_key, i);
        _motion_map.emplace(i, motion_key);

        // x
        if (animations_data[i].HasMember("offset_x")) {
            const auto& offset_x = animations_data[i]["offset_x"];
            _ASSERT_EXPR(offset_x.IsInt(),
                         L"offset_x type is not int");
            anim.OffsetX = offset_x.GetInt();
        } // if
        // y
        if (animations_data[i].HasMember("offset_y")) {
            const auto& offset_y = animations_data[i]["offset_y"];
            _ASSERT_EXPR(offset_y.IsInt(),
                         L"offset_y type is not int");
            anim.OffsetY = offset_y.GetInt();
        } // if

        // width
        if (animations_data[i].HasMember("width")) {
            const auto& width = animations_data[i]["width"];
            _ASSERT_EXPR(width.IsInt(),
                         L"width type is not int");
            anim.Width = width.GetInt();
        } // if
        // height
        if (animations_data[i].HasMember("height")) {
            const auto& height = animations_data[i]["height"];
            _ASSERT_EXPR(height.IsInt(),
                         L"height type is not int");
            anim.Height = height.GetInt();
        } // if


        // loop
        if (animations_data[i].HasMember("loop")) {
            const auto& loop = animations_data[i]["loop"];
            _ASSERT_EXPR(loop.IsInt(),
                         L"loop type is not int");
            anim.bLoop = loop.GetInt() == 1 ? true : false;
        } // if

        // pattern
        if (animations_data[i].HasMember("pattern")) {
            const auto& pattern_data = animations_data[i]["pattern"];
            _ASSERT_EXPR(pattern_data.IsArray(),
                         L"pattern type is not string");
            auto l = pattern_data.Size();
            std::vector<Mof::SpriteAnimationCreatePattern> patterns;
            for (size_t j = 0; j < l; j++) {
                const auto& index = pattern_data[j];
                _ASSERT_EXPR(index.IsInt(),
                             L"index type is not int");
                anim.Pattern[j] = pattern_table.at(index.GetInt());
            } // for
        } // if
        _anims.push_back(std::move(anim));
    } // for
}

br::SpritePart::SpritePart() :
    _directory_path(),
    _texture(),
    _anims() {
}

br::SpritePart::~SpritePart() {
}

std::weak_ptr<Mof::CTexture> br::SpritePart::GetTexture(void) {
    return this->_texture;
}

std::vector<Mof::SpriteAnimationCreate>& br::SpritePart::GetAnimsAddress(void) {
    // TODO: return ステートメントをここに挿入します
    return this->_anims;
}

//std::unordered_map<std::string, int>& br::SpritePart::GetMotionMapAddress(void) {
std::unordered_map<int, std::string>& br::SpritePart::GetMotionMapAddress(void) {
    // TODO: return ステートメントをここに挿入します
    return this->_motion_map;
}

bool br::SpritePart::Load(const char* path, ResourceManager& r) {
    if (auto format = std::strstr(path, ".sprite"); !format) {
        return false;
    } // if
    std::ifstream file(path);
    if (!file.is_open()) {
        TRACE;
        DEBUG_PRINT("sprite file not found");
        return false;
    } // if

    _directory_path = path;
    auto pos = _directory_path.rfind("/");
    _directory_path = std::string(path, path + pos + 1);

    std::stringstream stream;
    stream << file.rdbuf();
    std::string contents = stream.str();
    rapidjson::StringStream str(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(str);

    this->LoadAnimation(doc, r);
    return true;
}

bool br::SpritePart::Release(void) {
    _anims.clear();
    return true;
}


br::Sprite::Sprite() :
    _texture(),
    _motion(),
    _motion_map(nullptr),
    //_current_no(0),
    //_p(nullptr),
    _reverse_x(false) {
}

br::Sprite::~Sprite() {
}

void br::Sprite::SetReverseX(bool reverse) {
    this->_reverse_x = reverse;
}

std::unordered_map<int, std::string>* br::Sprite::GetMotionMap(void) {
    return _motion_map;
}

Mof::CRectangle br::Sprite::GetSrcRect(void)  {
    return _motion.GetSrcRect();
}

bool br::Sprite::Load(const char* path, br::ResourceManager& r) {
    auto part = r.GetSpritePart(path);
    _motion_map = &part->_motion_map;
    _motion.Create(part->_anims.data(), part->_anims.size());
    _texture = part->_texture;
    //_p = &*r.GetSpritePart(path);
    return true;
}

bool br::Sprite::Load(br::SpritePart& part) {
    _motion_map = &part._motion_map;
    _motion.Create(part._anims.data(), part._anims.size());
    _texture = part._texture;
    //_p = &part;
    return true;
}

void br::Sprite::Update(void) {
    _motion.AddTimer(Mof::CUtilities::GetFrameSecond());
}

void br::Sprite::Render(const Mof::Vector2 position) {
    if (auto r = _texture.lock()) {
#ifdef _DEBUG
        auto rect = _motion.GetSrcRect();
        ::CGraphicsUtilities::RenderFillRect(
            CRectangle(position.x,
                       position.y,
                       position.x + rect.GetWidth(),
                       position.y + rect.GetHeight()),
            MOF_ARGB(99, 99, 99, 99));
#endif // _DEBUG
        if (_reverse_x) {
            std::swap(rect.Left, rect.Right);
        } // if
        r->Render(position.x, position.y, rect);
    } // if
}

bool br::Sprite::Release(void) {
    _texture.reset();
    _motion.Release();
    return true;
}

bool br::Sprite::ChangeMotionByName(const char* name) {
    return _motion.ChangeMotionByName(name);
}

int br::Sprite::GetMotionNo(void) {
    return _motion.GetMotionNo();
}

bool br::Sprite::IsEndMotion(void) {
    return _motion.IsEndMotion();
}