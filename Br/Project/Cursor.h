//!-----------------------------------------------------
//! @file : Cursor.h
//! @brief : �Ֆʏ�̋���I�������
//! @date : 2020/05/31
//!-----------------------------------------------------


#ifndef BR_CURSOR_H
#define BR_CURSOR_H


#include "Actor.h"
#include "Tile.h"


namespace br {
struct DirectionWait {
    const int max = 4;
    const int max_hold = 4;
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    int hold = 0;
};
class Cursor : public br::Actor {
    using super = br::Actor;
public:
    enum class Mode {
        Normal, // �ʏ�ړ�
        Limit, // ���͈͓��̂��̂�I�����鎞
    };
private:
    //! ����{�^�����������t���O
    bool _is_enter;
    //! �߂�{�^�����������t���O
    bool _is_back;
    //! �J�[�\���ړ��҂�����
    DirectionWait _wait;
    //! �I�����Ă��郆�j�b�g
    class Unit* _select_unit;
    //! �ړ��\�Ȑ����͈� ���͐����Ȃ�
    std::vector<br::Tile*> _limit_range;
    //! �U������I�����[�h
    br::Cursor::Mode _mode;

    void WaitCountIncrement(void);
    void WaitCountIncrementGamePad(Mof::LPGamePad pad);
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Scene* scene) ���݂̃V�[��
    //! @param : [in](Mof::CVector2* scroll) �V�[���̃X�N���[���l�̃A�h���X
    //! @return : none
    //!-----------------------------------------------------
    Cursor(br::Scene* scene, Mof::CVector2* scroll);
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Cursor();

    virtual br::ActorState GetState(void) const override;
    virtual Mof::CVector2 GetPosition(void) const override;


    //!-----------------------------------------------------
    //! @brief : �Z�b�^�[
    //! @param : [in](br::Actor* unit) �I�񂾃��j�b�g
    //! @return : none
    //!-----------------------------------------------------
    void SetSelectUnit(br::Actor* unit);

    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](none) none
    //! @return : ���̃t���[�����Ɍ���{�^�������������ǂ���
    //!-----------------------------------------------------
    bool IsEnter(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](none) none
    //! @return : ���̃t���[�����ɖ߂�{�^�������������ǂ���
    //!-----------------------------------------------------
    bool IsBack(void) const;
    //!-----------------------------------------------------
    //! @brief : �J�[�\�������m��I���\�����ׂ�
    //! @param : [in](none) none
    //! @return : �\�ł����true��Ԃ�
    //!-----------------------------------------------------
    bool CanSelect(void) const;
    //!-----------------------------------------------------
    //! @brief : ���̈ʒu���I�����j�b�g�̈ړ��\�͈͂��𒲂ׂ�
    //! @param : [in](none) none
    //! @return : �����Ă����true��Ԃ�
    //!-----------------------------------------------------
    bool InMovableRange(br::Tile* tile) const;
    //!-----------------------------------------------------
    //! @brief : ���̈ʒu���I�����j�b�g�̍U���\�͈͂��𒲂ׂ�
    //! @param : [in](none) none
    //! @return : �����Ă����true��Ԃ�
    //!-----------------------------------------------------
    bool InAttackRange(br::Tile* tile) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](none) none
    //! @return : �I�𒆂̃��j�b�g
    //!-----------------------------------------------------
    class Unit* GetSelectUnit(void);
    //!-----------------------------------------------------
    //! @brief : �J�[�\���̐^���ɂ��郆�j�b�g��Ԃ�
    //! @param : [in](none) none
    //! @return : ���Ȃ��Ȃ�nullptr��Ԃ�
    //!-----------------------------------------------------
    class Unit* GetUnderUnit(void);

    br::Cursor::Mode GetMode(void);
    std::vector<br::Tile*>& GetLimitRange(void);

    //!-----------------------------------------------------
    //! @brief : �ړ����[�h�ύX
    //! @param : [in](std::vector<br::Tile*>& range) ���̏�Ԃł̐����͈�
    //! @return : �I�𒆂̃��j�b�g
    //!-----------------------------------------------------
    void ChangeMode(br::Cursor::Mode mode, std::vector<br::Tile*>& range);

    //!-----------------------------------------------------
    //! @brief : ���͏����@���j���[�\�����͎��s����Ȃ�
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Input(void) override;
    //!-----------------------------------------------------
    //! @brief : �X�V
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Update(void) override;
    //!-----------------------------------------------------
    //! @brief : �`��
    //! @param : [in](Mof::CVector2 scroll) �X�N���[���l
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Render(Mof::CVector2 scroll) override;
};
}
#endif // !BR_CURSOR_H