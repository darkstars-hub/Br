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
    //! ���݂̃V�[��
    br::Scene* _scene;
    //! �ێ����Ă���Bulder
    std::map<std::string, std::shared_ptr<br::Builder>> _type;

    br::Component* CreateComponent(br::ComponentType type, int priority);
    br::Component* CreateLordComponent(void);

    std::shared_ptr<br::Builder> CreateBuilder(const char* path);
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Scene* scene) ���݂̃V�[��
    //! @return : none
    //!-----------------------------------------------------
    ActorFactory(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~ActorFactory();

    void AddBuilder(const std::string& type, std::shared_ptr<br::Builder> bl) {
        _type[type] = bl;
    }
    
    //!-----------------------------------------------------
    //! @brief : �A�N�^�[����
    //! @param : [in](std;;string key) �}�b�v��key
    //! @param : [in](br::ActorBaseState& st) ��{�I�ȃp�����[�^
    //! @param : [in](int type) ��ނ̔ԍ�
    //! @return : �w�肵���^�̃|�C���^
    //!-----------------------------------------------------
    template<typename T>
    T* Create(const std::string& key, br::ActorBaseState& st) {
        T* ptr = new T(_scene);
        ptr->Construct(_type[key]);
        ptr->Initialize(st);
        return ptr;
    }
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !BR_ACTOR_FACTORY_H