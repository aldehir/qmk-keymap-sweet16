#include QMK_KEYBOARD_H

#define TAP_F_INTERVAL 80

static bool holding_w = false;
static bool tapping_f = false;
static uint16_t last_tapped_f = 0;

enum custom_keycodes {
  HOLD_W = SAFE_RANGE,
  TAP_F,
  RESET_ALL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_4x4(
        LALT(KC_1), LALT(KC_2), LALT(KC_3), LALT(KC_4),
        LALT(KC_Q), LALT(KC_W), LALT(KC_E), LALT(KC_R),
        LALT(KC_A), LALT(KC_S), LALT(KC_D), LALT(KC_F),
        OSL(1),     LALT(KC_X), LALT(KC_C), LALT(KC_V)
    ),
    LAYOUT_ortho_4x4(
        KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_AUDIO_VOL_UP,
        LCA(KC_Q),           LCA(KC_W),           LCA(KC_E),           KC_AUDIO_VOL_DOWN,
        LCA(KC_A),           LCA(KC_S),           LCA(KC_D),           LCA(KC_F),
        LWIN(LSFT(KC_S)),    HOLD_W,              TAP_F,               RESET_ALL
    )
};


static void tap_f(void) {
    tap_code(KC_F);
    last_tapped_f = timer_read();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOLD_W:
            if (record->event.pressed) {
                holding_w = !holding_w;

                if (holding_w) {
                    register_code(KC_W);
                } else {
                    unregister_code(KC_W);
                }
            }
            return false;
        case TAP_F:
            if (record->event.pressed) {
                tapping_f = !tapping_f;

                if (tapping_f) {
                    tap_f();
                }
            }
            return false;
        case RESET_ALL:
            if (record->event.pressed) {
                if (holding_w) {
                    unregister_code(KC_W);
                }

                holding_w = false;
                tapping_f = false;
            }
            return false;
    }
    return true;
}

void matrix_scan_user(void) {
    if (tapping_f && timer_elapsed(last_tapped_f) > TAP_F_INTERVAL) {
        tap_f();
    }
}
