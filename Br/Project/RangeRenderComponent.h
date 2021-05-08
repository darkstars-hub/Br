//!-----------------------------------------------------
//! @file : RangeRenderComponent.h
//! @brief : �󂯎�����͈͂�`�悷��@�\
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_RANGE_RENDER_COMPONENT_H
#define BR_RANGE_RENDER_COMPONENT_H


#include "RenderComponent.h"

#include <memory>
#include <Mof.h>
#include "Range.h"
#include "Tile.h"
#include "SelectableComponent.h"
namespace br {
class RangeRenderComponent : public br::RenderComponent {
    using super = br::RenderComponent;
private:
    //! �`��͈�
    std::vector<br::RangeDataPointer>* _range;
    //! �U���͈�
    std::vector<br::Tile*>* _attack_range;
    //! �Z���͈�
    std::vector<br::Tile*>* _fusion_range;
    //! ���͈́i��j
    std::vector<br::RangeDataPointer>* _sight_range;
    //! 
    br::SelectableComponent* _select;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    RangeRenderComponent(br::Actor* owner, int priority);
    virtual ~RangeRenderComponent();

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](std::vector<br::RangeDataPointer>* range) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetRange(std::vector<br::RangeDataPointer>* range);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](std::vector<br::Tile>* range) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetAttackRange(std::vector<br::Tile*>* range);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](std::vector<br::Tile>* range) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetFusionRange(std::vector<br::Tile*>* range);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](std::vector<br::RangeDataPointer>* range) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetSightRange(std::vector<br::RangeDataPointer>* range);


    bool Initialize(void) override;
    bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    bool Render(Mof::CVector2 scroll) override;
    bool Release(void) override;

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_RANGE_RENDER_COMPONENT_H