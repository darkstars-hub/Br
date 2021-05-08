#include "BattleSystem.h"

#include "DamageCalculator.h"
#include "EffectManager.h"
#include "AudioSystem.h"


br::BattleSystemUnit* br::BattleSystem::GetAttackerUnit(void) {
    auto& attacker = _player_unit.IsAttacker() ?
        _player_unit :
        _enemy_unit;
    return &attacker;
}

br::BattleSystemUnit* br::BattleSystem::GetTargetUnit(void) {
    auto& target = !_player_unit.IsAttacker() ?
        _player_unit :
        _enemy_unit;
    return &target;
}

bool br::BattleSystem::UpdateSystem(void) {
    _in_alpha -= 10;
    if (0 < _in_alpha) {
        return false;
    } // if
    // ��ʐ^�����Ńo�g����ʏI��
    if (_out_alpha >= 255) {
        if (!_result_text.IsShow()) {
            _is_show = false;
            auto a = _scene->GetAudioSystem();
            a->Play("Resource/bgm/stage0.mp3");
            a->Stop("Resource/bgm/battle.mp3");
        } // if
    } // if


    return true;
}

void br::BattleSystem::UpdateFade(void) {
        //auto attacker = this->GetAttackerUnitData();
    //auto em = attacker->GetScene()->GetEffectManager();
    //auto e = em->GetEffectByName("miss") ? em->GetEffectByName("miss")->IsEndMotion() : true;
    // �������������Ɏ��s����Ă���


    // �U�����������Ɏ��s����Ă���
    // Hp�̕\�����I����Ă���
    // �e�L�X�g��\�����I����Ă����
    // �t�F�[�h�A�E�g�̃A���t�@�l�𑝉�
    if (_attacker_excuted &&
        _counter_attack &&
        _player_hp.GetAlpha() <= 0 &&
        _enemy_hp.GetAlpha() <= 0 &&
        !_result_text.IsShow()) {
        _out_alpha += 10;
    } // if
}

void br::BattleSystem::RenderFadeIn(void) {
    ::CGraphicsUtilities::
        RenderFillRect(0.0f,
                       0.0f,
                       ::g_pFramework->GetWindow()->GetWidth(),
                       ::g_pFramework->GetWindow()->GetHeight(),
                       MOF_ARGB(_in_alpha, 0, 0, 0));
}

void br::BattleSystem::RenderFadeOut(void) {
    ::CGraphicsUtilities::
        RenderFillRect(0.0f,
                       0.0f,
                       ::g_pFramework->GetWindow()->GetWidth(),
                       ::g_pFramework->GetWindow()->GetHeight(),
                       MOF_ARGB(_out_alpha, 0, 0, 0));
}

void br::BattleSystem::RenderFade(void) {
    auto attacker_sprite_IsEndMotion = _player_unit.IsAttacker() ?
        _player_unit.IsEndMotion() :
        _enemy_unit.IsEndMotion();
    auto target_sprite_IsEndMotion = !_player_unit.IsAttacker() ?
        _player_unit.IsEndMotion() :
        _enemy_unit.IsEndMotion();
    // ���̉�ʂɓ���Ƃ��̑J�ڌ��ʕ\��
    if (attacker_sprite_IsEndMotion &&
        _counter_attack) {
        this->RenderFadeOut();
    } // if
    // ���̉�ʂ��I���Ƃ��̑J�ڌ��ʕ\��
    if (0 < _in_alpha) {
        this->RenderFadeIn();
    } // if
}

void br::BattleSystem::RenderHp(br::BattleSystemHp hp) {
    auto attacker = this->GetAttackerUnit()->GetUnit();
    auto target = this->GetTargetUnit()->GetUnit();

    if (0 < hp.GetAlpha()) {

        if (_player_unit.IsTarget()) {
            hp.Render(_player_unit.GetPosition(),
                      *attacker,
                      *target);
        } // if
        else {
            hp.Render(_enemy_unit.GetPosition(),
                      *attacker, *target);
        } // else
    } // if
}

void br::BattleSystem::AttackSuccess(br::Unit* attacker, br::Unit* target) {
    auto a = attacker->GetComponent<br::UnitAttackComponent>();
//a->Attack();
    br::DamageCalculator c;
    int value = c.Calculation((*attacker), *target);
    target->Damege(value);

    // �U�����ꂽ����\����Ԃ�
    if (_player_hp.GetUnit()->IsAttacker()) {
        _enemy_hp.IncrementAlpha(255);
    } // if
    else {
        _player_hp.IncrementAlpha(255);
    } // else 
}

void br::BattleSystem::AttackFailure(br::Unit* attacker, br::Unit* target) {

    auto pos = _player_unit.IsAttacker() ?
        _player_unit.GetPosition() :
        _enemy_unit.GetPosition();
    // �G�t�F�N�g�͕��iUIWindow�̃T�C�Y�����炵�ĕ\������Ă���
    pos.y -= def::kUIWindowOffset;

    auto e = attacker->GetScene()->GetEffectManager();
    e->Start("Resource/sprites/miss_effect/miss_effect.sprite", pos, "miss");
}

br::BattleSystem::BattleSystem() :
    _scene(nullptr),
    _is_show(false),
    _back_path(),
    _resource_manager(),
    _attacker_excuted(false),
    _in_alpha(255),
    _out_alpha(0),
    _enemy_hp(),
    _player_hp(),
    _player_unit(),
    _enemy_unit(),
    _player_info(),
    _enemy_info(),
    _result_text(),
    _counter_attack(false) {
}

br::BattleSystem::~BattleSystem() {
}

void br::BattleSystem::Initialize(std::weak_ptr<br::ResourceManager> r) {
    this->_resource_manager = r;
    _player_unit.SetResourceManager(r);
    _enemy_unit.SetResourceManager(r);
}

