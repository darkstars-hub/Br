//!-----------------------------------------------------
//! @file : Actor.h
//! @brief : ゲームオブジェクト
//! @date : 2020/05/28
//!-----------------------------------------------------


#ifndef BR_ACTOR_H
#define BR_ACTOR_H


#include <memory>

#include <Mof.h>

#include "Common.h"
#include "Scene.h"
#include "Builder.h"


namespace br {
enum class ActorState {
    Active,
    Dead
};
enum class ActorType {
    None,
    Unit,
    Tile,
    Effect,
    CountMax
};
//! 基本的なパラメータ
struct ActorBaseState {
    //! 名前
    //std::string name;
    const char* name;
    //! 種類
    br::ActorType type = br::ActorType::None;
    //! Activeで表示 Deadになったらdeleteする
    br::ActorState state = br::ActorState::Active;
    //! 位置 マス目の座標ではない
    Mof::CVector2 position;
};
class IActor {
public:
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 状態変数
    //!-----------------------------------------------------
    virtual br::ActorState GetState(void) const = 0;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 現在の位置
    //!-----------------------------------------------------
    virtual Mof::CVector2 GetPosition(void) const = 0;
};
class Actor : public IActor {
    friend class Component;
private:
protected:
    //! 全コンポーネント
    std::vector<class Component*> _components;
    //! 更新可能コンポーネント
    std::vector<class Component*> _update_components;
    //! 描画可能コンポーネント
    std::vector<class Component*> _render_components;
protected:
    //! 登録されるシーン
    br::Scene* _scene;
    //! 基本的な値
    br::ActorBaseState _base;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Scene* scene) 現在のシーン
    //! @return : none
    //!-----------------------------------------------------
    Actor(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Actor();

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](const Mof::CVector2 position) 位置
    //! @return : none
    //!-----------------------------------------------------
    void SetPosition(const Mof::CVector2 position);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 登録されているのシーン
    //!-----------------------------------------------------
    br::Scene* GetScene(void) const;


    //!-----------------------------------------------------
    //! @brief : コンポーネントのポインタを１つ取得する
    //! @param : [in](ComponentType type) コンポーネントの種類
    //! @return : 見つかった場合指定した型のポインタを返す
    //!-----------------------------------------------------
    template<typename T>
    T* GetComponent(ComponentType type) {
        auto it = std::find_if(_components.begin(), _components.end(), [type](br::Component* c) {
            return c->GetType() == type;
        });
        if (it == _components.end()) {
            return nullptr;
        } // if
        return dynamic_cast<T*>(*it);
    }

     template<typename T>
     T* GetComponent(void) {
         for (auto com : _components) {
             T* ret = dynamic_cast<T*>(com);
             if (ret != nullptr) {
                 return ret;
             } // if
         } // for
         return nullptr;
     }



     //!-----------------------------------------------------
     //! @brief : コンポーネントの追加
     //! @param : [in](Component* component) 追加するコンポーネントのポインタ
     //! @return : none
     //!-----------------------------------------------------
    void AddComponent(Component* component);
    //!-----------------------------------------------------
    //! @brief : 更新コンポーネントの追加
    //! @param : [in](Component* component) 追加するコンポーネントのポインタ
    //! @return : none
    //!-----------------------------------------------------
    void AddUpdateComponent(Component* component);
    //!-----------------------------------------------------
    //! @brief : 描画コンポーネントの追加
    //! @param : [in](Component* component) 追加するコンポーネントのポインタ
    //! @return : none
    //!-----------------------------------------------------
    void AddRenderComponent(Component* component);
    //!-----------------------------------------------------
    //! @brief : コンポーネントの削除
    //! @param : [in](Component* component) 削除するコンポーネントのポインタ
    //! @return : none
    //!-----------------------------------------------------
    void RemoveComponent(Component* component);
    //!-----------------------------------------------------
    //! @brief : 更新コンポーネントの削除
    //! @param : [in](Component* component) 削除するコンポーネントのポインタ
    //! @return : none
    //!-----------------------------------------------------
    void RemoveUpdateComponent(Component* component);
    //!-----------------------------------------------------
    //! @brief : 描画コンポーネントの削除
    //! @param : [in](Component* component) 削除するコンポーネントのポインタ
    //! @return : none
    //!-----------------------------------------------------
    void RemoveRenderComponent(Component* component);


    //!-----------------------------------------------------
    //! @brief : 読み込み
    //! @param : [in](const char* path) パス
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Load(const char* path);
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
    virtual bool Initialize(const br::ActorBaseState& base);
    //!-----------------------------------------------------
    //! @brief : 更新
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Update(void);
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll);
    //!-----------------------------------------------------
    //! @brief : 解放
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Release(void);

    //!-----------------------------------------------------
    //! @brief : 各パラメータセット
    //! @param : [in](std::shared_ptr<br::Builder> bl) ActorFactoryが持ってる
    //! @return : none
    //!-----------------------------------------------------
    virtual void Construct(std::shared_ptr<br::Builder> bl);
};
}
#endif // !BR_ACTOR_H