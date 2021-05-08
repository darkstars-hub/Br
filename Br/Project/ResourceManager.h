//!-----------------------------------------------------
//! @file : ResourceManager.h
//! @brief : �Q�[�����̃��\�[�X�̊Ǘ��A�ێ�������
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
    //! �S�ēǂݍ��܂ꂽ���ǂ���
    bool _is_loaded;
    //! �����n���p
    std::mutex _mutex;


    //! �Ǘ�����e�N�X�`��
    std::unordered_map
        <std::string, std::shared_ptr<Mof::CTexture>> _textures;
    //! �Ǘ�����X�v���C�g�̕��i
    std::unordered_map
        <std::string, std::shared_ptr<class SpritePart>> _sprite_parts;

    //! �Ǘ����鉹���f�[�^
    //std::unordered_map
      //  <std::string, std::shared_ptr<Mof::CSoundBuffer>> _sound_buffers;
    //T _next_resouce;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ResourceManager();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~ResourceManager();

    //!-----------------------------------------------------
    //! @brief : �ǂݍ��݊����t���O�擾
    //! @param : [in](none)
    //! @return :�ǂݍ��݂��S�ďI�����Ă����true��Ԃ�
    //!-----------------------------------------------------
    bool IsLoaded(void);

    //!-----------------------------------------------------
    //! @brief : �ǂݍ��ݍς݂̃e�N�X�`�����擾
    //! @param : [in](const std::string& path) �t�@�C���̃p�X 
    //! @return : �ǂݍ��܂ꂽ�e�N�X�`��
    //!-----------------------------------------------------
    std::shared_ptr<Mof::CTexture>GetTexture(
        const std::string& path);
    //!-----------------------------------------------------
    //! @brief : �ǂݍ��ݍς݂̃X�v���C�g�̕��i���擾
    //! @param : [in](const std::string& path) �t�@�C���̃p�X 
    //! @return : �ǂݍ��܂ꂽ�X�v���C�g�̕��i
    //!-----------------------------------------------------
    std::shared_ptr<class SpritePart>GetSpritePart(
        const std::string& path);
    //!-----------------------------------------------------
    //! @brief : �ǂݍ��ݍς݂̉����f�[�^���擾
    //! @param : [in](const std::string& path) �t�@�C���̃p�X 
    //! @return : �ǂݍ��ݍς݂̉����f�[�^
    //!-----------------------------------------------------
    //std::shared_ptr<Mof::CSoundBuffer>GetSoundBuffer(
      //  const std::string& path);

    bool Load(void);
    bool Load(const char* path);
    //!-----------------------------------------------------
    //! @brief : �ێ����Ă���S�Ẵ��\�[�X�̉��
    //! @param : [in](none)
    //! @return : ���������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool Release(void);
};
}
#endif // !BR_RESOURCE_MANAGER_H