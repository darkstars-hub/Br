//!-----------------------------------------------------
//! @file : PathComponent.h
//! @brief : Unit�����ړ��@�\
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_PATH_COMPONENT_H
#define BR_PATH_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "PathRenderComponent.h"
#include "Range.h"


namespace br {
class PathComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! �o�H���͌��PathRenderComponent*�ɓn��
    std::vector<br::PathDataPointer> _path;
    //! �o�H���Q�Ƃ��Ă��炤
    br::PathRenderComponent* _path_render;
    
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    PathComponent(Actor* owner, int priority = 100);
    virtual ~PathComponent();

    //!-----------------------------------------------------
    //! @brief : �ړ��o�H��n��
    //! @param : [in](void) none
    //! @return : �ړ��o�H
    //!-----------------------------------------------------
    const std::vector<br::PathDataPointer>& GetPath(void) const;
    //!-----------------------------------------------------
    //! @brief : �ړ��o�H��n��
    //! @param : [in](void) none
    //! @return : �ړ��o�H
    //!-----------------------------------------------------
    br::PathDataPointer GetElement(std::size_t index);
    //!-----------------------------------------------------
    //! @brief : �ڕW�n�_�ɓ����������ǂ���
    //! @param : [in](void) none
    //! @return : �����Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsArrived(size_t index) const;
    //!-----------------------------------------------------
    //! @brief : �v�Z�����p�X�̃N���A
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Clear(void);
        //!-----------------------------------------------------
    //! @brief : �ړ��o�H�v�Z�@tile��destination������������Ă���Ə������ׂ��傫��
    //! @param : [in](br::Tile* target) ���ׂ�^�C��
    //! @return : �����true��Ԃ�
    //!-----------------------------------------------------
    void Conpute(br::Tile* tile, br::Tile* destination);

    //!-----------------------------------------------------
    //! @brief : ���ׂ�^�C�����ړ��\�͈͂ɂ��邩���ׂ�
    //! @param : [in](const std::vector<br::RangeDataPointer>&range) �ړ��\�͈�
    //! @param : [in](br::Tile* target) ���ׂ�^�C��
    //! @return : �����true��Ԃ�
    //!-----------------------------------------------------
    bool CheckTargetTile(const std::vector<br::RangeDataPointer>& range, br::Tile* target)const;

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
#endif // !BR_UNIT_MOVE_COMPONENT_H