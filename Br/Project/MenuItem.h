//!-----------------------------------------------------
//! @file : MenuItem.h
//! @brief : ���j���[�̍���
//!          ��̃��j���[�̍��ڂ̃T�C�Y�͓����ł�����̂Ƃ���
//! @date : 2020/06/25
//!-----------------------------------------------------


#ifndef BR_MENU_ITEM_H
#define BR_MENU_ITEM_H


#include <vector>
#include <memory>

#include <Mof.h>

namespace br {
constexpr int _text_size = 32;

class MenuItem {
private:
//    static 
        std::vector<Mof::CRectangle> _texts;

    Mof::CVector2 _position;
    std::vector<size_t> _text_indices;
    std::weak_ptr<Mof::CTexture> _texture;
    std::function<bool(void)>_action;
    bool _selected;
    class Menu* _owner;

    Mof::CRectangle GetBackRect(void);
    void BackRender(void);
public:
    ////! std::vector<Mof::CRectangle> _texts�@�̃C���f�b�N�X
    //static std::vector<size_t> wait;
    ////! std::vector<Mof::CRectangle> _texts�@�̃C���f�b�N�X
    //static std::vector<size_t> attack;
    ////! std::vector<Mof::CRectangle> _texts�@�̃C���f�b�N�X
    //static std::vector<size_t> fusion;
    ////! std::vector<Mof::CRectangle> _texts�@�̃C���f�b�N�X
    //static std::vector<size_t> back;
    ////! std::vector<Mof::CRectangle> _texts�@�̃C���f�b�N�X
    //static std::vector<size_t> turn_end;



    //!-----------------------------------------------------
    //! @brief : static�ϐ����`����
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    //static void Setup(void);

    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](std::vector<size_t> indices) �\�����镶���̃C���f�b�N�X
    //! @param : [in](class MenuTextures* textures) �\�����镶���摜��������̂̃|�C���^
    //! @param : [in](std::function<bool(void)>action) �I�������肳�ꂽ�Ƃ��Ɏ��s����֐�
    //! @param : [in](class Menu* owner) ��g
    //! @return : none
    //!-----------------------------------------------------
    MenuItem(std::vector<size_t> indices, class MenuTextures*textures,
             std::function<bool(void)>action, class Menu* owner);

    //!-----------------------------------------------------
    //! @brief : �o�^���ꂽ�֐������s����
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Excute(void);

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](Mof::CVector2 position) �\���ʒu
    //! @return : none
    //!-----------------------------------------------------
    void SetPosition(Mof::CVector2 position);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](bool b) �^�U�l
    //! @return : none
    //!-----------------------------------------------------
    void SetSelect(bool b);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �U���\�͈́@���݂̈ʒu����̕ψ�
    //!-----------------------------------------------------
    std::vector<size_t>& GetIndices(void);

    void Render(void);
};
}
#endif // !BR_MENU_ITEM_H