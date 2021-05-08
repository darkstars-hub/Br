//!-----------------------------------------------------
//! @file : HpComponent.h
//! @brief : ���@�����Ȃ�Ǝ��S
//! @date : 2020/06/22
//!-----------------------------------------------------


#ifndef BR_HP_COMPONENT_H
#define BR_HP_COMPONENT_H


#include "RenderComponent.h"

#include <memory>

#include <Mof.h>


namespace br {
class HpComponent : public RenderComponent {
    using super = br::RenderComponent;
private:
    //! HP�̍ő�l
    int _value_max;
    //! ���݂�HP�̒l
    int _value;
    //! �摜�\���t���O
    bool _is_show;
    //! ���݂�HP�̒l�̐������\��
    std::weak_ptr<Mof::CTexture> _textrue;
    //! �`���`
    const Mof::CRectangle _render_rect;
    //! �`���`�I�t�Z�b�g �`���`�̕��ƍ����Ɠ�����
    const float _render_offset;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    HpComponent(Actor* owner, int priority = 100);
    virtual ~HpComponent();
    
    void SetShow(bool show);
    void SetMaxHp(int value);
    void SetHp(int value);
    int GetValue(void) const;
    int GetMaxValue(void) const;

    void Damege(int value);
    void Heal(int value);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_HP_COMPONENT_H