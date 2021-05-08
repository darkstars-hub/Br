//!-----------------------------------------------------
//! @file : SceneManager.h
//! @brief : 各シーンを管理する
//! @date : 2020/10/27
//!-----------------------------------------------------


#ifndef BR_SCENE_MANAGER_H
#define BR_SCENE_MANAGER_H


#include "Scene.h"

namespace br {
class SceneManager {
private:
    std::shared_ptr<Scene> _current;
    std::shared_ptr<Scene> _next;
public:
    //!-----------------------------------------------------
//! @brief : コンストラクタ
//! @param : [in](void) none
//! @return : none
//!-----------------------------------------------------
    SceneManager();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~SceneManager();

    static SceneManager& Singleton(void);

    template<typename T>
    void ChangeScene(void) {
        auto next_info = _current->GetNextSceneInfomation();
        auto r = _current->GetNextResourceManager();
        auto a = _current->GetNextAudioSystem();

        _current->Release();
        _current.reset();

        _current = std::make_shared<T>();
        _current->AcquireResource(r, a);
        _current->Initialize(next_info);
    }
//!-----------------------------------------------------
//! @brief : 入力処理
//! @param : [in](void) none
//! @return : 成功した場合true
//!-----------------------------------------------------
    bool Input(void);

    //!-----------------------------------------------------
    //! @brief : 初期化
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Initialize(void);
    //!-----------------------------------------------------
//! @brief : 更新
//! @param : [in](void) none
//! @return : 成功した場合true
//!-----------------------------------------------------
    bool Update(void);
    //!-----------------------------------------------------
//! @brief : 描画
//! @param : [in](void) none
//! @return : 成功した場合true
//!-----------------------------------------------------
    bool Render(void);
    //!-----------------------------------------------------
    //! @brief : 解放処理、他シーンへ遷移する前に呼び出す
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Release(void);
};
}
#endif // !BR_SCENE_MANAGER_H