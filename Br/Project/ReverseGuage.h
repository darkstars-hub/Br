//!-----------------------------------------------------
//! @file : ReverseGuage.h
//! @brief : 相性を反転させるゲージ
//! @date : 2020/07/14
//!-----------------------------------------------------


#ifndef BR_REVERSE_GUAGE_H
#define BR_REVERSE_GUAGE_H


#include <memory>

#include <Mof.h>

#include "ResourceManager.h"


namespace br {
class ReverseGuage {
private:
    //! ゲージの最大値
    const int _value_max;
    //! ゲージの現在の値
    int _value;

    std::weak_ptr<br::ResourceManager> _resource_manager;
public:
    ReverseGuage();
    ~ReverseGuage();

    //!-----------------------------------------------------
    //! @brief : セッター
    //! @param : [in](std::shared_ptr<br::ResourceManager> r) リソース保持者
    //! @return : none
    //!-----------------------------------------------------
    void SetResourceManager(std::weak_ptr<br::ResourceManager> r);
    
    //!-----------------------------------------------------
    //! @brief : ゲージが満タンかどうか
    //! @param : [in](void) none
    //! @return : そうであればtrueを返す
    //!-----------------------------------------------------
    bool IsMax(void);
    //!-----------------------------------------------------
    //! @brief : ゲージ加算
    //! @param : [in](int value) ゲージが増える値
    //! @return : none
    //!-----------------------------------------------------
    void Add(int value);
    //!-----------------------------------------------------
    //! @brief : ゲージを消費して相性を反転させる
    //! @param : [in](void) none
    //! @return : ゲージが満ちていないならfalseを返す（失敗する）
    //!-----------------------------------------------------
    bool Use(void);

    void Render(void);
//    void Render(Mof::CVector2 position);
};
}
#endif // !BR_REVERSE_GUAGE_H