//!-----------------------------------------------------
//! @file : MotionComponent.h
//! @brief : Actorが持つアニメーション機能
//! @date : 2020/06/08
//!-----------------------------------------------------


#ifndef BR_MOTION_COMPONENT_H
#define BR_MOTION_COMPONENT_H


#include "UpdateComponent.h"


#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <Mof.h>
#include "Actor.h"
#include "Sprite.h"
#include "ResourceManager.h"

namespace br {
class MotionComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
protected:
    //! モーションを更新するかどうか
    //bool _is_update;
    //! モーション
    Mof::CSpriteMotionController _motion;
    //! モーションの状態
    std::string _motion_state;
    //! モーション番号とモーション名のテーブル
//    std::unordered_map<std::string, int>* _motion_map;
    std::unordered_map<int, std::string>* _motion_map;
    //! モーションデータのパス
    std::string _path;
    //! リソース管理先のキャッシュ
    std::weak_ptr<br::ResourceManager> _resource_manager;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](br::Actor* owner) この機能の所有者
    //! @param : [in](int priority) 処理優先順位 0に近いほど高い
    //! @return : none
    //!-----------------------------------------------------
    MotionComponent(Actor* owner, int priority = 100);
    virtual ~MotionComponent();

        //!-----------------------------------------------------
    //! @brief : セッター   
    //! @param : [in](bool state) 更新するかどうか
    //! @return : none
    //!-----------------------------------------------------
    //void SetUpdateFlag(bool state);
            //!-----------------------------------------------------
    //! @brief : ゲッター   
    //! @param : [in](void) none
    //! @return : 更新するならtrueを返す;
    //!-----------------------------------------------------
    //bool IsUpdate(void) const;
            //!-----------------------------------------------------
    //! @brief : セッター   
    //! @param : [in](const std::string& motion_name) モーション名
    //! @return : none
    //!-----------------------------------------------------
    void SetState(const std::string& state);
            //!-----------------------------------------------------
    //! @brief : ゲッター   
    //! @param : [in](void) none
    //! @return : モーション名
    //!-----------------------------------------------------
    const std::string& GetState(void) const;

    //!-----------------------------------------------------
    //! @brief : アニメーション作成
    //! @param : [in](std::weak_ptr<br::ResourceManager>r) リソース保持者
    //! @param : [in](const char* path) パス
    //! @return : none
    //!-----------------------------------------------------
    void MakeAnimation(std::weak_ptr<br::ResourceManager>r, const char* path);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](Mof::CVector2 scroll) スクロール値
    //! @return : 成功した場合true
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : 現在の描画矩形
    //!-----------------------------------------------------
    Mof::CRectangle GetRenderRectangle(void);


    //!-----------------------------------------------------
    //! @brief : Mof::CSpriteMotionController.IsEndMotionのラッパー
    //! @param : [in](void) none
    //! @return : 終わっている場合trueを返す
    //!-----------------------------------------------------
    bool IsEndMotion(void);
    //!-----------------------------------------------------
    //! @brief : Mof::CSpriteMotionController.ChangeMotionByNameのラッパー
    //! @param : [in](const char* name) モーション名
    //! @return : 成功した場合trueを返す
    //!-----------------------------------------------------
    bool ChangeMotionByName(const char* name);
    //!-----------------------------------------------------
    //! @brief : Mof::CSpriteMotionController.GetMotionNoのラッパー
    //! @param : [in](void) none
    //! @return : 現在のモーション番号
    //!-----------------------------------------------------
    int GetMotionNo(void);
     //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : モーション番号とモーション名のテーブル
    //!-----------------------------------------------------
    //std::unordered_map<std::string, int>* GetMotionMap(void);
    std::unordered_map<int, std::string>* GetMotionMap(void);

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_MOTION_COMPONENT_H