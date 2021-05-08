#ifndef BR_ACTOR_FACTORY_H
#define BR_ACTOR_FACTORY_H


#include <string>
#include <memory>
#include <map>

#include "Scene.h"
#include "Actor.h"
#include "Builder.h"


namespace br {
class ActorFactory {
private:
    //! 現在のシーン
    br::Scene* _scene;
    //! 保持しているBulder
    std::map<std::string, std::shared_ptr<br::Builder>> _type;

    br::Component* CreateComponent(br::ComponentType type, int priority);
    br::Component* CreateLordComponent(void);

    std::shared_ptr<br::Builder> CreateBuilder(const char* path);
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Scene* scene) 現在のシーン
    //! @return : none
    //!-----------------------------------------------------
    ActorFactory(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~ActorFactory();

    void AddBuilder(const std::string& type, std::shared_ptr<br::Builder> bl) {
        _type[type] = bl;
    }
    
    //!-----------------------------------------------------
    //! @brief : アクター生成
    //! @param : [in](std;;string key) マップのkey
    //! @param : [in](br::ActorBaseState& st) 基本的なパラメータ
    //! @param : [in](int type) 種類の番号
    //! @return : 指定した型のポインタ
    //!-----------------------------------------------------
    template<typename T>
    T* Create(const std::string& key, br::ActorBaseState& st) {
        T* ptr = new T(_scene);
        ptr->Construct(_type[key]);
        ptr->Initialize(st);
        return ptr;
    }
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !BR_ACTOR_FACTORY_H