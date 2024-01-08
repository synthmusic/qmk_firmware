#pragma once
// https://docs.qmk.fm/#/feature_combo?id=combos

// here lies the combos
// right
const uint16_t PROGMEM qz_combo[]       = {KC_Q, KC_Z, COMBO_END};
const uint16_t PROGMEM pok_combo[]      = {KC_P, KC_O, KC_K, COMBO_END};
const uint16_t PROGMEM yu_combo[]       = {KC_Y, KC_U, COMBO_END};

const uint16_t PROGMEM _23_combo[]      = {KC_2, KC_3, COMBO_END};
const uint16_t PROGMEM _45_combo[]      = {KC_4, KC_5, COMBO_END};
const uint16_t PROGMEM _56_combo[]      = {KC_5, KC_6, COMBO_END};
const uint16_t PROGMEM ui_combo[]       = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM io_combo[]       = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM uo_combo[]       = {KC_U, KC_O, COMBO_END};
// const uint16_t PROGMEM hu_combo[]       = {KC_H, KC_U, COMBO_END};

const uint16_t PROGMEM ji_combo[]       = {KC_J, KC_I, COMBO_END};
const uint16_t PROGMEM _48_combo[]      = {KC_4, KC_8, COMBO_END};
const uint16_t PROGMEM il_combo[]       = {KC_I, KC_L, COMBO_END};
const uint16_t PROGMEM _86_combo[]      = {KC_8, KC_6, COMBO_END};
const uint16_t PROGMEM hj_combo[]       = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM jk_combo[]       = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[]       = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jl_combo[]       = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM nm_combo[]       = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM mcomma_combo[]   = {KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM commadot_combo[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM mdot_combo[]     = {KC_M, KC_DOT, COMBO_END};

const uint16_t PROGMEM dv_combo[]       = {KC_D, KC_V, COMBO_END};

// left
const uint16_t PROGMEM mk_combo[]       = {KC_M, KC_K, COMBO_END};

const uint16_t PROGMEM wq_combo[]       = {KC_W, KC_Q, COMBO_END};
// const uint16_t PROGMEM tr_combo[]       = {KC_T, KC_R, COMBO_END};
const uint16_t PROGMEM ew_combo[]       = {KC_E, KC_W, COMBO_END};
const uint16_t PROGMEM gf_combo[]       = {KC_G, KC_F, COMBO_END};
const uint16_t PROGMEM fd_combo[]       = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM ds_combo[]       = {KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM cx_combo[]       = {KC_C, KC_X, COMBO_END};
const uint16_t PROGMEM fs_combo[]       = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM vc_combo[]       = {KC_V, KC_C, COMBO_END};
const uint16_t PROGMEM funphi_combo[]   = {FUN, PHI, COMBO_END};

enum combo_events {
    QZ,
    POK,
    YU,
    _23,
    _45,
    _56,
    UI,
    IO,
    UO,
    // HU,
    JI,
    _48,
    IL,
    _86,
    HJ,
    JK,
    KL,
    JL,
    NM,
    MCOMMA,
    COMMADOT,
    MDOT,
    DV,
    MK,
    WQ,
    // TR,
    EW,
    GF,
    FD,
    DS,
    CX,
    FS,
    VC,
    FUNPHI,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

// it is absolutely worth noting that a keycode in the COMBO(,here) will be processed by process_record_user later
combo_t key_combos[] = {
    [QZ]       = COMBO(qz_combo, AS_TOGG),
    [POK]      = COMBO(pok_combo, QK_BOOT),
    [YU]       = COMBO(yu_combo, C(A(KC_I))),
    [_23]      = COMBO(_23_combo, C(KC_SLSH)),
    [_45]      = COMBO(_45_combo, S(KC_9)),
    [_56]      = COMBO(_56_combo, S(KC_0)),

    [UI]       = COMBO(ui_combo, KC_LBRC),
    [IO]       = COMBO(io_combo, KC_RBRC),
    [UO]       = COMBO(uo_combo, KC_BSLS),
    // [HU]       = COMBO(hu_combo, TO(_FUN)),
    [JI]       = COMBO(ji_combo, S(KC_9)),
    [_48]      = COMBO(_48_combo, S(KC_9)),
    [IL]       = COMBO(il_combo, S(KC_0)),
    [_86]      = COMBO(_86_combo, S(KC_0)),
    [HJ]       = COMBO(hj_combo, KC_MINS),
    [JK]       = COMBO(jk_combo, KC_EQL),
    [KL]       = COMBO(kl_combo, KC_SCLN),
    [JL]       = COMBO(jl_combo, KC_QUOT),
    [NM]       = COMBO(nm_combo, KC_DEL),
    [MCOMMA]   = COMBO(mcomma_combo, C(KC_Z)),
    [COMMADOT] = COMBO(commadot_combo, KC_SLSH),
    [MDOT]     = COMBO(mdot_combo, C(KC_SLSH)),
    [DV]       = COMBO(dv_combo, OSM(MOD_LGUI)),
    [MK]       = COMBO(mk_combo, OSM(MOD_LGUI)),
    [WQ]       = COMBO(wq_combo, KC_GRV),
    // [TR]       = COMBO(tr_combo, C(KC_T)),
    [EW]       = COMBO(ew_combo, KC_ESC),
    [GF]       = COMBO(gf_combo, PT_RUN),
    [FD]       = COMBO(fd_combo, PT_RUN),
    [DS]       = COMBO(ds_combo, KC_GRV),
    [CX]       = COMBO(cx_combo, KC_Z),
    [FS]       = COMBO(fs_combo, C(KC_S)),
    [VC]       = COMBO(vc_combo, C(KC_Z)),
    [FUNPHI]   = COMBO(funphi_combo, KC_MPLY),
    // [enum]     = COMBO_ACTION(combo),

};

/* COMBO_ACTION(x) is meant to be used for combos that need to do something other than send a keypress.
 * and will get processed below in process_combo_event.
 */
/* COMBO(x, KC_NO) will send a key from a combo, see above */

// void process_combo_event(uint16_t combo_index, bool pressed) {
// uint16_t i = combo_index;
// switch (i) {
//     case HU:
//         if (pressed) {
//             layer_invert(_NUM);
//         }
//         break;
//     case RE:
//         if (pressed) {
//             SEND_STRING(SS_DOWN(X_LGUI) SS_DELAY(20) SS_TAP(X_SPACE) SS_DELAY(20) SS_UP(X_LGUI));
//         }
//         break;
// }

// i == YU         ? key(KC_GRV, pressed)
// : i == _78      ? duo(KC_LSFT, KC_9, pressed)
// : i == _89      ? duo(KC_LSFT, KC_0, pressed)
// : i == UI       ? key(KC_LBRC, pressed)
// : i == IO       ? key(KC_RBRC, pressed)
// : i == UO       ? key(KC_BSLS, pressed)
// : i == HJ       ? key(KC_MINS, pressed)
// : i == JK       ? key(KC_EQL, pressed)
// : i == KL       ? key(KC_SCLN, pressed)
// : i == JL       ? key(KC_QUOT, pressed)
// : i == MCOMMA   ? c_mod(KC_Z, pressed)
// : i == COMMADOT ? key(KC_SLSH, pressed)
// : i == MDOT     ? c_mod(KC_SLSH, pressed)
// : i == TR       ? c_mod(KC_T, pressed)
// : i == EW       ? key(KC_ESC, pressed)
// : i == FD       ? c_mod(KC_F, pressed)
// : i == FS       ? c_mod(KC_S, pressed)
// : i == GS       ? c_mod(KC_A, pressed)
// : i == VC       ? c_mod(KC_V, pressed)
// : i == CX       ? c_mod(KC_C, pressed)
// : i == VX       ? c_mod(KC_X, pressed)
// : i == BX       ? c_mod(KC_Z, pressed)
// : i == FUNPHI   ? key(KC_LGUI, pressed)
// : 0;
// }
/*
    i == YU         ? delta_mod(KC_Y, pressed)
    : i == UI       ? delta_mod(KC_U, pressed)
    : i == IO       ? delta_mod(KC_I, pressed)
    : i == UO       ? delta_mod(KC_O, pressed)
    : i == HJ       ? delta_mod(KC_H, pressed)
    : i == JK       ? delta_mod(KC_J, pressed)
    : i == KL       ? delta_mod(KC_K, pressed)
    : i == JL       ? delta_mod(KC_L, pressed)
    : i == MCOMMA   ? c_mod(KC_Z, pressed)
    : i == COMMADOT ? delta_mod(KC_COMMA, pressed)
    : i == TR       ? c_mod(KC_T, pressed)
    // : i == RE ? c_mod(KC_R, pressed)
    // : i == EW ? c_mod(KC_E, pressed)
    // : i == RW ? c_mod(KC_W, pressed)
    // : i == TW ? c_mod(KC_Q, pressed)
    // : i == GF ? c_mod(KC_G, pressed)
    : i == FD ? c_mod(KC_F, pressed)
    // : i == DS ? c_mod(KC_D, pressed)
    : i == FS ? c_mod(KC_S, pressed)
    : i == GS ? c_mod(KC_A, pressed)
    // : i == BV ? c_mod(KC_B, pressed)
    : i == VC ? c_mod(KC_V, pressed)
    : i == CX ? c_mod(KC_C, pressed)
    : i == VX ? c_mod(KC_X, pressed)
    : i == BX ? c_mod(KC_Z, pressed)
              : 0;

*/