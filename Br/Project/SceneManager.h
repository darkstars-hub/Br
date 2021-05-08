//!-----------------------------------------------------
//! @file : SceneManager.h
//! @brief : �e�V�[�����Ǘ�����
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
//! @brief : �R���X�g���N�^
//! @param : [in](void) none
//! @return : none
//!-----------------------------------------------------
    SceneManager();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
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
//! @brief : ���͏���
//! @param : [in](void) none
//! @return : ���������ꍇtrue
//!-----------------------------------------------------
    bool Input(void);

    //!-----------------------------------------------------
    //! @brief : ������
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Initialize(void);
    //!-----------------------------------------------------
//! @brief : �X�V
//! @param : [in](void) none
//! @return : ���������ꍇtrue
//!-----------------------------------------------------
    bool Update(void);
    //!-----------------------------------------------------
//! @brief : �`��
//! @param : [in](void) none
//! @return : ���������ꍇtrue
//!-----------------------------------------------------
    bool Render(void);
    //!-----------------------------------------------------
    //! @brief : ��������A���V�[���֑J�ڂ���O�ɌĂяo��
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Release(void);
};
}
#endif // !BR_SCENE_MANAGER_H