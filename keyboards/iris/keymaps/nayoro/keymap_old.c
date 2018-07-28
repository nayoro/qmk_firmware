#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _SYMB 1
#define _NUMPAD 2
#define _META 3

enum custom_keycodes {
  EISU = SAFE_RANGE,
  KANA
};


#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_RST RESET
#define KC_DBUG DEBUG

#define KC_LORW LT(MO(_SYMB), KC_LANG2)
#define KC_RASE LT(MO(_SYMB), KC_LANG1)
#define KC_NUM TT(_NUMPAD)
#define KC_MSPC LT(MO(_META), KC_SPC)
#define KC_GTAB MT(MOD_LGUI, KC_TAB)
#define KC_MAC MAGIC_UNSWAP_RALT_RGUI
#define KC_WIN MAGIC_SWAP_RALT_RGUI
#define KC_GBSP MT(MOD_LGUI, KC_BSPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC ,GRV ,BSLS,LBRC,RBRC,ASTR,               PLUS,MINS,LEFT,DOWN, UP, RGHT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     GTAB, Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,ENT ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCTL, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,NUM ,     HYPR, N  , M  ,COMM,DOT ,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LORW,MSPC,        MSPC,RASE,GBSP
  //                  `----+----+----'        `----+----+----'
  ),

  [_SYMB] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_NUMPAD] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,               LPRN,RPRN,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,               LBRC,RBRC, 7  , 8  , 9  ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,               COMM,DOT , 4  , 5  , 6  ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,ASTR, 0  , 1  , 2  , 3  ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_META] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         , F1 , F2,  F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    , UP ,    ,    ,MAC ,               WIN ,HOME,PGUP,PGDN,END ,F12 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,LEFT,DOWN,RGHT,    ,    ,               BSPC,LEFT,DOWN, UP ,RGHT,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,RST ,DBUG,PSCR,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case EISU:
    if (record->event.pressed) {
      if(keymap_config.swap_ralt_rgui==false){
        register_code(KC_LANG2);
      }else{
        SEND_STRING(SS_LALT("`"));
      }
    } else {
      unregister_code(KC_LANG2);
    }
    return false;
    break;
  case KANA:
    if (record->event.pressed) {
      if(keymap_config.swap_ralt_rgui==false){
        register_code(KC_LANG1);
      }else{
        SEND_STRING(SS_LALT("`"));
      }
    } else {
      unregister_code(KC_LANG1);
    }
    return false;
    break;
  }
  return true;
}
