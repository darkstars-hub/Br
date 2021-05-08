//!-----------------------------------------------------
//! @file : RangeRenderComponent.h
//! @brief : 受け取った範囲を描画する機能
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_RANGE_RENDER_COMPONENT_H
#define BR_RANGE_RENDER_COMPONENT_H


#include "RenderComponent.h"

#include <memory>
#include <Mof.h>
#include "Range.h"
#include "Tile.h"
#include "SelectableComponent.h"
namespace br {
class RangeRenderComponent : public br::RenderComponent {
    using super = br::RenderComponent;
private:
    //! 描画範囲
    std::vector<br::RangeDataPointer>* _range;
    //! 攻撃範囲
    std::vector<br::Tile*>* _attack_range;
    //! 融合範囲
    std::vector<br::Tile*>* _fusion_range;
    //! 可視範囲（域）
    std::vector<br::RangeDataPointer>* _sight_range;
    //! 
    br::SelectableComponent* _select;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    RangeRenderComponent(br::Actor* owner, int priority);
    virtual ~RangeRenderComponent();

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](std::vector<br::RangeDataPointer>* range) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetRange(std::vector<br::RangeDataPointer>* range);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](std::vector<br::Tile>* range) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetAttackRange(std::vector<br::Tile*>* range);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](std::vector<br::Tile>* range) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetFusionRange(std::vector<br::Tile*>* range);
    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](std::vector<br::RangeDataPointer>* range) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetSightRange(std::vector<br::RangeDataPointer>* range);


    bool Initialize(void) override;
    bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    bool Render(Mof::CVector2 scroll) override;
    bool Release(void) override;

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_RANGE_RENDER_COMPONENT_H