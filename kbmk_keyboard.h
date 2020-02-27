#ifndef KBMK_KEYBOARD_H
#define KBMK_KEYBOARD_H

#include "kbmk_keybutton.h"





typedef struct kbmk_keyboard{
    //list_kbmk_keybutton_t buttons;
    char *name;
    char *event;
} kbmk_keyboard_t;

kbmk_keyboard_t *kbmk_keyboard_new(char *name);
void kbmk_keyboard_delete(kbmk_keyboard_t *keyboard);
void kbmk_keyboard_set_event(kbmk_keyboard_t *keyboard);



#endif // KBMK_KEYBOARD_H
