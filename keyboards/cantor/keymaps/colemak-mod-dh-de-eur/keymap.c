// Copyright 2024 j-hap (@j-hap)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "keymap_eurkey.h"
// #include "print.h"
// #include "limits.h" // for CHAR_BIT (number of bits in a char)

// void print_layer_state(layer_state_t state) {
//     int           nBits = sizeof(state) * CHAR_BIT;
//     layer_state_t mask  = 1 << (nBits - 1);
//     for (int iBit = nBits; iBit-- > 0;) {
//         int active = (state & mask) > 0;
//         printf("Layer %d active: %d\n", iBit, active);
//         mask = mask >> 1;
//     }
// }

enum LAYER { DE_BASE_, EU_BASE_, DE_SYML_, DE_SYMR_, EU_SYML_, EU_SYMR_, NUM_, NAV_ };

#define DE_CSS S(ALGR(DE_SS))

// custom shift key behavior for certain keys, by defaul the modifier trigger is suppressed on the replacement key code
const key_override_t shift_backspace_delete_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_BSPC, KC_DEL, (1 << DE_BASE_) | (1 << EU_BASE_));

const key_override_t de_shift_dquote_quote_override     = ko_make_with_layers(MOD_MASK_SHIFT, DE_DQUO, DE_QUOT, 1 << DE_BASE_);
const key_override_t de_shift_comma_exlamation_override = ko_make_with_layers(MOD_MASK_SHIFT, DE_COMM, DE_EXLM, 1 << DE_BASE_);
const key_override_t de_shift_semicolon_colon_override  = ko_make_with_layers(MOD_MASK_SHIFT, DE_SCLN, DE_COLN, 1 << DE_BASE_); // no need for this on the eurkey layout
const key_override_t de_shift_dot_question_override     = ko_make_with_layers(MOD_MASK_SHIFT, DE_DOT, DE_QUES, 1 << DE_BASE_);

const key_override_t eu_shift_dquote_quote_override     = ko_make_with_layers(MOD_MASK_SHIFT, EU_DQUO, EU_QUOT, 1 << EU_BASE_);
const key_override_t eu_shift_comma_exlamation_override = ko_make_with_layers(MOD_MASK_SHIFT, EU_COMM, EU_EXLM, 1 << EU_BASE_);
const key_override_t eu_shift_dot_question_override     = ko_make_with_layers(MOD_MASK_SHIFT, EU_DOT, EU_QUES, 1 << EU_BASE_);

// This globally defines all key overrides to be used
// clang-format off
const key_override_t *key_overrides[] = {
    &shift_backspace_delete_override,
    &de_shift_dquote_quote_override,
    &de_shift_comma_exlamation_override,
    &de_shift_semicolon_colon_override,
    &de_shift_dot_question_override,
    &eu_shift_dquote_quote_override,
    &eu_shift_comma_exlamation_override,
    &eu_shift_dot_question_override,
};
// clang-format on

enum combo_events { SWP_BASE };

const uint16_t PROGMEM toggle_base_layer_combo[] = {KC_G, KC_M, COMBO_END};

