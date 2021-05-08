//!-----------------------------------------------------
//! @file : AudioSystem.h
//! @brief : ゲーム内の音声の出力をする
//! @date : 2020/05/31
//!-----------------------------------------------------


#ifndef BR_AUDIO_SYSREM_H
#define BR_AUDIO_SYSREM_H


#include <memory>
#include <unordered_map>
#include <mutex>

#include <Mof.h>


namespace br {
struct Sound {
    //! 名前を兼ねる
    std::string path;
    //! ループするかどうか
    bool loop;
    //! 音量
    float volume;
};
class AudioSystem {
private:
    //! 全て読み込まれたかどうか
    bool _is_loaded;
    //! 同期地蔵用
    std::mutex _mutex;

    std::unordered_map
        <std::string, std::shared_ptr<Mof::CSoundBufferBase>> _sound_buffers;
public:
    //!-----------------------------------------------------
    //! @brief : コントラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    AudioSystem();
    //!-----------------------------------------------------
    //! @brief : デストラクタ
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~AudioSystem();

    //!-----------------------------------------------------
    //! @brief : 読み込み完了フラグ取得
    //! @param : [in](none)
    //! @return :読み込みが全て終了していればtrueを返す
    //!-----------------------------------------------------
    bool IsLoaded(void);
    //!-----------------------------------------------------
    //! @brief : 登録する予定のサウンドを読み込む
    //! @param : [in](const char* path) 読み込むファイルのパスが書かれたファイル
    //! @return : 成功した場合trueを返す
    //!-----------------------------------------------------
    bool Load(const char* path);
    //!-----------------------------------------------------
    //! @brief : ストリームの更新
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Update(void);
    //!-----------------------------------------------------
    //! @brief : 保持している全てのサウンドの解放
    //! @param : [in](none)
    //! @return : 成功した場合trueを返す
    //!-----------------------------------------------------
    bool Release(void);
    //!-----------------------------------------------------
    //! @brief : 音声の出力を依頼する
    //! @param : [in](const std::string path) 出力したいファイルのパス
    //! @return : none
    //!-----------------------------------------------------
    void Play(const std::string path);
    //!-----------------------------------------------------
    //! @brief : 音声の停止を依頼する
    //! @param : [in](const std::string path) 停止したいファイルのパス
    //! @return : none
    //!-----------------------------------------------------
    void Stop(const std::string path);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="path"></param>
    bool IsPlay(const std::string path);
    //!-----------------------------------------------------
    //! @brief : 追加
    //! @param : [in](const char* name) 名前
    //! @param : [in](const std::shared_ptr<Mof::CSoundBuffer>& sound) ポインタ
    //! @return : none
    //!-----------------------------------------------------
    void AddSound(const char* name,const std::shared_ptr<Mof::CSoundBufferBase>& sound);
};
}
#endif // !BR_AUDIO_SYSREM_H