//!-----------------------------------------------------
//! @file : ResourceManager.h
//! @brief : ゲーム内のリソースの管理、保持をする
//! @date : 2020/05/26
//!-----------------------------------------------------


#ifndef BR_RESOURCE_MANAGER_H
#define BR_RESOURCE_MANAGER_H


#include <unordered_map>
#include <memory>
#include <mutex>

#include <Mof.h>


namespace br {
class ResourceManager {
private:
    //! 全て読み込まれたかどうか
    bool _is_loaded;
    //! 同期地蔵用
    std::mutex _mutex;


    //! 管理するテクスチャ
    std::unordered_map
        <std::string, std::shared_ptr<Mof::CTexture>> _textures;
    //! 管理するスプライトの部品
    std::unordered_map
        <std::string, std::shared_ptr<class SpritePart>> _sprite_parts;

    //! 管理する音声データ
    //std::unordered_map
      //  <std::string, std::shared_ptr<Mof::CSoundBuffer>> _sound_buffers;
    //T _next_resouce;
public:
    //!-----------------------------------------------------
    //! @brief : コンストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ResourceManager();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~ResourceManager();

    //!-----------------------------------------------------
    //! @brief : 読み込み完了フラグ取得
    //! @param : [in](none)
    //! @return :読み込みが全て終了していればtrueを返す
    //!-----------------------------------------------------
    bool IsLoaded(void);

    //!-----------------------------------------------------
    //! @brief : 読み込み済みのテクスチャを取得
    //! @param : [in](const std::string& path) ファイルのパス 
    //! @return : 読み込まれたテクスチャ
    //!-----------------------------------------------------
    std::shared_ptr<Mof::CTexture>GetTexture(
        const std::string& path);
    //!-----------------------------------------------------
    //! @brief : 読み込み済みのスプライトの部品を取得
    //! @param : [in](const std::string& path) ファイルのパス 
    //! @return : 読み込まれたスプライトの部品
    //!-----------------------------------------------------
    std::shared_ptr<class SpritePart>GetSpritePart(
        const std::string& path);
    //!-----------------------------------------------------
    //! @brief : 読み込み済みの音声データを取得
    //! @param : [in](const std::string& path) ファイルのパス 
    //! @return : 読み込み済みの音声データ
    //!-----------------------------------------------------
    //std::shared_ptr<Mof::CSoundBuffer>GetSoundBuffer(
      //  const std::string& path);

    bool Load(void);
    bool Load(const char* path);
    //!-----------------------------------------------------
    //! @brief : 保持している全てのリソースの解放
    //! @param : [in](none)
    //! @return : 成功した場合trueを返す
    //!-----------------------------------------------------
    bool Release(void);
};
}
#endif // !BR_RESOURCE_MANAGER_H