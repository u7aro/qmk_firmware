#include QMK_KEYBOARD_H
#include "enums.h"

extern uint8_t is_master;

/**
 * Configuration.
 */

// 単独でキーを押下した時にIMを英語に切り替えるキーコード
#define IM_MAC_EN_KC    KC_LGUI
#define IM_WIN_EN_KC    KC_LCTL

// 単独でキーを押下した時にIMを日本語に切り替えるキーコード
#define IM_MAC_JA_KC    KC_RALT
#define IM_WIN_JA_KC    KC_RALT

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGB_RST,
  LANCHER
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define RGB_MDF RGB_MOD
#define RGB_MDR RGB_RMOD
#define MT_SFES MT(MOD_LSFT, KC_ESC)
#define G_SPC   G(KC_SPACE)
#define MO_WEPN MO(_WEAPON)
#define TG_GAME TG(_GAME)
#define TG_WIN  TG(_WINDOWS)
#define CA_DEL  LCTL(LALT(KC_DEL))
#define VOLDOWN KC__VOLDOWN
#define VOLUP   KC__VOLUP
#define MUTE    KC__MUTE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
    KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,       KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_MINS , \
    KC_LCTL , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,       KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT , \
    KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,       KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT , \
                                    KC_LGUI , LOWER   , KC_SPC  ,   KC_ENT  , RAISE   , KC_RALT \
  ),

  [_WINDOWS] = LAYOUT( \
    _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , \
    _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , \
    _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , \
                                    KC_LCTL , _______ , _______ ,   _______ , _______ , _______ \
  ),

  [_LOWER] = LAYOUT( \
    KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,       KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_ESC  , \
    _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,       KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , KC_PGUP , XXXXXXX , \
    _______ , G(KC_Z) , G(KC_X) , G(KC_C) , G(KC_V) , XXXXXXX ,       _______ , _______ , _______ , _______ , KC_PGDN , _______ , \
                                    _______ , _______ , _______ ,   LANCHER , _______ , _______ \
  ),

  [_RAISE] = LAYOUT( \
    KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,       KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_UNDS , \
    KC_CAPS , KC_BSLS , KC_PIPE , KC_EQL  , KC_PLUS , KC_LBRC ,       KC_RBRC , KC_MINS , XXXXXXX , XXXXXXX , KC_COLN , KC_DQUO , \
    _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LCBR ,       KC_RCBR , XXXXXXX , KC_LABK , KC_RABK , KC_QUES , _______ , \
                                    _______ , _______ , KC_BSPC ,   _______ , _______ , _______ \
  ),

  [_ADJUST] = LAYOUT( \
    KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,       KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , \
    RGB_TOG , RGB_HUI , RGB_SAI , RGB_VAI , RGB_SPI , RGB_MDF ,       TG_WIN  , _______ , _______ , _______ , _______ , _______ , \
    RGB_RST , RGB_HUD , RGB_SAD , RGB_VAD , RGB_SPD , RGB_MDR ,       TG_GAME , _______ , _______ , _______ , _______ , _______ , \
                                    _______ , _______ , _______ ,   _______ , _______ , _______ \
  ),

  [_GAME] = LAYOUT( \
    _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , \
    _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , \
    _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , \
                                    KC_LALT , _______ , _______ ,   _______ , _______ , _______ \
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
  // When add source files to SRC in rules.mk, you can use functions.
  const char *read_layer_state(void);
  const char *read_logo(void);
  void count_up(void);
  const char *read_countlog(void);
  void set_wpm(void);
  const char *read_wpm_string(void);

  void matrix_scan_user(void) {
     iota_gfx_task();
  }

  void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
      matrix_write_ln(matrix, read_layer_state());
      matrix_write(matrix, "------+--------------");
      matrix_write_ln(matrix, read_wpm_string());
      matrix_write(matrix, read_countlog());
    } else {
      matrix_write(matrix, read_logo());
    }
  }

  void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
      memcpy(dest->display, source->display, sizeof(dest->display));
      dest->dirty = true;
    }
  }

  void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
  }
