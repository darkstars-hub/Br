//!-----------------------------------------------------
//! @file : SelectIcon.h
//! @brief : StageSelect�̑I������
//! @date : 2020/08/22
//!-----------------------------------------------------


#ifndef BR_SELECT_ICON_H
#define BR_SELECT_ICON_H


#include <Mof.h>


namespace br {
class SelectIcon {
private:
    Mof::CRectangle _collision_rectangle;

    //! �J�[�\���Ȃǂ̑I�����邽�߂̃A�C�R���ɏd�Ȃ��Ă���
    bool _is_under;
    //! �d�Ȃ������̉����Đ�����t���O
    bool _sound_play;
public:
    SelectIcon(Mof::CRectangle rect);
    ~SelectIcon();

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](bool) b
    //! @return : none
    //!-----------------------------------------------------
    void SetUnder(bool b);
    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](bool) b
    //! @return : none
    //!-----------------------------------------------------
    void SetSoundPlay(bool b);
    //!-----------------------------------------------------
    //! @brief : �d�Ȃ��Ă���t���O�̔���
    //! @param : [in](void) none
    //! @return : �d�Ȃ��Ă���t���O
    //!-----------------------------------------------------
    bool IsUnder(void);
    //!-----------------------------------------------------
    //! @brief : �����Đ�����t���O�̔���
    //! @param : [in](void) none
    //! @return : �����Đ�����t���O
    //!-----------------------------------------------------
    bool IsSoundPlay(void);
    //!-----------------------------------------------------
    //! @brief : �����o�Ɏ���`�Ƃ̏Փ˔���
    //! @param : [in](Mof::CRectangle rect) rect
    //! @return : �Փ˂����ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool CollisionRectangle(Mof::CRectangle rect);
    //!-----------------------------------------------------
    //! @brief : �Փ˔���p�̋�`��`��
    //! @param : [in](int color) �F
    //! @return : none
    //!-----------------------------------------------------
    void RencerRect(int color);
};
}
#endif // !BR_SELECT_ICON_H