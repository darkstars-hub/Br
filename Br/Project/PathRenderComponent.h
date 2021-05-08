//!-----------------------------------------------------
//! @file : PathRenderComponent.h
//! @brief : 受け取った経路を描画する機能
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_PATH_RENDER_COMPONENT_H
#define BR_PATH_RENDER_COMPONENT_H


#include "RenderComponent.h"

#include <memory>
#include <Mof.h>
#include "AStar.h"

namespace br {
class PathRenderComponent : public br::RenderComponent {
    using super = br::RenderComponent;
private:
    std::vector<br::PathDataPointer>* _path;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    PathRenderComponent(br::Actor* owner, int priority);
    virtual ~PathRenderComponent();

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](std::vector<br::AStarDataPointer>* range) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetPath(std::vector<br::PathDataPointer>* range);


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
#endif // !BR_PATH_RENDER_COMPONENT_H