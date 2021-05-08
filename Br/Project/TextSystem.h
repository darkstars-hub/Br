//!-----------------------------------------------------
//! @file : TextSystem.h
//! @brief : テキストを表示をする
//! @date : 2020/07/10
//!-----------------------------------------------------


#ifndef BR_TEXT_SYSTEM_H
#define BR_TEXT_SYSTEM_H


#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "../include/rapidjson/document.h"

#include <Mof.h>

#include "ResourceManager.h"


namespace br {
class TextSystem {
private:
    //! 文字フォント
    Mof::CFont _font;
    //! テキスト表示域
    Mof::CRectangle _window;
    //! 表示フラグ
    bool _is_show;
    //! 表示するテキスト
    std::vector<std::string> _texts;
    //! 表示するテキストのインデックス
    size_t _index;
    //! 表示する文字数
    size_t _text_index;
    //! 描画するテクスチャのパス
    std::vector<std::string> _texture_paths;
    //! 描画するテクスチャUV
    std::vector<Mof::CRectangle> _rectangles;
    //! テクスチャを描画する位置
    std::vector<Mof::CVector2> _positions;
    //! 描画テクスチャを反転するかのフラグ
    std::vector<bool> _reverses;
    //! リソース保持
    std::weak_ptr<br::ResourceManager> _resource_manager;
    //! テキストを進めた時の音
    Mof::CSoundBuffer _sound;
    //! テキスト終了時に実行する関数
    std::function<void(void)> _end_event;
    //! テキストを全て表示したかどうか
    //bool _all_show;
public:
    TextSystem();
    ~TextSystem();

    void SetResourceManager(std::shared_ptr<br::ResourceManager>r);

    //!-----------------------------------------------------
    //! @brief : 表示状態取得
    //! @param : [in](void) none
    //! @return : 表示中ならtrueを返す
    //!-----------------------------------------------------
    bool IsShow(void)const;
    //!-----------------------------------------------------
    //! @brief : テキストデータを読み込み、表示状態にする
    //! @param : [in](const char* path) パス
    //! @return : none
    //!-----------------------------------------------------
    void Show(const char* path, std::function<void(void)>lambda = []() {});
    void Show(const std::string& text, std::function<void(void)>lambda = []() {});
    //!-----------------------------------------------------
    //! @brief : 非表示状態する
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Hide(void);

    void Input(void);
    void Update(void);
    void Render(void);

    void Reset(void);
    void Release(void);
};
}
#endif // !BR_TEXT_SYSTEM_H