#endif//SSD1306OLED


static uint16_t last_pressed_kc = 0;
static uint16_t im_lang = 0;
static bool is_lctl_pressing = false;
static bool is_lgui_pressing = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    last_pressed_kc = keycode;
    #ifdef SSD1306OLED
      count_up();
      set_wpm();
    #endif
  }

  // 特定の修飾キーを単発で押した時にIMの言語を切り替える
  if (IS_LAYER_ON(_QWERTY)) {
    switch (keycode) {
      case IM_MAC_EN_KC:
      case IM_MAC_JA_KC:
        if (!record->event.pressed) {
          // 離した keycode のキーと最後に押したキーが同じ（キーを単独で押して離した）場合
          if (last_pressed_kc == keycode) {
            im_lang = (keycode == IM_MAC_EN_KC) ? KC_LANG2 : KC_LANG1;
            unregister_code(keycode);
            register_code(im_lang);
            unregister_code(im_lang);
          }
        }
        break;
    }
  } else if (IS_LAYER_ON(_WINDOWS)) {
    switch (keycode) {
      case IM_WIN_EN_KC:
      case IM_WIN_JA_KC:
        if (!record->event.pressed) {
          // 離した keycode のキーと最後に押したキーが同じ（キーを単独で押して離した）場合
          if (last_pressed_kc == keycode) {
            // Google 日本語入力のキーバインドの設定は以下の通りにすることを想定
            //   直接入力: F23: ひらがな入力
            //   入力中: F24: IME 無効
            im_lang = (keycode == IM_WIN_EN_KC) ? KC_F23 : KC_F24;
            unregister_code(keycode);
            register_code(im_lang);
            unregister_code(im_lang);
          }
        }
        break;
    }
  }

  switch (keycode) {
    case KC_LGUI:
      if (record->event.pressed) {
        is_lgui_pressing = true;
      } else {
        is_lgui_pressing = false;
      }
      break;

    case KC_LCTL:
      if (record->event.pressed) {
        is_lctl_pressing = true;
      } else {
        is_lctl_pressing = false;
      }
      break;

    case KC_MINS:
      if (record->event.pressed) {
        // 左CTRLを押しながら - キーを押した時にESCキーを押したことにする。
        // Vimのキーバインドを真似ているため本来は [ キーに設定するべきだが、
        // キー配置の都合からキーを変更。
        if (is_lctl_pressing) {
          unregister_code(KC_LCTL);
          // 通常モードに入った時にIMEの言語を英語に戻す。
          if (im_lang != KC_LANG2) {
            register_code(KC_LANG2);
            unregister_code(KC_LANG2);
            im_lang = KC_LANG2;
          }
          register_code(KC_ESC);
          unregister_code(KC_ESC);
          return false;
        }
      }
      break;

    case KC_SCLN:
      // CMD 押しながら ; キーを押した時に [ を返す.
      // 「戻る」などで使うOSのショートカットをしやすくるための機能
      if (record->event.pressed) {
        if (is_lgui_pressing) {
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          return false;
        }
      }
      break;

    case KC_QUOT:
      // CMD 押しながら ' キーを押した時に ] を返す.
      // 「進む」などで使うOSのショートカットをしやすくるための機能
      if (record->event.pressed) {
        if (is_lgui_pressing) {
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
          return false;
        }
      }
      break;

    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;

    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      return false;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      return false;

    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;

    case RGB_RST:
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
        }
      #endif
      break;

    // Mac / Windows それぞれの環境でランチャーを起動するキーコードを送信
    case LANCHER:
      if (!record->event.pressed) {
        if (IS_LAYER_ON(_WINDOWS)) {
          register_code(KC_LGUI);
          unregister_code(KC_LGUI);
        } else {
          register_code(KC_LGUI);
          register_code(KC_SPACE);
          unregister_code(KC_SPACE);
          unregister_code(KC_LGUI);
        }
      }
      return false;
  }

  return true;
}
