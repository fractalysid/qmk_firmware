/* Copyright 2020 houn
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

uint16_t copy_paste_timer;

enum layers {
    QWERTY = 0,
    GAMING,
    FFXIV,
    FFXIVFUNC,
    LOWER,
    RAISE,
    NAV,
    ADJUST
};

enum custom_keycodes {
    KC_CCCV = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* 
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | ESC    |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | TAB    |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LCTL   |   Z  |   X  |   C  |   V  |   B  |      |  Del |  | Bspc | Lead |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GUI  | Alt  |      |      |      |  |      | Space|      | Tab  | AltGr|
 *                        |      |      | Lower| Shift| Enter|  | Shift| Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [QWERTY] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLASH,
      KC_TAB, MT(MOD_LGUI, KC_A), MT(MOD_LALT, KC_S), MT(MOD_LSFT, KC_D), MT(MOD_LCTL, KC_F),   KC_G,   KC_H,    MT(MOD_RCTL, KC_J), MT(MOD_RSFT, KC_K), MT(MOD_LALT, KC_L), MT(MOD_RGUI, KC_SCLN), KC_QUOT,
      KC_LCTL, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   XXXXXXX,   KC_DEL, KC_BSPC, KC_LEAD,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
              KC_LGUI, KC_LALT, MO(LOWER), KC_LSFT,  KC_ENT, KC_RSFT, LT(NAV, KC_SPC),  MO(RAISE), KC_TAB, KC_RALT
    ),
/*
 * General Gaming Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   ESC  |   1  |   2  |   3  |   E  |   R  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  LSFT  |   Q  |   A  |   W  |   D  |   F  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   F1   |   Z  |   X  |   S  |   C  |   G  |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      | LCTL | Space|  R   |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [GAMING] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_E,    KC_R,                                        _______, _______, _______, _______, _______, _______,
      KC_LSFT, KC_Q,    KC_A,    KC_W,    KC_D,    KC_F,                                        _______, _______, _______, _______, _______, _______,
      KC_F1,   KC_Z,    KC_X,    KC_S,    KC_C,    KC_G,    XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______,
                                 XXXXXXX, XXXXXXX, KC_LCTL, KC_SPC,  KC_R,    _______, _______, _______, _______, _______
    ),
/*
 * FFXIV Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   ESC  |   1  |   2  |   3  |   R  |   E  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  TAB   |   Q  |   A  |   W  |   D  |   F  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | Adjust |   Z  |   X  |   S  |   C  |   G  |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | Space|  Alt | Shift| Ctrl |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [FFXIV] = LAYOUT(
      KC_ESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        _______, _______, _______, _______, _______, _______,
      KC_TAB,        KC_Q,    KC_A,    KC_W,    KC_D,    KC_F,                                        _______, _______, _______, _______, _______, _______,
      MO(FFXIVFUNC), KC_Z,    KC_X,    KC_S,    KC_C,    KC_G,    XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______,
                                       XXXXXXX, KC_SPC,  KC_LALT, KC_LSFT, KC_LCTL, _______, _______, _______, _______, _______
    ),
/*
 * FFXIV Function Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      | F7   | F8   | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      | F4   | F5   | F6   | F11  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | F1   | F2   | F3   | F12  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [FFXIVFUNC] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Lower Layer: Numpad, Media
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      | VolUp|      |      |                              | / ?  | 7 &  | 8 *  | 9 (  | - _  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next |      |                              | *    | 4 $  | 5 %  | 6 ^  | , <  | +      |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      | VolDn| Mute |      |      |      |  |      |      | 0 )  | 1 !  | 2 @  | 3 #  | = +  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [LOWER] = LAYOUT(
      _______, _______, _______, KC_VOLU, _______, _______,                                     KC_SLSH, KC_7,    KC_8,    KC_9, KC_MINS, _______,
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                                     KC_ASTR, KC_4,    KC_5,    KC_6, KC_COMM, KC_PLUS,
      _______, _______, _______, KC_VOLD, KC_MUTE, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3, KC_EQL,  _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Raise Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |  _   |  €   |      |      |  \     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [RAISE] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                     _______, KC_UNDS, ALGR(KC_5),_______,_______,KC_BSLS,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Navigation Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home | Up   | End  |      | ScrlLk |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | PgDn | Left | Down | Right|      | CapsLk |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, KC_SLCK,
      _______, _______, _______, _______, _______, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_CAPS,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Adjust Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      | F7   | F8   | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | SAI  | HUI  | VAI  |      |                              |      | F4   | F5   | F6   | F11  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  |      |      |      |  |      |      |      | F1   | F2   | F3   | F12  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [ADJUST] = LAYOUT(
      RGB_TOG, _______, _______, _______, _______, _______,                                     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      RGB_RMOD, _______, RGB_SAI, RGB_HUI, RGB_VAI, _______,                                     _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,
      RGB_MOD, _______, RGB_SAD, RGB_HUD, RGB_VAD, _______, _______, _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LOWER, RAISE, ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else { // Tap, paste
                    tap_code16(LCTL(KC_V));
                }
            }
            break;
    }
    return true;
}


bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

LEADER_EXTERNS();

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_C) { // Inline Code
            SEND_STRING("`` " SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        }
        SEQ_ONE_KEY(KC_P) { // Invoke Password Manager
            SEND_STRING(SS_LCTRL(SS_LALT("\\")));
        }
        SEQ_ONE_KEY(KC_S) { // Windows screenshot
            SEND_STRING(SS_LGUI("\nS"));
        }
        SEQ_TWO_KEYS(KC_F, KC_P) { // Fusion Projection prefix
            SEND_STRING("[Projection] ");
        }
        SEQ_TWO_KEYS(KC_B, KC_B) { // Basecone invoice description
            SEND_STRING("[Leveranciersnaam] [Factuurnummer]");
        }
        SEQ_TWO_KEYS(KC_E, KC_S) { // Support email splitkb
            SEND_STRING("support@splitkb.com");
        }
        SEQ_TWO_KEYS(KC_E, KC_T) { // Email splitkb
            SEND_STRING("thomas@splitkb.com");
        }
        SEQ_TWO_KEYS(KC_E, KC_P) { // Email personal
            SEND_STRING("mail@thomasbaart.nl");
        }
        SEQ_TWO_KEYS(KC_S, KC_D) { // Splitkb documentation
            SEND_STRING("https://docs.splitkb.com/");
        }
        SEQ_TWO_KEYS(KC_S, KC_V) { // Splitkb VAT number
            SEND_STRING("NL210593349B01");
        }
        SEQ_TWO_KEYS(KC_B, KC_C) { // Discord bongocat
            SEND_STRING(":bongocat:\n");
        }
        SEQ_TWO_KEYS(KC_C, KC_B) { // Discord code block
            SEND_STRING("```c" SS_LSFT("\n\n") "``` " SS_TAP(X_UP));
        }
        SEQ_TWO_KEYS(KC_Y, KC_S) { // Greeting
            SEND_STRING("Yours sincerely,\n\nThomas Baart");
        }
        SEQ_THREE_KEYS(KC_M, KC_V, KC_G) { // Greeting
            SEND_STRING("Met vriendelijke groet,\n\nThomas Baart");
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

/* ---------- LUNA ANIMATION -------- */

