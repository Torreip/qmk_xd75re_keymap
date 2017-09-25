/* Copyright 2017 REPLACE_WITH_YOUR_NAME
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "xd75.h"
//#include "action_layer.h"

/* tap count needed for toggling a feature */
//#define TAPPING_TOGGLE  1

#define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped this number of times again. */
#define ONESHOT_TIMEOUT 2000  /* Time (in ms) before the one shot key is released */

/* Fillers to make layering more clear */
#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

/* Layer shorthand */
#define _QW 0
#define _LW 1
#define _RS 2
#define _FN 3

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
//  VRSN,
  RST,
};

/* Short forms for keycodes so that they fit into limited-width cells */
#define M_LOWER M(MACRO_LOWER)
#define M_UPPER M(MACRO_UPPER)
#define ROT_LED M(M_LED)   /* Rotate LED */
#define CTLENTER MT(MOD_RCTL, KC_ENT)
#define SHIFTQUOTE MT(MOD_RSFT, KC_QUOT)
#define ALTRIGHT MT(MOD_LALT, KC_RGHT)
#define MVERSION M(M_VERSION)
#define ALTSLASH LALT(KC_SLSH)
#define ALTSHFT LALT(KC_LSFT)
#define ALTBSP ALT_T(KC_BSPC)
#define ALTSLSH ALGR_T(KC_SLSH)
#define SFTBSLS MT(MOD_RSFT, KC_BSLS)
#define MLSHIFT OSM(KC_LSFT)
#define MLCTL OSM(KC_LCTL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY - MIT ENHANCED / GRID COMPATIBLE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `      | 1      | 2      | 3      | 4      | 5      | ESC    | F5     | BACKSP | 6      | 7      | 8      | 9      | 0      | -      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | Q      | W      | E      | R      | T      |        |        |        |        | Y      | U      | I      | O      | P      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | DEL    | A      | S      | D      | F      | G      |        |        |        |        | H      | J      | K      | L      | ;      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      |        |        |        |        | N      | M      | ,      | .      | /      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | LALTS  | LALT   | LOWER  | SPACE  | BACKSP | PG DN  | TAB    | ENTER  | RAISE  | /      | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 /* removed:
  * M(0)
  * , KC_RGUI, KC_RALT
  * MO(_LW)
  * 
  */
	
 [_QW] = { /* QWERTY */
  { KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_ESC,  KC_F5,   KC_BSPC, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS  },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, MO(_FN), KC_RBRC, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL   },
  { KC_DEL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_RSFT, KC_RSFT, KC_RSFT, KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_RSFT, KC_PGUP, KC_RCTL, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_UP,   SFTBSLS  },
  { KC_LCTL, KC_LGUI, ALTSHFT, KC_LALT, MO(_LW), KC_SPC,  KC_BSPC, KC_PGDN, KC_TAB,  KC_ENT, MO(_RS), ALTSLSH, KC_LEFT, KC_DOWN, KC_RGHT  },
 },


/* LOWERED
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX .        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      |        |        |        | INS    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | _      | +      | {      | }      | |      | XXXXXX .        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * |        | F7     | F8     | F9     | F10    | F11    | F12    |        |        |        |        | XXXXXX .        |        |        |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        | XXXXXX .        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

//  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___T___, ___T___  },
//  { _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, _______, KC_LPRN, KC_RPRN, _______, _______, _______, KC_INS   },
//  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, ___T___, ___T___, _______  },
//  { _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, ___T___, ___T___, _______, _______  },

 /* removed:
  * KC_CIRC, KC_AMPR, KC_ASTR
  */
 
 [_LW] = { /* LOWERED */
  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11   },
  { _______, KC_EXLM, KC_AT,   KC_LBRC, KC_RBRC, KC_PIPE, _______, ___T___, _______, _______, KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12   },
  { _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_PLUS, _______  },
  { _______, KC_PERC, KC_CIRC, KC_LCBR, KC_RCBR, KC_TILD, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_BSLS, _______  },
  { _______, _______, _______, _______, ___T___, _______, _______, _______, _______, _______, KC_0,    _______, _______, KC_EQL,  _______  },
 },

/* RAISED
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX .        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |        |        | INS    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | -      | =      | [      | ]      | \      | XXXXXX .        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * |        | F7     | F8     | F9     | F10    | F11    | F12    |        |        |        |        | XXXXXX .        |        |        |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        | XXXXXX .        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

//  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___T___, ___T___  },
//  { _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, _______, KC_9,    KC_0,    _______, _______, _______, KC_INS   },
//  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, ___T___, ___T___, _______  },
//  { _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, ___T___, ___T___, _______, _______  },
//  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },

 /* removed:
  */
 
 [_RS] = { /* RAISED */
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______, _______, KC_MS_U, _______, _______, _______, ___T___, _______, _______, KC_MPRV, KC_MNXT, _______, KC_MPLY, _______  },
  { _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______  },
  { _______, _______, _______, _______, ___T___, _______, _______, _______, _______, _______, ___T___, _______, _______, _______, _______  },
 },
 
