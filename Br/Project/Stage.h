//!-----------------------------------------------------
//! @file : Stage.h
//! @brief : 駒が動く盤面 １＊１の「ふち」があるので、実際には2列2行少ない
//! @date : 2020/05/30
//!-----------------------------------------------------


#ifndef BR_STAGE_H
#define BR_STAGE_H


#include "Actor.h"

#include <memory>
#include <vector>
#include <Mof.h>
#include "../include/rapidjson/document.h"

#include "Helper.h"
#include "Common.h"
#include "Tile.h"


namespace br {
class Stage : public br::Actor {
    using super = br::Actor;
private:
    //! ステージ上の地形
    std::vector<br::Tile*> _tiles;
    //! 列＊行
    Mof::Vector2 _tile_count;
    //! タイルの種類の番号 これを参照しTileは作成される
    std::vector<int> _tile_id;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Scene* scene) 現在のシーン
    //! @return : none
    //!-----------------------------------------------------
    Stage(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Stage();

    virtual br::ActorState GetState(void) const override;
    virtual Mof::CVector2 GetPosition(void) const override;

    //!-----------------------------------------------------
    //! @brief : 対応するタイルを取得
    //! @param : [in](int col) 列
    //! @param : [in](int row) 行
    //! @param : [in](br::Direction = br::Direction::None) タイルの隣接方向
    //! @return : その位置にあるタイルのポインタ
    //!-----------------------------------------------------
    br::Tile* GetTile(int col, int row, br::Direction = br::Direction::CountMax);
    br::Tile* GetTile(def::Vector2i position, br::Direction = br::Direction::CountMax);
    //!-----------------------------------------------------
    //! @brief : 列数と行数を取得
    //! @param : [in](void) none 
    //! @return : 列数と行数が格納されたMof::CVector2
    //!-----------------------------------------------------
    Mof::CVector2 GetTileCount(void) const;

    //!-----------------------------------------------------
    //! @brief : 読み込み
    //! @param : [in](const char* path) パス
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Load(const char* path) override;
    
    //!-----------------------------------------------------
    //! @brief : 初期化
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Initialize(const br::ActorBaseState& base) override;
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
    //! @brief : 解放
    //! @param : [in](void) none
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Release(void) override;
};
}
#endif // !BR_STAGE_H