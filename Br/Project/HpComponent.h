//!-----------------------------------------------------
//! @file : HpComponent.h
//! @brief : 命　無くなると死亡
//! @date : 2020/06/22
//!-----------------------------------------------------


#ifndef BR_HP_COMPONENT_H
#define BR_HP_COMPONENT_H


#include "RenderComponent.h"

#include <memory>

#include <Mof.h>


namespace br {
class HpComponent : public RenderComponent {
    using super = br::RenderComponent;
private:
    //! HPの最大値
    int _value_max;
    //! 現在のHPの値
    int _value;
    //! 画像表示フラグ
    bool _is_show;
    //! 現在のHPの値の数だけ表示
    std::weak_ptr<Mof::CTexture> _textrue;
    //! 描画矩形
    const Mof::CRectangle _render_rect;
    //! 描画矩形オフセット 描画矩形の幅と高さと等しい
    const float _render_offset;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    HpComponent(Actor* owner, int priority = 100);
    virtual ~HpComponent();
    
    void SetShow(bool show);
    void SetMaxHp(int value);
    void SetHp(int value);
    int GetValue(void) const;
    int GetMaxValue(void) const;

    void Damege(int value);
    void Heal(int value);

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
#endif // !BR_HP_COMPONENT_H