/* FUNCTION
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * | NUM LK | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX .        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | SCR LK | F13    | F14    | F15    | F16    | F17    | F18    | F19    | F20    | F21    | F22    | F23    | F24    | PAUSE  | PR SCR |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * | CAP LK | MS BT5 | MS BT4 | MS BT3 | MS BT2 | SLOW M | FAST M | NEXT   | VOL+   | VOL-   | PLAY   |        | XXXXXX .        | WHEEL+ |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * | RGB TG | RGB MD | RGB HI | RGB HD | RGB SI | RGB SD | RGB VI | RGB VD | BL TOG | BL INC | BL DEC | XXXXXX .        | MOUS U | WHEEL- |
 * |--------+--------+--------+--------+--------+-- 2u -----------+--------+--------+--------+--------+-----------------+--------+--------|
 * | RESET  |        | QWERTY | COLEMK | DVORAK | XXXXXX . MS BT1 |        |        |        |        |        | MOUS L | MOUS D | MOUS R |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
//  { KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___T___, ___T___  },
//  { KC_SLCK, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  _______, _______, _______, KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_PAUS, KC_PSCR  },
//  { KC_CAPS, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, KC_ACL0, KC_ACL2, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, ___T___, ___T___, KC_WH_U  },
//  { RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_TOGG, BL_INC,  BL_DEC,   ___T___, ___T___, KC_MS_U, KC_WH_D  },
//  { RST    , _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R  },
 
  /* removed:
  */
 
 [_FN] = { /* FUNCTION */
  { KC_NLCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TERM_OFF },
  { KC_SLCK, _______, _______, RGB_HUI, RGB_HUD, _______, RGB_TOG, ___T___, RGB_MOD, _______, _______, _______, _______, _______, TERM_ON  },
  { KC_CAPS, _______, _______, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______, _______, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { RST    , _______, _______, _______, ___T___, _______, _______, _______, _______, _______, ___T___, _______, _______, _______, _______  },
 },
};

/*const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(_LW),
    [2] = ACTION_LAYER_TAP_TOGGLE(_RS)
};*/

/*
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
* */


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    /*
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break; */
//      case KC_Q:
//          rgblight_mode(21);
//          rgblight_setrgb(0xFF, 0x00, 0x00);
//
//          if (record->event.pressed) {
//        	  register_code  (KC_Q);
//        	  unregister_code(KC_Q);
//          }
//
////          _delay_ms(2000);
//
//          return true;
//          break;

      case RST:
//      rgblight_mode(1);
//      rgblight_setrgb(0xFF, 0x00, 0x00);
//      _delay_ms(250);
//      rgblight_setrgb(0xFF, 0x20, 0x00);
//      _delay_ms(250);
//       rgblight_setrgb(0xFF, 0x00, 0x00);
//      _delay_ms(250);
      if (record->event.pressed) {
        rgblight_effect_knight(1);
        rgblight_sethsv(0x00, 0xFF, 0xFF);
      }
      else {
        reset_keyboard();
      }

//      reset_keyboard();
      return false;
      break;
  }
  return true;
}


void matrix_init_user(void) {
  rgblight_enable();
}

void matrix_scan_user(void) {
#ifdef RGBLIGHT_ENABLE
  #define NO_MODE 0xFFFFFFFF

  static uint8_t old_layer = 255;
//  static uint32_t old_mode = NO_MODE;
  uint8_t new_layer = biton32(layer_state);

  if (old_layer != new_layer) {
    switch (new_layer) {
      case _QW:
/*		if ((old_mode != NO_MODE) && (rgblight_get_mode() != 1))
		{
          rgblight_mode(old_mode);
	    }
	    else */
	    {
//          rgblight_mode(1);
//          rgblight_setrgb(0x22, 0x22, 0x44);
        }
        break;
      case _LW:
//		old_mode = rgblight_get_mode();
        rgblight_mode(1);
        rgblight_setrgb(0x00, 0xA0, 0xFF);
        break;
      case _RS:
//		old_mode = rgblight_get_mode();
        rgblight_mode(1);
        rgblight_setrgb(0xFF, 0x00, 0x00);
        break;
      case _FN:
//		old_mode = rgblight_get_mode();
        rgblight_mode(1);
        rgblight_setrgb(0xFF, 0x20, 0x00);
        break;
    }

    old_layer = new_layer;
  }

#endif //RGBLIGHT_ENABLE
}
