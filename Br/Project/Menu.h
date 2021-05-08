//!-----------------------------------------------------
//! @file : Menu.h
//! @brief : ���j���[���N���X
//! @date : 2020/06/15
//!-----------------------------------------------------


#ifndef BR_MENU_H
#define BR_MENU_H


#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "Scene.h"
#include "Unit.h"
#include "MenuItem.h"
#include "ResourceManager.h"
#include "MenuMessage.h"


namespace br {
class MenuTextures {
    friend class Menu;
    friend class MenuItem;
    std::shared_ptr<Mof::CTexture> _text;
public:
    bool Load(std::shared_ptr<br::ResourceManager> ptr) {
        _text = ptr->GetTexture("Resource/textures/text.png");
        return true;
    }
    void Release(void) {
        _text.reset();
    }
};
class Menu {
private:
protected:
    br::Scene* _scene;
    bool _is_show;
    Mof::CVector2 _position;
    int _index;
    //class Unit* _target;

    br::MenuTextures _textures;
    std::vector<br::MenuItem> _items;

//    std::vector<br::MenuListenerComponent*> _listeners;
//    br::Menu* _child;


    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �\�����镶���̑傫��
    //!-----------------------------------------------------
    size_t GetTextSize(void)const;

    //!-----------------------------------------------------
    //! @brief : ���ݑI�𒆂̍��ڂ����s����
    //! @param : [in](void) none 
    //! @return : none
    //!-----------------------------------------------------
    virtual void Decide(void) = 0;
    //!-----------------------------------------------------
    //! @brief : ���ƁJ����������Ƃ��ɓ���
    //! @param : [in](void) none 
    //! @return : none
    //!-----------------------------------------------------
    virtual void Cancel(void) = 0;
public:
    Menu(br::Scene* scene);
    virtual ~Menu();

    //!-----------------------------------------------------
    //! @brief : �\����Ԏ擾
    //! @param : [in](void) none
    //! @return : �\�����Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsShow(void);
    //!-----------------------------------------------------
    //! @brief : �\����Ԃ���
    //! @param : [in](class Unit* ptr) ���j���[��\�������l
    //! @return : none
    //!-----------------------------------------------------
  //  virtual void Show(class Unit* ptr);
    virtual void Show(br::MenuMessage* event) = 0;
    //!-----------------------------------------------------
    //! @brief : ��\����Ԃ���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual   void Hide(void) = 0;

    Mof::CVector2 GetPosition(void);
    int GetIndex(void);
    //!-----------------------------------------------------
    //! @brief : �w�i�̋�`�擾
    //! @param : [in](void) none
    //! @return : �w�i�̋�`
    //!-----------------------------------------------------
    Mof::CRectangle GetBackRect(void);



    bool Load(void);
    bool Input(void);
    //!-----------------------------------------------------
    //! @brief : �X�V
    //! @param : [in](void) none
    //! @return : �\������Ă��Ȃ��Ƃ���false��Ԃ�
    //!-----------------------------------------------------
    bool Update(void);
    bool Render(void);

    //!-----------------------------------------------------
    //! @brief : ���ڂ��Q�Ƃ���Ƃ��̃C���f�b�N�X�����炷
    //! @param : [in](const int count) ���炷�l
    //! @return : none
    //!-----------------------------------------------------
    virtual void ShiftIndex(const int count);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    void Release(void);
};
}
#endif // !BR_MENU_H