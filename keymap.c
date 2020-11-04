#include QMK_KEYBOARD_H

enum custom_keycodes {
  UP_URL = SAFE_RANGE
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
        LWIN(LSFT(KC_S)),    LCA(KC_X),           LCA(KC_C),           LCA(KC_V)
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UP_URL:
            if (record->event.pressed) {
                SEND_STRING("http://1upkeyboards.com");
            }
            return false;
            break;
    }
    return true;
}
