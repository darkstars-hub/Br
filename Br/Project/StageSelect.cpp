#include "StageSelect.h"

#include <Mof.h>

#include <bitset>

#include "Helper.h"
#include "ResourceManager.h"
#include "AudioSystem.h"


Mof::CRectangle br::StageSelect::GetIconRectangle(void) {
    auto pos = _icon_position;
    auto size = Mof::CVector2(_select_icon.GetWidth(), _select_icon.GetHeight());
    pos.x -= size.x * 0.5f;
    pos.y -= size.y * 0.5f;
    return Mof::CRectangle(pos.x, pos.y,
                           pos.x + size.x, pos.y + size.y);
}

void br::StageSelect::UpdateScene(void) {
    super::Fade();
}

bool br::StageSelect::CheckCleared(const std::string& path) {
    if (path == "") {
        return false;
    } // if

    auto it = std::find(_cleared_stage_string.begin(),
                        _cleared_stage_string.end(),
                        path);
    if (it != _cleared_stage_string.end()) {
        return true;
    } // if
    return false;
}

void br::StageSelect::Load(void) {
    std::ifstream stream("Resource/stage/cleared_stage_paths.txt");
    std::vector<std::string> paths;

    // 読み込むファイルのパスを格納
    while (stream) {
        std::string buffer;
        std::getline(stream, buffer);
        _cleared_stage_string.push_back(buffer);
    } // while
    //_cleared_stage_string.push_back("Resource/stage/stage4.txt");
}

br::StageSelect::StageSelect() :
    _icon_position(),
    _select_icon(),
    _stage_texture(),
    //_stage0_rect(Mof::CRectangle(260.0f, 500.0f, 320.0f, 560.0f)),
    _stage0(Mof::CRectangle(260.0f, 500.0f, 320.0f, 560.0f)),
    _stage1(Mof::CRectangle(260.0f, 400.0f, 320.0f, 460.0f)),
    _stage2(Mof::CRectangle(260.0f, 260.0f, 320.0f, 320.0f)),
    _stage3(Mof::CRectangle(260.0f, 600.0f, 320.0f, 660.0f)),
    _stage4(Mof::CRectangle(190.0f, 220.0f, 250.0f, 280.0f)),
    _stage_name(),
    _stage_info(),
    _bgm(),
    _select_sound(),
    _enter_sound(),
    _infomation() {
    this->Load();

    super::_resource_manager = std::make_shared<br::ResourceManager>();
    super::_audio_system = std::make_shared<br::AudioSystem>();

    _select_icon.Load("Resource/textures/select_icon.png");
    _stage_texture.Load("Resource/textures/stage_map.png");

    _bgm.Load("Resource/bgm/castle02.mp3");
    _bgm.SetLoop(true);
    _bgm.Play();
    _select_sound.Load("Resource/sound/se_maoudamashii_system47.mp3");
    _enter_sound.Load("Resource/sound/se_maoudamashii_system49.mp3");
}

br::StageSelect::~StageSelect() {
}

br::SceneId br::StageSelect::GetSceneId(void) const {
    return br::SceneId::StageSelect;
}

br::SceneId br::StageSelect::GetNextScene(void) const {
    return br::SceneId::Load;
}

std::shared_ptr<br::SceneInfomation> br::StageSelect::GetNextSceneInfomation(void) {
    auto ret = std::make_shared <br::LoadSceneInfomation>();
    ret->resource_manager_data_path =
        "Resource/scene/game_scene_resources.txt";
    ret->audio_system_data_path =
        "Resource/scene/game_scene_sounds.txt";
    ret->next_scene = br::SceneId::Game;
    ret->select_infomation = this->GetSelectInfomation();

    if (_infomation.stage_data_path == "Resource/stage/stage0.txt") {
        ret->back_texture_path = "Resource/textures/pipo-battlebg001.jpg";
    } // if
    else if (_infomation.stage_data_path == "Resource/stage/stage1.txt") {
        ret->back_texture_path = "Resource/textures/pipo-battlebg002b.jpg";
    } // else if
    else if (_infomation.stage_data_path == "Resource/stage/stage2.txt") {
        ret->back_texture_path = "Resource/textures/pipo-battlebg009b.jpg";
    } // else if
    else if (_infomation.stage_data_path == "Resource/stage/stage3.txt") {
        ret->back_texture_path = "Resource/textures/pipo-battlebg007b.jpg";
    } // else if
    else if (_infomation.stage_data_path == "Resource/stage/stage4.txt") {
        ret->back_texture_path = "Resource/textures/pipo-battlebg010b.jpg";
    } // else if

    ret->next_scene_info = std::make_shared<br::SelectInfomation>(
        this->GetSelectInfomation()
        );
    return ret;
}

