#pragma once
#include <stdint.h>
#include <stdbool.h>
// #include "print.h"

#define wait SS_DELAY(20) // 20ms delay

// char pr_buffer[128];
// size_t pr_offset = 0;

#define BUF_APPEND(fmt, ...)                \
    uprintf(fmt __VA_OPT__(, )__VA_ARGS__)

    // pr_offset += snprintf(pr_buffer + pr_offset, sizeof(pr_buffer) - pr_offset, fmt __VA_OPT__(, )__VA_ARGS__)

#define BUF_UPRINT_CLEAR()                   \
    uprintf("\n")

bool tabs = true;

    // uprintf("%s\n", pr_buffer);
    // memset(pr_buffer, 0, sizeof(pr_buffer));
    // pr_offset = 0


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

void bufferInfo(uint16_t* keycode, keyrecord_t* record, const char* funcString) {
    if (tabs) {
        BUF_APPEND("%04X  ", *keycode);
        BUF_APPEND("%s  ", funcString);
        BUF_APPEND("%s  ",
            record->event.pressed ? "\\/" : "^"
        );
        // BUF_APPEND("Taps ");
        if (record->tap.count) {
            BUF_APPEND("%u  ", record->tap.count);
        } else {
            BUF_APPEND("-  ");
        }
        BUF_APPEND("%s  ",
            record->tap.interrupted ? "Int" : ""
        );

    } else {
        BUF_APPEND("  %04X ", *keycode);
        BUF_APPEND(" %s ", funcString);
        BUF_APPEND("%s ",
            record->event.pressed ? "\\/ " : "  ^"
        );
        BUF_APPEND("Taps ");
        if (record->tap.count) {
            BUF_APPEND("%1u", record->tap.count);
        } else {
            BUF_APPEND("-");
        }
        BUF_APPEND(" %s  ",
            record->tap.interrupted ? "Int" : "   "
        );

    }
}

uint16_t  entTimer = 0,
          tabTimer = 0,
          bspcTimer = 0,
          medTimer = 0;


uint16_t lastKeyPressed = 0;
uint16_t lastEventTime = 0;
uint16_t eventElapStartTime = 0;
uint16_t funcElapStartTime = 0;
bool resetEventElaps = true;
bool resetFuncElaps = true;

void bufferEventTime(uint16_t* keycode, keyrecord_t* record) {
    if (tabs) {
        if (resetEventElaps) {
            BUF_APPEND("-----  -----  ");
            eventElapStartTime = record->event.time;
        } else if (record->event.time == 0) {
            BUF_APPEND("--  --  ");
        } else {
            BUF_APPEND("%u  ",
                TIMER_DIFF_16(record->event.time, eventElapStartTime)
            );
            BUF_APPEND("%d  ",
                TIMER_DIFF_16(record->event.time, lastEventTime)
            );
        }
    } else {
        if (resetEventElaps) {
            BUF_APPEND("   event: -----, ----- ");
            eventElapStartTime = record->event.time;
        } else if (record->event.time == 0) {
            BUF_APPEND("   event:    --,    -- ");
        } else {
            BUF_APPEND("   event: %5u",
                TIMER_DIFF_16(record->event.time, eventElapStartTime)
            );
            BUF_APPEND(", %5d ",
                TIMER_DIFF_16(record->event.time, lastEventTime)
            );
        }

    }
    if (record->event.time) {
        lastEventTime = record->event.time;
    }
    resetEventElaps = false;
}

uint16_t lastFuncTimer = 0;
void bufferFuncTime(void) {
    if (tabs) {
        if (resetFuncElaps) {
            BUF_APPEND("-----  -----  ");
            funcElapStartTime = timer_read();
        } else {
            BUF_APPEND("%u  %u  ",
                timer_elapsed(funcElapStartTime),
                timer_elapsed(lastFuncTimer)
            );
        }
    } else {
        if (resetFuncElaps) {
            BUF_APPEND("   func: -----, ----- ");
            funcElapStartTime = timer_read();
        } else {
            BUF_APPEND("   func: %5u, %5u ",
                timer_elapsed(funcElapStartTime),
                timer_elapsed(lastFuncTimer)
            );
        }
    }
    lastFuncTimer = timer_read();
    resetFuncElaps = false;
}

bool _DEL_SPC_held = false;
bool _DEL_ENT_held = false;
bool _DEL_doubledown_no_clear_layer = false;

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

    #ifdef CONSOLE_ENABLE
    if (tabs) {
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


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode == 0x5226) {
        return true;
    }

    #ifdef CONSOLE_ENABLE
        // uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
        if (tabs) {
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

    const bool pressed = record->event.pressed;
    // const bool held = !record->tap.count;
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
    }
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
            return 1000;
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
    if (tabs) {
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
            retTapTerm = 1000;
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
