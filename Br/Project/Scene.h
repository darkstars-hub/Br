//!-----------------------------------------------------
//! @file : Scene.h
//! @brief : �e�V�[���̊��N���X
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
    //! �V�[���̏I���t���O ���ꂪtrue�őJ�ڂ���
    bool _is_end;
    //! ���̃V�[���Ŏg�����\�[�X��ێ�����
    std::shared_ptr<class ResourceManager> _resource_manager;
    //! ���̃V�[���Ŏg�����\�[�X��ێ�����
    std::shared_ptr<class ResourceManager> _next_resource;
    //! ���̃V�[���ōĐ������鉹�����o�͂���
    std::shared_ptr<class AudioSystem> _audio_system;
    //! ���̃V�[���ōĐ������鉹�����o�͂���
    std::shared_ptr<class AudioSystem> _next_audio;
    //! �Q�[�����
    class Stage* _world;
    //! �J�[�\��
    class Cursor* _cursor;
    //! ���j���[
    //class Menu* _menu;
    class MenuMessenger* _menu_messenger;
    //! �Q�[���I�u�W�F�N�g�Ǘ���(����Unit���Ǘ�)
    class ActorManager* _actor_manager;
    //! �G�t�F�N�g�����p
    class EffectManager* _effect_manager;

    //! �V�[������V�[���̑J�ڂ̂Ƃ��t�F�[�h�C���E�t�F�[�h�A�E�g����
    int _alpha;
    //! �V�[����J�ڂ��� ���ꂪtrue�őJ�ڃA�j���[�V�������J�n����
    bool _is_change;
    //! �����n���p
    std::mutex _mutex;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Scene();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Scene();

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](const std::shared_ptr<class ResourceManager> r) �󂯎��l
    //! @param : [in](const std::shared_ptr<class AudioSystem> r) �󂯎��l
    //! @return : none
    //!-----------------------------------------------------
    void AcquireResource(const std::shared_ptr<class ResourceManager> r,
                         const std::shared_ptr<class AudioSystem> a);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �ێ����Ă���ResourceManager
    //!-----------------------------------------------------
    std::shared_ptr<class ResourceManager> GetResourceManager(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ���̃V�[���ɓn������ResourceManager
    //!-----------------------------------------------------
    std::shared_ptr<class ResourceManager> GetNextResourceManager(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �ێ����Ă���AudioSystem
    //!-----------------------------------------------------
    std::shared_ptr<class AudioSystem> GetAudioSystem(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ���̃V�[���ɓn������AudioSystem
    //!-----------------------------------------------------
    std::shared_ptr<class AudioSystem> GetNextAudioSystem(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �ێ����Ă���Stage�|�C���^
    //!-----------------------------------------------------
    class Stage* GetStage(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �ێ����Ă���Cursor�|�C���^
    //!-----------------------------------------------------
    class Cursor* GetCursor(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �ێ����Ă���Menu�|�C���^
    //!-----------------------------------------------------
    //class Menu* GetMenu(void) const;
    class MenuMessenger* GetMenu(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �ێ����Ă���ActorManager�|�C���^
    //!-----------------------------------------------------
    class ActorManager* GetActorManager(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �ێ����Ă���ActorManager�|�C���^
    //!-----------------------------------------------------
    class EffectManager* GetEffectManager(void) const;


    //!-----------------------------------------------------
    //! @brief : ���̃V�[�����I�������邩�ǂ���
    //! @param : [in](void) none
    //! @return : �I��������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool IsEnd(void) const;
    //!-----------------------------------------------------
    //! @brief : ���̃V�[����Id���擾����
    //! @param : [in](void) none
    //! @return : ���̃V�[����Id
    //!-----------------------------------------------------
    virtual br::SceneId GetSceneId(void) const = 0;
    //!-----------------------------------------------------
    //! @brief : �J�ڂ�����Id���擾����
    //! @param : [in](void) none
    //! @return : �J�ڂ�����Id
    //!-----------------------------------------------------
    virtual br::SceneId GetNextScene(void) const = 0;
    //!-----------------------------------------------------
    //! @brief : ���̃V�[�����K�v�ȏ���Ԃ�
    //! @param : [in](void) none
    //! @return : ���[�h�V�[���̏��
    //!-----------------------------------------------------
    virtual std::shared_ptr<br::SceneInfomation> GetNextSceneInfomation(void);
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
    virtual bool Initialize(std::shared_ptr<br::SceneInfomation> info) = 0;
    //!-----------------------------------------------------
    //! @brief : �X�V
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Update(void) = 0;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(void) = 0;
    //!-----------------------------------------------------
    //! @brief : ��������A���V�[���֑J�ڂ���O�ɌĂяo��
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Release(void) = 0;
    //!-----------------------------------------------------
    //! @brief : ��ʑJ�ڌ��ʂ̕`��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual void RenderFade(void);
        //!-----------------------------------------------------
    //! @brief : ��ʑJ�ڌ��ʂ̃A���t�@�l����
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual void Fade(void);
        //!-----------------------------------------------------
    //! @brief : ��ʂ̑J��
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual void ChangeScene(void);
        //!-----------------------------------------------------
    //! @brief : ��ʂ̑J�ڂ����Ă��邩�ǂ���
    //! @param : [in](void) bool
    //! @return : ���Ă���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsChange(void);
};
}
#endif // !BR_SCENE_H