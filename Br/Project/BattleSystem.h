//!-----------------------------------------------------
//! @file : BattleSystem.h
//! @brief : Unitが戦う時の舞台
//! @date : 2020/07/13
//!-----------------------------------------------------


#ifndef BR_BATTLE_SYSTEM_H
#define BR_BATTLE_SYSTEM_H


#include <memory>
#include <string>

#include <Mof.h>

#include "Scene.h"
#include "ResourceManager.h"
//#include "Tile.h"
#include "Unit.h"
#include "Sprite.h"
#include "BattleSystemHp.h"
#include "BattleSystemUnit.h"
#include "BattleSystemUnitInfomation.h"
#include "TextSystem.h"


namespace br {
class BattleSystem {
private:
    br::Scene* _scene;
    //! 全てのアクションが終わったらUpdateの中でfalseにする
    //! 画面真っ黒でバトル画面終了
    bool _is_show;
    //! 表示するテクスチャのパス
    std::string _back_path;
    //! リソースマネージャのポインタ
    std::weak_ptr<br::ResourceManager> _resource_manager;
    //! 攻撃側の攻撃終了フラグ
    bool _attacker_excuted;
    //! フェードインする時のアルファ値
    int _in_alpha;
    //! フェードアウトする時のアルファ値
    int _out_alpha;


    //! プレイヤーのHPを表示する
    br::BattleSystemHp _player_hp;
    //! エネミーのHPを表示する
    br::BattleSystemHp _enemy_hp;
    //! ここで動く人（プレイヤー）
    br::BattleSystemUnit _player_unit;
    //! ここで動く人（エネミー）
    br::BattleSystemUnit _enemy_unit;
    //! ユニットの情報表示
    br::BattleSystemUnitInfomation _player_info;
    br::BattleSystemUnitInfomation _enemy_info;
    
    br::TextSystem _result_text;
    //! 攻撃された側が生きていたら反撃開始する
    bool _counter_attack;
    //! 反撃（攻撃された）側の反撃終了フラグ
    //bool _counter_excuted;
    //bool _is_change;

    br::BattleSystemUnit* GetAttackerUnit(void);
    br::BattleSystemUnit* GetTargetUnit(void);
    //!-----------------------------------------------------
    //! @brief : バトルシステムの画面に入るときの遷移効果の更新
    //! @param : [in](void) none
    //! @return : Updateの処理を実行するかどうか
    //!-----------------------------------------------------
    bool UpdateSystem(void);
    //!-----------------------------------------------------
    //! @brief : 遷移効果（フェードアウトのアルファ値）の更新
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void UpdateFade(void);
    //!-----------------------------------------------------
    //! @brief : バトルシステムの画面に入るときの遷移効果の描画
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void RenderFadeIn(void);
    //!-----------------------------------------------------
    //! @brief : バトルシステムの画面から出るときの遷移効果の描画
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void RenderFadeOut(void);
    //!-----------------------------------------------------
    //! @brief : 遷移効果の描画
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void RenderFade(void);
    //!-----------------------------------------------------
    //! @brief : 体力を描画
    //! @param : [in](br::BattleSystemHp) Hp情報
    //! @return : none
    //!-----------------------------------------------------
    void RenderHp(br::BattleSystemHp);
    //!-----------------------------------------------------
    //! @brief : 攻撃処理の部分攻撃が当たった時
    //! @param : [in](br::Unit* attacker) 攻撃側
    //! @param : [in](br::Unit* target) 反撃側
    //! @return : none
    //!-----------------------------------------------------
    void AttackSuccess(br::Unit* attacker, br::Unit* target);
    //!-----------------------------------------------------
    //! @brief : 攻撃処理の部分攻撃が当たった時
    //! @param : [in](br::Unit* attacker) 攻撃側
    //! @param : [in](br::Unit* target) 反撃側
    //! @return : none
    //!-----------------------------------------------------
    void AttackFailure(br::Unit* attacker, br::Unit* target);
public:
    BattleSystem();
    ~BattleSystem();

    //!-----------------------------------------------------
    //! @brief : メンバの初期化
    //! @param : [in](std::weak_ptr<br::ResourceManager>r) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void Initialize(std::weak_ptr<br::ResourceManager>r);

    //!-----------------------------------------------------
    //! @brief : 表示フラグ
    //! @param : [in](void) none
    //! @return : 表示していればtrueを返す
    //!-----------------------------------------------------
    bool IsShow(void);
    //!-----------------------------------------------------
    //! @brief : BallteSystemを開始する
    //! @param : [in](br::Unit* attacker) 攻撃を仕掛けた側のポインタ
    //! @param : [in](br::Unit* target) 攻撃された側のポインタ
    //! @param : [in](br::Tile* filed) 戦場
    //! @return : none
    //!-----------------------------------------------------
    void Show(br::Unit* attacker, br::Unit* target);
   // void Show(br::Unit* attacker, br::Unit* target, br::Tile* back);

   
    //!-----------------------------------------------------
    //! @brief : 何か入れるかも
    //! @param : [in](void) none
    //! @return : true
    //!-----------------------------------------------------
    bool Input(void);
    //!-----------------------------------------------------
    //! @brief : 更新 表示フラグの設定
    //!          画面真っ黒（フェードアウトのアルファ値＝２５５）でバトル画面終了
    //! @param : [in](void) none
    //! @return : true
    //!-----------------------------------------------------
    bool Update(void);
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](void) none
    //! @return : true
    //!-----------------------------------------------------
    bool Render(void);
};
}
#endif // !BR_BATTLE_SYSTEM_H