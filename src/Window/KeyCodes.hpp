#pragma once
#include "../stl_headers.hpp"


#define NUMBER_KEYS            349
#define NUMBER_MOUSE_BUTTONS   8

/* Mouse buttons */
#define MOUSE_BUTTON_1         0
#define MOUSE_BUTTON_2         1
#define MOUSE_BUTTON_3         2
#define MOUSE_BUTTON_4         3
#define MOUSE_BUTTON_5         4
#define MOUSE_BUTTON_6         5
#define MOUSE_BUTTON_7         6
#define MOUSE_BUTTON_8         7
#define MOUSE_BUTTON_LAST      MOUSE_BUTTON_8

#define LEFT_MOUSE_BUTTON      MOUSE_BUTTON_1
#define RIGHT_MOUSE_BUTTON     MOUSE_BUTTON_2
#define MOUSE_WHEEL            MOUSE_BUTTON_3


/* Printable keys */
#define KEY_SPACE              32
#define KEY_APOSTROPHE         39  /* ' */
#define KEY_COMMA              44  /* , */
#define KEY_MINUS              45  /* - */
#define KEY_PERIOD             46  /* . */
#define KEY_SLASH              47  /* / */
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59  /* ; */
#define KEY_EQUAL              61  /* = */
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91  /* [ */
#define KEY_BACKSLASH          92  /* \ */
#define KEY_RIGHT_BRACKET      93  /* ] */
#define KEY_GRAVE_ACCENT       96  /* ` */
#define KEY_WORLD_1            161 /* non-US #1 */
#define KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE             256
#define KEY_ENTER              257
#define KEY_TAB                258
#define KEY_BACKSPACE          259
#define KEY_INSERT             260
#define KEY_DELETE             261
#define KEY_RIGHT              262
#define KEY_LEFT               263
#define KEY_DOWN               264
#define KEY_UP                 265
#define KEY_PAGE_UP            266
#define KEY_PAGE_DOWN          267
#define KEY_HOME               268
#define KEY_END                269
#define KEY_CAPS_LOCK          280
#define KEY_SCROLL_LOCK        281
#define KEY_NUM_LOCK           282
#define KEY_PRINT_SCREEN       283
#define KEY_PAUSE              284
#define KEY_F1                 290
#define KEY_F2                 291
#define KEY_F3                 292
#define KEY_F4                 293
#define KEY_F5                 294
#define KEY_F6                 295
#define KEY_F7                 296
#define KEY_F8                 297
#define KEY_F9                 298
#define KEY_F10                299
#define KEY_F11                300
#define KEY_F12                301
#define KEY_F13                302
#define KEY_F14                303
#define KEY_F15                304
#define KEY_F16                305
#define KEY_F17                306
#define KEY_F18                307
#define KEY_F19                308
#define KEY_F20                309
#define KEY_F21                310
#define KEY_F22                311
#define KEY_F23                312
#define KEY_F24                313
#define KEY_F25                314
#define KEY_KP_0               320
#define KEY_KP_1               321
#define KEY_KP_2               322
#define KEY_KP_3               323
#define KEY_KP_4               324
#define KEY_KP_5               325
#define KEY_KP_6               326
#define KEY_KP_7               327
#define KEY_KP_8               328
#define KEY_KP_9               329
#define KEY_KP_DECIMAL         330
#define KEY_KP_DIVIDE          331
#define KEY_KP_MULTIPLY        332
#define KEY_KP_SUBTRACT        333
#define KEY_KP_ADD             334
#define KEY_KP_ENTER           335
#define KEY_KP_EQUAL           336
#define KEY_LEFT_SHIFT         340
#define KEY_LEFT_CONTROL       341
#define KEY_LEFT_ALT           342
#define KEY_LEFT_SUPER         343
#define KEY_RIGHT_SHIFT        344
#define KEY_RIGHT_CONTROL      345
#define KEY_RIGHT_ALT          346
#define KEY_RIGHT_SUPER        347
#define KEY_MENU               348

