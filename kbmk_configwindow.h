#ifndef KBMK_CONFIGWINDOW_H
#define KBMK_CONFIGWINDOW_H

#include "includes.h"
#include "kbmk_mainwindow.h"
#include "kbmk_keybutton.h"

typedef struct kbmk_configwindow{
    GtkAdjustment *sb_keycode_adj;
    GtkWidget *win_config;
    GtkWidget *box_toplvl;
    GtkWidget *box_info;
    GtkWidget *box_name;
    GtkWidget *box_keycode;
    GtkWidget *box_command;
    GtkWidget *box_close;
    GtkWidget *lbl_info;
    GtkWidget *lbl_name;
    GtkWidget *lbl_keycode;
    GtkWidget *lbl_command;
    GtkWidget *ent_name;
    GtkWidget *ent_command;
    GtkWidget *sb_keycode;
    GtkWidget *btn_command;
    GtkWidget *btn_close;
    struct kbmk_mainwindow *parent;
    struct kbmk_keybutton *keybutton;

} kbmk_configwindow_t;

kbmk_configwindow_t *kbmk_configwindow_new(struct kbmk_mainwindow *parent, struct kbmk_keybutton *keybutton);
void kbmk_configwindow_delete(kbmk_configwindow_t *win);

static void btn_close_clicked(GtkWidget *wid, kbmk_configwindow_t *win);
static void btn_command_clicked(GtkWidget *wid, kbmk_configwindow_t *win);
static void ent_name_changed(GtkWidget *wid, kbmk_configwindow_t *win);
static void ent_command_changed(GtkWidget *wid, kbmk_configwindow_t *win);
static void sb_keycode_changed(GtkWidget *wid, kbmk_configwindow_t *win);

#endif // KBMK_CONFIGWINDOW_H
