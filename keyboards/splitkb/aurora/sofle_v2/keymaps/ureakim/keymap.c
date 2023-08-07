#include QMK_KEYBOARD_H


/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_GRV,
        KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                               KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
        KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                               KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_MUTE,    XXXXXXX,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                                KC_LGUI,    KC_LALT,    KC_LCTL,    MO(2),      KC_ENT,     KC_SPC,     MO(1),      KC_RCTL,    KC_RALT,    KC_RGUI
    ),
	[1] = LAYOUT(
        KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,                              KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
        XXXXXXX,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_DEL,
        _______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,                            KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_PIPE,
        _______,    KC_LT,      KC_GT,      XXXXXXX,    KC_EQL,     KC_PEQL,    _______,    _______,    KC_PSLS,    KC_PPLS,    KC_PMNS,    KC_LBRC,    KC_RBRC,    _______,
                                _______,    _______,    _______,    XXXXXXX,    _______,    _______,    _______,    _______,    _______,    _______
    ),
	[2] = LAYOUT(
        QK_BOOT,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    KC_INS,     KC_PSCR,    KC_SCRL,    KC_PAUS,    XXXXXXX,                            KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   XXXXXXX,    XXXXXXX,
        KC_CAPS,    LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_CAPS,
                                XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
    )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)  },
    [1] =   { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  },
    [2] =   { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  }
};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
