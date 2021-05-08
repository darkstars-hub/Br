//!-----------------------------------------------------
//! @file : MotionComponent.h
//! @brief : Actor�����A�j���[�V�����@�\
//! @date : 2020/06/08
//!-----------------------------------------------------


#ifndef BR_MOTION_COMPONENT_H
#define BR_MOTION_COMPONENT_H


#include "UpdateComponent.h"


#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <Mof.h>
#include "Actor.h"
#include "Sprite.h"
#include "ResourceManager.h"

namespace br {
class MotionComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
protected:
    //! ���[�V�������X�V���邩�ǂ���
    //bool _is_update;
    //! ���[�V����
    Mof::CSpriteMotionController _motion;
    //! ���[�V�����̏��
    std::string _motion_state;
    //! ���[�V�����ԍ��ƃ��[�V�������̃e�[�u��
//    std::unordered_map<std::string, int>* _motion_map;
    std::unordered_map<int, std::string>* _motion_map;
    //! ���[�V�����f�[�^�̃p�X
    std::string _path;
    //! ���\�[�X�Ǘ���̃L���b�V��
    std::weak_ptr<br::ResourceManager> _resource_manager;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    MotionComponent(Actor* owner, int priority = 100);
    virtual ~MotionComponent();

        //!-----------------------------------------------------
    //! @brief : �Z�b�^�[   
    //! @param : [in](bool state) �X�V���邩�ǂ���
    //! @return : none
    //!-----------------------------------------------------
    //void SetUpdateFlag(bool state);
            //!-----------------------------------------------------
    //! @brief : �Q�b�^�[   
    //! @param : [in](void) none
    //! @return : �X�V����Ȃ�true��Ԃ�;
    //!-----------------------------------------------------
    //bool IsUpdate(void) const;
            //!-----------------------------------------------------
    //! @brief : �Z�b�^�[   
    //! @param : [in](const std::string& motion_name) ���[�V������
    //! @return : none
    //!-----------------------------------------------------
    void SetState(const std::string& state);
            //!-----------------------------------------------------
    //! @brief : �Q�b�^�[   
    //! @param : [in](void) none
    //! @return : ���[�V������
    //!-----------------------------------------------------
    const std::string& GetState(void) const;

    //!-----------------------------------------------------
    //! @brief : �A�j���[�V�����쐬
    //! @param : [in](std::weak_ptr<br::ResourceManager>r) ���\�[�X�ێ���
    //! @param : [in](const char* path) �p�X
    //! @return : none
    //!-----------------------------------------------------
    void MakeAnimation(std::weak_ptr<br::ResourceManager>r, const char* path);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ���݂̕`���`
    //!-----------------------------------------------------
    Mof::CRectangle GetRenderRectangle(void);


    //!-----------------------------------------------------
    //! @brief : Mof::CSpriteMotionController.IsEndMotion�̃��b�p�[
    //! @param : [in](void) none
    //! @return : �I����Ă���ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool IsEndMotion(void);
    //!-----------------------------------------------------
    //! @brief : Mof::CSpriteMotionController.ChangeMotionByName�̃��b�p�[
    //! @param : [in](const char* name) ���[�V������
    //! @return : ���������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool ChangeMotionByName(const char* name);
    //!-----------------------------------------------------
    //! @brief : Mof::CSpriteMotionController.GetMotionNo�̃��b�p�[
    //! @param : [in](void) none
    //! @return : ���݂̃��[�V�����ԍ�
    //!-----------------------------------------------------
    int GetMotionNo(void);
     //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ���[�V�����ԍ��ƃ��[�V�������̃e�[�u��
    //!-----------------------------------------------------
    //std::unordered_map<std::string, int>* GetMotionMap(void);
    std::unordered_map<int, std::string>* GetMotionMap(void);

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_MOTION_COMPONENT_H