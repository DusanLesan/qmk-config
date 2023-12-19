/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

enum layers {
  _QWERTY = 0,
  _NAV,
  _SYM,
  _FUNCTION,
};

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define SFT_ENT  MT(MOD_RSFT, KC_ENT)
#define CTL_SPC  MT(MOD_LCTL, KC_SPC)

#define NAV_SPC LT(_NAV, KC_SPC)
#define SYS_ENT LT(_SYM, KC_ENT)

bool shift_held = false; // Track if Shift is held


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |  E   |  R   |  T   |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |  D   |  F   |  G   |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |  C   |  V   |  B   | [ {  | Caps |  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Ctl  | Alt  | GUI  | Ctl/ | Nav/ |  | Sym/ | Sft/ | Alt  | RGUI | Menu |
 *                        |      |      |      | Spc  | Spc  |  | Ent  | Ent  |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
  [_QWERTY] = LAYOUT(
    KC_TAB , KC_Q, KC_W, KC_E   , KC_R   , KC_T   ,                                          KC_Y   , KC_U   , KC_I   , KC_O  , KC_P   , KC_BSPC ,
    CTL_ESC, KC_A, KC_S, KC_D   , KC_F   , KC_G   ,                                          KC_H   , KC_J   , KC_K   , KC_L  , KC_SCLN, CTL_QUOT,
    KC_LSFT, KC_Z, KC_X, KC_C   , KC_V   , KC_B   , KC_LBRC, KC_CAPS,        FKEYS, KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT, KC_SLSH, KC_RSFT ,
                         KC_LCTL, KC_LALT, KC_LGUI, CTL_SPC, NAV_SPC,      SYS_ENT, SFT_ENT, KC_RALT, KC_RGUI, KC_APP
  ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
  [_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_VOLU, KC_DEL ,
    _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS ,
    _______, _______, _______, _______, _______, _______, _______, KC_SCRL, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
  [_SYM] = LAYOUT(
    KC_GRV  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
    KC_TILD , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
    KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______, _______, KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
  [_FUNCTION] = LAYOUT(
    _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
    _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
    _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool shift_held = false;

  switch (keycode) {
    case SFT_ENT:
      if (record->event.pressed) {
        shift_held = true;
      } else {
        shift_held = false;
      }
      return true;

    case NAV_SPC:
      if (record->event.pressed && shift_held) {
        layer_invert(_NAV);
        return false;
      }
      break;

    case SYS_ENT:
      if (record->event.pressed && shift_held) {
        layer_invert(_SYM);
        return false;
      }
      break;
  }
  return true;
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_BLACK);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

void housekeeping_task_user(void) {
  uint8_t values[][3] = {
    {0, 0, 0},
    {0, 20, 0},
    {20, 0, 0},
    {0, 0, 20},
    {20, 0, 20},
    {20, 20, 0},
    {0, 20, 20},
    {20, 20, 20}
  };

  uint8_t mods = get_mods();
  uint8_t* params = values[
    mods & MOD_MASK_GUI ? 4 :
    mods & MOD_MASK_ALT ? 5 :
    mods & MOD_MASK_CTRL ? 6 :
    mods & MOD_MASK_SHIFT ? 7 :
    get_highest_layer(layer_state | default_layer_state)
  ];

  rgblight_setrgb_at(params[0], params[1], params[2], 0);
  rgblight_setrgb_at(params[0], params[1], params[2], 1);
}
