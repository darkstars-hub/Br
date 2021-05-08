//!-----------------------------------------------------
//! @file : Effect.h
//! @brief : ��ʌ���
//! @date : 2020/07/13
//!-----------------------------------------------------


#ifndef BR_EFFECT_H
#define BR_EFFECT_H


#include "Actor.h"

#include <Mof.h>

#include "MotionComponent.h"
#include "TextureComponent.h"


namespace br {
class Effect : public br::Actor {
    using super = br::Actor;
private:
    br::MotionComponent* _motion;
    br::TextureComponent* _texture;

    bool _is_show;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Scene* scene) ���݂̃V�[��
    //! @return : none
    //!-----------------------------------------------------
    Effect(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Effect();

    virtual br::ActorState GetState(void) const override;
    virtual Mof::CVector2 GetPosition(void) const override;
    
    //!-----------------------------------------------------
    //! @brief : ���[�V�������I���������ǂ���
    //! @param : [in](void) none
    //! @return : ���[�V�������I���������ǂ���
    //!-----------------------------------------------------
    bool IsEndMotion(void);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �ŗL�̖��O
    //!-----------------------------------------------------
    const char* GetName(void) const;

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
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    //!-----------------------------------------------------
    //! @brief : �G�t�F�N�g����
    //! @param : [in](Mof::CVector2 scroll) �X�v���C�g�̃p�X
    //! @param : [in](Mof::CVector2 position) �\���ʒu
    //! @param : [in](Mof::CVector2 scroll) ���O
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    void Start(const char* path, Mof::CVector2 position, const char* name = "");
};
}
#endif // !BR_EFFECT_H