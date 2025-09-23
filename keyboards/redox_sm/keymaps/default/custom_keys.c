// BR = browser
// SM = synthmusic


enum custom_keycodes {
    ALP = SAFE_RANGE,
    // DEL,
    RHO,
    PHI,
    // FUN,
    MED,

    MIN_WIN,
    A_TAB,
    SA_TAB,
    PT_RUN,
    SM_CAPS,

    // DEL_ENT,
    // FUN_TAB,
    // FUN_BSP,
    // SM_TH,
    SM_DF_EX, // deferred execution

    BR_EJTB, // eject tab
    SM_MSUL, // mouse up left
    SM_MSUR, // mouse up right
    SM_MSDL, // mouse down left
    SM_MSDR, // mouse down right
    EX_AS,
    EX_AS_S,
    TH_INT,
    PRNT_LN,
};

// this allows for a custom Tap Hold keys in custom handlers!
// it only works with keys (numbers) below 0xFF
// however, it can be used with keycodes used elsewhere because the regular key still works independently
#define TH(x) LT(0, x)

#define EX_TH_1 TH(0)
#define EX_TH_1S TH(1)

// further, the LT(y, x) really just translates to a keycode of 0x4000, so just create an enum to make it easy
enum tap_hold_keycodes {
    EX_TH_2 = LT(0, 2), // or = 0x4002,
    EX_TH_2S,
    TH_H_STD,
    TH_H_PRM,
    TH_H_OTH,
    TH_H_RET
};

#define _L_KEY_ KC_TRNS
#define DEL_SPC LT(_DEL, KC_SPC)
#define DEL_ENT LT(_DEL, KC_ENT)
#define FUN_TAB LT(_FUN, KC_TAB)
#define FUN_BSP LT(_FUN, KC_BSPC)
#define LSFT_Z LSFT_T(KC_Z)
#define LALT_Q LALT_T(KC_Q)

#define MT_C_0  MT(MOD_LCTL, KC_0)
#define MT_S_DT MT(MOD_LSFT, KC_DOT)

// can not use custom keycode in MT combos!
// #define MT_A_NO MT(MOD_LALT, KC_Q)
