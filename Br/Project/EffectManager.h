//!-----------------------------------------------------
//! @file : EffectManager.h
//! @brief : �Q�[���I�u�W�F�N�g�͂�����g���ăG�t�F�N�g�𔭐�������
//! @date : 2020/07/13
//!-----------------------------------------------------


#ifndef BR_EFFECT_MANAGER_H
#define BR_EFFECT_MANAGER_H


#include <memory>
#include <string>
#include <vector>

#include "Effect.h"
#include "Scene.h"


namespace br {
class EffectManager {
private:
    std::vector<std::shared_ptr<br::Effect>> _effects;
    br::Scene* _scene;
public:
    EffectManager(br::Scene* _scene);
    ~EffectManager();

    //!-----------------------------------------------------
    //! @brief : ���O���Q�Ƃ��ăG�t�F�N�g���擾����@��������ꍇ��z�肵�Ȃ�
    //! @param : [in](const char* name) �擾�������G�t�F�N�g�̖��O
    //! @return : �����ɂ������O�����G�t�F�N�g
    //!-----------------------------------------------------
    std::shared_ptr<br::Effect>GetEffectByName(const char* name);

    bool Update(void);
    bool Render(Mof::CVector2 scroll);
    bool Release(void);

    //!-----------------------------------------------------
    //! @brief : �G�t�F�N�g����
    //! @param : [in](Mof::CVector2 scroll) �X�v���C�g�̃p�X
    //! @param : [in](Mof::CVector2 position) �\���ʒu
    //! @param : [in](Mof::CVector2 scroll) ���O
    //! @return : ���������ꍇtrue
    //!-----------------------------------------------------
    void Start(const char* path, Mof::CVector2 position, const char* name = "");
};
}
#endif // !BR_EFFECT_MANAGER_H