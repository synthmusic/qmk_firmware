#pragma once
#include <stdint.h>
#include <stdbool.h>

bool process_record_user_taphold(uint16_t keycode, keyrecord_t *record) {
    const bool pressed = record->event.pressed;

    switch (keycode) {
        case EX_TH_1:
        case EX_TH_2:
            if (record->tap.count > 1) {
                pressed ? tap_code16(KC_5) : tap_code16(KC_6);
            } else if (record->tap.count > 0) {
                pressed ? tap_code16(KC_1) : tap_code16(KC_2);
            } else {
                pressed ? tap_code16(KC_3) : tap_code16(KC_4);
            }
            return false;
        case EX_TH_1S:
        case EX_TH_2S:
            if (record->tap.count > 1) {
                pressed ? tap_code16(S(KC_5)) : tap_code16(S(KC_6));
            } else if (record->tap.count > 0) {
                pressed ? tap_code16(S(KC_1)) : tap_code16(S(KC_2));
            } else {
                pressed ? tap_code16(S(KC_3)) : tap_code16(S(KC_4));
            }
            return false;
        default:
            return true;
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    uint16_t retTapTerm = TAPPING_TERM;

    switch (keycode) {
        // how long to allow space to be held before it becomes a modifier.
        case (LT(_DEL, KC_ENT)):
        case (LT(_DEL, KC_SPC)):
            if (record->tap.count > 0) {
                retTapTerm = 0;
            } else {
                retTapTerm = 180;
            }
            break;
        case (LSFT_T(KC_Z)):
            if (record->tap.count > 0) {
                retTapTerm = 0;
            }
            break;
        case (EX_TH_1):
        case (EX_TH_1S):
        case (EX_TH_2):
        case (EX_TH_2S):
        case (TH_H_STD):
        case (TH_H_PRM):
        case (TH_H_OTH):
        case (TH_H_RET):
        case (TH_INT):
            retTapTerm = 1500;
            break;
        default:
            break;
    }
    #ifdef CONSOLE_ENABLE
        // if (elapsed < 16 || (elapsed + 5) >= retTapTerm) {
        if (0) {
            // BUF_APPEND_LIT("                    ");
            // bufferInfo(&keycode, record);

            // BUF_APPEND("      TAP_TERM - %4u - el: %4u",
            //     retTapTerm,
            //     timer_read() - record->event.time
            // );
            // BUF_APPEND_LIT("\n");
            // BUF_UPRINT();
        }
    #endif

    return retTapTerm;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case (LT(_DEL, KC_ENT)):
        case (LT(_DEL, KC_SPC)):
        case (EX_TH_2):
        case (EX_TH_2S):
        case (TH_H_PRM):
            return true;
        default:
            return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case (TH_H_OTH):
            return true;
        default:
            return false;
    }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case (TH_H_RET):
            return true;
        default:
            return false;
    }
}
