#include "kbmk_configwindow.h"

kbmk_configwindow_t *kbmk_configwindow_new(struct kbmk_mainwindow *parent, kbmk_keybutton_t *keybutton){
    kbmk_configwindow_t *configwindow = malloc(sizeof(kbmk_configwindow_t));

    configwindow->sb_keycode_adj = gtk_adjustment_new(0, 0, 255, 1, 10,  0);
    configwindow->win_config = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    configwindow->box_toplvl = gtk_vbox_new(FALSE, 2);
    configwindow->box_info = gtk_hbox_new(FALSE, 0);
    configwindow->box_name = gtk_hbox_new(FALSE, 0);
    configwindow->box_keycode = gtk_hbox_new(FALSE, 0);
    configwindow->box_command = gtk_hbox_new(FALSE, 0);
    configwindow->box_close = gtk_hbox_new(FALSE, 0);
    configwindow->lbl_info = gtk_label_new("Configure Key: ");
    configwindow->lbl_name = gtk_label_new("KeyName: ");
    configwindow->lbl_keycode = gtk_label_new("KeyCode: ");
    configwindow->lbl_command = gtk_label_new("Command: ");
    configwindow->ent_name = gtk_entry_new();
    configwindow->ent_command = gtk_entry_new();
    configwindow->sb_keycode = gtk_spin_button_new(configwindow->sb_keycode_adj, 0.01, 0);
    configwindow->btn_command = gtk_button_new();
    configwindow->btn_close = gtk_button_new();
    configwindow->parent = parent;
    configwindow->keybutton = keybutton;


    gtk_container_add(GTK_CONTAINER(configwindow->win_config), configwindow->box_toplvl);

    gtk_box_pack_start(GTK_BOX(configwindow->box_toplvl), configwindow->box_info, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(configwindow->box_toplvl), configwindow->box_name, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(configwindow->box_toplvl), configwindow->box_keycode, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(configwindow->box_toplvl), configwindow->box_command, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(configwindow->box_toplvl), configwindow->box_close, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(configwindow->box_info), configwindow->lbl_info, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(configwindow->box_name), configwindow->lbl_name, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(configwindow->box_name), configwindow->ent_name, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(configwindow->box_keycode), configwindow->lbl_keycode, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(configwindow->box_keycode), configwindow->sb_keycode, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(configwindow->box_command), configwindow->lbl_command, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(configwindow->box_command), configwindow->ent_command, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(configwindow->box_command), configwindow->btn_command, FALSE, TRUE, 0);

    gtk_box_pack_end(GTK_BOX(configwindow->box_close), configwindow->btn_close, FALSE, TRUE, 0);


    gtk_button_set_label(GTK_BUTTON(configwindow->btn_command), "...");
    gtk_button_set_label(GTK_BUTTON(configwindow->btn_close), "Save");

    gtk_entry_set_text(GTK_ENTRY(configwindow->ent_command), kbmk_keybutton_get_command(configwindow->keybutton));
    gtk_entry_set_text(GTK_ENTRY(configwindow->ent_name), kbmk_keybutton_get_keyname(configwindow->keybutton));
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(configwindow->sb_keycode), (double)kbmk_keybutton_get_keycode(configwindow->keybutton));

    //g_signal_connect(G_OBJECT(configwindow->win_config), "destroy", G_CALLBACK(btn_close_clicked), (gpointer)configwindow);
    g_signal_connect(G_OBJECT(configwindow->btn_command), "clicked", G_CALLBACK(btn_command_clicked), (gpointer)configwindow);
    g_signal_connect(G_OBJECT(configwindow->btn_close), "clicked", G_CALLBACK(btn_close_clicked), (gpointer)configwindow);
    g_signal_connect(G_OBJECT(configwindow->ent_name), "changed", G_CALLBACK(ent_name_changed), (gpointer)configwindow);
    g_signal_connect(G_OBJECT(configwindow->ent_command), "changed", G_CALLBACK(ent_command_changed), (gpointer)configwindow);
    g_signal_connect(G_OBJECT(configwindow->sb_keycode), "changed", G_CALLBACK(sb_keycode_changed), (gpointer)configwindow);


    gtk_window_set_default_size(GTK_WINDOW(configwindow->win_config), 500, 300);
    gtk_window_set_position(GTK_WINDOW(configwindow->win_config), GTK_WIN_POS_MOUSE);

    return configwindow;
}

void kbmk_configwindow_delete(kbmk_configwindow_t *win){
    if(win != NULL){
        gtk_widget_destroy(win->win_config);
        win->parent->configwindow = NULL;
        free(win);
    }
}

static void btn_close_clicked(GtkWidget *wid, kbmk_configwindow_t *win){
    kbmk_configwindow_delete(win);
}
static void btn_command_clicked(GtkWidget *wid, kbmk_configwindow_t *win){}

static void ent_name_changed(GtkWidget *wid, kbmk_configwindow_t *win){
    char *name = gtk_entry_get_text(GTK_ENTRY(wid));
    kbmk_keybutton_set_keyname(win->keybutton, name);
}

static void ent_command_changed(GtkWidget *wid, kbmk_configwindow_t *win){
    char *command = gtk_entry_get_text(GTK_ENTRY(wid));
    kbmk_keybutton_set_command(win->keybutton, command);
}
static void sb_keycode_changed(GtkWidget *wid, kbmk_configwindow_t *win){
    uint16_t keycode = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(wid));
    kbmk_keybutton_set_keycode(win->keybutton, keycode);
}
