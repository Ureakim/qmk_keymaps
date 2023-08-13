#include QMK_KEYBOARD_H

enum layers {
	_BASE,
	_SIGNS,
	_MOVE
};

enum c_keycodes {
	OLED_T = SAFE_RANGE,
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
		KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_GRV,
		KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                               KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
		KC_ESC,     LSFT_A,     LCTL_S,     LGUI_D,     LALT_F,     KC_G,                               KC_H,       RALT_J,     RGUI_K,     RCTL_L,     RSFT_SCLN,  KC_QUOT,
		KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_MUTE,    XXXXXXX,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
		/*                    */KC_LGUI,    KC_LALT,    KC_LCTL,    MO(_MOVE),  KC_SPC,     KC_ENT,     MO(_SIGNS), KC_RCTL,    KC_RALT,    KC_RGUI
	),
	[_SIGNS] = LAYOUT(
		KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,                              KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
		_______,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_DEL,
		_______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,                            KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_PIPE,
		_______,    KC_LT,      KC_GT,      XXXXXXX,    KC_EQL,     KC_PEQL,    _______,    _______,    KC_PSLS,    KC_PPLS,    KC_PMNS,    KC_LBRC,    KC_RBRC,    _______,
		/*                    */_______,    _______,    _______,    XXXXXXX,    _______,    _______,    _______,    _______,    _______,    _______
	),
	[_MOVE] = LAYOUT(
		QK_BOOT,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    OLED_T,
		XXXXXXX,    KC_INS,     KC_PSCR,    KC_SCRL,    KC_PAUS,    XXXXXXX,                            KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     XXXXXXX,    XXXXXXX,
		_______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   XXXXXXX,    XXXXXXX,
		KC_CAPS,    LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX,    _______,    _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_CAPS,
		/*                    */_______,    _______,    _______,    _______,    _______,    _______,    XXXXXXX,    _______,    _______,    _______
	)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
	[_BASE]  =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)  },
	[_SIGNS] =  { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  },
	[_MOVE]  =  { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  }
};

#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
void keyboard_pre_init_user(void) {
	// turning off the onboard power LED
	setPinOutput(24);
	writePinHigh(24);
}

bool oled_enabled = true;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case OLED_T:
			if (record->event.pressed) {
				oled_enabled = !oled_enabled;
			}
			break;
	}
	return true;
}

#ifdef OLED_ENABLE
bool should_process_keypress(void) {
	return true;
}

void render_space_widget(void) {
	oled_write_P(PSTR("     "), false);
}

void render_keyboard_widget(void) {
	static const char PROGMEM c_keyboard[] = {
		0xFF, 0x01, 0x6D, 0x6D, 0x01, 0x6D,
		0x6D, 0x01, 0x6D, 0x6D, 0x01, 0x6D,
		0x6D, 0x01, 0x6D, 0x6D, 0x01, 0x6D,
		0x6D, 0x01, 0x6D, 0x6D, 0x01, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00,
		0x0F, 0x08, 0x0B, 0x0B, 0x08, 0x0B,
		0x0B, 0x08, 0x0B, 0x0B, 0x0B, 0x0B,
		0x0B, 0x0B, 0x0B, 0x0B, 0x08, 0x0B,
		0x0B, 0x08, 0x0B, 0x0B, 0x08, 0x0F,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00,
	};
	oled_write_raw_P(c_keyboard, sizeof(c_keyboard));
	oled_set_cursor(0, 2);

	switch (get_highest_layer(layer_state)) {
		case _BASE:
			oled_write_P(PSTR(" Base"), false);
			break;
		case _SIGNS:
			oled_write_P(PSTR(" Sign"), false);
			break;
		case _MOVE:
			oled_write_P(PSTR(" Move"), false);
			break;
		default:
			oled_write_ln_P(PSTR("?????"), false);
	}
}

