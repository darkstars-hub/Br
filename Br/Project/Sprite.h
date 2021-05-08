//!-----------------------------------------------------
//! @file : Sprite.h
//! @brief : �A�j���[�V��������摜�̏W�� �g���q�u~.sprite�v������
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
    //! �Q�Ƃ���t�@�C���ւ̃p�X
    std::string _directory_path;
    //! �`��摜
    std::weak_ptr<Mof::CTexture> _texture;
    //! �A�j���[�V�����̕��i�ASprite���Q�Ƃ���
    std::vector<Mof::SpriteAnimationCreate> _anims;
    //! ���[�V�����ԍ��ƃ��[�V�������̃e�[�u��
    //std::unordered_map<std::string, int> _motion_map;
    std::unordered_map<int, std::string> _motion_map;
    //!-----------------------------------------------------
    //! @brief : Load()�ɌĂ΂�� �A�j���[�V�����쐬
    //! @param : [in](const rapidjson::Document& document) �ǂݍ��݃f�[�^
    //! @param : [in](ResourceManager& r) �e�N�X�`���擾�� 
    //! @return : none
    //!-----------------------------------------------------
    void LoadAnimation(const rapidjson::Document& document, class ResourceManager& r);
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    SpritePart();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~SpritePart();

    std::weak_ptr<Mof::CTexture> GetTexture(void);
    std::vector<Mof::SpriteAnimationCreate>& GetAnimsAddress(void);
    //std::unordered_map<std::string, int>& GetMotionMapAddress(void);
    std::unordered_map<int,std::string>& GetMotionMapAddress(void);

    //!-----------------------------------------------------
    //! @brief : �ǂݍ���
    //! @param : [in](const char* path) �t�@�C���̃p�X 
    //! @param : [in](ResourceManager& r) �e�N�X�`���擾�� 
    //! @return : �ǂݍ��݂ɐ��������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool Load(const char* path, class ResourceManager& r);
    //!-----------------------------------------------------
    //! @brief : �ێ����Ă���S�Ẵ��\�[�X�̉��
    //! @param : [in](none)
    //! @return : ���������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool Release(void);
};
class Sprite {
private:
    //! �`��摜
    std::weak_ptr<Mof::CTexture> _texture;
    //! �J�ڂ���A�j���[�V�����̕ϓ��l��ێ�
    Mof::CSpriteMotionController _motion;
    //! ���[�V�����ԍ��ƃ��[�V�������̃e�[�u�� ���̂�SpritePart������
    //std::unordered_map<std::string, int>* _motion_map;
    std::unordered_map<int,std::string>* _motion_map;
    //! ���݂̃��[�V�����ԍ�
    //int _current_no;
    //! �A�j���[�V�����f�[�^�̃L���b�V��
    bool _reverse_x;
public:
    //SpritePart* _p;

    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Sprite();
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~Sprite();


    void SetReverseX(bool reverse);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ���[�V�����ԍ��ƃ��[�V�������̃e�[�u���̃|�C���^
    //!-----------------------------------------------------
    //std::unordered_map<std::string, int>* GetMotionMap(void) {
    std::unordered_map<int, std::string>* GetMotionMap(void);
    //!-----------------------------------------------------
    //! @brief : CSpriteMotionController::GetSrcRect�̃��b�p�[
    //! @param : [in](void) none
    //! @return : �\�����̋�`
    //!-----------------------------------------------------
    Mof::CRectangle GetSrcRect(void) ;
    //!-----------------------------------------------------
    //! @brief : �ǂݍ���
    //! @param : [in](const char* path) �t�@�C���̃p�X 
    //! @param : [in](ResourceManager& r) �e�N�X�`���擾�� 
    //! @return : �ǂݍ��݂ɐ��������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool Load(const char* path, class ResourceManager& r);
    //!-----------------------------------------------------
    //! @brief : �ǂݍ���
    //! @param : [in](br::SpritePart& part) ���i�̎Q�� 
    //! @return : �ǂݍ��݂ɐ��������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool Load(br::SpritePart& part);
    //!-----------------------------------------------------
    //! @brief : �A�j���[�V�����̒l�Ȃǂ̍X�V
    //! @param : [in](void) none 
    //! @return : none
    //!-----------------------------------------------------
    void Update(void);
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](const Mof::Vector2 position) �`��ʒu 
    //! @return : none
    //!-----------------------------------------------------
    void Render(const Mof::Vector2 position);
    //!-----------------------------------------------------
    //! @brief : �ێ����Ă���S�Ẵ��\�[�X�̉��
    //! @param : [in](none)
    //! @return : ���������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool Release(void);

    //!-----------------------------------------------------
    //! @brief : CSpriteMotionController.ChangeMotionByName�̃��b�p�[
    //! @param : [in](const char* name) ���[�V������
    //! @return : ���������ꍇtrue��Ԃ�
    //!-----------------------------------------------------
    bool ChangeMotionByName(const char* name);
    //!-----------------------------------------------------
    //! @brief : CSpriteMotionController.GetMotionNo�̃��b�p�[
    //! @param : [in](none) none
    //! @return : ���[�V�����ԍ�
    //!-----------------------------------------------------
    int GetMotionNo(void);
    //!-----------------------------------------------------
    //! @brief : CSpriteMotionController.IsEndMotion�̃��b�p�[
    //! @param : [in](none) none
    //! @return : ���[�V�����ԍ�
    //!-----------------------------------------------------
    bool IsEndMotion(void);
};
}
#endif // !BR_SPRITE_H