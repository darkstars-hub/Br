//!-----------------------------------------------------
//! @file : Cursor.h
//! @brief : 盤面上の区画を選択する印
//! @date : 2020/05/31
//!-----------------------------------------------------


#ifndef BR_CURSOR_H
#define BR_CURSOR_H


#include "Actor.h"
#include "Tile.h"


namespace br {
struct DirectionWait {
    const int max = 4;
    const int max_hold = 4;
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    int hold = 0;
};
class Cursor : public br::Actor {
    using super = br::Actor;
public:
    enum class Mode {
        Normal, // 通常移動
        Limit, // 一定範囲内のものを選択する時
    };
private:
    //! 決定ボタンを押したフラグ
    bool _is_enter;
    //! 戻るボタンを押したフラグ
    bool _is_back;
    //! カーソル移動待ち時間
    DirectionWait _wait;
    //! 選択しているユニット
    class Unit* _select_unit;
    //! 移動可能な制限範囲 今は制限なし
    std::vector<br::Tile*> _limit_range;
    //! 攻撃相手選択モード
    br::Cursor::Mode _mode;

    void WaitCountIncrement(void);
    void WaitCountIncrementGamePad(Mof::LPGamePad pad);
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Scene* scene) 現在のシーン
    //! @param : [in](Mof::CVector2* scroll) シーンのスクロール値のアドレス
    //! @return : none
    //!-----------------------------------------------------
    Cursor(br::Scene* scene, Mof::CVector2* scroll);
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Cursor();

    virtual br::ActorState GetState(void) const override;
    virtual Mof::CVector2 GetPosition(void) const override;


    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](br::Actor* unit) 選んだユニット
    //! @return : none
    //!-----------------------------------------------------
    void SetSelectUnit(br::Actor* unit);

    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](none) none
    //! @return : このフレーム中に決定ボタンを押したかどうか
    //!-----------------------------------------------------
    bool IsEnter(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](none) none
    //! @return : このフレーム中に戻るボタンを押したかどうか
    //!-----------------------------------------------------
    bool IsBack(void) const;
    //!-----------------------------------------------------
    //! @brief : カーソルがモノを選択可能か調べる
    //! @param : [in](none) none
    //! @return : 可能であればtrueを返す
    //!-----------------------------------------------------
    bool CanSelect(void) const;
    //!-----------------------------------------------------
    //! @brief : その位置が選択ユニットの移動可能範囲かを調べる
    //! @param : [in](none) none
    //! @return : 入っていればtrueを返す
    //!-----------------------------------------------------
    bool InMovableRange(br::Tile* tile) const;
    //!-----------------------------------------------------
    //! @brief : その位置が選択ユニットの攻撃可能範囲かを調べる
    //! @param : [in](none) none
    //! @return : 入っていればtrueを返す
    //!-----------------------------------------------------
    bool InAttackRange(br::Tile* tile) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](none) none
    //! @return : 選択中のユニット
    //!-----------------------------------------------------
    class Unit* GetSelectUnit(void);
    //!-----------------------------------------------------
    //! @brief : カーソルの真下にいるユニットを返す
    //! @param : [in](none) none
    //! @return : いないならnullptrを返す
    //!-----------------------------------------------------
    class Unit* GetUnderUnit(void);

    br::Cursor::Mode GetMode(void);
    std::vector<br::Tile*>& GetLimitRange(void);

    //!-----------------------------------------------------
    //! @brief : 移動モード変更
    //! @param : [in](std::vector<br::Tile*>& range) この状態での制限範囲
    //! @return : 選択中のユニット
    //!-----------------------------------------------------
    void ChangeMode(br::Cursor::Mode mode, std::vector<br::Tile*>& range);

    //!-----------------------------------------------------
    //! @brief : 入力処理　メニュー表示中は実行されない
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Input(void) override;
    //!-----------------------------------------------------
    //! @brief : 更新
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;
};
}
#endif // !BR_CURSOR_H