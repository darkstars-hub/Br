#include "Title.h"

#include <Mof.h>

#include "Helper.h"
#include "ResourceManager.h"
#include "AudioSystem.h"


br::Title::Title() {
    super::_resource_manager = std::make_shared<br::ResourceManager>();
    super::_audio_system = std::make_shared<br::AudioSystem>();
}

br::Title::~Title() {
}

br::SceneId br::Title::GetSceneId(void) const {
    return br::SceneId::Title;
}

br::SceneId br::Title::GetNextScene(void) const {
    return br::SceneId::Load;
}

br::TextSceneInfomation br::Title::GetTextSceneInfomation(void) {
    auto ret = br::TextSceneInfomation();
    ret.text_path = "Resource/texts/game_start.text_system";
    ret.texture_path = "Resource/textures/back_ground_0.png";
    ret.bgm_path = "Resource/bgm/castle01.mp3";
    ret.next_scene = br::SceneId::StageSelect;
    return ret;
}

std::shared_ptr<br::SceneInfomation> br::Title::GetNextSceneInfomation(void) {
    auto ret = std::make_shared<br::LoadSceneInfomation>();
    ret->resource_manager_data_path =
        "Resource/scene/text_scene_resources.txt";
    ret->audio_system_data_path =
        "Resource/scene/text_scene_sounds.txt";
    ret->text_infomation = this->GetTextSceneInfomation();
    ret->next_scene = br::SceneId::TextScene;

    ret->next_scene_info = std::make_shared<br::TextSceneInfomation>(
        this->GetTextSceneInfomation()
        );
    return ret;
}

bool br::Title::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        super::ChangeScene();
        return true;
    } // if
    return true;
}

bool br::Title::Initialize(std::shared_ptr<br::SceneInfomation> info) {
    return true;
}

bool br::Title::Update(void) {
    super::Fade();
    _audio_system->Update();
    return true;
}

bool br::Title::Render(void) {
    auto back = super::_resource_manager->GetTexture("Resource/textures/title.jpg");
    back->Render(0.0f, 0.0f, Mof::CRectangle(0.0f, 0.0f, back->GetWidth(), back->GetHeight())
                 , MOF_ARGB(255, 200, 200, 200));

    ::CGraphicsUtilities::RenderString(
        400.0f, 400.0f,
        "Press Space",
        MOF_COLOR_WHITE);
    // ‘JˆÚŒø‰Ê•\Ž¦
    super::RenderFade();
    return true;
}

bool br::Title::Release(void) {
    return true;
}