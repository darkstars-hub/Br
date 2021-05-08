//!-----------------------------------------------------
//! @file : Scene.h
//! @brief : 各シーンの基底クラス
//! @date : 2020/05/28
//!-----------------------------------------------------


#ifndef BR_SCENE_H
#define BR_SCENE_H


#include <memory>
#include <mutex>

#include "SceneInfomation.h"


namespace br {
class Scene : public std::enable_shared_from_this<br::Scene> {
    friend class Actor;
private:
protected:
    //! シーンの終了フラグ これがtrueで遷移する
    bool _is_end;
    //! このシーンで使うリソースを保持する
    std::shared_ptr<class ResourceManager> _resource_manager;
    //! 次のシーンで使うリソースを保持する
    std::shared_ptr<class ResourceManager> _next_resource;
    //! このシーンで再生させる音声を出力する
    std::shared_ptr<class AudioSystem> _audio_system;
    //! このシーンで再生させる音声を出力する
    std::shared_ptr<class AudioSystem> _next_audio;
    //! ゲーム空間
    class Stage* _world;
    //! カーソル
    class Cursor* _cursor;
    //! メニュー
    //class Menu* _menu;
    class MenuMessenger* _menu_messenger;
    //! ゲームオブジェクト管理者(今はUnitを管理)
    class ActorManager* _actor_manager;
    //! エフェクト発生用
    class EffectManager* _effect_manager;

    //! シーンからシーンの遷移のときフェードイン・フェードアウトする
    int _alpha;
    //! シーンを遷移する これがtrueで遷移アニメーションが開始する
    bool _is_change;
    //! 同期地蔵用
    std::mutex _mutex;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Scene();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Scene();

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](const std::shared_ptr<class ResourceManager> r) 受け取る値
    //! @param : [in](const std::shared_ptr<class AudioSystem> r) 受け取る値
    //! @return : none
    //!-----------------------------------------------------
    void AcquireResource(const std::shared_ptr<class ResourceManager> r,
                         const std::shared_ptr<class AudioSystem> a);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 保持しているResourceManager
    //!-----------------------------------------------------
    std::shared_ptr<class ResourceManager> GetResourceManager(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 次のシーンに渡したいResourceManager
    //!-----------------------------------------------------
    std::shared_ptr<class ResourceManager> GetNextResourceManager(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 保持しているAudioSystem
    //!-----------------------------------------------------
    std::shared_ptr<class AudioSystem> GetAudioSystem(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 次のシーンに渡したいAudioSystem
    //!-----------------------------------------------------
    std::shared_ptr<class AudioSystem> GetNextAudioSystem(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 保持しているStageポインタ
    //!-----------------------------------------------------
    class Stage* GetStage(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 保持しているCursorポインタ
    //!-----------------------------------------------------
    class Cursor* GetCursor(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 保持しているMenuポインタ
    //!-----------------------------------------------------
    //class Menu* GetMenu(void) const;
    class MenuMessenger* GetMenu(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 保持しているActorManagerポインタ
    //!-----------------------------------------------------
    class ActorManager* GetActorManager(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 保持しているActorManagerポインタ
    //!-----------------------------------------------------
    class EffectManager* GetEffectManager(void) const;


    //!-----------------------------------------------------
    //! @brief : このシーンを終了させるかどうか
    //! @param : [in](void) none
    //! @return : 終了させる場合trueを返す
    //!-----------------------------------------------------
    bool IsEnd(void) const;
    //!-----------------------------------------------------
    //! @brief : このシーンのIdを取得する
    //! @param : [in](void) none
    //! @return : このシーンのId
    //!-----------------------------------------------------
    virtual br::SceneId GetSceneId(void) const = 0;
    //!-----------------------------------------------------
    //! @brief : 遷移する先のIdを取得する
    //! @param : [in](void) none
    //! @return : 遷移する先のId
    //!-----------------------------------------------------
    virtual br::SceneId GetNextScene(void) const = 0;
    //!-----------------------------------------------------
    //! @brief : 次のシーンが必要な情報を返す
    //! @param : [in](void) none
    //! @return : ロードシーンの情報
    //!-----------------------------------------------------
    virtual std::shared_ptr<br::SceneInfomation> GetNextSceneInfomation(void);
    //!-----------------------------------------------------
    //! @brief : 入力処理
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Input(void);
    //!-----------------------------------------------------
    //! @brief : 初期化
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Initialize(std::shared_ptr<br::SceneInfomation> info) = 0;
    //!-----------------------------------------------------
    //! @brief : 更新
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Update(void) = 0;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(void) = 0;
    //!-----------------------------------------------------
    //! @brief : 解放処理、他シーンへ遷移する前に呼び出す
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Release(void) = 0;
    //!-----------------------------------------------------
    //! @brief : 画面遷移効果の描画
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual void RenderFade(void);
        //!-----------------------------------------------------
    //! @brief : 画面遷移効果のアルファ値増減
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual void Fade(void);
        //!-----------------------------------------------------
    //! @brief : 画面の遷移
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual void ChangeScene(void);
        //!-----------------------------------------------------
    //! @brief : 画面の遷移をしているかどうか
    //! @param : [in](void) bool
    //! @return : しているならtrueを返す
    //!-----------------------------------------------------
    bool IsChange(void);
};
}
#endif // !BR_SCENE_H