void render_mod_gui_alt(uint8_t modifiers) {
	static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
	static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
	static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
	static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

	static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
	static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
	static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
	static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

	// fillers between the modifier icons bleed into the icon frames
	static const char PROGMEM off_off_1[] = {0xc5, 0};
	static const char PROGMEM off_off_2[] = {0xc6, 0};
	static const char PROGMEM on_off_1[] = {0xc7, 0};
	static const char PROGMEM on_off_2[] = {0xc8, 0};
	static const char PROGMEM off_on_1[] = {0xc9, 0};
	static const char PROGMEM off_on_2[] = {0xca, 0};
	static const char PROGMEM on_on_1[] = {0xcb, 0};
	static const char PROGMEM on_on_2[] = {0xcc, 0};

	if(modifiers & MOD_MASK_GUI) {
		oled_write_P(gui_on_1, false);
	} else {
		oled_write_P(gui_off_1, false);
	}

	if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
		oled_write_P(on_on_1, false);
	} else if(modifiers & MOD_MASK_GUI) {
		oled_write_P(on_off_1, false);
	} else if(modifiers & MOD_MASK_ALT) {
		oled_write_P(off_on_1, false);
	} else {
		oled_write_P(off_off_1, false);
	}

	if(modifiers & MOD_MASK_ALT) {
		oled_write_P(alt_on_1, false);
	} else {
		oled_write_P(alt_off_1, false);
	}

	if(modifiers & MOD_MASK_GUI) {
		oled_write_P(gui_on_2, false);
	} else {
		oled_write_P(gui_off_2, false);
	}

	if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
		oled_write_P(on_on_2, false);
	} else if(modifiers & MOD_MASK_GUI) {
		oled_write_P(on_off_2, false);
	} else if(modifiers & MOD_MASK_ALT) {
		oled_write_P(off_on_2, false);
	} else {
		oled_write_P(off_off_2, false);
	}

	if(modifiers & MOD_MASK_ALT) {
		oled_write_P(alt_on_2, false);
	} else {
		oled_write_P(alt_off_2, false);
	}
}

void render_mod_ctrl_shift(uint8_t modifiers) {
	static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
	static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
	static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
	static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

	static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
	static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
	static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
	static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

	// fillers between the modifier icons bleed into the icon frames
	static const char PROGMEM off_off_1[] = {0xc5, 0};
	static const char PROGMEM off_off_2[] = {0xc6, 0};
	static const char PROGMEM on_off_1[] = {0xc7, 0};
	static const char PROGMEM on_off_2[] = {0xc8, 0};
	static const char PROGMEM off_on_1[] = {0xc9, 0};
	static const char PROGMEM off_on_2[] = {0xca, 0};
	static const char PROGMEM on_on_1[] = {0xcb, 0};
	static const char PROGMEM on_on_2[] = {0xcc, 0};

	if(modifiers & MOD_MASK_CTRL) {
		oled_write_P(ctrl_on_1, false);
	} else {
		oled_write_P(ctrl_off_1, false);
	}

	if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
		oled_write_P(on_on_1, false);
	} else if(modifiers & MOD_MASK_CTRL) {
		oled_write_P(on_off_1, false);
	} else if(modifiers & MOD_MASK_SHIFT) {
		oled_write_P(off_on_1, false);
	} else {
		oled_write_P(off_off_1, false);
	}

	if(modifiers & MOD_MASK_SHIFT) {
		oled_write_P(shift_on_1, false);
	} else {
		oled_write_P(shift_off_1, false);
	}

	if(modifiers & MOD_MASK_CTRL) {
		oled_write_P(ctrl_on_2, false);
	} else {
		oled_write_P(ctrl_off_2, false);
	}

	if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
		oled_write_P(on_on_2, false);
	} else if(modifiers & MOD_MASK_CTRL) {
		oled_write_P(on_off_2, false);
	} else if(modifiers & MOD_MASK_SHIFT) {
		oled_write_P(off_on_2, false);
	} else {
		oled_write_P(off_off_2, false);
	}

	if(modifiers & MOD_MASK_SHIFT) {
		oled_write_P(shift_on_2, false);
	} else {
		oled_write_P(shift_off_2, false);
	}
}

void render_mods_widget(void) {
	oled_write_P(PSTR("Mod: "), false);
	render_mod_gui_alt(get_mods()|get_oneshot_mods());
	render_mod_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_locks_widget(void) {
	led_t led_usb_state = host_keyboard_led_state();
	oled_write_P(PSTR("Lock:"), false);
	oled_write_P(led_usb_state.num_lock ? PSTR("N ") : PSTR("  "), false);
	oled_write_P(led_usb_state.caps_lock ? PSTR("C ") : PSTR("  "), false);
	oled_write_P(led_usb_state.scroll_lock ? PSTR("S") : PSTR(" "), false);
}

bool oled_task_user(void) {
	if (!oled_enabled) {
		if(is_oled_on()) {
			oled_clear();
			oled_off();
		}
		return false;
	}

	if (is_keyboard_master()) {
		render_keyboard_widget();
	} else {
		render_space_widget();
		render_space_widget();
		render_space_widget();
	}
	render_space_widget();
	render_mods_widget();
	render_space_widget();
	render_locks_widget();
	return false;
}
#endif