bool br::BattleSystem::IsShow(void) {
    return this->_is_show;
}

void br::BattleSystem::Show(br::Unit* attacker, br::Unit* target) {
    _ASSERT_EXPR(attacker->GetTeam() != target->GetTeam(), L"���m�������Ă͂����Ȃ�");
    this->_is_show = true;
    _scene = attacker->GetScene();
    auto a = _scene->GetAudioSystem();
    a->Stop("Resource/bgm/stage0.mp3");
    a->Play("Resource/bgm/battle.mp3");

    // �U�����d�|���������v���C���[�̎�
    if (attacker->GetTeam() == def::kPlayerTeam) {
        _player_unit.Initialize(attacker, { 250.0f, 500.0f }, true, &_enemy_unit);
        _enemy_unit.Initialize(target, { 650.0f, 300.0f }, false, &_player_unit);
    } // if
    // �U�������G�l�~�[�̏ꍇ
    else {
        _player_unit.Initialize(target, { 250.0f, 500.0f }, false, &_enemy_unit);
        _enemy_unit.Initialize(attacker, { 650.0f, 300.0f }, true, &_player_unit);

    } // else
    _player_unit.MakeControlPoint();
    _enemy_unit.MakeControlPoint();


    _back_path = std::string("Resource/textures/back_ground_1.png");
    _player_hp.Initialize(_resource_manager, &_player_unit);
    _enemy_hp.Initialize(_resource_manager, &_enemy_unit);
    _attacker_excuted = false;
    _in_alpha = 255;
    _out_alpha = 0;
    //_counter_attack = false;
    _counter_attack = false;
//    _counter_excuted = false;

    // �����ʒu�ݒ�
    auto  size = _player_info.GetSize();
    _player_info.SetUnit(&_player_unit);
    _player_info.SetPosition(Mof::CVector2(0.0f, 0.0f));
    _enemy_info.SetUnit(&_enemy_unit);
    _enemy_info.SetPosition(Mof::CVector2(::g_pFramework->GetWindow()->GetWidth() - size.x, 0.0f));
}

bool br::BattleSystem::Input(void) {
    _result_text.Input();
    return true;
}

bool br::BattleSystem::Update(void) {
    // ��ʑJ�ڌ��ʂ��I����Ă��珈�������s����
    if (!this->UpdateSystem()) {
        return true;
    } // if
    this->UpdateFade();

    auto attack_end = _player_unit.IsAttacker() ?
        _player_unit.IsEndMotion() :
        _enemy_unit.IsEndMotion();

    // �U�����̃��[�V�������I��������̂ݏ�������
    if (attack_end) {
        // �_���[�W�����͂P�x����
        if (!_attacker_excuted) {
            auto attacker = this->GetAttackerUnit()->GetUnit();
            auto target = this->GetTargetUnit()->GetUnit();
            _attacker_excuted = true;

            int hit = attacker->GetStateComponent()->GetStatus()->GetHit();
            int avoid = target->GetStateComponent()->GetStatus()->GetAvoid();
            // �U���������������@0����100�͈̔͂Ő��l�𐶐������̒l�����ۂ̖��������Ⴏ��Γ�����
            if (ut::GenerateRandom(0, 100) < hit - avoid) {
                this->AttackSuccess(attacker, target);
            } // f
            // �U�����O�ꂽ��
            else {
                this->AttackFailure(attacker, target);
            } // else
            // �U���A�N�V�������I�������onEnd���Ă�
            attacker->onEnd();
            // �U�����ꂽ���̔����J�n
            /*if (target->GetState() != br::ActorState::Dead) {
                _counter_attack = true;
            } */// if
            if (_counter_attack) {
                _result_text.Show(std::string("�U���I��"));
            } // if
        } // if
        // Hp�̕\����
        else {
            // �U�����ꂽ���̃A���t�@�l�����炷
            if (_player_hp.GetAlpha() > 0) {
                _player_hp.DecrementAlpha(3);
            } // if
            else if (_enemy_hp.GetAlpha() > 0) {
                _enemy_hp.DecrementAlpha(3);
            } // else if
        } // else
    } // if

    auto target = this->GetTargetUnit()->GetUnit();
    // �W�I������������
    if (!_counter_attack && this->GetAttackerUnit()->AttackEnd()) {
        _counter_attack = true;
        if (target->GetState() != br::ActorState::Dead && 
            this->GetTargetUnit()->CanAttakck(*this->GetAttackerUnit())) {
            _attacker_excuted = false;
            auto a = this->GetAttackerUnit();
            auto t = this->GetTargetUnit();
            a->SetAttacker(false);
            t->SetAttacker(true);
        } // if
    } // if


    // ���j�b�g�̍X�V
    _player_unit.Update();
    _enemy_unit.Update();

    // �o�g���V�X�e�����UI���X�V
    _enemy_hp.Update();
    _player_hp.Update();
    if (_result_text.IsShow()) {
        _result_text.Update();
    } // if
    return true;
}

bool br::BattleSystem::Render(void) {
    auto r = _resource_manager.lock();
    //! �w�i�@����`��
    auto back = r->GetTexture(_back_path.c_str());
    back->Render(0.0f, 0.0f);
    // ���j�b�g�̕`��
    _player_unit.Render();
    _enemy_unit.Render();



    // �o�g���V�X�e�����UI��`��
    auto attacker = this->GetAttackerUnit()->GetUnit();
    auto target = this->GetTargetUnit()->GetUnit();
    // HP�\��
    this->RenderHp(_enemy_hp);
    this->RenderHp(_player_hp);


    _player_info.Render();
    _enemy_info.Render();
    if (_result_text.IsShow()) {
        _result_text.Render();
    } // if
    this->RenderFade();
    return true;
}