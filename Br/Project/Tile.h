//!-----------------------------------------------------
//! @file : Stage.h
//! @brief : 駒が動く盤面の一区画 Stageに管理される
//! @date : 2020/05/30
//!-----------------------------------------------------


#ifndef BR_TILE_H
#define BR_TILE_H


#include "Actor.h"

#include <string>
#include <memory>
#include <array>
#include <vector>

#include <Mof.h>

#include "Helper.h"
#include "Common.h"
//#include "Unit.h"

namespace br {
class Unit;
class Tile : public br::Actor {
    using super = br::Actor;
    //! このタイルに隣接する(このTileから見える)地形の配列
    //! 各要素はarray[(int)direction]に格納する
    using tile_array = std::array<br::Tile*, static_cast<int>(br::Direction::CountMax)>;
private:
    //! 種類識別番号
    int _type;
    //! 名前
    const char* _name;
    //! 地形コスト
    int _cost;
    //! 隣接する(このTileから見える)地形とその方向
    tile_array _adjacents;
    //! 列 デバッグ用
    int _col;
    //! 行 デバッグ用
    int _row;

    //! 上に乗ってる人
    //UnitManager* _unit_manager;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Scene* scene) 現在のシーン
    //! @param : [in](int type) タイルの種類
    //! @return : none
    //!-----------------------------------------------------
    Tile(br::Scene* scene, int type);
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Tile();

    virtual br::ActorState GetState(void) const override;
    virtual Mof::CVector2 GetPosition(void) const override;

        //!-----------------------------------------------------
    //! @brief : ここに乗っているUnitのポインタを取得
    //! @param : [in](void) none
    //! @return : いない場合nullptr
    //!-----------------------------------------------------
    Unit* GetOnUnit(void);

    def::Vector2i GetGridPosition(void);

    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 名前
    //!-----------------------------------------------------
    //std::string GetName(void) const;
    const char* GetName(void) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 地形コスト
    //!-----------------------------------------------------
    int GetCost(void) const;
    int GetCost(class Unit* ptr) const;
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 隣接するタイル群
    //!-----------------------------------------------------
    br::Tile::tile_array& GetAdjacents(void);
    //!-----------------------------------------------------
    //! @brief : 現在立ち入り禁止かどうか
    //! @param : [in](br::Unit* ptr) 通りたい人
    //! @return : 道が塞がれていなければ、ここを通れるならtrueを返す   
    //!-----------------------------------------------------
    bool IsBlocked(void);
    bool IsBlocked(Unit* ptr);

    //!-----------------------------------------------------
    //! @brief : 初期化
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Initialize(const br::ActorBaseState& base);
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

    //!-----------------------------------------------------
    //! @brief : 隣接するTileの登録
    //! @param : [in](br::Direction direction) 方向
    //! @param : [in](Tile* tile) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void RegisterAdjacent(br::Direction direction, Tile* tile);
    //!-----------------------------------------------------
    //! @brief : タイルの列と行が等しいか調べる
    //! @param : [in](br::Tile* r) 比較対象
    //! @return : 同じ列かつ同じ行であればtrueを返す
    //!-----------------------------------------------------
    bool Equal(br::Tile* r);
};
}
#endif // !BR_TILE_H