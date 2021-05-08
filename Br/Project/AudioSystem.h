//!-----------------------------------------------------
//! @file : AudioSystem.h
//! @brief : �Q�[�����̉����̏o�͂�����
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
    //! ���O�����˂�
    std::string path;
    //! ���[�v���邩�ǂ���
    bool loop;
    //! ����
    float volume;
};
class AudioSystem {
private:
    //! �S�ēǂݍ��܂ꂽ���ǂ���
    bool _is_loaded;
    //! �����n���p
    std::mutex _mutex;

    std::unordered_map
        <std::string, std::shared_ptr<Mof::CSoundBufferBase>> _sound_buffers;
public:
    //!-----------------------------------------------------
    //! @brief : �R���g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    AudioSystem();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~AudioSystem();

    //!-----------------------------------------------------
    //! @brief : �ǂݍ��݊����t���O�擾
    //! @param : [in](none)
    //! @return :�ǂݍ��݂��S�ďI�����Ă����true��Ԃ�
    //!-----------------------------------------------------
    bool IsLoaded(void);
    //!-----------------------------------------------------
    //! @brief : �o�^����\��̃T�E���h��ǂݍ���
    //! @param : [in](const char* path) �ǂݍ��ރt�@�C���̃p�X�������ꂽ�t�@�C��
    //! @return : ���������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool Load(const char* path);
    //!-----------------------------------------------------
    //! @brief : �X�g���[���̍X�V
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    void Update(void);
    //!-----------------------------------------------------
    //! @brief : �ێ����Ă���S�ẴT�E���h�̉��
    //! @param : [in](none)
    //! @return : ���������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool Release(void);
    //!-----------------------------------------------------
    //! @brief : �����̏o�͂��˗�����
    //! @param : [in](const std::string path) �o�͂������t�@�C���̃p�X
    //! @return : none
    //!-----------------------------------------------------
    void Play(const std::string path);
    //!-----------------------------------------------------
    //! @brief : �����̒�~���˗�����
    //! @param : [in](const std::string path) ��~�������t�@�C���̃p�X
    //! @return : none
    //!-----------------------------------------------------
    void Stop(const std::string path);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="path"></param>
    bool IsPlay(const std::string path);
    //!-----------------------------------------------------
    //! @brief : �ǉ�
    //! @param : [in](const char* name) ���O
    //! @param : [in](const std::shared_ptr<Mof::CSoundBuffer>& sound) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void AddSound(const char* name,const std::shared_ptr<Mof::CSoundBufferBase>& sound);
};
}
#endif // !BR_AUDIO_SYSREM_H