//!-----------------------------------------------------
//! @file : BezierCurve.h
//! @brief : �x�W�G�Ȑ��̃f�[�^���擾����
//! @date : 2020/07/18
//!-----------------------------------------------------


#ifndef BR_BEZIER_CURVE_H
#define BR_BEZIER_CURVE_H


#include <Mof.h>


namespace br {
enum class EaseType {
    Linear,
    EaseIn,
    EaseOut,
    EaseInOut,
};
struct AnimData {
    float value;
    float time;
    EaseType ease_type;
};

class BezierCurve {
private:
public:
    // time�͐��K������Ă�����̂Ƃ��� 
    float Interpolation(float time, float prev, float next,
                        br::EaseType type = br::EaseType::Linear) {
        //int phase;
        //for (phase = 1; phase < cnt; phase++) {
        //    if (AnimTime < AnimData[phase].Time) {
        //        break;
        //    } // if
        //} // for
        //phase = MOF_MIN(phase, cnt - 1);
        //float nt = AnimTime - AnimData[phase - 1].Time;
        //float at = AnimData[phase].Time - AnimData[phase - 1].Time;
        //float t = nt / at; // �z����
        //t = MOF_CLIPING(t, 0.0f, 1.0f);
        //switch (AnimData[phase].EasingType) {
        //    case EASING_TYPE::EASE_IN_SINE:
        //        t = 1.0f - MOF_COS(MOF_MATH_HALFPI * t);
        //        break;
        //    case EASING_TYPE::EASE_OUT_SINE:
        //        t = MOF_SIN(MOF_MATH_HALFPI * t);
        //        break;
        //    case EASING_TYPE::EASE_INOUT_SINE:
        //        t = 0.5f - 0.5f * MOF_COS(MOF_MATH_PI * t);
        //        break;
        //    default:
        //        break;
        //} // switch

        if (time < 0.5f) {
        } // if

        switch (type) {
            case br::EaseType::EaseInOut:
                time = 0.5f - 0.5f * MOF_COS(MOF_MATH_PI * time);
                break;
        } // switch


        float from = prev;
        float to = next;
        return from + (to - from) * time;
    }

    //!-----------------------------------------------------
    //! @brief : ��Ԍv�Z
    //! @param : [in](float normalized) �A�j���[�V���������������ԂŊ������l
    //!                                 �ő�l��1.0f
    //! @param : [in](std::vector<float>& poistion) �R���g���[���|�C���g�̈ʒu 
    //! @param : [in](br::EaseType type) �C�[�W���O�̃^�C�v
    //! @return : none
    //!-----------------------------------------------------
    float InterpolationAnimData(float normalized,
                                std::vector<float>& control,
                                br::EaseType type = br::EaseType::Linear) {
        _ASSERT_EXPR(0.0 <= normalized && normalized <= 1.0f,
                     L"�A�j���[�V�����̎��Ԃ�臒l�𒴂��Ă��܂�");
        if (control.size() > 2) {
            std::vector<float> anim_data;
            for (int i = 1; i < control.size(); i++) {
                float value = Interpolation(normalized,
                                            control.at(i - 1),
                                            control.at(i),
                                            type);
                anim_data.push_back(value);
            } // for
            return InterpolationAnimData(normalized, anim_data);
        } // if
        else if (control.size() == 2) {
            return Interpolation(normalized,
                                 control.at(0),
                                 control.at(1),
                                 type);
        } // else if
        return 0.0f;
    }
};
}
#endif // !BR_BEZIER_CURVE_H