combo_t key_combos[] = {[SWP_BASE] = COMBO_ACTION(toggle_base_layer_combo)};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (combo_index == SWP_BASE && pressed) {
        if (IS_LAYER_ON(DE_BASE_)) {
            set_single_persistent_default_layer(EU_BASE_);
        } else if (IS_LAYER_ON(EU_BASE_)) {
            set_single_persistent_default_layer(DE_BASE_);
        }
        layer_state_set(default_layer_state);
    }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DE_BASE_] = LAYOUT_split_3x6_3(
        KC_ESC,               KC_Q,                 KC_W,                 KC_F,                 KC_P,                 KC_B,                                  KC_J,                 KC_L,                 KC_U,                 DE_Y,              DE_ODIA,              DE_DQUO,
        DE_ADIA,              LGUI_T(KC_A),         LALT_T(KC_R),         LSFT_T(KC_S),         LCTL_T(KC_T),         KC_G,                                  KC_M,         RCTL_T(KC_N),         RSFT_T(KC_E),         LALT_T(KC_I),         RGUI_T(KC_O),              DE_SCLN,
        KC_TAB,               DE_Z,                 KC_X,                 KC_C,                 KC_D,                 KC_V,                                  KC_K,                 KC_H,              DE_UDIA,                DE_SS,              KC_COMM,               KC_DOT,
                                                                          S(KC_LGUI),           LT(NAV_, KC_SPC),     LT(DE_SYMR_, KC_DEL),  LT(DE_SYML_, KC_ENT),              KC_BSPC,             MO(NUM_)
    ),
    [EU_BASE_] = LAYOUT_split_3x6_3(
        KC_ESC,               KC_Q,                 KC_W,                 KC_F,                 KC_P,                 KC_B,                                  KC_J,                 KC_L,                 KC_U,                 KC_Y,              EU_ODIA,              EU_DQUO,
        EU_ADIA,              LGUI_T(KC_A),         LALT_T(KC_R),         LSFT_T(KC_S),         LCTL_T(KC_T),         KC_G,                                  KC_M,         RCTL_T(KC_N),         RSFT_T(KC_E),         LALT_T(KC_I),         RGUI_T(KC_O),              EU_SCLN,
        KC_TAB,               KC_Z,                 KC_X,                 KC_C,                 KC_D,                 KC_V,                                  KC_K,                 KC_H,              EU_UDIA,                EU_SS,              KC_COMM,               KC_DOT,
                                                                          S(KC_LGUI),           LT(NAV_, KC_SPC),     LT(EU_SYMR_, KC_DEL),  LT(EU_SYML_, KC_ENT),              KC_BSPC,             MO(NUM_)
    ),
    [DE_SYML_] = LAYOUT_split_3x6_3(
        XXXXXXX,  DE_AT,    DE_DLR,   DE_AMPR,  DE_ASTR,  DE_GRV,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  DE_TILD,  DE_MINS,  DE_EQL,   DE_UNDS,  DE_BSLS,    XXXXXXX,  KC_RCTL,  KC_RSFT,  KC_LALT,  KC_RGUI,  XXXXXXX,
        XXXXXXX,  DE_ACUT,  DE_PLUS,  DE_LABK,  DE_RABK,  DE_CIRC,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                      XXXXXXX,  XXXXXXX,  XXXXXXX,    KC_TRNS,  XXXXXXX,  XXXXXXX
    ),
    [DE_SYMR_] = LAYOUT_split_3x6_3(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    DE_HASH,  DE_LBRC,  DE_RBRC,  DE_EURO,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  KC_RGUI,  KC_LALT,  KC_RSFT,  KC_RCTL,  XXXXXXX,    DE_SLSH,  DE_LPRN,  DE_RPRN,  DE_PIPE,  DE_DEG,   XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    DE_PERC,  DE_LCBR,  DE_RCBR,  DE_SECT,  XXXXXXX,  XXXXXXX,
                                      XXXXXXX,  XXXXXXX,  KC_TRNS,    XXXXXXX,  XXXXXXX,  XXXXXXX
    ),
    [EU_SYML_] = LAYOUT_split_3x6_3(
        XXXXXXX,  EU_AT,    EU_DLR,   EU_AMPR,  EU_ASTR,  EU_GRV,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  EU_TILD,  EU_MINS,  EU_EQL,   EU_UNDS,  EU_BSLS,    XXXXXXX,  KC_RCTL,  KC_RSFT,  KC_LALT,  KC_RGUI,  XXXXXXX,
        XXXXXXX,  EU_ACUT,  EU_PLUS,  EU_LABK,  EU_RABK,  EU_CIRC,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                      XXXXXXX,  XXXXXXX,  XXXXXXX,    KC_TRNS,  XXXXXXX,  XXXXXXX
    ),
    [EU_SYMR_] = LAYOUT_split_3x6_3(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    EU_HASH,  EU_LBRC,  EU_RBRC,  EU_EURO,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_LCTL,  XXXXXXX,    EU_SLSH,  EU_LPRN,  EU_RPRN,  EU_PIPE,  EU_DEG,   XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    EU_PERC,  EU_LCBR,  EU_RCBR,  EU_SECT,  XXXXXXX,  XXXXXXX,
                                      XXXXXXX,  XXXXXXX,  KC_TRNS,    XXXXXXX,  XXXXXXX,  XXXXXXX
    ),
    [NUM_] = LAYOUT_split_3x6_3(
        XXXXXXX,  XXXXXXX,  KC_7,     KC_8,     KC_9,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  KC_4,     KC_5,     KC_6,     XXXXXXX,    XXXXXXX,  KC_RCTL,  KC_RSFT,  KC_LALT,  KC_RGUI,  XXXXXXX,
        XXXXXXX,  KC_0,     KC_1,     KC_2,     KC_3,     XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                      XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  KC_TRNS
    ),
    [NAV_] = LAYOUT_split_3x6_3(
       XXXXXXX,       KC_F9,         KC_F10,        KC_F11,        KC_F12,        C(KC_X),              KC_PGUP,       KC_HOME,         KC_UP,        KC_END,       KC_PSCR,       KC_VOLU,
       KC_CAPS,       LGUI_T(KC_F5), LALT_T(KC_F6), LSFT_T(KC_F7), LCTL_T(KC_F8), C(KC_C),              KC_PGDN,       KC_LEFT,       KC_DOWN,      KC_RIGHT,       XXXXXXX,       KC_MUTE,
       XXXXXXX,       KC_F1,         KC_F2,         KC_F3,         KC_F4,         C(KC_V),              XXXXXXX,       KC_RCTL,       KC_RSFT,       KC_LALT,       KC_RGUI,       KC_VOLD,
                                                    XXXXXXX,       KC_TRNS,       XXXXXXX,              KC_RSFT,       KC_RCTL,       KC_RGUI
    ),
};
// clang-format on

// makes the dead gravis `, and circumflex ^ keys on a german keyboard non-dead
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // only send space after dead key on release
    if ((IS_LAYER_ON(DE_SYML_) || IS_LAYER_ON(DE_SYMR_)) && !record->event.pressed) {
        switch (keycode) {
            case DE_CIRC:
            case DE_GRV: {
                register_code(KC_SPACE);
                unregister_code(KC_SPACE);
                return;
            }
        }
    }
}

//
// ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
// │   │   │   │   │   │   │       │   │   │   │   │   │   │
// ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
// │   │   │   │   │   │   │       │   │   │   │   │   │   │
// ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
// │   │   │   │   │   │   │       │   │   │   │   │   │   │
// └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
//             ┌───┬───┬───┐       ┌───┬───┬───┐
//             │   │   │   │       │   │   │   │
//             └───┴───┴───┘       └───┴───┴───┘
//

void keyboard_post_init_user(void) {
    layer_state_set(default_layer_state);
}