br::SelectInfomation br::StageSelect::GetSelectInfomation(void) {
    return this->_infomation;
}

bool br::StageSelect::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        if (_infomation.ExistData()) {
            _stage_name = "Game Start !";
            super::ChangeScene();
            _enter_sound.Play();
        } // if
    } // if
    return true;
}

bool br::StageSelect::Initialize(std::shared_ptr<br::SceneInfomation> info) {
    return true;
}

bool br::StageSelect::Update(void) {
    this->UpdateScene();
    if (!super::IsChange()) {
        ::g_pInput->GetMousePos(_icon_position);
    } // if

    _stage_name = "Please Select Play Stage !";
    _stage_info = "";
    _infomation.Initialize();

    auto it_begin = _cleared_stage_string.begin();
    auto it_end = _cleared_stage_string.end();
    auto rect = this->GetIconRectangle();
    // stage0
    if (_stage0.CollisionRectangle(rect)) {
        _stage0.SetUnder(true);
        _stage_name = "Masara Town Press Space !";
        _stage_info = "マサラは真っ白 始まりの色";
        _infomation.SetData("Resource/stage/stage0.txt",
                            "Resource/stage/stage0.unit_initial_coordinate",
                            "Resource/texts/stage0_start.text_system",
                            "Resource/texts/stage0_clear.text_system"
        );
    } // if
    else {
        _stage0.SetSoundPlay(true);
    } //else
    // stage1
    if (_stage1.CollisionRectangle(rect)) {
        _stage1.SetUnder(true);
        if (std::find(it_begin, it_end, std::string("Resource/stage/stage0.txt")) == it_end) {
            _stage_info = "stage 0 クリアで解放されます";
        } // if
        else {
            _stage_name = "Tokiwa City Press Space !";
            _stage_info = "トキワは緑 永遠の色";
            _infomation.SetData("Resource/stage/stage1.txt",
                                "Resource/stage/stage1.unit_initial_coordinate",
                                "Resource/texts/stage1_start.text_system",
                                "Resource/texts/stage1_clear.text_system"
            );
        } // else
    } // if
    else {
        _stage1.SetSoundPlay(true);
    } //else
    // stage2
    if (_stage2.CollisionRectangle(rect)) {
        _stage2.SetUnder(true);
        if (std::find(it_begin, it_end, std::string("Resource/stage/stage1.txt")) == it_end) {
            _stage_info = "stage 1 クリアで解放されます";
        } // if
        else {
            _stage_name = "Nibi City Press Space !";
            _stage_info = "ニビは灰色 石の色";
            _infomation.SetData("Resource/stage/stage2.txt",
                                "Resource/stage/stage2.unit_initial_coordinate",
                                "Resource/texts/stage2_start.text_system",
                                "Resource/texts/stage2_clear.text_system");
        } // else
    } // if
    else {
        _stage2.SetSoundPlay(true);
    } //else

    if (_stage3.CollisionRectangle(rect)) {
        _stage3.SetUnder(true);
        if (std::find(it_begin, it_end, std::string("Resource/stage/stage2.txt")) == it_end) {
            _stage_info = "stage 2 クリアで解放されます";
        } // if
        else {
            _stage_name = "Guren Town Press Space !";
            _stage_info = "グレンの赤は 情熱の色";
            _infomation.SetData("Resource/stage/stage3.txt",
                                "Resource/stage/stage3.unit_initial_coordinate",
                                "Resource/texts/stage3_start.text_system",
                                "Resource/texts/stage3_clear.text_system"
            );
        } // else
    } // if
    else {
        _stage3.SetSoundPlay(true);
    } //else

    if (_stage4.CollisionRectangle(rect)) {
        _stage4.SetUnder(true);
        if (std::find(it_begin, it_end, std::string("Resource/stage/stage3.txt")) == it_end) {
            _stage_info = "stage 3 クリアで解放されます";
        } // if
        else {
            _stage_name = "Pokemon League Press Space !";
            _stage_info = "セキエイこうげん";
            _infomation.SetData("Resource/stage/stage4.txt",
                                "Resource/stage/stage4.unit_initial_coordinate",
                                "Resource/texts/stage4_start.text_system",
                                "Resource/texts/stage4_clear.text_system"
            );
        } // else
    } // if
    else {
        _stage4.SetSoundPlay(true);
    } //else

    _audio_system->Update();
    return true;
}

