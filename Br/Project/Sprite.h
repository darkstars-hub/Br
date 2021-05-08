//!-----------------------------------------------------
//! @file : Sprite.h
//! @brief : アニメーションする画像の集合 拡張子「~.sprite」を扱う
//! @date : 2020/05/27
//!-----------------------------------------------------


#ifndef BR_SPRITE_H
#define BR_SPRITE_H


#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <Mof.h>
#include "../include/rapidjson/document.h"


namespace br {
class SpritePart {
    friend class Sprite;
private:
    //! 参照するファイルへのパス
    std::string _directory_path;
    //! 描画画像
    std::weak_ptr<Mof::CTexture> _texture;
    //! アニメーションの部品、Spriteが参照する
    std::vector<Mof::SpriteAnimationCreate> _anims;
    //! モーション番号とモーション名のテーブル
    //std::unordered_map<std::string, int> _motion_map;
    std::unordered_map<int, std::string> _motion_map;
    //!-----------------------------------------------------
    //! @brief : Load()に呼ばれる アニメーション作成
    //! @param : [in](const rapidjson::Document& document) 読み込みデータ
    //! @param : [in](ResourceManager& r) テクスチャ取得先 
    //! @return : none
    //!-----------------------------------------------------
    void LoadAnimation(const rapidjson::Document& document, class ResourceManager& r);
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    SpritePart();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~SpritePart();

    std::weak_ptr<Mof::CTexture> GetTexture(void);
    std::vector<Mof::SpriteAnimationCreate>& GetAnimsAddress(void);
    //std::unordered_map<std::string, int>& GetMotionMapAddress(void);
    std::unordered_map<int,std::string>& GetMotionMapAddress(void);

    //!-----------------------------------------------------
    //! @brief : 読み込み
    //! @param : [in](const char* path) ファイルのパス 
    //! @param : [in](ResourceManager& r) テクスチャ取得先 
    //! @return : 読み込みに成功した場合trueを返す
    //!-----------------------------------------------------
    bool Load(const char* path, class ResourceManager& r);
    //!-----------------------------------------------------
    //! @brief : 保持している全てのリソースの解放
    //! @param : [in](none)
    //! @return : 成功した場合trueを返す
    //!-----------------------------------------------------
    bool Release(void);
};
class Sprite {
private:
    //! 描画画像
    std::weak_ptr<Mof::CTexture> _texture;
    //! 遷移するアニメーションの変動値を保持
    Mof::CSpriteMotionController _motion;
    //! モーション番号とモーション名のテーブル 実体はSpritePartが持つ
    //std::unordered_map<std::string, int>* _motion_map;
    std::unordered_map<int,std::string>* _motion_map;
    //! 現在のモーション番号
    //int _current_no;
    //! アニメーションデータのキャッシュ
    bool _reverse_x;
public:
    //SpritePart* _p;

    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Sprite();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~Sprite();


    void SetReverseX(bool reverse);
    //!-----------------------------------------------------
    //! @brief : ゲッター
    //! @param : [in](void) none
    //! @return : モーション番号とモーション名のテーブルのポインタ
    //!-----------------------------------------------------
    //std::unordered_map<std::string, int>* GetMotionMap(void) {
    std::unordered_map<int, std::string>* GetMotionMap(void);
    //!-----------------------------------------------------
    //! @brief : CSpriteMotionController::GetSrcRectのラッパー
    //! @param : [in](void) none
    //! @return : 表示中の矩形
    //!-----------------------------------------------------
    Mof::CRectangle GetSrcRect(void) ;
    //!-----------------------------------------------------
    //! @brief : 読み込み
    //! @param : [in](const char* path) ファイルのパス 
    //! @param : [in](ResourceManager& r) テクスチャ取得先 
    //! @return : 読み込みに成功した場合trueを返す
    //!-----------------------------------------------------
    bool Load(const char* path, class ResourceManager& r);
    //!-----------------------------------------------------
    //! @brief : 読み込み
    //! @param : [in](br::SpritePart& part) 部品の参照 
    //! @return : 読み込みに成功した場合trueを返す
    //!-----------------------------------------------------
    bool Load(br::SpritePart& part);
    //!-----------------------------------------------------
    //! @brief : アニメーションの値などの更新
    //! @param : [in](void) none 
    //! @return : none
    //!-----------------------------------------------------
    void Update(void);
    //!-----------------------------------------------------
    //! @brief : 描画
    //! @param : [in](const Mof::Vector2 position) 描画位置 
    //! @return : none
    //!-----------------------------------------------------
    void Render(const Mof::Vector2 position);
    //!-----------------------------------------------------
    //! @brief : 保持している全てのリソースの解放
    //! @param : [in](none)
    //! @return : 成功した場合trueを返す
    //!-----------------------------------------------------
    bool Release(void);

    //!-----------------------------------------------------
    //! @brief : CSpriteMotionController.ChangeMotionByNameのラッパー
    //! @param : [in](const char* name) モーション名
    //! @return : 成功した場合trueを返す
    //!-----------------------------------------------------
    bool ChangeMotionByName(const char* name);
    //!-----------------------------------------------------
    //! @brief : CSpriteMotionController.GetMotionNoのラッパー
    //! @param : [in](none) none
    //! @return : モーション番号
    //!-----------------------------------------------------
    int GetMotionNo(void);
    //!-----------------------------------------------------
    //! @brief : CSpriteMotionController.IsEndMotionのラッパー
    //! @param : [in](none) none
    //! @return : モーション番号
    //!-----------------------------------------------------
    bool IsEndMotion(void);
};
}
#endif // !BR_SPRITE_H