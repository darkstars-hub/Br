//!-----------------------------------------------------
//! @file : TextSystem.h
//! @brief : �e�L�X�g��\��������
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
    //! �����t�H���g
    Mof::CFont _font;
    //! �e�L�X�g�\����
    Mof::CRectangle _window;
    //! �\���t���O
    bool _is_show;
    //! �\������e�L�X�g
    std::vector<std::string> _texts;
    //! �\������e�L�X�g�̃C���f�b�N�X
    size_t _index;
    //! �\�����镶����
    size_t _text_index;
    //! �`�悷��e�N�X�`���̃p�X
    std::vector<std::string> _texture_paths;
    //! �`�悷��e�N�X�`��UV
    std::vector<Mof::CRectangle> _rectangles;
    //! �e�N�X�`����`�悷��ʒu
    std::vector<Mof::CVector2> _positions;
    //! �`��e�N�X�`���𔽓]���邩�̃t���O
    std::vector<bool> _reverses;
    //! ���\�[�X�ێ�
    std::weak_ptr<br::ResourceManager> _resource_manager;
    //! �e�L�X�g��i�߂����̉�
    Mof::CSoundBuffer _sound;
    //! �e�L�X�g�I�����Ɏ��s����֐�
    std::function<void(void)> _end_event;
    //! �e�L�X�g��S�ĕ\���������ǂ���
    //bool _all_show;
public:
    TextSystem();
    ~TextSystem();

    void SetResourceManager(std::shared_ptr<br::ResourceManager>r);

    //!-----------------------------------------------------
    //! @brief : �\����Ԏ擾
    //! @param : [in](void) none
    //! @return : �\�����Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsShow(void)const;
    //!-----------------------------------------------------
    //! @brief : �e�L�X�g�f�[�^��ǂݍ��݁A�\����Ԃɂ���
    //! @param : [in](const char* path) �p�X
    //! @return : none
    //!-----------------------------------------------------
    void Show(const char* path, std::function<void(void)>lambda = []() {});
    void Show(const std::string& text, std::function<void(void)>lambda = []() {});
    //!-----------------------------------------------------
    //! @brief : ��\����Ԃ���
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