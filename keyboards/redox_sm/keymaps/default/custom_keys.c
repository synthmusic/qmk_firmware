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

};

// this allows for a custom TH keycode in custom handlers!
#define TH(x) LT(0, x)

#define _L_KEY_ KC_TRNS
#define DEL_SPC LT(_DEL, KC_SPC)
#define DEL_ENT LT(_DEL, KC_ENT)
#define FUN_TAB LT(_FUN, KC_TAB)
#define FUN_BSP LT(_FUN, KC_BSPC)
#define LSFT_Z LSFT_T(KC_Z)
#define LALT_Q LALT_T(KC_Q)
// can not use custom keycode in MT combos!
// #define MT_A_NO MT(MOD_LALT, KC_Q)
