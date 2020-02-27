#ifndef KBMK_KEY_H
#define KBMK_KEY_H

#include "includes.h"
#include "kbmk_keybutton.h"


typedef struct kbmk_key{
    uint16_t keycode;
    char *keyname;
    char *command;
    struct kbmk_keybutton *keybutton;
}kbmk_key_t;

extern char kbmk_key_keyname_default[];
extern char kbmk_key_command_default[];
extern const uint16_t kbmk_key_keycode_default;

kbmk_key_t *kbmk_key_new(struct kbmk_keybutton *button);
void kbmk_key_delete(kbmk_key_t *key);

#endif // KBMK_KEY_H
