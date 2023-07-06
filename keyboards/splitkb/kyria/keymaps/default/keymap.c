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

int cur_dance (tap_dance_state_t *state);
void td_finished (tap_dance_state_t *state, void *user_data);
void td_reset (tap_dance_state_t *state, void *user_data);

#define ACTION_TAP_DANCE_FN_CUSTOM(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, user_user_data) \
  { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = (void *)user_user_data, }

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

enum {
  NAV_SPC = 0,
  SYM_ENT
};

typedef struct {
  uint16_t layer;
  uint16_t tap_key;
} td_user_data_t;

tap_dance_action_t tap_dance_actions[] = {
  [NAV_SPC] = ACTION_TAP_DANCE_FN_CUSTOM(NULL, td_finished, td_reset, &((td_user_data_t) { _NAV, KC_SPC })),
  [SYM_ENT] = ACTION_TAP_DANCE_FN_CUSTOM(NULL, td_finished, td_reset, &((td_user_data_t) { _SYM, KC_ENT }))
};

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define SFT_ENT  MT(MOD_RSFT, KC_ENT)
#define CTL_SPC  MT(MOD_LCTL, KC_SPC)

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
 *                        | Ctl  | GUI  | Alt  | Ctl/ | Nav/ |  | Sym/ | Sft/ | Alt  | RGUI | Menu |
 *                        |      |      |      | Spc  | Spc  |  | Ent  | Ent  |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
  [_QWERTY] = LAYOUT(
    KC_TAB , KC_Q, KC_W, KC_E   , KC_R   , KC_T   ,                                              KC_Y   , KC_U   , KC_I   , KC_O  , KC_P   , KC_BSPC ,
    CTL_ESC, KC_A, KC_S, KC_D   , KC_F   , KC_G   ,                                              KC_H   , KC_J   , KC_K   , KC_L  , KC_SCLN, CTL_QUOT,
    KC_LSFT, KC_Z, KC_X, KC_C   , KC_V   , KC_B   , KC_LBRC, KC_CAPS    ,        FKEYS, KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT, KC_SLSH, KC_RSFT ,
                         KC_LCTL, KC_LGUI, KC_LALT, CTL_SPC, TD(NAV_SPC),  TD(SYM_ENT), SFT_ENT, KC_RALT, KC_RGUI, KC_APP
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

int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 8;
}

static tap td_tap_state = {
  .is_press_action = true,
  .state = 0
};

void td_finished(tap_dance_state_t *state, void *user_data) {
  td_tap_state.state = cur_dance(state);
  td_user_data_t *data = (td_user_data_t *)user_data;
  switch (td_tap_state.state) {
    case SINGLE_TAP:
      tap_code(data->tap_key);
      break;
    case SINGLE_HOLD:
      layer_on(data->layer);
      break;
    case DOUBLE_TAP:
      if (layer_state_is(data->layer)) {
        layer_off(data->layer);
      } else {
        layer_on(data->layer);
      }
      break;
  }
}

void td_reset(tap_dance_state_t *state, void *user_data) {
  if (td_tap_state.state==SINGLE_HOLD) {
    layer_off(((td_user_data_t *)user_data)->layer);
  }
  td_tap_state.state = 0;
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_BLACK);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

void housekeeping_task_user(void) {
  uint8_t values[4][3] = {
    {0, 0, 0},
    {0, 20, 0},
    {20, 0, 0},
    {0, 0, 20}
  };

  uint8_t* params = values[get_highest_layer(layer_state | default_layer_state)];
  rgblight_setrgb_at(params[0], params[1], params[2], 0);
  rgblight_setrgb_at(params[0], params[1], params[2], 1);
}
