#include QMK_KEYBOARD_H

#define TAP_RATE_MIN 25
#define TAP_RATE_MAX 500
#define TAP_RATE_INCREMENT 25

enum custom_keycodes {
  HOLD_W = SAFE_RANGE,
  TAP_F,
  INCREASE_TAP_RATE,
  DECREASE_TAP_RATE,
  RESET_ALL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_4x4(
        TO(0),               TO(1),               TO(2),               TO(3),
        KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_AUDIO_VOL_UP,
        KC_NO,               KC_NO,               KC_NO,               KC_AUDIO_VOL_DOWN,
        LWIN(LSFT(KC_S)),    KC_NO,               KC_NO,               KC_NO
    ),
    LAYOUT_ortho_4x4(
        _______,    _______,    _______,    _______,
        LALT(KC_Q), LALT(KC_W), LALT(KC_E), LALT(KC_R),
        LALT(KC_A), LALT(KC_S), LALT(KC_D), LALT(KC_F),
        LALT(KC_Z), LALT(KC_X), LALT(KC_C), LALT(KC_V)
    ),
    LAYOUT_ortho_4x4(
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    INCREASE_TAP_RATE,
        HOLD_W,     TAP_F,      RESET_ALL,  DECREASE_TAP_RATE
    )
};

static bool holding_w = false;
static bool tapping_f = false;
static uint16_t tap_rate = 75;
static uint16_t last_tapped_f = 0;

static void tap_f(void);
static void increase_tap_rate(keyrecord_t *record);
static void decrease_tap_rate(keyrecord_t *record);

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
        case INCREASE_TAP_RATE:
            increase_tap_rate(record);
            return false;
        case DECREASE_TAP_RATE:
            decrease_tap_rate(record);
            return false;
    }
    return true;
}

void matrix_scan_user(void) {
    if (tapping_f && timer_elapsed(last_tapped_f) > tap_rate) {
        tap_f();
    }
}

static void tap_f(void) {
    tap_code(KC_F);
    last_tapped_f = timer_read();
}

static void increase_tap_rate(keyrecord_t *record) {
    if (!record->event.pressed) return;

    tap_rate -= TAP_RATE_INCREMENT;

    if (tap_rate < TAP_RATE_MIN) {
        tap_rate = TAP_RATE_MIN;
    }
}

static void decrease_tap_rate(keyrecord_t *record) {
    if (!record->event.pressed) return;

    tap_rate += TAP_RATE_INCREMENT;

    if (tap_rate > TAP_RATE_MAX) {
        tap_rate = TAP_RATE_MAX;
    }
}
