//!-----------------------------------------------------
//! @file : TextureComponent.h
//! @brief : Actorが持つSprite描画機能
//! @date : 2020/05/30
//!-----------------------------------------------------


#ifndef BR_TEXTURE_COMPONENT_H
#define BR_TEXTURE_COMPONENT_H


#include "RenderComponent.h"

#include <memory>
#include <Mof.h>

#include "MotionComponent.h"


namespace br {
class TextureComponent : public br::RenderComponent {
    using super = br::RenderComponent;
private:
protected:
    //! 描画テクスチャ
    std::weak_ptr<Mof::CTexture> _texture;
    //! 描画矩形
    Mof::Rectangle _rectangle;
    //! アニメーションデータ
    br::MotionComponent* _motion;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    TextureComponent(br::Actor* owner, int priority);
    virtual ~TextureComponent();

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](std::shared_ptr<Mof::CTexture> texture) ポインタ
    //! @param : [in](const Mof::Rectangle* rectangle = 0) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void SetTexture(std::weak_ptr<Mof::CTexture> texture,
                    const Mof::Rectangle* rectangle = 0);
        //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](br::MotionComponent& c) 参照
    //! @return : none
    //!-----------------------------------------------------
    void SetMotionComponent(br::MotionComponent& c);


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
#endif // !BR_TEXTURE_COMPONENT_H