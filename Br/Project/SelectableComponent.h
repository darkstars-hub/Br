//!-----------------------------------------------------
//! @file : SelectableComponent.h
//! @brief : Actorが持つカーソルに選ばれる機能
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_SELECTABLE_COMPONENT_H
#define BR_SELECTABLE_COMPONENT_H


#include "UpdateComponent.h"

#include "Actor.h"
#include "Cursor.h"


namespace br {

    //! 選択用イベント登録
using OnEventFunc = std::function<bool(void)>;
using OnEventPair = std::pair<std::string, OnEventFunc>;
class OnEvent : public std::vector<std::pair<std::string, OnEventFunc>> {
public:
    //!-----------------------------------------------------
    //! @brief : イベントの登録
    //! @param : [in](std::pair<std::string, OnEventFunc> val) イベントの登録
    //!-----------------------------------------------------
    void Register(const char* key, OnEventFunc fn) {
        //同名キーでの重複登録会費
        if (std::find_if(this->begin(), this->end(), [&](auto& t) {return key == t.first; }) != this->end()) { return; }
        this->push_back(std::make_pair(key, fn));
    }
    void operator += (OnEventPair val) {
        //同名キーでの重複登録会費
        if (std::find_if(this->begin(), this->end(), [&](auto& t) {return val.first == t.first; }) != this->end()) { return; }
        this->push_back(val);
    }

    //!-----------------------------------------------------
    //! @brief : イベントの削除
    //! @param : [in](const char* key) 削除するイベントのキー
    //!-----------------------------------------------------
    void operator -= (const char* key) {
        this->erase(std::remove_if(this->begin(), this->end(), [&](auto& v) {return v.first == key; }), this->end());
    }
    void operator -= (std::string& key) {
        this->erase(std::remove_if(this->begin(), this->end(), [&](auto& v) {return v.first == key; }), this->end());
    }
    void MatchRemove(const char* key) {
        // パターンマッチを全削除
        this->erase(std::remove_if(this->begin(), this->end(), [&](auto& v) {return v.first.find(key) != std::string::npos; }), this->end());
    }
    //!-----------------------------------------------------
    //! @brief : 登録イベントの実行
    //! @param : [in](void) none
    //! @return : イベント内で処理終了ならtrueを返す
    //!-----------------------------------------------------
    bool operator ()(void) {
        for (auto& fn : *this) {
            if (fn.second()) {
                return true;
            } // if
        } // for
        return false;
    }
};
//! カーソル下時イベント登録
class ICursor {
public:
    OnEvent		onCursor;
};
//! 選択時イベント登録
class ISelect {
public:
    OnEvent		onSelect;
};
//! 決定時イベント登録
class IDecide {
public:
    OnEvent		onDecide;
};
//! 攻撃時イベント登録
//class IAttackCancel {
//class IAttack {
//public:
//    OnEvent		onAttack;
//};
//! キャンセル時イベント登録
class ICancel {
public:
    OnEvent		onCancel;
};
//! 終了時イベント登録
class IEnd {
public:
    OnEvent		onEnd;
};
//! イベント一括継承
class IUnitEvent : public ICursor, public ISelect, public IDecide, public ICancel, public IEnd {
private:
    std::vector<std::string> delkey;
public:
    //!-----------------------------------------------------
    //! @brief : イベントの削除
    //! @param : [in](const char* key) 削除するイベントのキー
    //!-----------------------------------------------------
    void MatchRemove(const char* key) {
        //onDefault.MatchRemove(key);
        onCursor.MatchRemove(key);
        onSelect.MatchRemove(key);
        onDecide.MatchRemove(key);
        onCancel.MatchRemove(key);
        onEnd.MatchRemove(key);
    }

    void MatchRemoveDelay(const char* key) {
        delkey.push_back(key);
    }

    void doRemove() {
        if (delkey.empty()) {
            return;
        } //if
        for (auto& str : delkey) {
            MatchRemove(str.c_str());
        } //for
        delkey.clear();
    }
};

class SelectableComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! カーソルのポインタ
    br::Cursor* _cursor;
    //! 選択されている状態
    bool _is_select;
    //! カーソルの下にある状態
    bool _under_cursor;
    //! 選択された状態で決定ボタンが押された
    bool _is_decide;

public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    SelectableComponent(Actor* owner, int priority = 100);
    virtual ~SelectableComponent();


        //!-----------------------------------------------------
    //! @brief : 選択されている状態を返す
    //! @param : [in](void) none
    //! @return : 選ばれているならtrueを返す
    //!-----------------------------------------------------
    //bool SetSelected(void);
    //!-----------------------------------------------------
    //! @brief : カーソルの下にある状態を返す
    //! @param : [in](void) none
    //! @return : 下にあるならtrueを返す
    //!-----------------------------------------------------
    //bool SetUnderCursor(void);
    //!-----------------------------------------------------
    //! @brief : 選択された状態で決定ボタンが押されたかどうかを返す
    //! @param : [in](void) none
    //! @return : 確定されているならtrueを返す
    //!-----------------------------------------------------
    //bool SetDecide(void);
    //!-----------------------------------------------------
    //! @brief : 選択されている状態を返す
    //! @param : [in](void) none
    //! @return : 選ばれているならtrueを返す
    //!-----------------------------------------------------
    bool IsSelected(void);
    //!-----------------------------------------------------
    //! @brief : カーソルの下にある状態を返す
    //! @param : [in](void) none
    //! @return : 下にあるならtrueを返す
    //!-----------------------------------------------------
    bool IsUnderCursor(void);
    //!-----------------------------------------------------
    //! @brief : 選択された状態で決定ボタンが押されたかどうかを返す
    //! @param : [in](void) none
    //! @return : 確定されているならtrueを返す
    //!-----------------------------------------------------
    bool IsDecide(void);
        //!-----------------------------------------------------
    //! @brief : カーソルのポインタを登録する
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    //void RegisterCursor(br::Cursor* cursor);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : カーソルのポインタ
    //!-----------------------------------------------------
    br::Cursor* GetCursor(void);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : カーソルの位置
    //!-----------------------------------------------------
    Mof::CVector2 GetCursorPosition(void);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_SELECTABLE_COMPONENT_H