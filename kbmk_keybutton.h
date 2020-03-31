#ifndef KBMK_KEYBUTTON_H
#define KBMK_KEYBUTTON_H

#include "includes.h"
#include "kbmk_mainwindow.h"


typedef struct kbmk_keybutton{
    GtkWidget *box_outline;
    GtkWidget *btn_drag;
    GtkWidget *btn_config;
    gint x;
    gint y;
    struct kbmk_mainwindow *parent;
    uint16_t keycode;
    char *keyname;
    char *command;
} kbmk_keybutton_t;

extern char kbmk_key_keyname_default[];
extern char kbmk_key_command_default[];
extern const uint16_t kbmk_key_keycode_default;

kbmk_keybutton_t *kbmk_keybutton_new(struct kbmk_mainwindow *parent);
void kbmk_keybutton_delete(kbmk_keybutton_t *win);
void kbmk_keybutton_set_keyname(kbmk_keybutton_t *keybutton, char *keyname);
void kbmk_keybutton_set_keycode(kbmk_keybutton_t *keybutton, uint16_t keycode);
void kbmk_keybutton_set_command(kbmk_keybutton_t *keybutton, char *command);
void kbmk_keybutton_set_position(kbmk_keybutton_t *keybutton, gint x, gint y);

char *kbmk_keybutton_get_keyname(kbmk_keybutton_t *keybutton);
char *kbmk_keybutton_get_command(kbmk_keybutton_t *keybutton);
uint16_t kbmk_keybutton_get_keycode(kbmk_keybutton_t *keybutton);
void kbmk_keybutton_get_position(kbmk_keybutton_t *keybutton, gint *x, gint *y);

static void btn_drag_pressed(GtkWidget *wid, kbmk_keybutton_t *parent);
static void btn_drag_released(GtkWidget *wid, kbmk_keybutton_t *parent);
static void btn_config_clicked(GtkWidget *wid, kbmk_keybutton_t *parent);

#endif // KBMK_KEYBUTTON_H
