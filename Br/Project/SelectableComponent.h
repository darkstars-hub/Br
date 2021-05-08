//!-----------------------------------------------------
//! @file : SelectableComponent.h
//! @brief : Actor�����J�[�\���ɑI�΂��@�\
//! @date : 2020/06/09
//!-----------------------------------------------------


#ifndef BR_SELECTABLE_COMPONENT_H
#define BR_SELECTABLE_COMPONENT_H


#include "UpdateComponent.h"

#include "Actor.h"
#include "Cursor.h"


namespace br {

    //! �I��p�C�x���g�o�^
using OnEventFunc = std::function<bool(void)>;
using OnEventPair = std::pair<std::string, OnEventFunc>;
class OnEvent : public std::vector<std::pair<std::string, OnEventFunc>> {
public:
    //!-----------------------------------------------------
    //! @brief : �C�x���g�̓o�^
    //! @param : [in](std::pair<std::string, OnEventFunc> val) �C�x���g�̓o�^
    //!-----------------------------------------------------
    void Register(const char* key, OnEventFunc fn) {
        //�����L�[�ł̏d���o�^���
        if (std::find_if(this->begin(), this->end(), [&](auto& t) {return key == t.first; }) != this->end()) { return; }
        this->push_back(std::make_pair(key, fn));
    }
    void operator += (OnEventPair val) {
        //�����L�[�ł̏d���o�^���
        if (std::find_if(this->begin(), this->end(), [&](auto& t) {return val.first == t.first; }) != this->end()) { return; }
        this->push_back(val);
    }

    //!-----------------------------------------------------
    //! @brief : �C�x���g�̍폜
    //! @param : [in](const char* key) �폜����C�x���g�̃L�[
    //!-----------------------------------------------------
    void operator -= (const char* key) {
        this->erase(std::remove_if(this->begin(), this->end(), [&](auto& v) {return v.first == key; }), this->end());
    }
    void operator -= (std::string& key) {
        this->erase(std::remove_if(this->begin(), this->end(), [&](auto& v) {return v.first == key; }), this->end());
    }
    void MatchRemove(const char* key) {
        // �p�^�[���}�b�`��S�폜
        this->erase(std::remove_if(this->begin(), this->end(), [&](auto& v) {return v.first.find(key) != std::string::npos; }), this->end());
    }
    //!-----------------------------------------------------
    //! @brief : �o�^�C�x���g�̎��s
    //! @param : [in](void) none
    //! @return : �C�x���g���ŏ����I���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool operator ()(void) {
        for (auto& fn : *this) {
            if (fn.second()) {
                return true;
            } // if
        } // for
        return false;
    }
};
//! �J�[�\�������C�x���g�o�^
class ICursor {
public:
    OnEvent		onCursor;
};
//! �I�����C�x���g�o�^
class ISelect {
public:
    OnEvent		onSelect;
};
//! ���莞�C�x���g�o�^
class IDecide {
public:
    OnEvent		onDecide;
};
//! �U�����C�x���g�o�^
//class IAttackCancel {
//class IAttack {
//public:
//    OnEvent		onAttack;
//};
//! �L�����Z�����C�x���g�o�^
class ICancel {
public:
    OnEvent		onCancel;
};
//! �I�����C�x���g�o�^
class IEnd {
public:
    OnEvent		onEnd;
};
//! �C�x���g�ꊇ�p��
class IUnitEvent : public ICursor, public ISelect, public IDecide, public ICancel, public IEnd {
private:
    std::vector<std::string> delkey;
public:
    //!-----------------------------------------------------
    //! @brief : �C�x���g�̍폜
    //! @param : [in](const char* key) �폜����C�x���g�̃L�[
    //!-----------------------------------------------------
    void MatchRemove(const char* key) {
        //onDefault.MatchRemove(key);
        onCursor.MatchRemove(key);
        onSelect.MatchRemove(key);
        onDecide.MatchRemove(key);
        onCancel.MatchRemove(key);
        onEnd.MatchRemove(key);
    }

    void MatchRemoveDelay(const char* key) {
        delkey.push_back(key);
    }

    void doRemove() {
        if (delkey.empty()) {
            return;
        } //if
        for (auto& str : delkey) {
            MatchRemove(str.c_str());
        } //for
        delkey.clear();
    }
};

class SelectableComponent : public UpdateComponent {
    using super = br::UpdateComponent;
private:
    //! �J�[�\���̃|�C���^
    br::Cursor* _cursor;
    //! �I������Ă�����
    bool _is_select;
    //! �J�[�\���̉��ɂ�����
    bool _under_cursor;
    //! �I�����ꂽ��ԂŌ���{�^���������ꂽ
    bool _is_decide;

public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Actor* owner) ���̋@�\�̏��L��
    //! @param : [in](int priority) �����D�揇�� 0�ɋ߂��قǍ���
    //! @return : none
    //!-----------------------------------------------------
    SelectableComponent(Actor* owner, int priority = 100);
    virtual ~SelectableComponent();


        //!-----------------------------------------------------
    //! @brief : �I������Ă����Ԃ�Ԃ�
    //! @param : [in](void) none
    //! @return : �I�΂�Ă���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    //bool SetSelected(void);
    //!-----------------------------------------------------
    //! @brief : �J�[�\���̉��ɂ����Ԃ�Ԃ�
    //! @param : [in](void) none
    //! @return : ���ɂ���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    //bool SetUnderCursor(void);
    //!-----------------------------------------------------
    //! @brief : �I�����ꂽ��ԂŌ���{�^���������ꂽ���ǂ�����Ԃ�
    //! @param : [in](void) none
    //! @return : �m�肳��Ă���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    //bool SetDecide(void);
    //!-----------------------------------------------------
    //! @brief : �I������Ă����Ԃ�Ԃ�
    //! @param : [in](void) none
    //! @return : �I�΂�Ă���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsSelected(void);
    //!-----------------------------------------------------
    //! @brief : �J�[�\���̉��ɂ����Ԃ�Ԃ�
    //! @param : [in](void) none
    //! @return : ���ɂ���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsUnderCursor(void);
    //!-----------------------------------------------------
    //! @brief : �I�����ꂽ��ԂŌ���{�^���������ꂽ���ǂ�����Ԃ�
    //! @param : [in](void) none
    //! @return : �m�肳��Ă���Ȃ�true��Ԃ�
    //!-----------------------------------------------------
    bool IsDecide(void);
        //!-----------------------------------------------------
    //! @brief : �J�[�\���̃|�C���^��o�^����
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    //void RegisterCursor(br::Cursor* cursor);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �J�[�\���̃|�C���^
    //!-----------------------------------------------------
    br::Cursor* GetCursor(void);
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �J�[�\���̈ʒu
    //!-----------------------------------------------------
    Mof::CVector2 GetCursorPosition(void);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;

    virtual br::Component* Clone(void) override;
};
}
#endif // !BR_SELECTABLE_COMPONENT_H