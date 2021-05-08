//!-----------------------------------------------------
//! @file : PathRenderComponent.h
//! @brief : �󂯎�����o�H��`�悷��@�\
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_PATH_RENDER_COMPONENT_H
#define BR_PATH_RENDER_COMPONENT_H


#include "RenderComponent.h"

#include <memory>
#include <Mof.h>
#include "AStar.h"

namespace br {
class PathRenderComponent : public br::RenderComponent {
    using super = br::RenderComponent;
private:
    std::vector<br::PathDataPointer>* _path;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    PathRenderComponent(br::Actor* owner, int priority);
    virtual ~PathRenderComponent();

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](std::vector<br::AStarDataPointer>* range) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetPath(std::vector<br::PathDataPointer>* range);


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
#endif // !BR_PATH_RENDER_COMPONENT_H