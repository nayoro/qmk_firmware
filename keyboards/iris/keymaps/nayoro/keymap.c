#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _META  1
#define _NUMPAD 2
#define _ADJUST 3

enum custom_keycodes {
   KANA1 = SAFE_RANGE
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_RST RESET
#define KC_DBUG DEBUG

#define KC_LORW LT(MO(_NUMPAD), KC_LANG2)
#define KC_RASE KANA1
#define KC_NUM TT(_NUMPAD)
#define KC_MSPC LT(MO(_META), KC_SPC)
#define KC_GTAB MT(MOD_LGUI, KC_TAB)
#define KC_MAC MAGIC_UNSWAP_RALT_RGUI
#define KC_WIN MAGIC_SWAP_RALT_RGUI
#define KC_GBSP MT(MOD_LGUI, KC_BSPC)
#define KC_HGRV MT(MOD_HYPR, KC_GRV)
#define KC_SLBC MT(MOD_LSFT, KC_LBRC)
#define KC_SRBC MT(MOD_RSFT, KC_RBRC)
#define KC_CAD ALTG(KC_DEL)
#define KC_CAI ALTG(KC_INS)
#define KC_AESC LT(MO(_ADJUST), KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     AESC, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     GTAB, Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,ENT ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCTL, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     SLBC, Z  , X  , C  , V  , B  ,EQL,      MINS, N  , M  ,COMM,DOT ,SLSH,SRBC,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LORW,MSPC,        GBSP,RASE,HGRV
  //                  `----+----+----'        `----+----+----'
  ),

  [_META] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         , F1 , F2,  F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,PSCR,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,F11 ,F12 ,    ,    ,    ,                   ,HOME,PGDN,PGUP,END ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,               BSPC,LEFT,DOWN, UP ,RGHT,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,CAI ,     CAD ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_NUMPAD] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,               HASH, 7  , 8  , 9  , 0  ,ASTR,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,               LPRN, 4  , 5  , 6  ,RPRN,SLSH,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,               LBRC, 1  , 2  , 3  ,RBRC,PLUS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,LCBR,PERC,COMM,DOT ,RCBR,MINS,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,RST ,    ,    ,    ,DBUG,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,MAC ,     WIN ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),


};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KANA1:
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
