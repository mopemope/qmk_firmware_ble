/*
Copyright 2019 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "app_ble_func.h"
#include "keymap_jp.h"
#include <stdio.h>

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
    CXCF,
    CXCB,
    CXCS,
    CXO
};

#define QGMLWY  0
#define LOWER   1
#define RAISE   2
#define MISCL   3
#define MISCR   4
#define COMBA   5
#define COMBN   6
#define COMBE   7
#define COMBT   8
#define GAME1   9
#define GAME2  10
#define GAME3  11
#define GAME4  12
#define GAME5  13
#define GAME6  14
#define GAME7  15

#define WRKSP1 LALT(LCTL(KC_UP))
#define WRKSP2 LALT(LCTL(KC_DOWN))
#define UWRKSP LSFT(LALT(LCTL(KC_UP)))
#define DWRKSP LSFT(LALT(LCTL(KC_DOWN)))
#define PREVTB LSFT(LCTL(KC_UP))
#define NEXTTB LSFT(LCTL(KC_DOWN))
#define CAF2   LALT(LCTL(KC_F2))
#define CAF7   LALT(LCTL(KC_F7))

#define TAB    KC_TAB
//#define TAB    LT(MISCL,KC_TAB)
#define MINS   ALT_T(JP_MINS)
#define SMINS  SFT_T(JP_MINS)
#define SBSLS  SFT_T(JP_BSLS)
#define BSP    KC_BSPC
#define DEL    KC_DEL
#define SDEL   SFT_T(KC_DEL)
#define PSCR   KC_PSCR
#define SPSCR  LSFT(KC_PSCR)
#define RJ     LT(RAISE,KC_J)
#define LK     LT(LOWER,KC_K)
#define AC     LT(COMBA,KC_A)
#define NC     LT(COMBN,KC_N)
#define EC     LT(COMBE,KC_E)
#define KC     LT(COMBE,KC_K)
#define TC     LT(COMBT,KC_T)
//#define SPC    KC_SPC
#define SPC    LT(RAISE,KC_SPC)
#define LSPC   LT(LOWER,KC_SPC)
#define CSPC   LCTL(KC_SPC)
#define CRET   LCTL(KC_ENT)
// #define ENT    KC_ENT
#define ENT   LT(LOWER,KC_ENT)
#define CENT   CTL_T(KC_ENT)
#define BSPC   RCTL_T(KC_BSPC)
#define CTL    CTL_T(KC_BSPC)
#define ALT    ALT_T(KC_DEL)
#define SBSPC  SFT_T(KC_BSPC)
#define ABSPC  ALT_T(KC_BSPC)
#define CBSPC  CTL_T(KC_BSPC)
#define D_M    LT(MISCL,KC_D)
#define D_C    CTL_T(KC_D)
#define Z_A    ALT_T(KC_Z)
#define Z_C    CTL_T(KC_Z)
#define Z_S    LSFT_T(KC_Z)
#define I_S    LSFT_T(KC_I)
#define X_CT   LCTL_T(KC_X)
#define P_AL   LALT_T(KC_P)
#define J_C    RCTL_T(KC_J)
#define P_C    RCTL_T(KC_P)
#define A_C    RCTL_T(KC_A)
#define H_M    LT(MISCR,KC_H)
#define S_C    CTL_T(JP_SLSH)
#define S_S    RSFT_T(JP_SLSH)
#define V_A    LALT_T(KC_V)
#define O_C    CTL_T(KC_O)
#define AT_A   ALT_T(JP_AT)
#define AT_C   CTL_T(JP_AT)
#define GL     LGUI(KC_LEFT)
#define GU     LGUI(KC_UP)
#define GD     LGUI(KC_DOWN)
#define GR     LGUI(KC_RIGHT)
#define CLEFT  LCTL(KC_LEFT)
#define CUP    LCTL(KC_UP)
#define CDOWN  LCTL(KC_DOWN)
#define CRIGHT LCTL(KC_RIGHT)
#define MLEFT  LALT(KC_LEFT)
#define MUP    LALT(KC_UP)
#define MDOWN  LALT(KC_DOWN)
#define MRIGHT LALT(KC_RIGHT)
#define MLT    LALT(KC_LT)
#define MGT    LALT(KC_GT)
#define GH     LGUI(KC_H)
#define GTAB   TD(G_TAB)
#define ELT    TD(E_LT)
#define EGT    TD(E_GT)
#define EXLM   JP_EXLM
#define DQT    JP_DQT
#define HASH   JP_HASH
#define DLR    JP_DLR
#define PERC   JP_PERC
#define AMPR   JP_AMPR
#define QUOT   JP_QUOT
#define GRV    JP_GRV
#define PIPE   JP_PIPE
#define YEN    JP_YEN
#define AT     JP_AT
#define LCBR   JP_LCBR
#define RCBR   JP_RCBR
#define UNDS   JP_UNDS
#define TILD   JP_TILD
#define EQL    JP_EQL
#define COLN   JP_COLN
#define SLSH   JP_SLSH
#define ASTR   JP_ASTR
#define LPRN   JP_LPRN
#define RPRN   JP_RPRN
#define BSLS   JP_BSLS
#define CIRC   CTL_T(JP_CIRC)
#define SCLN   JP_SCLN
#define COMM   JP_COMM
#define CCOM   LCTL(JP_COMM)
#define DOT    JP_DOT
#define CDOT   LCTL(JP_DOT)
#define MCOM   LALT(JP_COMM)
#define MDOT   LALT(JP_DOT)
#define PLUS   JP_PLUS
#define LBRC   JP_LBRC
#define RBRC   ALT_T(JP_RBRC)
#define GUI    KC_LGUI
///#define GUI    LT(RAISE,KC_LGUI)
#define ZHTG   JP_ZHTG
#define C_S    SFT_T(KC_C)
#define ESC    KC_ESC
#define DQG    DF(QGMLWY)
#define DG1    DF(GAME1)
#define DG2    DF(GAME2)
#define DG3    DF(GAME3)
#define DG4    DF(GAME4)
#define DG5    DF(GAME5)
#define DG6    DF(GAME6)
#define DG7    DF(GAME7)
#define SELA   LCTL(KC_A)
#define COPY   LCTL(KC_C)
#define PASTE  LCTL(KC_V)
#define CZ     LCTL(KC_Z)
#define CSL    LCTL(JP_SLSH)
#define CF     LCTL(KC_F)
#define CMN    LALT(LCTL(KC_N))
#define CMM     LALT(LCTL(KC_M))
#define CMD    LALT(LCTL(JP_DOT))
#define CMY    LALT(LCTL(JP_YEN))
#define CG     LCTL(KC_G)
#define CT     LCTL(KC_T)
#define CC     LCTL(KC_C)
#define CS     LCTL(KC_S)
#define CX     LCTL(KC_X)
#define CL     LCTL(KC_L)
#define CK     LCTL(KC_K)
#define CE     LCTL(KC_E)
#define CP     LCTL(KC_P)
#define CN     LCTL(KC_N)
#define CAT    LCTL(JP_AT)
#define MX     LALT(KC_X)
#undef  MD
#define MD     LALT(KC_D)
#define MSCLN  LALT(JP_SCLN)
#define APERC  LALT(JP_PERC)
#define CPIPE  LCTL(JP_PIPE)
#define WH_D   KC_WH_D
#define WH_U   KC_WH_U
#define PGDN   KC_PGDN
#define PGUP   KC_PGUP
#define MS_L   KC_MS_L
#define MS_U   KC_MS_U
#define MS_D   KC_MS_D
#define MS_R   KC_MS_R
#define KLEFT  KC_LEFT
#define KUP    KC_UP
#define KDOWN  KC_DOWN
#define KRIGHT KC_RIGHT
#define MUTE   KC_MUTE
#define VOLD   KC_VOLD
#define VOLU   KC_VOLU
#define BTN2   KC_BTN2
#define BTN1   KC_BTN1
#define ASTG   KC_ASTG
#define C_V LCTL(KC_V)
#define M_V LALT(KC_V)
#define C_LT LCTL(JP_LT)
#define C_GT LCTL(JP_GT)

extern keymap_config_t keymap_config;

// Fillers to make layering more clear
#define _____ KC_TRNS
#define XXXXX KC_NO

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QGMLWY] = LAYOUT( // OK
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    XXXXX,   KC_Q,    KC_G,    KC_M,    KC_L,    KC_W,                             KC_Y,    KC_F,    KC_U,    KC_B,    BSP,     BSP,     \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    XXXXX,   D_M,     KC_S,    TC,      NC,      KC_R,    XXXXX,          ZHTG,    KC_I,    AC,      EC,      KC_O,    H_M,     XXXXX,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    KC_LSFT, Z_S,     X_CT,    KC_C,    V_A,     GUI,     XXXXX,          XXXXX,   KC_F12,  J_C,     KC_K,    P_AL,    S_S,     KC_RSFT, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               KC_LSFT, ALT,     CTL,     SPC,            ENT,     CTL,     ALT,     KC_RSFT \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [LOWER] = LAYOUT( // OK
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   EXLM,    DQT,     HASH,    DLR,     PERC,                             AMPR,    QUOT,    GRV,     PIPE,    YEN,     _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   ESC,     LPRN,    RPRN,    LCBR,    RCBR,    _____,          _____,   TILD,    PLUS,    ASTR,    EQL,     AT,      _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   CIRC,    LBRC,    RBRC,    KC_LT,   KC_GT,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [RAISE] = LAYOUT( // OK
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   TAB,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   _____,          _____,   KC_F5,   KC_F12,  KC_F7,   KC_F8,   AT,      _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   UNDS,    KC_F9,   KC_F10,  KC_F11,  _____,   _____,          _____,   DOT,     KC_F6,   KC_LT,   KC_GT,   MINS,    _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [MISCL] = LAYOUT( // OK
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   KUP,     _____,   WRKSP1,                           UWRKSP,  PGDN,    GU,      PGUP,    _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   KLEFT,   KDOWN,   KRIGHT,  WRKSP2,   CAF2,          PSCR,    DWRKSP,  GL,      GD,      GR,      _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,    CAF7,          BATT_LV, BTN1,    BTN2,    PSCR,    GH,      _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   COPY,    PASTE,    GUI,           _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [MISCR] = LAYOUT( // OK
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   _____,   _____,   _____,                            PREVTB,  MLT,     KUP,     MGT,     _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   TAB,     _____,   _____,   _____,   _____,   _____,          PSCR,    NEXTTB,  KLEFT,   KDOWN,   KRIGHT,  _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          BATT_LV, _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [COMBA] = LAYOUT( // OK
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    ZHTG,    ZHTG,    XXXXX,   CMM,     CL,      APERC,                            _____,   CXCF,    CK,      CXCB,    _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   MD,      CXCS,    CT,      CMN,     MX,      _____,          _____,   _____,   _____,   CE,      CXO,     CAT,     _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   CZ,      CX,      CC,      _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   ZHTG,           _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [COMBN] = LAYOUT( // OK
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   CG,      CMM,     CL,      _____,                            CMY,     MLEFT,   CP,      MRIGHT,  MD,      _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   TAB,     CS,      CT,      _____,   _____,   _____,          _____,   MSCLN,   CLEFT,   CN,      CRIGHT,  CAT,     _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   CX,      CRET,    CSPC,    _____,   _____,          _____,   MCOM,    MDOT,    CCOM,    CDOT,    CSL,     _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [COMBE] = LAYOUT( // OK
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   CUP,     _____,   _____,                            DQG,     MLEFT,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   CLEFT,   CDOWN,   CRIGHT,  _____,   _____,          ADV_ID0, _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          ADV_ID1, _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [COMBT] = LAYOUT( // OK
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   _____,   _____,   _____,                            DQT,     EXLM,    PLUS,    ASTR,    PIPE,    _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   ADV_ID0,        DEL_ID0, TILD,    EQL,     COLN,    SCLN,    AT,      _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   ADV_ID1,        DEL_ID1, _____,   MINS,    COMM,    DOT,     SLSH,    _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               AD_WO_L, ENT_SLP, _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [GAME1] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   _____,   _____,   _____,                            _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [GAME2] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   _____,   _____,   _____,                            _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [GAME3] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   _____,   _____,   _____,                            _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [GAME4] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   _____,   _____,   _____,                            _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [GAME5] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   _____,   _____,   _____,                            _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [GAME6] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   _____,   _____,   _____,                            _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),
  [GAME7] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _____,   _____,   _____,   _____,   _____,   _____,                            _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _____,   _____,   _____,   _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____,   _____,   _____,   _____,   \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _____,   _____,   _____,   _____,          _____,   _____,   _____,   _____   \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];
  switch (keycode) {
  case CXCF:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("xf"));
    }
    return false;
  case CXCB:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("xb"));
    }
    return false;
  case CXCS:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("xs"));
    }
    return false;
  case CXO:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("x") "o");
    }
    return false;
  }
  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU:
      bootloader_jump();
      return false;
    }
  } else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    }
  }
  return true;
};
