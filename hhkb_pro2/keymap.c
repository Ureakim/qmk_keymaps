#include QMK_KEYBOARD_H

enum layers {
	_BASE,
	_SIGNS,
	_MOVE
};

#define LSFT_A    LSFT_T(KC_A)
#define LCTL_S    LCTL_T(KC_S)
#define LGUI_D    LGUI_T(KC_D)
#define LALT_F    LALT_T(KC_F)
#define RALT_J    RALT_T(KC_J)
#define RGUI_K    RGUI_T(KC_K)
#define RCTL_L    RCTL_T(KC_L)
#define RSFT_SCLN RSFT_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT(
		KC_GRV,			KC_1,				KC_2,				KC_3,				KC_4,				KC_5,				KC_6,				KC_7,				KC_8,				KC_9,				KC_0,				KC_MINS,		KC_EQL,			KC_BSLS,		KC_GRV,
		KC_TAB,			KC_Q,				KC_W,				KC_E,				KC_R,				KC_T,				KC_Y,				KC_U,				KC_I,				KC_O,				KC_P,				KC_LBRC,		KC_RBRC,		KC_BSPC,
		KC_ESC,			LSFT_A,     LCTL_S,     LGUI_D,     LALT_F,     KC_G,       KC_H,       RALT_J,     RGUI_K,     RCTL_L,			RSFT_SCLN,	KC_QUOT,		KC_ENT,
		KC_LSFT,		KC_Z,				KC_X,				KC_C,				KC_V,				KC_B,				KC_N,				KC_M,				KC_COMM,		KC_DOT,			KC_SLSH,		KC_RSFT,		XXXXXXX,
		/*										*/KC_LALT,		MO(_MOVE),													KC_SPC,															MO(_SIGNS),	KC_RALT
	),

	[_SIGNS] = LAYOUT(
		XXXXXXX,		KC_F1,			KC_F2,			KC_F3,			KC_F4,			KC_F5,			KC_F6,			KC_F7,			KC_F8,			KC_F9,			KC_F10,			KC_F11,			KC_F12,			XXXXXXX,		XXXXXXX,
		_______,		KC_1,				KC_2,				KC_3,				KC_4,				KC_5,				KC_6,				KC_7,				KC_8,				KC_9,				KC_0,				XXXXXXX,		XXXXXXX,		KC_BSPC,
		_______,		KC_EXLM,		KC_AT,			KC_HASH,		KC_DLR,			KC_PERC,		KC_CIRC,		KC_AMPR,		KC_ASTR,		KC_LPRN,		KC_RPRN,		KC_PIPE,		_______,
		_______,		KC_SLSH,		XXXXXXX,		KC_TILD,		KC_LT,			KC_GT,			KC_BSLS,		KC_EQL,			KC_MINS,		KC_LBRC,		KC_RBRC,		_______,		XXXXXXX,
		/*										*/_______,		XXXXXXX,														_______,														_______,		_______
	),

	[_MOVE] = LAYOUT(
		QK_BOOT,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,
		XXXXXXX,		KC_INS,			KC_PSCR,		KC_SCRL,		KC_PAUS,		XXXXXXX,		XXXXXXX,		KC_HOME,		KC_PGDN,		KC_PGUP,		KC_END,			XXXXXXX,		XXXXXXX,		XXXXXXX,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		KC_LEFT,		KC_DOWN,		KC_UP,			KC_RIGHT,		XXXXXXX,		XXXXXXX,		XXXXXXX,
		KC_CAPS,		LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		KC_CAPS,		XXXXXXX,
		/*										*/_______,		_______,														_______,														XXXXXXX,		_______
	)
};

// key override
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL
};
