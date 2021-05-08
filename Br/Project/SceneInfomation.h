//!-----------------------------------------------------
//! @file : SceneInfomation.h
//! @brief : Sceneクラスを継承するクラスの構成情報の基底クラス
//! @date : 2020/08/10
//!-----------------------------------------------------


#ifndef BR_SCENE_INFOMATION_H
#define BR_SCENE_INFOMATION_H


namespace br {
enum class SceneId {
    Title,
    TextScene,
    StageSelect,
    Load,
    Game,
    GameClear,
    GameOver,
    CountMax
};

struct SceneInfomation {
    SceneInfomation() = default;
    virtual ~SceneInfomation() = default;
};
}
#endif // !BR_SCENE_INFOMATION_H