bool br::StageSelect::Render(void) {
    // 背景（一枚絵）の表示
    _stage_texture.Render(0.0f, 0.0f);

    // アイコンのテクスチャとその当たり判定の表示
    auto pos = this->GetIconRectangle().GetTopLeft();
    auto rect = this->GetIconRectangle();
    _select_icon.Render(pos.x, pos.y);
    ::CGraphicsUtilities::RenderFillRect(rect,
                                         MOF_ARGB(100, 0, 0, 0));
    // ステージを選択する矩形の表示  
#undef min
#undef max
    auto render_stage_icon = [&](br::SelectIcon& icon) {
        auto color = std::numeric_limits<unsigned int>::max();
        auto bit = std::bitset<32>(color);
        if (icon.CollisionRectangle(rect)) {
            bit.reset(23);
            bit.reset(7);
            if (!_select_sound.IsPlay() && icon.IsSoundPlay()) {
                _select_sound.Play();
                icon.SetSoundPlay(false);
            } // if
        } // if
        bit.reset(31);
        color = bit.to_ulong();
        icon.RencerRect(color);
    };

    render_stage_icon(_stage0);
    render_stage_icon(_stage1);
    render_stage_icon(_stage2);
    render_stage_icon(_stage3);
    render_stage_icon(_stage4);


    { // 未実装ステージを隠す
        auto tex = _resource_manager->GetTexture("Resource/textures/working.png");
        tex->Render(400.0f, 200.0f);
    }
    // 選択中のステージの名前表示
    ::CGraphicsUtilities::RenderString(
        20.0f, 20.0f,
        MOF_ARGB(255, 255, 0, 0),
        _stage_name);
    ::CGraphicsUtilities::RenderString(
        620.0f, 20.0f,
        _stage_info);
    // クリア済みと表示
    auto path = std::string(_infomation.stage_data_path);
    if (this->CheckCleared(path)) {
        ::CGraphicsUtilities::RenderString(
            620.0f, 50.0f,
            "Cleared !");
    } // if

    auto it_begin = _cleared_stage_string.begin();
    auto it_end = _cleared_stage_string.end();
    if (std::find(it_begin, it_end, std::string("Resource/stage/stage0.txt")) == it_end) {
        _stage1.RencerRect(MOF_COLOR_CBLACK);
    } // if
    if (std::find(it_begin, it_end, std::string("Resource/stage/stage1.txt")) == it_end) {
        _stage2.RencerRect(MOF_COLOR_CBLACK);
    } // if
    if (std::find(it_begin, it_end, std::string("Resource/stage/stage2.txt")) == it_end) {
        _stage3.RencerRect(MOF_COLOR_CBLACK);
    } // if
    if (std::find(it_begin, it_end, std::string("Resource/stage/stage3.txt")) == it_end) {
        _stage4.RencerRect(MOF_COLOR_CBLACK);
    } // if


    super::RenderFade();
    return true;
}

bool br::StageSelect::Release(void) {
    _stage_texture.Release();
    _select_icon.Release();
    _bgm.Release();
    _select_sound.Release();
    _enter_sound.Release();
    return true;
}