// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for the LED wavepool effect.
#include <Kaleidoscope-LED-Wavepool.h>

// Support for playing a short animation on boot.
#include "Kaleidoscope-LEDEffect-BootAnimation.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for one-shot modifier and layers.
#include <Kaleidoscope-OneShot.h>
#include <Kaleidoscope-Escape-OneShot.h>

// Show the active modifier.
#include <Kaleidoscope-LED-ActiveModColor.h>

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_ANY,
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { PRIMARY, NUMPAD, FUNCTION, QWERTY, MOUSE }; // layers


/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(

  [PRIMARY] = KEYMAP_STACKED
  (LSHIFT(Key_4), LSHIFT(Key_7), Key_LeftBracket, Key_LeftCurlyBracket, Key_RightCurlyBracket, Key_LeftParen, Key_Equals,
   Key_Tab, Key_Semicolon, Key_Comma, Key_Period, Key_P, Key_Y, ShiftToLayer(NUMPAD),
   OSM(LeftControl),   Key_A,         Key_O,     Key_E,      Key_U, Key_I,
   OSM(LeftShift), Key_Quote, Key_Q,     Key_J,      Key_K, Key_X, LCTRL(LALT(Key_Delete)),
   Key_LeftGui, Key_Enter, Key_Tab, LALT(Key_Tab),
   MoveToLayer(QWERTY),

   LSHIFT(Key_8),  Key_RightParen, LSHIFT(Key_Equals), Key_RightBracket, LSHIFT(Key_1), LSHIFT(Key_3), Key_Backslash,
   OSL(NUMPAD), Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
                         Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
   Key_Escape,   Key_B, Key_M, Key_W, Key_V, Key_Z, OSM(LeftAlt),
   OSM(LeftAlt), Key_Backspace, Key_Spacebar, OSL(FUNCTION),
   ___),


  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, LSHIFT(Key_1), LSHIFT(Key_2), Key_LeftCurlyBracket, Key_RightCurlyBracket, Key_Pipe, ___,
   ___, LSHIFT(Key_3), LSHIFT(Key_4), Key_LeftParen, Key_RightParen, Key_Backtick,
   ___, LSHIFT(Key_5), LSHIFT(Key_6), Key_LeftBracket, Key_RightBracket, LSHIFT(Key_Backtick), ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_0, Key_Period, Key_KeypadMultiply, Key_KeypadSubtract, ___,
   ___,                    ___, Key_7, Key_8,      Key_9,              Key_KeypadAdd,      ___,
                           ___, Key_4, Key_5,      Key_6,              Key_Equals,         ___,
   ___,                    ___, Key_1, Key_2,      Key_3,              Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, Key_0,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           Key_CapsLock,
   ___, ___, ___, ___,  ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___,  ___, ___, ___,  ___,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, LSHIFT(Key_7),            LSHIFT(Key_8),            LSHIFT(Key_9),   LSHIFT(Key_0),    Key_F12,
                               ___,                    Key_LeftArrow,            Key_DownArrow,            Key_UpArrow,     Key_RightArrow,   ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   LockLayer(MOUSE)),

  [QWERTY] = KEYMAP_STACKED
  (MoveToLayer(PRIMARY), Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Tab, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Enter,
   Key_LeftControl,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_LeftShift, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_Spacebar, Key_Tab, Key_LeftAlt,
   MoveToLayer(PRIMARY),

   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NUMPAD),
   ShiftToLayer(NUMPAD), Key_Y, Key_U, Key_I, Key_O,      Key_P,         Key_Equals,
                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   MoveToLayer(PRIMARY),  Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_Backspace, Key_Enter, Key_RightControl,
   ShiftToLayer(FUNCTION)),

  [MOUSE] =  KEYMAP_STACKED
  (___, ___, ___, ___,  ___, ___, ___,
   ___, ___,              Key_mouseWarpNW, Key_mouseWarpN,  Key_mouseWarpNE, Key_mouseBtnR, ___,
   ___, Key_mouseWarpEnd, Key_mouseWarpW, Key_mouseWarpIn, Key_mouseWarpE, Key_mouseBtnL,
   ___, ___,              Key_mouseWarpSW, Key_mouseWarpS, Key_mouseWarpSE, Key_mouseBtnM,  ___,
   Key_mouseBtnM, Key_mouseBtnL, Key_mouseBtnR, ___,
   ___,

   ___, ___, ___, ___,  ___, ___, ___,
   ___,                    ___, Key_mouseUpL, Key_mouseUp, Key_mouseUpR, ___,  ___,
                           ___, Key_mouseL, Key_mouseDn, Key_mouseR, ___, ___,
   ___,                    ___, Key_mouseDnL, Key_mouseDn, Key_mouseDnR, ___, ___,
   Key_mouseScrollL, Key_mouseScrollR, Key_mouseScrollDn, Key_mouseScrollUp,
   ___)
) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t key_state) {
  if (keyToggledOn(key_state)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    event.key.setKeyCode(Key_A.getKeyCode() + (uint8_t)(millis() % 36));
    event.key.setFlags(0);
  }
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(event.state);
    break;

  case MACRO_ANY:
    anyKeyMacro(event);
    break;
  }
  return MACRO_NONE;
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
    // LEDControl provides support for other LED modes
    LEDControl,

    // The boot greeting effect pulses the LED button for 10 seconds after the
    // keyboard is first connected
    BootAnimationEffect,

    // We start with the LED effect that turns off all the LEDs.
    LEDOff,

    // Use the wavepool effect when typing.
    WavepoolEffect,

    // The macros plugin adds support for macros
    Macros,

    // Adds keys for moving the mouse.
    MouseKeys,

    // The HostPowerManagement plugin allows us to turn LEDs off when then host
    // goes to sleep, and resume them when it wakes up.
    HostPowerManagement,

    // One-shot modifiers.
    OneShot, EscapeOneShot,

    // Highlight active modifiers
    ActiveModColorEffect);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  MouseKeys.speed = 8;
  MouseKeys.accelSpeed = 4;
  MouseKeys.wheelSpeed = 2;
  MouseKeys.setSpeedLimit(64);
  MouseKeys.setWarpGridSize(MOUSE_WARP_GRID_3X3);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  // LEDOff.activate();
  WavepoolEffect.idle_timeout = 0;
  WavepoolEffect.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
