#include "kbmk_keybutton.h"

char kbmk_key_keyname_default[] = "";
char kbmk_key_command_default[] = "";
const uint16_t kbmk_key_keycode_default = 0;

kbmk_keybutton_t *kbmk_keybutton_new(kbmk_mainwindow_t *parent){
    kbmk_keybutton_t *keybutton = malloc(sizeof(kbmk_keybutton_t));

    keybutton->box_outline = gtk_hbox_new(FALSE, 0);
    keybutton->btn_config = gtk_button_new();
    keybutton->btn_drag = gtk_button_new();
    keybutton->parent = parent;
    keybutton->command = kbmk_key_command_default;
    keybutton->keyname = kbmk_key_keyname_default;
    keybutton->keycode = kbmk_key_keycode_default;

    gtk_box_pack_start(GTK_BOX(keybutton->box_outline), keybutton->btn_drag, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(keybutton->box_outline), keybutton->btn_config, FALSE, TRUE, 0);

    gtk_button_set_label(GTK_BUTTON(keybutton->btn_config), "V");
    gtk_widget_set_size_request(keybutton->btn_drag, 50, 50);

    g_signal_connect(G_OBJECT(keybutton->btn_config), "clicked", G_CALLBACK(btn_config_clicked), (gpointer)keybutton);
    g_signal_connect(G_OBJECT(keybutton->btn_drag), "pressed", G_CALLBACK(btn_drag_pressed), (gpointer)keybutton);
    g_signal_connect(G_OBJECT(keybutton->btn_drag), "released", G_CALLBACK(btn_drag_released), (gpointer)keybutton);

    return keybutton;
}
void kbmk_keybutton_delete(kbmk_keybutton_t *win){
    if(win != NULL){
        if(win->parent->moved_keybutton == win)
            win->parent->moved_keybutton = NULL;
        gtk_widget_destroy(win->box_outline);
        free(win->keyname);
        free(win->command);
        free(win);
    }
}

void kbmk_keybutton_set_keyname(kbmk_keybutton_t *keybutton, char *keyname){
    keybutton->keyname = malloc(strlen(keyname)+1);
    strcpy(keybutton->keyname, keyname);
    gtk_button_set_label(GTK_BOX(keybutton->btn_drag), keybutton->keyname);
}

char *kbmk_keybutton_get_keyname(kbmk_keybutton_t *keybutton){
    return keybutton->keyname;
}

void kbmk_keybutton_set_keycode(kbmk_keybutton_t *keybutton, uint16_t keycode){
    keybutton->keycode = keycode;
}
void kbmk_keybutton_set_command(kbmk_keybutton_t *keybutton, char *command){
    keybutton->command = malloc(strlen(command)+1);
    strcpy(keybutton->command, command);
}

char *kbmk_keybutton_get_command(kbmk_keybutton_t *keybutton){
    return keybutton->command;
}
uint16_t kbmk_keybutton_get_keycode(kbmk_keybutton_t *keybutton){
    return keybutton->keycode;
}

static void btn_drag_pressed(GtkWidget *wid, kbmk_keybutton_t *parent){
    if(parent->parent->moved_keybutton != parent && parent->parent->locked == 0)
        parent->parent->moved_keybutton = parent;
    else
        parent->parent->moved_keybutton = NULL;
}
static void btn_drag_released(GtkWidget *wid, kbmk_keybutton_t *parent){
    //parent->parent->moved_keybutton = NULL;
}
static void btn_config_clicked(GtkWidget *wid, kbmk_keybutton_t *parent){
    kbmk_configwindow_delete(parent->parent->configwindow);
    parent->parent->configwindow = kbmk_configwindow_new(parent->parent, parent);
    gtk_widget_show_all(parent->parent->configwindow->win_config);
}

void kbmk_keybutton_set_position(kbmk_keybutton_t *keybutton, gint x, gint y){
    gtk_fixed_move(GTK_FIXED(keybutton->parent->grd_layout), keybutton->box_outline, x, y);
    keybutton->x = x;
    keybutton->y = y;
}

void kbmk_keybutton_get_position(kbmk_keybutton_t *keybutton, gint *x, gint *y){
    *x = keybutton->x;
    *y = keybutton->y;
}