constexpr std::vector<std::string> createKeyNameMap()
{
    std::vector<std::string> v;
    v.reserve(NUMBER_KEYS+1);
    v.resize(NUMBER_KEYS+1);
    for (int i=0; i<NUMBER_KEYS; i++){
        v[i] = "UnknownButtonName";
    }
    v[NUMBER_KEYS] = "InvalidKeyCodeRange";

    v[MOUSE_BUTTON_1] = "LMB";
    v[MOUSE_BUTTON_2] = "RMB";
    v[MOUSE_BUTTON_3] = "MB3";
    v[MOUSE_BUTTON_4] = "MB4";
    v[MOUSE_BUTTON_5] = "MB5";
    v[MOUSE_BUTTON_6] = "MB6";
    v[MOUSE_BUTTON_7] = "MB7";
    v[MOUSE_BUTTON_8] = "MB8";

    v[KEY_SPACE] = "Space";
    v[KEY_APOSTROPHE] = "'";
    v[KEY_COMMA] = ",";
    v[KEY_MINUS] = "-";
    v[KEY_PERIOD] = ".";
    v[KEY_SLASH] = "/";
    v[KEY_0] = "0";
    v[KEY_1] = "1";
    v[KEY_2] = "2";
    v[KEY_3] = "3";
    v[KEY_4] = "4";
    v[KEY_5] = "5";
    v[KEY_6] = "6";
    v[KEY_7] = "7";
    v[KEY_8] = "8";
    v[KEY_9] = "9";
    v[KEY_SEMICOLON] = ";";
    v[KEY_EQUAL] = "=";
    v[KEY_A] = "A";
    v[KEY_B] = "B";
    v[KEY_C] = "C";
    v[KEY_D] = "D";
    v[KEY_E] = "E";
    v[KEY_F] = "F";
    v[KEY_G] = "G";
    v[KEY_H] = "H";
    v[KEY_I] = "I";
    v[KEY_J] = "J";
    v[KEY_K] = "K";
    v[KEY_L] = "L";
    v[KEY_M] = "M";
    v[KEY_N] = "N";
    v[KEY_O] = "O";
    v[KEY_P] = "P";
    v[KEY_Q] = "Q";
    v[KEY_R] = "R";
    v[KEY_S] = "S";
    v[KEY_T] = "T";
    v[KEY_U] = "U";
    v[KEY_V] = "V";
    v[KEY_W] = "W";
    v[KEY_X] = "X";
    v[KEY_Y] = "Y";
    v[KEY_Z] = "Z";
    v[KEY_LEFT_BRACKET] = "[";
    v[KEY_BACKSLASH] = "\\";
    v[KEY_RIGHT_BRACKET] = "]";
    v[KEY_GRAVE_ACCENT] = "`";
    v[KEY_WORLD_1] = "World1";
    v[KEY_WORLD_2] = "World2";

    v[KEY_ESCAPE] = "ESC";
    v[KEY_ENTER] = "Enter";
    v[KEY_TAB] = "TAB";
    v[KEY_BACKSPACE] = "Backspace";
    v[KEY_INSERT] = "Insert";
    v[KEY_DELETE] = "DEL";
    v[KEY_RIGHT] = "Right";
    v[KEY_LEFT] = "Left";
    v[KEY_DOWN] = "Down";
    v[KEY_UP] = "Up";
    v[KEY_PAGE_UP] = "Page Up";
    v[KEY_PAGE_DOWN] = "Page Down";
    v[KEY_HOME] = "Home";
    v[KEY_END] = "End";
    v[KEY_CAPS_LOCK] = "CAPS";
    v[KEY_SCROLL_LOCK] = "Scroll Lock";
    v[KEY_NUM_LOCK] = "Num Lock";
    v[KEY_PRINT_SCREEN] = "Print Screen";
    v[KEY_PAUSE] = "Pause";
    v[KEY_F1] = "F1";
    v[KEY_F2] = "F2";
    v[KEY_F3] = "F3";
    v[KEY_F4] = "F4";
    v[KEY_F5] = "F5";
    v[KEY_F6] = "F6";
    v[KEY_F7] = "F7";
    v[KEY_F8] = "F8";
    v[KEY_F9] = "F9";
    v[KEY_F10] = "F10";
    v[KEY_F11] = "F11";
    v[KEY_F12] = "F12";
    v[KEY_F13] = "F13";
    v[KEY_F14] = "F14";
    v[KEY_F15] = "F15";
    v[KEY_F16] = "F16";
    v[KEY_F17] = "F17";
    v[KEY_F18] = "F18";
    v[KEY_F19] = "F19";
    v[KEY_F20] = "F20";
    v[KEY_F21] = "F21";
    v[KEY_F22] = "F22";
    v[KEY_F23] = "F23";
    v[KEY_F24] = "F24";
    v[KEY_F25] = "F25";
    v[KEY_KP_0] = "KP 0";
    v[KEY_KP_1] = "KP 1";
    v[KEY_KP_2] = "KP 2";
    v[KEY_KP_3] = "KP 3";
    v[KEY_KP_4] = "KP 4";
    v[KEY_KP_5] = "KP 5";
    v[KEY_KP_6] = "KP 6";
    v[KEY_KP_7] = "KP 7";
    v[KEY_KP_8] = "KP 8";
    v[KEY_KP_9] = "KP 9";
    v[KEY_KP_DECIMAL] = "KP Decimal";
    v[KEY_KP_DIVIDE] = "KP Divide";
    v[KEY_KP_MULTIPLY] = "KP Multiply";
    v[KEY_KP_SUBTRACT] = "KP Subtract";
    v[KEY_KP_ADD] = "KP Add";
    v[KEY_KP_ENTER] = "KP Enter";
    v[KEY_KP_EQUAL] = "KP Equal";
    v[KEY_LEFT_SHIFT] = "KP Left Shift";
    v[KEY_LEFT_CONTROL] = "KP Left Control";
    v[KEY_LEFT_ALT] = "KP Left Alt";
    v[KEY_LEFT_SUPER] = "KP Left Super";
    v[KEY_RIGHT_SHIFT] = "KP Right Shift";
    v[KEY_RIGHT_CONTROL] = "KP Right Control";
    v[KEY_RIGHT_ALT] = "KP Right Alt";
    v[KEY_RIGHT_SUPER] = "KP Right Super";
    v[KEY_MENU] = "KP Menu";

    return v;
}