#pragma once
#include <stdint.h>
#include <stdbool.h>
// #include "print.h"

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

void printInfo(uint16_t* keycode, keyrecord_t* record) {
    uprintf("%s%04X  ", 
        record->event.pressed ? "\\/ " : "  ^",
        *keycode
    );
    if (record->tap.count) {
        uprintf("T%1u",
            record->tap.count
        );
    } else {
        uprintf("  ");
    }
    uprintf("%s -",
        record->tap.interrupted ? "I" : " "
    );
}


uint16_t  entTimer = 0, 
          tabTimer = 0, 
          bspcTimer = 0, 
          medTimer = 0;
uint16_t lastKeyPressTime = 0;
bool _DEL_SPC_held = false;
bool _DEL_ENT_held = false;
bool _DEL_doubledown_no_clear_layer = false;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    #ifdef CONSOLE_ENABLE
        // uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
        uprintf("  ");
        printInfo(&keycode, record);
        uprintf("    PRO t: %5u, el: %5u\n", 
            record->event.time,
            record->event.time - lastKeyPressTime);
        lastKeyPressTime = record->event.time;
    #endif 

    const bool pressed = record->event.pressed;
    switch (keycode) {
        case RHO:
            layer(_RHO, pressed);
            if (!pressed) SetAltTabMode(false);
            return false;
        // case FUN:
        //     layer(_FUN, pressed);
        //     return false;
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
                uprintf("\n");

            }
            return false;
        case PHI:
            autoshift_enable();
            if (capsLockMode) {
                capsLockMode = false;
                tap_code(KC_CAPS);
            }
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

        case LT(_DEL, KC_ENT):
            if (pressed) {
                if(!record->tap.count) {
                    _DEL_ENT_held = true;
                }
            } else {
                if (_DEL_ENT_held && _DEL_SPC_held) {
                    _DEL_doubledown_no_clear_layer = true;
                }
                _DEL_ENT_held = false;
            }
            return true;
        case LT(_DEL, KC_SPC):
            if (pressed) {
                if(!record->tap.count) {
                    _DEL_SPC_held = true;
                }
            } else {
                if (_DEL_ENT_held && _DEL_SPC_held) {
                    _DEL_doubledown_no_clear_layer = true;
                }                
                _DEL_SPC_held = false;
            }
            return true;
        // case DEL_ENT:
        //     layer(_DEL, pressed);
        //     timedTap(KC_ENT, &entTimer, pressed);
        //     return false;
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
        // case KC_Q:
        //     return false;
    }
    // only here to keep track of layerstate check, it wasn't useful yet
    // if (layer_state_is(_DEL) && pressed) {
    //     entTimer = holdWait + 1;
    // }
    return true;
}

static layer_state_t lastState = 0;


layer_state_t layer_state_set_user(layer_state_t state) {
    uprintf("        layer_state_set_user: %02X, lastState: %02X, 2?: %u\n", 
        state,
        lastState,
        IS_LAYER_ON_STATE(state, _DEL)
    );
    if (_DEL_doubledown_no_clear_layer && IS_LAYER_ON_STATE(lastState, _DEL)) {
        state |= (1 << _DEL);
        _DEL_doubledown_no_clear_layer = false;
    }

    lastState = state;
    return state;
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
            return 200;
        default:
            return AUTO_SHIFT_TIMEOUT;
    }
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
        default:
            break;
    }
    #ifdef CONSOLE_ENABLE
        // if (elapsed < 16 || (elapsed + 5) >= retTapTerm) {
        if (1) {
            uprintf("                    ");
            printInfo(&keycode, record);

            uprintf("      TAP_TERM - %4u - el: %4u\n", 
                retTapTerm,
                timer_read() - record->event.time
            );
        }
    #endif

    return retTapTerm;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case (LT(_DEL, KC_ENT)):
        case (LT(_DEL, KC_SPC)):
            return true;
        default:
            return false;
    }
}

// bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
//     switch (keycode) {
//         default:
//             return false;
//     }
// }
