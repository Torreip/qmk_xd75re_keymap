/* Copyright 2017 Pierre V.
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

#include QMK_KEYBOARD_H
//#include "debug.h"
//#include "action_layer.h"
#include "version.h"

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
  LOWER,
  RAISE,
  FUNC,
  VRSN,
  KMAP,
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

int RGB_current_mode;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY - MIT ENHANCED / GRID COMPATIBLE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `      | 1      | 2      | 3      | 4      | 5      | ESC    | F5     | BACKSP | 6      | 7      | 8      | 9      | 0      | -      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | FUNC   | ]      | Y      | U      | I      | O      | P      | =      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | DEL    | A      | S      | D      | F      | G      |        |        |        | H      | J      | K      | L      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      |        | PG UP  | RCTRL  | N      | M      | ,      | .      | UP     | \      |
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
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, FUNC,    KC_RBRC, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL   },
  { KC_DEL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, XXXXXXX, XXXXXXX, KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX, KC_PGUP, KC_RCTL, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_UP,   SFTBSLS  },
  { KC_LCTL, KC_LGUI, ALTSHFT, KC_LALT, LOWER,   KC_SPC,  KC_BSPC, KC_PGDN, KC_TAB,  KC_ENT, RAISE,   ALTSLSH, KC_LEFT, KC_DOWN, KC_RGHT  },
 },


/* LOWERED
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     |        |        |        | F6     | F7     | F8     | F9     | F10    | F11    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | !      | @      | [      | ]      | |      |        |        |        |        | 7      | 8      | 9      | *      | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | #      | $      | (      | )      | `      |        |        |        |        | 4      | 5      | 6      | +      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | %      | ^      | {      | }      | ~      |        |        |        |        | 1      | 2      | 3      | \      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        | 0      |        |        | =      |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 /* removed:
  * KC_CIRC, KC_AMPR, KC_ASTR
  */
 
 [_LW] = { /* LOWERED */
  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11   },
  { _______, KC_EXLM, KC_AT,   KC_LBRC, KC_RBRC, KC_PIPE, _______, XXXXXXX, _______, _______, KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12   },
  { _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_PLUS, _______  },
  { _______, KC_PERC, KC_CIRC, KC_LCBR, KC_RCBR, KC_TILD, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_BSLS, _______  },
  { _______, _______, _______, _______, ___T___, _______, _______, _______, _______, _______, KC_0,    _______, _______, KC_EQL,  _______  },
 },

/* RAISED
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 /* removed:
  */
 
 [_RS] = { /* RAISED */
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, _______, _______, _______  },
  { _______, _______, _______, KC_MS_U, _______, _______, _______, XXXXXXX, _______, _______, KC_WBAK, KC_WFWD, _______, KC_MPLY, _______  },
  { _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______  },
  { _______, _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, ___T___, _______, _______, _______, _______  },
 },
 
/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 /* removed:
  */
 
 [_FN] = { /* FUNCTION */
  { KC_NLCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TERM_OFF },
  { KC_SLCK, _______, _______, RGB_HUI, RGB_HUD, _______, RGB_TOG, ___T___, RGB_MOD, _______, _______, _______, _______, _______, TERM_ON  },
  { KC_CAPS, _______, _______, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { VRSN   , _______, _______, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { RST    , KMAP,    _______, _______, XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______, _______  },
 },

 /* NEXT
  * .--------------------------------------------------------------------------------------------------------------------------------------.
  * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint8_t skip = false;  /* if true: we do not restore the RGB state */

  switch (keycode) {
    // dynamically generate these.
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;

    case KMAP:
      if (record->event.pressed) {
        SEND_STRING("http://www.keyboard-layout-editor.com/#/gists/0e924c013c75d1dc4bbf51806b5500ee");
      }
      return false;
      break;

    /* Skip restoring the old RGB if we changed the current manually */
    case RGB_TOG:
    case RGB_MOD:
    case RGB_HUI:
    case RGB_HUD:
    case RGB_SAI:
    case RGB_SAD:
    case RGB_VAI:
    case RGB_VAD:
      skip = true;
      return true;
      break;

    case LOWER:
      if (record->event.pressed) {
        layer_on(_LW);
        if (biton32(layer_state) == _QW) {
          RGB_current_mode = rgblight_get_mode();
        }
        rgblight_mode(1);
        rgblight_setrgb(0x00, 0xA0, 0xFF);
      } else {
        layer_off(_LW);
        if (!skip) {
          rgblight_mode(RGB_current_mode);
        } else {
          skip = false;
        }
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RS);
        if (biton32(layer_state) == _QW) {
          RGB_current_mode = rgblight_get_mode();
        }
        rgblight_mode(1);
        rgblight_setrgb(0xFF, 0x00, 0x00);
      } else {
        layer_off(_RS);
        if (!skip) {
          rgblight_mode(RGB_current_mode);
        } else {
          skip = false;
        }
      }
      return false;
      break;

    case FUNC:
      if (record->event.pressed) {
        layer_on(_FN);
        if (biton32(layer_state) == _QW) {
          RGB_current_mode = rgblight_get_mode();
        }
        rgblight_mode(1);
        rgblight_setrgb(0xFF, 0x20, 0x00);
      } else {
        layer_off(_FN);
        if (!skip) {
          rgblight_mode(RGB_current_mode);
        } else {
          skip = false;
        }
      }
      return false;
      break;

    case RST:
      rgblight_enable();
      rgblight_mode(1);

      rgblight_sethsv(0x00, 0xFF, 0xFF);
      _delay_ms(250);
      rgblight_sethsv(0x3C, 0xFF, 0xFF);
      _delay_ms(250);
      rgblight_sethsv(0x00, 0xFF, 0xFF);
      _delay_ms(250);

      reset_keyboard();
      return false;
      break;
  }
  return true;
}


/* Called at startup */
void matrix_init_user(void) {
  /* Setup startup underglow */
  rgblight_enable();
  rgblight_sethsv(0xF0, 0xFF, 0xFF);
  rgblight_mode(10);
  RGB_current_mode = rgblight_get_mode();
}

/* Called all the time */
void matrix_scan_user(void) {

}
