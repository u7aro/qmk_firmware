#include QMK_KEYBOARD_H
#include "crkbd.h"
#include "enums.h"

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (get_highest_layer(layer_state)) {
    case _QWERTY:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer | MAC");
      break;
    case _WINDOWS:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer | WINDOWS");
      break;
    case _RAISE:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer | RAISE");
      break;
    case _LOWER:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer | LOWER");
      break;
    case _ADJUST:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer | ADJUST");
      break;
    case _GAME:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer | GAME");
      break;
    case _WEAPON:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer | WEAPON");
      break;
    default:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer | Undef-%ld", layer_state);
  }

  return layer_state_str;
}
