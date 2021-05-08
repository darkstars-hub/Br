//!-----------------------------------------------------
//! @file : SelectIcon.h
//! @brief : StageSelectの選択項目
//! @date : 2020/08/22
//!-----------------------------------------------------


#ifndef BR_SELECT_ICON_H
#define BR_SELECT_ICON_H


#include <Mof.h>


namespace br {
class SelectIcon {
private:
    Mof::CRectangle _collision_rectangle;

    //! カーソルなどの選択するためのアイコンに重なっている
    bool _is_under;
    //! 重なった時の音を再生するフラグ
    bool _sound_play;
public:
    SelectIcon(Mof::CRectangle rect);
    ~SelectIcon();

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](bool) b
    //! @return : none
    //!-----------------------------------------------------
    void SetUnder(bool b);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](bool) b
    //! @return : none
    //!-----------------------------------------------------
    void SetSoundPlay(bool b);
    //!-----------------------------------------------------
    //! @brief : 重なっているフラグの判定
    //! @param : [in](void) none
    //! @return : 重なっているフラグ
    //!-----------------------------------------------------
    bool IsUnder(void);
    //!-----------------------------------------------------
    //! @brief : 音を再生するフラグの判定
    //! @param : [in](void) none
    //! @return : 音を再生するフラグ
    //!-----------------------------------------------------
    bool IsSoundPlay(void);
    //!-----------------------------------------------------
    //! @brief : メンバに持つ矩形との衝突判定
    //! @param : [in](Mof::CRectangle rect) rect
    //! @return : 衝突した場合trueを返す
    //!-----------------------------------------------------
    bool CollisionRectangle(Mof::CRectangle rect);
    //!-----------------------------------------------------
    //! @brief : 衝突判定用の矩形を描画
    //! @param : [in](int color) 色
    //! @return : none
    //!-----------------------------------------------------
    void RencerRect(int color);
};
}
#endif // !BR_SELECT_ICON_H