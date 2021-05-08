//!-----------------------------------------------------
//! @file : UnitJobComponent.h
//! @brief : Unitが持つ職業機能の基底クラス
//! @date : 2020/06/22
//!-----------------------------------------------------


#ifndef BR_UNIT_JOB_COMPONENT_H
#define BR_UNIT_JOB_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>

//#include "Unit.h"
#include "UnitStateComponent.h"
#include "MotionComponent.h"
#include "UnitTextureComponent.h"
#include "HpComponent.h"
#include "Range.h"


namespace br {
class UnitJobComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //!-----------------------------------------------------
    //! @brief : Initialize内で実行される
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual void RegisterType(void) = 0;
protected:
    const char* _resource_path;
    class Unit* _unit;
    br::UnitStateComponent* _state;
    br::MotionComponent* _motion;
    br::UnitTextureComponent* _texture;
    br::HpComponent* _hp;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    UnitJobComponent(Actor* owner, int priority = 100);
    ~UnitJobComponent();

    class Unit* GetOwnerUnit(void) const;
    virtual std::shared_ptr<br::IRangeAlgorithm> GetRangeAlgorithm(void);

    virtual bool Fusion(class Unit& target) = 0;

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll);
    virtual bool Release(void) override;

    virtual br::Component* Clone(void) = 0;
};
}
#endif // !BR_UNIT_COMPONENT_H