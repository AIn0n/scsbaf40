// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define MOUSE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NO,		KC_Q,		KC_W,		KC_F,		KC_P,		    KC_G,	/* - */ KC_J,	KC_L,		    KC_U,		KC_Y,
        KC_BSPC,	CTL_T(KC_A),CMD_T(KC_R),ALT_T(KC_S),RALT_T(KC_T),	KC_D,	/* - */ KC_H,	RALT_T(KC_N),	ALT_T(KC_E),	CMD_T(KC_I),
        KC_TAB,		KC_Z,		KC_X,   	KC_C,   	SFT_T(KC_V),	KC_B,	/* - */ KC_K,	SFT_T(KC_M),	KC_COMMA,	KC_DOT,
        KC_NO,		KC_NO,		KC_NO,		MO(MOUSE),		KC_ENT,		    KC_SPC, /* - */ MO(1),	KC_SLSH,	    CTL_T(KC_O),	KC_SCLN
    ),
    [1] = LAYOUT(
        KC_GRV,		KC_1,   	KC_2,   	KC_3,   	KC_EQL,         KC_TRNS, /* - */ KC_QUOT,	KC_HOME,    	KC_PGDN,	    KC_PGUP,
        KC_ESC,		CTL_T(KC_4),CMD_T(KC_5),ALT_T(KC_6),RALT_T(KC_MINS),KC_TRNS, /* - */ KC_DEL,	RALT_T(KC_LEFT),ALT_T(KC_DOWN),	CMD_T(KC_UP),
        KC_TRNS,	KC_7,		KC_8,   	KC_9,   	SFT_T(KC_0),	KC_TRNS, /* - */ KC_LBRC,	SFT_T(KC_RBRC), KC_TRNS,	    KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	    KC_TRNS, /* - */ KC_TRNS,	KC_BSLS, 	    CTL_T(KC_RGHT),	KC_END
    ),
    [MOUSE] = LAYOUT(
        KC_TRNS,	KC_TRNS,   	KC_TRNS,   	KC_TRNS,   	KC_TRNS,    KC_TRNS, /* - */ KC_TRNS,	KC_MPRV,    MS_WHLD,	MS_WHLU,
        KC_TRNS,	KC_TRNS,    KC_TRNS,    MS_BTN1,    MS_BTN3,    KC_TRNS, /* - */ KC_MPLY,	MS_LEFT,    MS_DOWN,    MS_UP,
        KC_TRNS,	KC_TRNS,	KC_TRNS,   	KC_TRNS,   	MS_BTN2,	KC_TRNS, /* - */ KC_TRNS,	KC_TRNS,    KC_VOLD,	KC_VOLU,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS, /* - */ KC_TRNS,	KC_TRNS, 	MS_RGHT,	KC_MNXT
    )
};
