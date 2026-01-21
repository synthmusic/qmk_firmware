#pragma once
#include <stdint.h>
#include <stdbool.h>

uint16_t wkS(uint16_t keycode) {
    add_weak_mods(MOD_BIT(KC_LSFT));
    return keycode;
}

uint16_t wkC(uint16_t keycode) {
    add_weak_mods(MOD_BIT(KC_LCTL));
    return keycode;
}

uint16_t wkA(uint16_t keycode) {
    add_weak_mods(MOD_BIT(KC_LALT));
    return keycode;
}

uint16_t wkW(uint16_t keycode) {
    add_weak_mods(MOD_BIT(KC_LGUI));
    return keycode;
}

// this allows for custom ctrl keys to also be auto shifted.
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case C(A(KC_I)):
        case C(KC_A):
        case C(KC_C):
        case C(KC_F):
        case C(KC_P):
        case C(KC_S):
        case C(KC_T):
        case C(KC_V):
        case C(KC_X):
        case C(KC_Z):
        case KC_F1:
        case KC_F2:
        case KC_F3:
        case KC_F4:
        case KC_F5:
        case KC_F6:
        case KC_F7:
        case KC_F8:
        case KC_F9:
        case KC_F10:
        case KC_F11:
        case KC_F12:
        case KC_F13:
        case KC_F14:
        case KC_F15:
        case KC_F16:
        case KC_F17:
        case KC_F18:
        case KC_F19:
        case KC_F20:
        case KC_F21:
        case KC_F22:
        case KC_F23:
        case KC_F24:
        case LAG(KC_A):
        case LAG(KC_C):
        case LAG(KC_E):
        case LAG(KC_H):
        case LAG(KC_Q):
        case LAG(KC_V):
        case C(KC_TAB):
        case C(S(KC_TAB)):
        case EX_AS:
        case EX_AS_S:
            return true;
        default:
            return false;
    }// todo: define a case for z where the second tap is auto shifted?
}

uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_A:
        // case KC_Q:
        case KC_Z:
        case C(KC_TAB):
        case C(S(KC_TAB)):
            return 200;
        case EX_AS:
        case EX_AS_S:
            return 1500;
        default:
            return AUTO_SHIFT_TIMEOUT;
    }
}

void autoshift_process(uint16_t keycode, bool shifted, keyrecord_t* record, bool pressed) {
    bool tap = !shifted;
    bool both_pressed = record->event.pressed && pressed;
    bool hold = shifted && ((both_pressed) || (record->event.pressed && !pressed));
    bool hold_repeat = shifted && ((both_pressed) || (!record->event.pressed && !pressed));
    #ifdef CONSOLE_ENABLE
    if (bufferUseTabs) {
        bufferInfo(&keycode, record, "A");
        BUF_APPEND("%u  %u  ", pressed, shifted);
    } else {
        bufferInfo(&keycode, record, "  A");
        BUF_APPEND("pr: %1u sh: %1u", pressed, shifted);
    }
        bufferEventTime(&keycode, record);
        bufferFuncTime();
        BUF_UPRINT_CLEAR();
    #endif
    switch(keycode) {
        case EX_AS:
            // if (tap) {
            //     pressed ? tap_code16(KC_1) : tap_code16(KC_2);
            // } else if (hold) {
            //     pressed ? tap_code16(KC_3) : tap_code16(KC_4);
            // }
            break;
        case EX_AS_S:
            if (tap) {
                // if (pressed) {
                //     tap_code16(S(KC_1));
                // } else {
                //     tap_code16(S(KC_2));
                // }
            } else if (hold_repeat) {
                // if (pressed) {
                //     tap_code16(S(KC_3));
                // } else {
                //     tap_code16(S(KC_4));
                // }
            }
            break;
        case C(KC_TAB):
            if (tap && pressed) {
                tap_code16(C(KC_TAB));
            } else if (hold && pressed) {
                tap_code16(C(S(KC_PGDN)));
            }
            break;
        case C(S(KC_TAB)):
            if (tap && pressed) {
                tap_code16(C(S(KC_TAB)));
            } else if (hold && pressed) {
                tap_code16(C(S(KC_PGUP)));
            }
            break;
        default:
            if (pressed) {
                if (shifted) {
                    add_weak_mods(MOD_BIT(KC_LSFT));
                }
                // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
                register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);

            } else {
                // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
                // The IS_RETRO check isn't really necessary here, always using
                // keycode & 0xFF would be fine.
                unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);

            }
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    autoshift_process(keycode, shifted, record, true);
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    autoshift_process(keycode, shifted, record, false);
}