/* Graphical Luna dog animation display, requires WPM_ENABLE.
   Luna is 4x3 on OLED and its optimized for Kyria.
   Modified from @HellSingCoder's Luna dog
   (https://github.com/HellSingCoder/qmk_firmware/tree/master/keyboards/sofle/keymaps/HellSingCoder)

   Based on filterpaper code
   https://github.com/filterpaper/qmk_firmware/blob/filterspace/users/filterpaper/luna.c
*/

// Animation frame defaults
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40
#define LUNA_SIZE 96 // 96-byte arrays for the little dog
#define LUNA_FRAMES 2
#define LUNA_FRAME_DURATION 200 // Number of ms per frame

uint32_t luna_anim_timer = 0;
uint32_t luna_anim_sleep = 0;
uint8_t luna_current_frame = 0;
static long int luna_oled_timeout = 50000;

static void render_luna_sit(void) {
    static const char PROGMEM sit[LUNA_FRAMES][3][LUNA_SIZE/3] = {
        {
            {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x1c,
            0x02,0x05,0x02,0x24,0x04,0x04,0x02,0xa9,0x1e,0xe0,0x00,0x00,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x10,0x08,0x68,0x10,0x08,0x04,0x03,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x02,0x06,0x82,0x7c,0x03,0x00,0x00,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x0c,0x10,0x10,0x20,0x20,0x20,0x28,
            0x3e,0x1c,0x20,0x20,0x3e,0x0f,0x11,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
        },
        {
            {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x1c,
            0x02,0x05,0x02,0x24,0x04,0x04,0x02,0xa9,0x1e,0xe0,0x00,0x00,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0xe0,0x90,0x08,0x18,0x60,0x10,0x08,0x04,0x03,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x02,0x0e,0x82,0x7c,0x03,0x00,0x00,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x0c,0x10,0x10,0x20,0x20,0x20,0x28,
            0x3e,0x1c,0x20,0x20,0x3e,0x0f,0x11,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
        }
    };
    oled_set_cursor(7,5);
    luna_current_frame = (luna_current_frame + 1) % LUNA_FRAMES;
    oled_write_raw_P(sit[abs(1 - luna_current_frame)][0], LUNA_SIZE/3);
    oled_set_cursor(7,6);
    oled_write_raw_P(sit[abs(1 - luna_current_frame)][1], LUNA_SIZE/3);
    oled_set_cursor(7,7);
    oled_write_raw_P(sit[abs(1 - luna_current_frame)][2], LUNA_SIZE/3);
}

static void render_luna_walk(void) {
    static const char PROGMEM walk[LUNA_FRAMES][3][LUNA_SIZE/3] = {
        {
            {0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x20,0x10,0x90,0x90,0x90,0xa0,0xc0,0x80,0x80,
            0x80,0x70,0x08,0x14,0x08,0x90,0x10,0x10,0x08,0xa4,0x78,0x80,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x07,0x08,0xfc,0x01,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
            0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x18,0xea,0x10,0x0f,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x1c,0x20,0x20,0x3c,0x0f,0x11,0x1f,0x03,
            0x06,0x18,0x20,0x20,0x3c,0x0c,0x12,0x1e,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
        },
        {
            {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x20,0x20,0x20,0x40,0x80,0x00,0x00,0x00,
            0x00,0xe0,0x10,0x28,0x10,0x20,0x20,0x20,0x10,0x48,0xf0,0x00,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x1f,0x20,0xf8,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
            0x03,0x00,0x00,0x00,0x00,0x01,0x00,0x10,0x30,0xd5,0x20,0x1f,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x20,0x30,0x0c,0x02,0x05,0x09,0x12,0x1e,
            0x02,0x1c,0x14,0x08,0x10,0x20,0x2c,0x32,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
        }
    };
    oled_set_cursor(7,5);
    luna_current_frame = (luna_current_frame + 1) % LUNA_FRAMES;
    oled_write_raw_P(walk[abs(1 - luna_current_frame)][0], LUNA_SIZE/3);
    oled_set_cursor(7,6);
    oled_write_raw_P(walk[abs(1 - luna_current_frame)][1], LUNA_SIZE/3);
    oled_set_cursor(7,7);
    oled_write_raw_P(walk[abs(1 - luna_current_frame)][2], LUNA_SIZE / 3);
}

static void render_luna_run(void) {
    static const char PROGMEM run[LUNA_FRAMES][3][LUNA_SIZE/3] = {
        {
            {0x00,0x00,0x00,0x00,0xe0,0x10,0x08,0x08,0xc8,0xb0,0x80,0x80,0x80,0x80,0x80,0x80,
            0x80,0x40,0x40,0x3c,0x14,0x04,0x08,0x90,0x18,0x04,0x08,0xb0,0x40,0x80,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x01,0x02,0xc4,0xa4,0xfc,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc8,0x58,0x28,0x2a,0x10,0x0f,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x0e,0x09,0x04,0x04,0x04,0x04,0x02,0x03,0x02,0x01,0x01,
            0x02,0x02,0x04,0x08,0x10,0x26,0x2b,0x32,0x04,0x05,0x06,0x00,0x00,0x00,0x00,0x00}
        },
        {
            {0x00,0x00,0x00,0xe0,0x10,0x10,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
            0x80,0x80,0x78,0x28,0x08,0x10,0x20,0x30,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x03,0x04,0x08,0x10,0x11,0xf9,0x01,0x01,0x01,0x01,0x01,0x01,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x10,0xb0,0x50,0x55,0x20,0x1f,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x0c,0x10,0x20,0x28,0x37,
            0x02,0x1e,0x20,0x20,0x18,0x0c,0x14,0x1e,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
        }
    };
    luna_current_frame = (luna_current_frame + 1) % LUNA_FRAMES;
    oled_set_cursor(7,5);
    oled_write_raw_P(run[abs(1 - luna_current_frame)][0], LUNA_SIZE/3);
    oled_set_cursor(7,6);
    oled_write_raw_P(run[abs(1 - luna_current_frame)][1], LUNA_SIZE/3);
    oled_set_cursor(7,7);
    oled_write_raw_P(run[abs(1 - luna_current_frame)][2], LUNA_SIZE / 3);
}

static void render_luna_bark(void) {
    static const char PROGMEM bark[LUNA_FRAMES][3][LUNA_SIZE/3] = {
        {
            {0x00,0xc0,0x20,0x10,0xd0,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x40,
            0x3c,0x14,0x04,0x08,0x90,0x18,0x04,0x08,0xb0,0x40,0x80,0x00,0x00,0x00,0x00,0x00},
            {0x00,0x03,0x04,0x08,0x10,0x11,0xf9,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x80,0xc8,0x48,0x28,0x2a,0x10,0x0f,0x00,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x0c,0x10,0x20,0x28,0x37,0x02,0x02,
            0x04,0x08,0x10,0x26,0x2b,0x32,0x04,0x05,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
        },
        {
            {0x00,0xe0,0x10,0x10,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x40,
            0x40,0x2c,0x14,0x04,0x08,0x90,0x18,0x04,0x08,0xb0,0x40,0x80,0x00,0x00,0x00,0x00},
            {0x00,0x03,0x04,0x08,0x10,0x11,0xf9,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x48,0x28,0x2a,0x10,0x0f,0x20,0x4a,0x09,0x10},
            {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x0c,0x10,0x20,0x28,0x37,0x02,0x02,
            0x04,0x08,0x10,0x26,0x2b,0x32,0x04,0x05,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
        }
    };
    luna_current_frame = (luna_current_frame + 1) % LUNA_FRAMES;
    oled_set_cursor(7,5);
    oled_write_raw_P(bark[abs(1 - luna_current_frame)][0], LUNA_SIZE/3);
    oled_set_cursor(7,6);
    oled_write_raw_P(bark[abs(1 - luna_current_frame)][1], LUNA_SIZE/3);
    oled_set_cursor(7,7);
    oled_write_raw_P(bark[abs(1 - luna_current_frame)][2], LUNA_SIZE / 3);
}

static void render_luna_sneak(void) {
    static const char PROGMEM sneak[LUNA_FRAMES][3][LUNA_SIZE/3] = {
        {
            {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x40,0x40,0x40,0x80,0x00,0x00,0x00,0x00,
            0x00,0x00,0xc0,0x40,0x40,0x80,0x00,0x80,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x1e,0x21,0xf0,0x04,0x02,0x02,0x02,0x02,0x03,0x02,0x02,0x04,
            0x04,0x04,0x03,0x01,0x00,0x00,0x09,0x01,0x80,0x80,0xab,0x04,0xf8,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x1c,0x20,0x20,0x3c,0x0f,0x11,0x1f,0x02,0x06,
            0x18,0x20,0x20,0x38,0x08,0x10,0x18,0x04,0x04,0x02,0x02,0x01,0x00,0x00,0x00,0x00}
        },
        {
            {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0xe0,0xa0,0x20,0x40,0x80,0xc0,0x20,0x40,0x80,0x00,0x00,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x3e,0x41,0xf0,0x04,0x02,0x02,0x02,0x03,0x02,0x02,0x02,0x04,
            0x04,0x02,0x01,0x00,0x00,0x00,0x04,0x00,0x40,0x40,0x55,0x82,0x7c,0x00,0x00,0x00},
            {0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x20,0x30,0x0c,0x02,0x05,0x09,0x12,0x1e,0x04,
            0x18,0x10,0x08,0x10,0x20,0x28,0x34,0x06,0x02,0x01,0x01,0x00,0x00,0x00,0x00,0x00}
        }
    };
    luna_current_frame = (luna_current_frame + 1) % LUNA_FRAMES;
    oled_set_cursor(7,5);
    oled_write_raw_P(sneak[abs(1 - luna_current_frame)][0], LUNA_SIZE/3);
    oled_set_cursor(7,6);
    oled_write_raw_P(sneak[abs(1 - luna_current_frame)][1], LUNA_SIZE/3);
    oled_set_cursor(7,7);
    oled_write_raw_P(sneak[abs(1 - luna_current_frame)][2], LUNA_SIZE / 3);
}

void animate_luna(void) {

    void animation_phase(void) {
        if (get_mods() & (MOD_MASK_SHIFT)) { render_luna_bark(); }
        else if (get_mods() & (MOD_MASK_CAG)) { render_luna_sneak(); }
        else if (get_current_wpm() <= MIN_WALK_SPEED) { render_luna_sit(); }
        else if (get_current_wpm() <= MIN_RUN_SPEED) { render_luna_walk(); }
        else { render_luna_run(); }
    }

    // Animate on WPM, turn off OLED on idle
    if (get_current_wpm() != 000 || host_keyboard_led_state().caps_lock || get_mods() & (MOD_MASK_CSAG)) {
        oled_on();
        if (timer_elapsed32(luna_anim_timer) >LUNA_FRAME_DURATION) {
            luna_anim_timer = timer_read32();
            animation_phase();
        }
        luna_anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(luna_anim_sleep) > luna_oled_timeout) {
            oled_off();
        } else {
            if (timer_elapsed32(luna_anim_timer) >LUNA_FRAME_DURATION) {
                luna_anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

/*
static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}
*/

/* Old Render Status Code
static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("       Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case GAMING:
            oled_write_P(PSTR("Game\n"), false);
            break;
        case FFXIV:
            oled_write_P(PSTR("FFXIV\n"), false);
            break;
        case FFXIVFUNC:
            oled_write_P(PSTR("FFXIV Fnc\n"), false);
            break;
        case LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case NAV:
            oled_write_P(PSTR("Navigation\n"), false);s
            break;
        case ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK)    ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK)   ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}
*/

// Custom Render Status with Luna

static void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case GAMING:
            oled_write_P(PSTR("Game\n"), false);
            break;
        case FFXIV:
            oled_write_P(PSTR("FFXIV\n"), false);
            break;
        case FFXIVFUNC:
            oled_write_P(PSTR("FFXIV Fnc\n"), false);
            break;
        case LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }
    
    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK)    ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK)   ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
    
    // Luna
    //animate_luna();
}
  
void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        //animate_luna();
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Note: "clockwise" is actually counter-clockwise on a right master kyria...
        switch (biton32(layer_state)) {
            case QWERTY:
                // Advance to Gaming layer
                if (!clockwise) {
                    layer_move(GAMING);
                }
                break;
            case GAMING:
                // Return to QWERTY
                if (clockwise) {
                    layer_move(QWERTY);
                // Advance to FFXIV
                } else {
                    layer_move(FFXIV);
                }
                break;
            case FFXIV:
                // Return to Gaming
                if (clockwise) {
                    layer_move(GAMING);
                }
                break;
            default:
                // Switch between windows on Windows with alt tab.
                if (clockwise) {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                        register_code(KC_LALT);
                    } 
                    alt_tab_timer = timer_read();
                    tap_code16(KC_TAB);
                } else {
                    tap_code16(S(KC_TAB));
                }
                break;
        }
    } else if (index == 1) {
        switch (biton32(layer_state)) {
            case QWERTY:
                // Scrolling with PageUp and PgDn.
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            default:
                // Volume control.
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
}
#endif
