//!-----------------------------------------------------
//! @file : EffectManager.h
//! @brief : ゲームオブジェクトはこれを使ってエフェクトを発生させる
//! @date : 2020/07/13
//!-----------------------------------------------------


#ifndef BR_EFFECT_MANAGER_H
#define BR_EFFECT_MANAGER_H


#include <memory>
#include <string>
#include <vector>

#include "Effect.h"
#include "Scene.h"


namespace br {
class EffectManager {
private:
    std::vector<std::shared_ptr<br::Effect>> _effects;
    br::Scene* _scene;
public:
    EffectManager(br::Scene* _scene);
    ~EffectManager();

    //!-----------------------------------------------------
    //! @brief : 名前を参照してエフェクトを取得する　複数ある場合を想定しない
    //! @param : [in](const char* name) 取得したいエフェクトの名前
    //! @return : 引数にした名前を持つエフェクト
    //!-----------------------------------------------------
    std::shared_ptr<br::Effect>GetEffectByName(const char* name);

    bool Update(void);
    bool Render(Mof::CVector2 scroll);
    bool Release(void);

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
#endif // !BR_EFFECT_MANAGER_H