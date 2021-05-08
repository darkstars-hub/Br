//!-----------------------------------------------------
//! @file : Effect.h
//! @brief : 画面効果
//! @date : 2020/07/13
//!-----------------------------------------------------


#ifndef BR_EFFECT_H
#define BR_EFFECT_H


#include "Actor.h"

#include <Mof.h>

#include "MotionComponent.h"
#include "TextureComponent.h"


namespace br {
class Effect : public br::Actor {
    using super = br::Actor;
private:
    br::MotionComponent* _motion;
    br::TextureComponent* _texture;

    bool _is_show;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Scene* scene) 現在のシーン
    //! @return : none
    //!-----------------------------------------------------
    Effect(br::Scene* scene);
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Effect();

    virtual br::ActorState GetState(void) const override;
    virtual Mof::CVector2 GetPosition(void) const override;
    
    //!-----------------------------------------------------
    //! @brief : モーションが終了したかどうか
    //! @param : [in](void) none
    //! @return : モーションが終了したかどうか
    //!-----------------------------------------------------
    bool IsEndMotion(void);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 固有の名前
    //!-----------------------------------------------------
    const char* GetName(void) const;

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
    //! @brief : エフェクト発生
    //! @param : [in](Mof::CVector2 scroll) スプライトのパス
    //! @param : [in](Mof::CVector2 position) 表示位置
    //! @param : [in](Mof::CVector2 scroll) 名前
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    void Start(const char* path, Mof::CVector2 position, const char* name = "");
};
}
#endif // !BR_EFFECT_H