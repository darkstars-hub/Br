//!-----------------------------------------------------
//! @file : UIWindow.h
//! @brief : ゲーム中の情報を表示する枠 L字型
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
    // カーソルの下にあるタイルの情報
    br::Tile* _tile;
    // カーソルの下にあるユニットの情報
    br::Unit* _unit;

    Mof::CTexture _compatibility_texture;
    std::weak_ptr<br::ResourceManager> _resource_manager;

    // ターン情報の表示
    void RenderTurn(void);
    // タイン情報の表示
    void RenderTileInfomation(void);
    // ユニット情報の表示
    void RenderUnitInfomation(void);
    // ユニット相性情報の表示
    void RenderCompatibility(void);
public:
    UIWindow();
    ~UIWindow();



    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](br::Game* ptr) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetGame(br::Game* ptr);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](br::Cursor* cursor) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetCursor(br::Cursor* cursor);


    //!-----------------------------------------------------
    //! @brief : このUIはL字型
    //! @param : [in](void) none
    //! @return : UIウインドウがウインドウを占める値
    //!-----------------------------------------------------
    Mof::CVector2 GetOffset(void) const;
    //!-----------------------------------------------------
    //! @brief : このUIはL字型
    //! @param : [in](void) none
    //! @return : UIウインドウがウインドウを占める値(マス目の数)
    //!-----------------------------------------------------
    def::Vector2i GetOffsetCount(void) const;


    //!-----------------------------------------------------
    //! @brief : 更新
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Update(void);
    //!-----------------------------------------------------
    //! @brief : 取得している情報を表示する
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Render(void);
};
}
#endif // !BR_UI_WINDOW_H