//!-----------------------------------------------------
//! @file : PathComponent.h
//! @brief : Unitが持つ移動機能
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_PATH_COMPONENT_H
#define BR_PATH_COMPONENT_H


#include "UpdateComponent.h"

#include <vector>

#include <Mof.h>

#include "PathRenderComponent.h"
#include "Range.h"


namespace br {
class PathComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! 経路情報は後でPathRenderComponent*に渡す
    std::vector<br::PathDataPointer> _path;
    //! 経路を参照してもらう
    br::PathRenderComponent* _path_render;
    
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    PathComponent(Actor* owner, int priority = 100);
    virtual ~PathComponent();

    //!-----------------------------------------------------
    //! @brief : 移動経路を渡す
    //! @param : [in](void) none
    //! @return : 移動経路
    //!-----------------------------------------------------
    const std::vector<br::PathDataPointer>& GetPath(void) const;
    //!-----------------------------------------------------
    //! @brief : 移動経路を渡す
    //! @param : [in](void) none
    //! @return : 移動経路
    //!-----------------------------------------------------
    br::PathDataPointer GetElement(std::size_t index);
    //!-----------------------------------------------------
    //! @brief : 目標地点に到着したかどうか
    //! @param : [in](void) none
    //! @return : したならtrueを返す
    //!-----------------------------------------------------
    bool IsArrived(size_t index) const;
    //!-----------------------------------------------------
    //! @brief : 計算したパスのクリア
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Clear(void);
        //!-----------------------------------------------------
    //! @brief : 移動経路計算　tileとdestinationがすごく離れていると処理負荷が大きい
    //! @param : [in](br::Tile* target) 調べるタイル
    //! @return : あればtrueを返す
    //!-----------------------------------------------------
    void Conpute(br::Tile* tile, br::Tile* destination);

    //!-----------------------------------------------------
    //! @brief : 調べるタイルが移動可能範囲にあるか調べる
    //! @param : [in](const std::vector<br::RangeDataPointer>&range) 移動可能範囲
    //! @param : [in](br::Tile* target) 調べるタイル
    //! @return : あればtrueを返す
    //!-----------------------------------------------------
    bool CheckTargetTile(const std::vector<br::RangeDataPointer>& range, br::Tile* target)const;

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
#endif // !BR_UNIT_MOVE_COMPONENT_H