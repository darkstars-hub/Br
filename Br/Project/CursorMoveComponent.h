//!-----------------------------------------------------
//! @file : CursorMoveComponent.h
//! @brief : カーソルが持つ移動機能
//! @date : 2020/05/30
//!-----------------------------------------------------


#ifndef BR_CURSOR_MOVE_COMPONENT_H
#define BR_CURSOR_MOVE_COMPONENT_H


#include "UpdateComponent.h"

#include <Mof.h>

#include "Helper.h"
#include "Cursor.h"
#include "Tile.h"


namespace br {
class CursorMoveComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    Cursor* _cursor;
    DirectionWait* _wait;
    //! 選択ユニットの移動可能範囲の外へ移動しようとすると引っかかる
    bool _stop;
    //int _inner_range_count;
    //const int _inner_range_count_max;

    //!-----------------------------------------------------
    //! @brief : 方向別移動処理
    //! @param : [in](br::Scene* scene) 現在のシーン
    //! @param : [in](Mof::CVector2& pos) この値は変更される
    //! @return : none
    //!-----------------------------------------------------
    void Move(const def::Vector2i m, Mof::CVector2& pos);
	void Move(br::Direction dir, Mof::CVector2& pos);
    void MoveOnAttackMode(Mof::CVector2& pos);

    //!-----------------------------------------------------
    //! @brief : 現在指し示しているTile
    //! @param : [in](br::Actor* actor) 処理するActor
    //! @param : [in](br::Scene* scene) 現在のシーン
    //! @return : 今、示しているTile
    //!-----------------------------------------------------
    br::Tile* GetSelectedTile(br::Actor* actor, br::Scene* scene);
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    CursorMoveComponent(Actor* owner, int priority = 100);
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](none)
    //! @return : none
    //!-----------------------------------------------------
    virtual ~CursorMoveComponent();

    //!-----------------------------------------------------
    //! @brief : ポインタの設定
    //! @param : [in](class Cursor* ptr) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetCursor(br::Cursor* ptr);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](bool b) 止まる
    //! @return : none
    //!-----------------------------------------------------
    void SetStop(bool b);
    //!-----------------------------------------------------
    //! @brief : ポインタの設定
    //! @param : [in](DirectionWait _wait) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void RegisterWait(DirectionWait* wait);
     //!-----------------------------------------------------
    //! @brief : ポインタの設定
    //! @param : [in](Mof::CVector2* scroll) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    //void RegisterScroll(Mof::CVector2* scroll);

    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll);

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_CURSOR_MOVE_COMPONENT_H