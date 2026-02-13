#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "handlers_console.c"

#include "handlers_autoshift.c"
#include "handlers_taphold.c"

#define wait SS_DELAY(20) // 20ms delay

// char pr_buffer[128];
// size_t pr_offset = 0;


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

uint16_t HOLD_DEFAULT = 160;

void timedTap(uint16_t keycode, uint16_t* timer, bool pressed) {
    if (pressed) {
        *timer = timer_read();
    } else {
        if (timer_elapsed(*timer) < HOLD_DEFAULT) {
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
bool phiHeld = false;
uint16_t phiTapTimer = 0;
bool phiOtherKeyPressed = true;

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

uint16_t  entTimer = 0,
          tabTimer = 0,
          bspcTimer = 0,
          medTimer = 0;


uint16_t lastKeyPressed = 0;
// void anyHeldSet(uint16_t keycode, keyrecord_t* record) {
//     if (record->event.pressed) {
//         lastKeyPressed = keycode;
//         lastFuncTimer = timer_read();
//     }
// }

// void anyHeldCheck() {

// }

// void anyHeldCheck(time) {

// }
bool pre_process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode == 0x7e52 || keycode == 0x5226) {
        BUF_APPEND("\n");
        BUF_UPRINT_CLEAR();
        resetEventElaps = true;
        resetFuncElaps = true;
        return keycode != 0x7e52;
    }

    // Release PHI_HOLD before any other key is pressed (except PHI itself)
    if (phiHeld && keycode != PHI && record->event.pressed) {
        phiOtherKeyPressed = true;
        unregister_code16(PHI_HOLD);
        phiHeld = false;
    }

    #ifdef CONSOLE_ENABLE
    if (bufferUseTabs) {
        bufferInfo(&keycode, record, "P");
        BUF_APPEND("    ");
    } else {
        bufferInfo(&keycode, record, "P  ");
        BUF_APPEND("           ");
    }

        bufferEventTime(&keycode, record);
        bufferFuncTime();
        BUF_UPRINT_CLEAR();
    #endif
    return true;
}

bool process_record_user_standard(uint16_t keycode, keyrecord_t* record) {
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
                if (timer_elapsed(medTimer) < HOLD_DEFAULT) {
                    mouseLockTaps++;
                } else {
                    mouseLockTaps = 0;
                }
                mouseLockMode = false;
                medTimer = timer_read();
                layer_on(_MED);
            } else {
                if (timer_elapsed(medTimer) < HOLD_DEFAULT) {
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
            if (pressed) {
                // Start PHI tap timing and send PHI_HOLD
                phiTapTimer = timer_read();
                phiOtherKeyPressed = false;
                register_code16(PHI_HOLD);
                phiHeld = true;
            } else {
                // Send PHI_TAP on short tap with no other key pressed
                if (!phiOtherKeyPressed && timer_elapsed(phiTapTimer) < HOLD_DEFAULT) {
                    tap_code16(PHI_TAP);
                }
                // Release PHI_HOLD when PHI is released
                if (phiHeld) {
                    unregister_code16(PHI_HOLD);
                    phiHeld = false;
                }
                SetAltTabMode(false);
            }
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
            if (pressed) SetAltTabMode(true);i
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
        case TH_H_OTH:
        case TH_H_RET:
        case TH_H_STD:
        case TH_H_PRM:
        case TH_INT:
            return false;
        // case KC_Q:
        //     return false;
        default:
            return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode == 0x5226) {
        return true;
    }

    #ifdef CONSOLE_ENABLE
        // uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
        if (bufferUseTabs) {
            bufferInfo(&keycode, record, "R");
            BUF_APPEND("    ");
        } else {
            bufferInfo(&keycode, record, " R ");
            BUF_APPEND("           ");
        }

        bufferEventTime(&keycode, record);
        bufferFuncTime();
        BUF_UPRINT_CLEAR();
    #endif

    // const bool held = !record->tap.count;

    if (process_record_user_standard(keycode, record) == false) return false;
    if (process_record_user_taphold(keycode, record) == false) return false;

    // only here to keep track of layerstate check, it wasn't useful yet
    // if (layer_state_is(_DEL) && pressed) {
    //     entTimer = HOLD_DEFAULT + 1;
    // }
    return true;
}


static layer_state_t lastState = 0;


layer_state_t layer_state_set_user(layer_state_t state) {
    #ifdef CONSOLE_ENABLE
        if (!IS_LAYER_ON_STATE(state, _NUM) &&
            !IS_LAYER_ON_STATE(state, _FUN) &&
            state != 0x40 && lastState != 0x40) {
            uprintf("        layer_state_set_user: %02X, lastState: %02X, 2?: %u\n",
                state,
                lastState,
                IS_LAYER_ON_STATE(state, _DEL)
            );
        }
    #endif
    if (_DEL_doubledown_no_clear_layer && IS_LAYER_ON_STATE(lastState, _DEL)) {
        state |= (1 << _DEL);
        _DEL_doubledown_no_clear_layer = false;
    }

    lastState = state;
    return state;
}

