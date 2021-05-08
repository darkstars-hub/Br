//!-----------------------------------------------------
//! @file : FusionSystem.h
//! @brief : 合体する時の舞台
//! @date : 2020/07/114
//!-----------------------------------------------------


#ifndef BR_FUSION_SYSTEM_H
#define BR_FUSION_SYSTEM_H


#include <memory>

#include <Mof.h>

#include "ResourceManager.h"
//#include "Tile.h"
#include "Unit.h"
#include "Sprite.h"


namespace br {
class FusionSystem {
private:
    bool _is_show;

    //! ここで動く人
    br::Unit* _unit;
    //! ここで動く人
    br::Unit* _target;

    //! 表示するテクスチャのパス
    std::string _back_path;
    //! 表示位置
    Mof::CVector2 _unit_position;
    Mof::CVector2 _target_position;
    //! 表示するスプライト
    br::Sprite _unit_sprite;
    br::Sprite _target_sprite;
    
    std::shared_ptr<br::ResourceManager> _resource_manager;

    void SetSprite(br::UnitType type, br::Sprite& out);
public:
    FusionSystem();
    ~FusionSystem();

    void SetResourceManager(std::shared_ptr<br::ResourceManager>r);

    bool IsShow(void);
    void Show(br::Unit* unit, br::Unit* target);

    bool Input(void);
    bool Update(void);
    bool Render(void);
};
}
#endif // !BR_FUSION_SYSTEM_H