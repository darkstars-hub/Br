//!-----------------------------------------------------
//! @file : Actor.h
//! @brief : �Q�[���I�u�W�F�N�g
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
//! ��{�I�ȃp�����[�^
struct ActorBaseState {
    //! ���O
    //std::string name;
    const char* name;
    //! ���
    br::ActorType type = br::ActorType::None;
    //! Active�ŕ\�� Dead�ɂȂ�����delete����
    br::ActorState state = br::ActorState::Active;
    //! �ʒu �}�X�ڂ̍��W�ł͂Ȃ�
    Mof::CVector2 position;
};
class IActor {
public:
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ��ԕϐ�
    //!-----------------------------------------------------
    virtual br::ActorState GetState(void) const = 0;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ���݂̈ʒu
    //!-----------------------------------------------------
    virtual Mof::CVector2 GetPosition(void) const = 0;
};
class Actor : public IActor {
    friend class Component;
private:
protected:
    //! �S�R���|�[�l���g
    std::vector<class Component*> _components;
    //! �X�V�\�R���|�[�l���g
    std::vector<class Component*> _update_components;
    //! �`��\�R���|�[�l���g
    std::vector<class Component*> _render_components;
protected:
    //! �o�^�����V�[��
    br::Scene* _scene;
    //! ��{�I�Ȓl
    br::ActorBaseState _base;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Scene* scene) ���݂̃V�[��
    //! @return : none
    //!-----------------------------------------------------
    Actor(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Actor();

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](const Mof::CVector2 position) �ʒu
    //! @return : none
    //!-----------------------------------------------------
    void SetPosition(const Mof::CVector2 position);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �o�^����Ă���̃V�[��
    //!-----------------------------------------------------
    br::Scene* GetScene(void) const;


    //!-----------------------------------------------------
    //! @brief : �R���|�[�l���g�̃|�C���^���P�擾����
    //! @param : [in](ComponentType type) �R���|�[�l���g�̎��
    //! @return : ���������ꍇ�w�肵���^�̃|�C���^��Ԃ�
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
     //! @brief : �R���|�[�l���g�̒ǉ�
     //! @param : [in](Component* component) �ǉ�����R���|�[�l���g�̃|�C���^
     //! @return : none
     //!-----------------------------------------------------
    void AddComponent(Component* component);
    //!-----------------------------------------------------
    //! @brief : �X�V�R���|�[�l���g�̒ǉ�
    //! @param : [in](Component* component) �ǉ�����R���|�[�l���g�̃|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void AddUpdateComponent(Component* component);
    //!-----------------------------------------------------
    //! @brief : �`��R���|�[�l���g�̒ǉ�
    //! @param : [in](Component* component) �ǉ�����R���|�[�l���g�̃|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void AddRenderComponent(Component* component);
    //!-----------------------------------------------------
    //! @brief : �R���|�[�l���g�̍폜
    //! @param : [in](Component* component) �폜����R���|�[�l���g�̃|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void RemoveComponent(Component* component);
    //!-----------------------------------------------------
    //! @brief : �X�V�R���|�[�l���g�̍폜
    //! @param : [in](Component* component) �폜����R���|�[�l���g�̃|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void RemoveUpdateComponent(Component* component);
    //!-----------------------------------------------------
    //! @brief : �`��R���|�[�l���g�̍폜
    //! @param : [in](Component* component) �폜����R���|�[�l���g�̃|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void RemoveRenderComponent(Component* component);


    //!-----------------------------------------------------
    //! @brief : �ǂݍ���
    //! @param : [in](const char* path) �p�X
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Load(const char* path);
    //!-----------------------------------------------------
    //! @brief : ���͏���
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Input(void);
    //!-----------------------------------------------------
    //! @brief : ������
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Initialize(const br::ActorBaseState& base);
    //!-----------------------------------------------------
    //! @brief : �X�V
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Update(void);
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll);
    //!-----------------------------------------------------
    //! @brief : ���
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Release(void);

    //!-----------------------------------------------------
    //! @brief : �e�p�����[�^�Z�b�g
    //! @param : [in](std::shared_ptr<br::Builder> bl) ActorFactory�������Ă�
    //! @return : none
    //!-----------------------------------------------------
    virtual void Construct(std::shared_ptr<br::Builder> bl);
};
}
#endif // !BR_ACTOR_H