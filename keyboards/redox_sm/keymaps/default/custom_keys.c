
// todo: what is this doing?
#define TH(x) LT(0, x)
#define _L_KEY_ KC_TRNS
#define DEL_SPC LT(_DEL, KC_SPC)
// #define DEL_ENT LT(_DEL, KC_ENT)
#define FUN_TAB LT(_FUN, KC_TAB)
#define FUN_BSP LT(_FUN, KC_BSPC)

// BR = browser
// SM = synthmusic

enum custom_keycodes {
    ALP = SAFE_RANGE,
    DEL,
    RHO,
    PHI,
    FUN,
    MED,

    MIN_WIN,
    A_TAB,
    SA_TAB,
    PT_RUN,
    SM_CAPS,

    DEL_ENT,
    // FUN_TAB,
    // FUN_BSP,
    // SM_TH,
    SM_DF_EX,

    BR_EJTB,
    SM_MSUL,
    SM_MSUR,
    SM_MSDL,
    SM_MSDR,
};
