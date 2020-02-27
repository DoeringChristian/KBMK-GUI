#include "kbmk_key.h"

char kbmk_key_keyname_default[] = "";
char kbmk_key_command_default[] = "";
const uint16_t kbmk_key_keycode_default = 0;

kbmk_key_t *kbmk_key_new(kbmk_keybutton_t *button){
    kbmk_key_t *key = malloc(sizeof(kbmk_key_t));
    key->command = kbmk_key_command_default;
    key->keyname = kbmk_key_keyname_default;
    key->keycode = kbmk_key_keycode_default;

    key->keybutton = button;
    return key;
}
void kbmk_key_delete(kbmk_key_t *key){

}
