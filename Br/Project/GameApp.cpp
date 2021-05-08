/*************************************************************************//*!

                    @file	GameApp.cpp
                    @brief	��{�Q�[���A�v���B

                                                            @author	�_�c�@��
                                                            @date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"



/*************************************************************************//*!
        @brief			�A�v���P�[�V�����̏�����
        @param			None

        @return			TRUE		����<br>
                        ����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
    puts("\033[7m game start \033[m \n");
    _scene_manager = std::make_shared<br::SceneManager>();
    _scene_manager->Initialize();
    return TRUE;
}
/*************************************************************************//*!
        @brief			�A�v���P�[�V�����̍X�V
        @param			None

        @return			TRUE		����<br>
                        ����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
    //�L�[�̍X�V
    g_pInput->RefreshKey();
    _scene_manager->Input();

    // �X�V
    _scene_manager->Update();
    return TRUE;
}
/*************************************************************************//*!
        @brief			�A�v���P�[�V�����̕`��
        @param			None

        @return			TRUE		����<br>
                        ����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
    //�`��J�n
    g_pGraphics->RenderStart();
    //��ʂ̃N���A
    g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
    // �`��
    _scene_manager->Render();
    //�`��̏I��
    g_pGraphics->RenderEnd();
    return TRUE;
}
/*************************************************************************//*!
        @brief			�A�v���P�[�V�����̉��
        @param			None

        @return			TRUE		����<br>
                        ����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {
    // ���
    _scene_manager->Release();
    _scene_manager.reset();
    return TRUE;
}