//!-----------------------------------------------------
//! @file : MenuItem.h
//! @brief : メニューの項目
//!          一つのメニューの項目のサイズは同じであるものとする
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
    ////! std::vector<Mof::CRectangle> _texts　のインデックス
    //static std::vector<size_t> wait;
    ////! std::vector<Mof::CRectangle> _texts　のインデックス
    //static std::vector<size_t> attack;
    ////! std::vector<Mof::CRectangle> _texts　のインデックス
    //static std::vector<size_t> fusion;
    ////! std::vector<Mof::CRectangle> _texts　のインデックス
    //static std::vector<size_t> back;
    ////! std::vector<Mof::CRectangle> _texts　のインデックス
    //static std::vector<size_t> turn_end;



    //!-----------------------------------------------------
    //! @brief : static変数を定義する
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    //static void Setup(void);

    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](std::vector<size_t> indices) 表示する文字のインデックス
    //! @param : [in](class MenuTextures* textures) 表示する文字画像を内包するもののポインタ
    //! @param : [in](std::function<bool(void)>action) 選択→決定されたときに実行する関数
    //! @param : [in](class Menu* owner) 大枠
    //! @return : none
    //!-----------------------------------------------------
    MenuItem(std::vector<size_t> indices, class MenuTextures*textures,
             std::function<bool(void)>action, class Menu* owner);

    //!-----------------------------------------------------
    //! @brief : 登録された関数を実行する
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Excute(void);

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](Mof::CVector2 position) 表示位置
    //! @return : none
    //!-----------------------------------------------------
    void SetPosition(Mof::CVector2 position);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](bool b) 真偽値
    //! @return : none
    //!-----------------------------------------------------
    void SetSelect(bool b);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 攻撃可能範囲　現在の位置からの変位
    //!-----------------------------------------------------
    std::vector<size_t>& GetIndices(void);

    void Render(void);
};
}
#endif // !BR_MENU_ITEM_H