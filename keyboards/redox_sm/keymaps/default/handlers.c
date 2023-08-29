#pragma once
#include <stdint.h>
#include <stdbool.h>

#define wait SS_DELAY(20) // 20ms delay

// void delta_mod(uint16_t keycode, bool pressed) {
//     if (pressed) {
//         register_code16(AHK_DEL);
//         register_code16(keycode);
//     } else {
//         unregister_code16(keycode);
//         unregister_code16(AHK_DEL);
//     }
// }

void c_mod(uint16_t keycode, bool pressed) {
    if (pressed) {
        register_code16(KC_LCTL);
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
        unregister_code16(KC_LCTL);
    }
}

void key(uint16_t keycode, bool pressed) {
    if (pressed) {
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
    }
}

void duo(uint16_t outer_keycode, uint16_t inner_keycode, bool pressed) {
    if (pressed) {
        register_code16(outer_keycode);
        register_code16(inner_keycode);
    } else {
        unregister_code16(inner_keycode);
        unregister_code16(outer_keycode);
    }
}

void layer(uint16_t layer, bool pressed) {
    if (pressed) {
        layer_on(layer);
    } else {
        layer_off(layer);
    }
}

uint16_t holdWait = 160;

void timedTap(uint16_t keycode, uint16_t* timer, bool pressed) {
    if (pressed) {
        *timer = timer_read();
    } else {
        if (timer_elapsed(*timer) < holdWait) {
            tap_code16(keycode);
        }
    }
}

/*  important links
 *   keys
 * https://docs.qmk.fm/#/keycodes
 *
 * functions (macros)
 * https://docs.qmk.fm/#/feature_macros
 * https://docs.qmk.fm/#/feature_macros?id=advanced-macro-functions
 */

bool altTabMode = false;
void SetAltTabMode(bool enable) {
    if (altTabMode != enable) {
        key(KC_LALT, enable);
        altTabMode = enable;
    }
}

bool capsLockMode = false;
bool mouseLockMode = false;
uint8_t mouseLockTaps    = 0;

// int  deltaCount = 0;
// void deltaTracker(bool pressed) {
//     pressed ? deltaCount++ : deltaCount--;
//     deltaCount ? layer_on(_DEL) : layer_off(_DEL);
// }

// bool rhoMode = false;

// typedef struct {
//     uint16_t timer;
//     uint16_t keycode;
//     bool     registered;
// } keyTrack;

// enum keyTrackerKeys { tSM_ENT = 0, tSM_TAB, tSM_BSPC };

// keyTrack keyTracker[] = {[tSM_ENT] = {0, 0, false}, [tSM_TAB] = {0, 0, false}, [tSM_BSPC] = {0, 0, false}};

static deferred_token later_token = INVALID_DEFERRED_TOKEN;
uint32_t              later_cb(uint32_t time, void* param) {
    tap_code16(KC_9);
    return 0;
}

uint16_t entTimer = 0, tabTimer = 0, bspcTimer = 0, medTimer = 0;


//
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    const bool pressed = record->event.pressed;
    switch (keycode) {
        case RHO:
            // layer(_DEL, pressed);
            layer(_RHO, pressed);
            if (!pressed) SetAltTabMode(false);
            return false;
        case FUN:
            layer(_FUN, pressed);
            return false;
        case MED:
            if(pressed) {
                //double tap to lock mouse
                if (timer_elapsed(medTimer) < holdWait) {
                    mouseLockTaps++;
                } else {
                    mouseLockTaps = 0;
                }
                mouseLockMode = false;
                medTimer = timer_read();
                layer_on(_MED);
            } else {
                if (timer_elapsed(medTimer) < holdWait) {
                    if (mouseLockTaps > 0) {
                        mouseLockMode = true;
                    }
                }
                layer(_MED, mouseLockMode);
            }
            return false;
        case PHI:
            layer(_PHI, pressed);
            if (!pressed) SetAltTabMode(false);
            return false;
        case SM_CAPS:
            if (pressed) {
                tap_code(KC_CAPS);
                capsLockMode = !capsLockMode;
            }
            return false;
        case KC_MINS:
            if (capsLockMode) {
                duo(KC_LSFT, KC_MINS, pressed);
                return false;
            }
            return true;
        case DEL_ENT:
            layer(_DEL, pressed);
            timedTap(KC_ENT, &entTimer, pressed);
            return false;
        // case FUN_TAB:
        //     layer(_FUN, pressed);
        //     timedTap(KC_TAB, &tabTimer, pressed);
        //     return false;
        // case FUN_BSP:
        //     layer(_FUN, pressed);
        //     timedTap(KC_BSPC, &bspcTimer, pressed);
        //     return false;
        // case DEL:
        //     layer(_DEL, pressed);
        //     return false;
        case A_TAB:
            if (pressed) SetAltTabMode(true);
            key(KC_TAB, pressed);
            return false;
        case SA_TAB:
            if (pressed) SetAltTabMode(true);
            duo(KC_LSFT, KC_TAB, pressed);
            return false;
        case MIN_WIN:
            if (pressed) {
                SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_SPACE) wait SS_UP(X_SPACE) wait SS_UP(X_LALT) wait SS_TAP(X_N));
            }
            return false;
        case PT_RUN:
            if (pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) wait SS_TAP(X_SPACE) wait SS_UP(X_LGUI));
            }
            return false;
        case BR_EJTB:
            if (pressed) {
                SEND_STRING(SS_LCTL("l") wait SS_TAP(X_F6) wait SS_LSFT(SS_TAP(X_F10)) wait "m" SS_TAP(X_ENTER));
            }
            return false;
        // case TH(SM_TH):
        //     if (record->tap.count > 1) {
        //         pressed ? tap_code16(KC_5) : tap_code16(KC_6);
        //     } else if (record->tap.count > 0) {
        //         pressed ? tap_code16(KC_1) : tap_code16(KC_2);
        //     } else {
        //         pressed ? tap_code16(KC_3) : tap_code16(KC_4);
        //     }
        //     return false;
        case SM_DF_EX: // here to allow compilation of referenced function
            if (pressed) {
                cancel_deferred_exec(later_token);
                later_token = defer_exec(1000, later_cb, NULL);
            }
            return false;
        case SM_MSUL:
            duo(KC_MS_U, KC_MS_L, pressed);
            return false;
        case SM_MSUR:
            duo(KC_MS_U, KC_MS_R, pressed);
            return false;
        case SM_MSDL:
            duo(KC_MS_D, KC_MS_L, pressed);
            return false;
        case SM_MSDR:
            duo(KC_MS_D, KC_MS_R, pressed);
            return false;
    }
    // only here to keep track of layerstate check, it wasn't useful yet
    // if (layer_state_is(_DEL) && pressed) {
    //     entTimer = holdWait + 1;
    // }
    return true;
}

// this allows for custom ctrl keys to also be auto shifted.
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case C(KC_Z):
        case C(KC_T):
        case C(KC_F):
        case C(KC_S):
        case C(KC_V):
        case C(KC_C):
        case C(KC_X):
        case C(KC_A):
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
        case LAG(KC_A):
        case LAG(KC_E):
        case LAG(KC_Q):
        case LAG(KC_C):
        case LAG(KC_V):
            return true;
        default:
            return false;
    }
}

uint16_t get_autoshift_timeout(uint16_t k, keyrecord_t* record) {
    switch (k) {
        case KC_A:
            return 200;
        default:
            return AUTO_SHIFT_TIMEOUT;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // case TH(SM_TH):
        //     return 3000;
        case (LT(_DEL, KC_SPC)):
            return 140;
        default:
            return TAPPING_TERM;
    }
}
