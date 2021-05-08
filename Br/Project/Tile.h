//!-----------------------------------------------------
//! @file : Stage.h
//! @brief : ������Ֆʂ̈��� Stage�ɊǗ������
//! @date : 2020/05/30
//!-----------------------------------------------------


#ifndef BR_TILE_H
#define BR_TILE_H


#include "Actor.h"

#include <string>
#include <memory>
#include <array>
#include <vector>

#include <Mof.h>

#include "Helper.h"
#include "Common.h"
//#include "Unit.h"

namespace br {
class Unit;
class Tile : public br::Actor {
    using super = br::Actor;
    //! ���̃^�C���ɗאڂ���(����Tile���猩����)�n�`�̔z��
    //! �e�v�f��array[(int)direction]�Ɋi�[����
    using tile_array = std::array<br::Tile*, static_cast<int>(br::Direction::CountMax)>;
private:
    //! ��ގ��ʔԍ�
    int _type;
    //! ���O
    const char* _name;
    //! �n�`�R�X�g
    int _cost;
    //! �אڂ���(����Tile���猩����)�n�`�Ƃ��̕���
    tile_array _adjacents;
    //! �� �f�o�b�O�p
    int _col;
    //! �s �f�o�b�O�p
    int _row;

    //! ��ɏ���Ă�l
    //UnitManager* _unit_manager;
public:
    //!-----------------------------------------------------
    //! @brief : �R���X�g���N�^
    //! @param : [in](br::Scene* scene) ���݂̃V�[��
    //! @param : [in](int type) �^�C���̎��
    //! @return : none
    //!-----------------------------------------------------
    Tile(br::Scene* scene, int type);
    //!-----------------------------------------------------
    //! @brief : �f�X�g���N�^
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    virtual ~Tile();

    virtual br::ActorState GetState(void) const override;
    virtual Mof::CVector2 GetPosition(void) const override;

        //!-----------------------------------------------------
    //! @brief : �����ɏ���Ă���Unit�̃|�C���^���擾
    //! @param : [in](void) none
    //! @return : ���Ȃ��ꍇnullptr
    //!-----------------------------------------------------
    Unit* GetOnUnit(void);

    def::Vector2i GetGridPosition(void);

    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : ���O
    //!-----------------------------------------------------
    //std::string GetName(void) const;
    const char* GetName(void) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �n�`�R�X�g
    //!-----------------------------------------------------
    int GetCost(void) const;
    int GetCost(class Unit* ptr) const;
    //!-----------------------------------------------------
    //! @brief : �Q�b�^�[
    //! @param : [in](void) none
    //! @return : �אڂ���^�C���Q
    //!-----------------------------------------------------
    br::Tile::tile_array& GetAdjacents(void);
    //!-----------------------------------------------------
    //! @brief : ���ݗ�������֎~���ǂ���
    //! @param : [in](br::Unit* ptr) �ʂ肽���l
    //! @return : �����ǂ���Ă��Ȃ���΁A������ʂ��Ȃ�true��Ԃ�   
    //!-----------------------------------------------------
    bool IsBlocked(void);
    bool IsBlocked(Unit* ptr);

    //!-----------------------------------------------------
    //! @brief : ������
    //! @param : [in](void) none
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    virtual bool Initialize(const br::ActorBaseState& base);
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

    //!-----------------------------------------------------
    //! @brief : �אڂ���Tile�̓o�^
    //! @param : [in](br::Direction direction) ����
    //! @param : [in](Tile* tile) �|�C���^
    //! @return : none
    //!-----------------------------------------------------
    void RegisterAdjacent(br::Direction direction, Tile* tile);
    //!-----------------------------------------------------
    //! @brief : �^�C���̗�ƍs�������������ׂ�
    //! @param : [in](br::Tile* r) ��r�Ώ�
    //! @return : �����񂩂����s�ł����true��Ԃ�
    //!-----------------------------------------------------
    bool Equal(br::Tile* r);
};
}
#endif // !BR_TILE_H