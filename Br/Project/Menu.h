//!-----------------------------------------------------
//! @file : Menu.h
//! @brief : メニュー基底クラス
//! @date : 2020/06/15
//!-----------------------------------------------------


#ifndef BR_MENU_H
#define BR_MENU_H


#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "Scene.h"
#include "Unit.h"
#include "MenuItem.h"
#include "ResourceManager.h"
#include "MenuMessage.h"


namespace br {
class MenuTextures {
    friend class Menu;
    friend class MenuItem;
    std::shared_ptr<Mof::CTexture> _text;
public:
    bool Load(std::shared_ptr<br::ResourceManager> ptr) {
        _text = ptr->GetTexture("Resource/textures/text.png");
        return true;
    }
    void Release(void) {
        _text.reset();
    }
};
class Menu {
private:
protected:
    br::Scene* _scene;
    bool _is_show;
    Mof::CVector2 _position;
    int _index;
    //class Unit* _target;

    br::MenuTextures _textures;
    std::vector<br::MenuItem> _items;

//    std::vector<br::MenuListenerComponent*> _listeners;
//    br::Menu* _child;


    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 表示する文字の大きさ
    //!-----------------------------------------------------
    size_t GetTextSize(void)const;

    //!-----------------------------------------------------
    //! @brief : 現在選択中の項目を実行する
    //! @param : [in](void) none 
    //! @return : none
    //!-----------------------------------------------------
    virtual void Decide(void) = 0;
    //!-----------------------------------------------------
    //! @brief : もと゛るを押したときに同じ
    //! @param : [in](void) none 
    //! @return : none
    //!-----------------------------------------------------
    virtual void Cancel(void) = 0;
public:
    Menu(br::Scene* scene);
    virtual ~Menu();

    //!-----------------------------------------------------
    //! @brief : 表示状態取得
    //! @param : [in](void) none
    //! @return : 表示中ならtrueを返す
    //!-----------------------------------------------------
    bool IsShow(void);
    //!-----------------------------------------------------
    //! @brief : 表示状態する
    //! @param : [in](class Unit* ptr) メニューを表示した人
    //! @return : none
    //!-----------------------------------------------------
  //  virtual void Show(class Unit* ptr);
    virtual void Show(br::MenuMessage* event) = 0;
    //!-----------------------------------------------------
    //! @brief : 非表示状態する
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual   void Hide(void) = 0;

    Mof::CVector2 GetPosition(void);
    int GetIndex(void);
    //!-----------------------------------------------------
    //! @brief : 背景の矩形取得
    //! @param : [in](void) none
    //! @return : 背景の矩形
    //!-----------------------------------------------------
    Mof::CRectangle GetBackRect(void);



    bool Load(void);
    bool Input(void);
    //!-----------------------------------------------------
    //! @brief : 更新
    //! @param : [in](void) none
    //! @return : 表示されていないときはfalseを返す
    //!-----------------------------------------------------
    bool Update(void);
    bool Render(void);

    //!-----------------------------------------------------
    //! @brief : 項目を参照するときのインデックスをずらす
    //! @param : [in](const int count) ずらす値
    //! @return : none
    //!-----------------------------------------------------
    virtual void ShiftIndex(const int count);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    void Release(void);
};
}
#endif // !BR_MENU_H