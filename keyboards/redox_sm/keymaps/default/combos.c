#pragma once
// https://docs.qmk.fm/#/feature_combo?id=combos

// COMB = COMBO
// COMB_A = COMBO_ACTION - must add more to the case statement at end

// sort: 
//COMB( enum,   action,         input keys
#define combosdef \
COMB(   CV,         C(KC_Z),        KC_C, KC_V) \
COMB(   CX,         KC_Z,           KC_C, KC_X) \
COMB(   BF,         OSM(MOD_LGUI),  KC_B, KC_F) \
COMB(   DF,         KC_EQL,         KC_D, KC_F) \
COMB(   DS,         KC_ESC,         KC_D, KC_S) \
COMB_A( DV,         swallow,        KC_D, KC_V) \
COMB(   DWLALT,     QK_BOOT,        KC_D, KC_W, KC_LALT) \
COMB(   DWALT_Q,    QK_BOOT,        KC_D, KC_W, LALT_Q) \
COMB(   EW,         KC_Q,           KC_E, KC_W) \
COMB(   FG,         S(KC_LBRC),     KC_F, KC_G) \
COMB(   FS,         KC_GRV,         KC_F, KC_S) \
COMB(   HJ,         KC_MINS,        KC_H, KC_J) \
COMB(   IJ,         S(KC_9),        KC_I, KC_J) \
COMB(   IL,         S(KC_0),        KC_I, KC_L) \
COMB(   IO,         KC_RBRC,        KC_I, KC_O) \
COMB_A( IOU,        fC_S_A,         KC_I, KC_O, KC_U) \
COMB(   IU,         KC_LBRC,        KC_I, KC_U) \
COMB(   JK,         KC_EQL,         KC_J, KC_K) \
COMB(   JL,         KC_QUOT,        KC_J, KC_L) \
COMB(   JN,         OSM(MOD_LGUI),  KC_J, KC_N) \
COMB(   KL,         KC_SCLN,        KC_K, KC_L) \
COMB_A( KM,         swallow,        KC_K, KC_M) \
COMB(   MCOMM,      C(KC_Z),        KC_M, KC_COMM) \
COMB(   MDOT,       C(KC_SLSH),     KC_M, KC_DOT) \
COMB(   NM,         KC_DEL,         KC_N, KC_M) \
COMB(   OP,         C(KC_P),        KC_O, KC_P) \
COMB(   OU,         KC_BSLS,        KC_O, KC_U) \
COMB(   POK,        QK_BOOT,        KC_P, KC_O, KC_K) \
COMB(   QWD,        QK_BOOT,        KC_Q, KC_W, KC_D) \
COMB(   QZ,         AS_TOGG,        KC_Q, KC_Z) \
COMB(   UY,         C(A(KC_I)),     KC_U, KC_Y) \
COMB(   WLALT,      KC_GRV,         KC_W, KC_LALT) \
COMB(   XLSFT_Z,    KC_Z,           KC_X, LSFT_Z) \
COMB(   COMMDOT,    KC_SLSH,        KC_COMM, KC_DOT) \
COMB(   _48,        S(KC_9),        KC_4, KC_8) \
COMB(   _86,        S(KC_0),        KC_8, KC_6) \
COMB(   _23,        C(KC_SLSH),     KC_2, KC_3) \
COMB(   _45,        S(KC_9),        KC_4, KC_5) \
COMB(   _56,        S(KC_0),        KC_5, KC_6) \

void swallow(bool pressed) {
    // no-op
}
void fC_S_A(bool pressed) {
    key(C(S(KC_A)), pressed);
}
void sendANFN(bool pressed) {
    if (pressed){
                SEND_STRING(SS_TAP(X_END) " => {");
    } 
}

// COMB(   FUNPHI, KC_MPLY,        FUN, PHI) 
// COMB(   DF,     PT_RUN,         KC_D, KC_F)

#define K_ENUM(name, key, ...) name, 
#define K_DATA(name, key, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#define K_COMB(name, key, ...) [name] = COMBO(cmb_##name, key),
#define K_COMB_A(name, key, ...) [name] = COMBO_ACTION(cmb_##name), 
#define K_PROCESS(name, fn, ...) case name: \
    fn(pressed); \
    break;

#define BLANK(...)

#define COMB K_DATA
#define COMB_A K_DATA

/*** declare key combos */
combosdef
// const uint16_t PROGMEM pok_combo[]      = {KC_P, KC_O, KC_K, COMBO_END};
/*** declare key combos */

#undef COMB
#undef COMB_A

#define COMB K_ENUM
#define COMB_A K_ENUM

/*** declare enum for the combo names */
enum combo_events {
    combosdef
    // POK,
    // this must be here for the COMBO_LEN define
    COMBO_LENGTH
};
/*** declare enum for the combo names */

uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!
#undef COMB
#undef COMB_A


#define COMB K_COMB
#define COMB_A K_COMB_A
// it is absolutely worth noting that a keycode in the COMBO(,here) will be processed by process_record_user later

/*** register key combos and actions */
combo_t key_combos[] = {
    combosdef
    // [POK]      = COMBO(pok_combo, QK_BOOT),
    // [enum]     = COMBO_ACTION(combo),
};
/*** register key combos and actions */

#undef COMB
#undef COMB_A

#define COMB BLANK
#define COMB_A K_PROCESS
/************** define combo actions ******************/
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        combosdef
        // case UIO: 
        //     key(C(S(KC_A)), pressed);
        //     break;
    }
}
/************** define combo actions ******************/
#undef COMB
#undef COMB_A

/* COMBO_ACTION(x) is meant to be used for combos that need to do something other than send a keypress.
 * and will get processed below in process_combo_event.
 */
/* COMBO(x, KC_NO) will send a key from a combo, see above */

// pattern for ..._event
// i == YU         ? key(KC_GRV, pressed)
// : i == _78      ? duo(KC_LSFT, KC_9, pressed)
// : i == _89      ? duo(KC_LSFT, KC_0, pressed)
