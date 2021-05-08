#define MUTE
#include "TextSystem.h"

#include "Helper.h"


br::TextSystem::TextSystem() :
    _window(def::kChipSize * 2,
            def::kChipSize * 17,
            ::g_pGraphics->GetTargetWidth() - def::kChipSize * 2,
            ::g_pGraphics->GetTargetHeight() - def::kChipSize),
    _font(),
    _is_show(false),
    _end_event(),
    _texts(),
    _index(0),
    _text_index(0),
    _texture_paths(),
    _rectangles(),
    _positions(),
    _reverses(),
    _resource_manager(),
    _sound() {
    _font.Create();
    _sound.Load("Resource/sound/se_maoudamashii_system48.mp3");
}

br::TextSystem::~TextSystem() {
}

void br::TextSystem::SetResourceManager(std::shared_ptr<br::ResourceManager> r) {
    this->_resource_manager = r;
}

bool br::TextSystem::IsShow(void) const {
    return this->_is_show;
}

void br::TextSystem::Show(const char* path, std::function<void(void)>lambda) {
    _is_show = true;
    _end_event = lambda;
    _index = 0;
    _text_index = 0;

    //! テキスト情報
    rapidjson::Document document;
    ut::LoadJsonDocument(path, document);
    const auto& info = document["infomation"];
    _ASSERT_EXPR(info.IsArray(),
                 L"infomation type is not array");
    _texts.reserve(info.Size());
    _texture_paths.reserve(info.Size());
    _rectangles.reserve(info.Size());
    _positions.reserve(info.Size());
    _reverses.reserve(info.Size());
    for (int i = 0; i < info.Size(); i++) {
        if (!info[i].HasMember("text") || !info[i]["text"].IsString() ||
            !info[i].HasMember("texture") || !info[i]["texture"].IsString() ||
            !info[i].HasMember("rect_left") || !info[i]["rect_left"].IsFloat() ||
            !info[i].HasMember("rect_right") || !info[i]["rect_right"].IsFloat() ||
            !info[i].HasMember("rect_top") || !info[i]["rect_top"].IsFloat() ||
            !info[i].HasMember("rect_down") || !info[i]["rect_down"].IsFloat() ||
            !info[i].HasMember("position_x") || !info[i]["position_x"].IsFloat() ||
            !info[i].HasMember("position_y") || !info[i]["position_y"].IsFloat() ||
            !info[i].HasMember("reverse_x") || !info[i]["reverse_x"].IsBool()) {
            break;
        } // if
        // 値の設定
        _texts.push_back(info[i]["text"].GetString());
        _texture_paths.push_back(info[i]["texture"].GetString());
        _rectangles.push_back(Mof::CRectangle(
            info[i]["rect_left"].GetFloat(),
            info[i]["rect_top"].GetFloat(),
            info[i]["rect_right"].GetFloat(),
            info[i]["rect_down"].GetFloat()));
        _positions.push_back(Mof::CVector2(
            info[i]["position_x"].GetFloat(),
            info[i]["position_y"].GetFloat()));
        _reverses.push_back(info[i]["reverse_x"].GetBool());
    } // if

}

void br::TextSystem::Show(const std::string& text, std::function<void(void)> lambda) {
    _is_show = true;
    _end_event = lambda;
    _index = 0;
    _text_index = 0;
    // １文にのみ対応
    _texts.push_back(text);
}

void br::TextSystem::Hide(void) {
    _is_show = false;
    _end_event();
    _texts.clear();
    _texture_paths.clear();
    _rectangles.clear();
    _positions.clear();
    _reverses.clear();
}

void br::TextSystem::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        if (_index < _texts.size() - 1) {
            _index++;
            _text_index = 0;
            _sound.Play();
        } // if
        else {
            this->Hide();
        } // else
    } // if
}

void br::TextSystem::Update(void) {
    if (_index < _texts.size()) {
        if (_text_index < _texts.at(_index).size()) {
            _text_index++;
        } // if
    } // if
}

void br::TextSystem::Render(void) {
    ::CGraphicsUtilities::RenderFillRect(
        _window,
        MOF_ARGB(200, 0, 0, 0));

    // テクスチャを表示できるなら表示する
    if (!_texture_paths.empty()) {
        if (auto r = _resource_manager.lock()) {
            if (auto tex = r->GetTexture(
                _texture_paths.at(_index)); tex) {
                auto rect = _rectangles.at(_index);
                auto pos = _positions.at(_index);
                if (_reverses.at(_index)) {
                    std::swap(rect.Left, rect.Right);
                } // if
                tex->Render(pos.x, pos.y, rect);
            } // if
        } // if
    } // if

    // テキスト表示
    auto text = _texts.at(_index);

    auto str = std::string(_texts.at(_index), 0, _text_index);

    auto pos = _window.GetTopLeft();
    _font.RenderString(pos.x, pos.y, str.c_str());
}

void br::TextSystem::Reset(void) {
}

void br::TextSystem::Release(void) {
    _sound.Release();
    _font.Release();
    _resource_manager.reset();
}
