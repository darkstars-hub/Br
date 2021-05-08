//!-----------------------------------------------------
//! @file : ReverseGuage.h
//! @brief : �����𔽓]������Q�[�W
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
    //! �Q�[�W�̍ő�l
    const int _value_max;
    //! �Q�[�W�̌��݂̒l
    int _value;

    std::weak_ptr<br::ResourceManager> _resource_manager;
public:
    ReverseGuage();
    ~ReverseGuage();

    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](std::shared_ptr<br::ResourceManager> r) ���\�[�X�ێ���
    //! @return : none
    //!-----------------------------------------------------
    void SetResourceManager(std::weak_ptr<br::ResourceManager> r);
    
    //!-----------------------------------------------------
    //! @brief : �Q�[�W�����^�����ǂ���
    //! @param : [in](void) none
    //! @return : �����ł����true��Ԃ�
    //!-----------------------------------------------------
    bool IsMax(void);
    //!-----------------------------------------------------
    //! @brief : �Q�[�W���Z
    //! @param : [in](int value) �Q�[�W��������l
    //! @return : none
    //!-----------------------------------------------------
    void Add(int value);
    //!-----------------------------------------------------
    //! @brief : �Q�[�W������đ����𔽓]������
    //! @param : [in](void) none
    //! @return : �Q�[�W�������Ă��Ȃ��Ȃ�false��Ԃ��i���s����j
    //!-----------------------------------------------------
    bool Use(void);

    void Render(void);
//    void Render(Mof::CVector2 position);
};
}
#endif // !BR_REVERSE_GUAGE_H