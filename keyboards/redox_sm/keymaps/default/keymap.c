#include QMK_KEYBOARD_H  

// layers
#define _ALP 0
#define _DEL 1
#define _RHO 2
#define _PHI 3
#define _FUN 4
#define _MED 5

#include "custom_keys.c"
#include "config_handlers.c"
#include "handlers.c"
#include "combos.c"

//these are undef'd at eof
#define xx      KC_NO
#define CS(x)   C(S(x))
#define WA(x)   LAG(x)
#define W(x)    G(x)
#define lf      KC_LEFT
#define rt      KC_RIGHT
#define dn      KC_DOWN
#define up      KC_UP
#define tab     KC_TAB
#define alt     KC_LALT
#define MT_C_0  MT(MOD_LCTL, KC_0)
#define MT_S_DT MT(MOD_LSFT, KC_DOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ALP] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┐   
    KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                           KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   ,
//├────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┤   
    KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_BTN1,                         KC_BTN1, KC_H   , KC_J   , KC_K   , KC_L   , RHO    ,
//├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤   
    LSFT_Z , KC_X   , KC_C   , KC_V   , KC_B   , PHI    ,                         PHI    , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_LSFT,
//└────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┐     ┌────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┘   
               xx   , KC_LALT,      KC_LCTL,     DEL_ENT, FUN_TAB,       FUN_BSP, DEL_SPC,     KC_RCTL,      KC_RALT, MED     
//         └────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┘   
    ),
    [_DEL] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┐   
    KC_LALT, KC_HOME, KC_UP  , KC_END , KC_PGUP,                                           _______, KC_7   , KC_8   , KC_9   , KC_LSFT,
//├────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┤   
    S(alt) , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_BTN3,                         KC_BTN3, _______, KC_4   , KC_5   , KC_6   , _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤   
    _______, _______, KC_DOWN, _______, _______,TO(_ALP),                        TO(_ALP), _______, KC_1   , KC_2   , KC_3   , _______,
//└────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┐     ┌────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┘   
             _______, _______,      _______,     _L_KEY_, S(tab) ,       KC_DEL , _L_KEY_,     KC_0   ,      _______, KC_DOT  
//         └────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┘   
    ),                                           /*  ^^          _L_KEY_          ^^  */
    // also includes delta underneath
    [_RHO] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┐   
    _______, _______,WA(KC_Q), AS_TOGG, _______,                                           _______, _______, C(KC_A), C(KC_X), _______,
//├────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┤   
    SM_CAPS,WA(KC_A),WA(KC_C),WA(KC_E), _______, _______,                         _______, _______, KC_ENT , C(KC_V), C(KC_C), _L_KEY_,
//├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤   
    _______, _______, SM_CAPS, _______, _______,TO(_PHI),                        TO(_PHI), KC_NUM , C(KC_S), C(KC_Z), KC_MPLY, _______,
//└────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┐     ┌────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┘   
             _______, _______,      _______,    TO(_DEL),TO(_FUN),      TO(_FUN),TO(_DEL),     A_TAB  ,      _______,TO(_MED) 
//         └────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┘   
    ),
    [_PHI] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┐   
    A_TAB  , MIN_WIN, W(up)  ,A(KC_F4), KC_WH_U,                                           KC_WH_U, CS(tab), C(KC_T), C(tab) , A_TAB  ,
//├────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┤   
    SA_TAB , W(lf)  , W(dn)  , W(rt)  , KC_WH_D, KC_BTN3,                         KC_BTN3, KC_WH_D, A(lf)  ,C(KC_F4), A(rt)  , SA_TAB ,
//├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤   
    _______, _______,WA(KC_V),WA(KC_H), _______,TO(_ALP), /* <-- _L_KEY_ --> */  TO(_ALP), _______, _______, BR_EJTB, _______, _______,
//└────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┐     ┌────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┘   
             _______, _______,      _______,     KC_SPC , KC_ESC ,       KC_INS , KC_ENT ,     _______,      _______, _______ 
//         └────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┘   
    ),
    [_FUN] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┐   
    _______, KC_F7  , KC_F8  , KC_F9  , KC_F12 ,                                           KC_PAST, KC_P7  , KC_P8  , KC_P9  , KC_PMNS,
//├────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┤   
    _______, KC_F4  , KC_F5  , KC_F6  , KC_F11 , KC_BTN2,                         KC_BTN2, KC_PSLS, KC_P4  , KC_P5  , KC_P6  , KC_PPLS,
//├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤   
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F10 ,TO(_ALP),                        TO(_ALP), KC_P0  , KC_P1  , KC_P2  , KC_P3  , KC_PENT,
//└────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┐     ┌────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┘   
             _______, _______,      _______,     KC_ENT , KC_TAB ,       KC_BSPC, KC_SPC ,     KC_P0  ,      _______, KC_PDOT 
//         └────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┘   
    ),                                                    /*  ^^ _L_KEY_ ^^  */
    [_MED] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┐   
    _______, SM_MSUL, KC_MS_U, SM_MSUR, KC_WH_U,                                           _______, _______, KC_MRWD, KC_MFFD, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┤   
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_BTN1,                         KC_BTN1, _______, _______, KC_MPRV, KC_MNXT, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤   
    _______, SM_MSDL, KC_MS_D, SM_MSDR, _______,TO(_ALP),                        TO(_ALP), _______, KC_LEFT, KC_RGHT, _______, _______,
//└────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┐     ┌────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┘   
             _______, _______,      KC_BTN3,     KC_BTN1, KC_BTN2,       _______, _______,     _______,      _______, _L_KEY_ 
//         └────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┴   
    )
};
// for nums in the small layout version, send the numpad keys on tap, the shifted chars on hold (1 = !, 2 = @, etc)
// if shift is held, send the shifted numpad chars (for macros and what not)
#undef xx
#undef CS
#undef WA
#undef W
#undef lf 
#undef rt
#undef dn 
#undef up
#undef tab
#undef alt
#undef MT_C_0
#undef MT_S_DT

// for reference!!!!
/*** 

    [BLANK] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┐   
    _______, _______, _______, _______, _______,                                           _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┤   
    _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┤   
    _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
//└────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┐     ┌────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┘   
             _______, _______,      _______,     _______, _______,       _______, _______,     _______,      _______, _______ 
//         └────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┴   
    ),

***/