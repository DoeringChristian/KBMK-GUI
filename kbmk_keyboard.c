#include "kbmk_keyboard.h"

kbmk_keyboard_t *kbmk_keyboard_new(char *name){
    kbmk_keyboard_t *keyboard = malloc(sizeof(kbmk_keyboard_t));

    keyboard->name = malloc(strlen(name)+1);
    strcpy(keyboard->name, name);

    kbmk_keyboard_set_event(keyboard);
    return keyboard;
}
void kbmk_keyboard_delete(kbmk_keyboard_t *keyboard){
    //list_for_all_kbmk_keybutton_t(&keyboard->buttons, kbmk_keybutton_delete);
    //list_free_kbmk_keybutton_t(&keyboard->buttons);
    free(keyboard->event);
    free(keyboard->name);
    free(keyboard);
}

void kbmk_keyboard_set_event(kbmk_keyboard_t *keyboard){
    struct stat sb;
    char *buf;
    ssize_t nbytes, bufsiz;
    char *path = malloc(strlen(keyboard->name)+strlen(kbmk_mainwindow_keybord_idpath)+1);
    strcpy(path, kbmk_mainwindow_keybord_idpath);
    strcat(path, keyboard->name);

    if (lstat(path, &sb) == -1) {
        keyboard->event = NULL;
        return ;
    }

    bufsiz = sb.st_size + 2;

    buf = malloc(bufsiz);

    nbytes = readlink(path, buf, bufsiz);

    if(nbytes == -1){
        keyboard->event = NULL;
        return ;
    }

    buf[sb.st_size+1] = 0;

    keyboard->event = malloc(sb.st_size);
    strcpy(keyboard->event, &buf[3]);
    free(buf);
    free(path);
}
