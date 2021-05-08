//!-----------------------------------------------------
//! @file : UIWindow.h
//! @brief : �Q�[�����̏���\������g L���^
//! @date : 2020/07/09
//!-----------------------------------------------------


#ifndef BR_UI_WINDOW_H
#define BR_UI_WINDOW_H


#include <memory>

#include <Mof.h>

#include "Helper.h"
#include "Cursor.h"
#include "Tile.h"
#include "Unit.h"
#include "ResourceManager.h"


namespace br {
class UIWindow {
private:
    class Game* _game;
    br::Cursor* _cursor;
    // �J�[�\���̉��ɂ���^�C���̏��
    br::Tile* _tile;
    // �J�[�\���̉��ɂ��郆�j�b�g�̏��
    br::Unit* _unit;

    Mof::CTexture _compatibility_texture;
    std::weak_ptr<br::ResourceManager> _resource_manager;

    // �^�[�����̕\��
    void RenderTurn(void);
    // �^�C�����̕\��
    void RenderTileInfomation(void);
    // ���j�b�g���̕\��
    void RenderUnitInfomation(void);
    // ���j�b�g�������̕\��
    void RenderCompatibility(void);
public:
    UIWindow();
    ~UIWindow();



    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](br::Game* ptr) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetGame(br::Game* ptr);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](br::Cursor* cursor) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void SetCursor(br::Cursor* cursor);


    //!-----------------------------------------------------
    //! @brief : ����UI��L���^
    //! @param : [in](void) none
    //! @return : UI�E�C���h�E���E�C���h�E���߂�l
    //!-----------------------------------------------------
    Mof::CVector2 GetOffset(void) const;
    //!-----------------------------------------------------
    //! @brief : ����UI��L���^
    //! @param : [in](void) none
    //! @return : UI�E�C���h�E���E�C���h�E���߂�l(�}�X�ڂ̐�)
    //!-----------------------------------------------------
    def::Vector2i GetOffsetCount(void) const;


    //!-----------------------------------------------------
    //! @brief : �X�V
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Update(void);
    //!-----------------------------------------------------
    //! @brief : �擾���Ă������\������
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Render(void);
};
}
#endif // !BR_UI_WINDOW_H