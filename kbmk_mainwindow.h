#ifndef KBMK_MAINWINDOW_H
#define KBMK_MAINWINDOW_H

#include "includes.h"
#include "kbmk_configwindow.h"
//#include "list.h"
#include "kbmk_keyboard.h"
#include "sll.h"

#define PARSER_ERROR 0
#define PARSER_BEGIN 1
#define PARSER_DASH 2
#define PARSER_NAME 3
#define PARSER_KEYCODE 4
#define PARSER_COMMAND 5
#define PARSER_POSITION 6

extern const gint EvMask;
extern const char parser_alph_numb[];
extern const char parser_alph_letter[];
extern const char kbmk_mainwindow_btn_lock_label_locked[];
extern const char kbmk_mainwindow_btn_lock_label_unlocked[];
extern const char kbmk_mainwindow_keybord_idpath[];

typedef struct kbmk_keybutton *kbmk_keybutton_p;
typedef struct kbmk_keyboard *kbmk_keyboard_p;



SLL_TYPEDEF_H(kbmk_keyboard_p);
SLL_TYPEDEF_H(kbmk_keybutton_p);

typedef struct kbmk_mainwindow{
    GtkWidget *win;
    GtkWidget *ch_keyboard;
    GtkWidget *ch_layout;
    GtkWidget *btn_load;
    GtkWidget *btn_save;
    GtkWidget *box_main;
    GtkWidget *box_chose;
    GtkWidget *box_bottom;
    GtkWidget *box_middle;
    GtkWidget *box_menu;
    GtkWidget *grd_layout;
    GtkWidget *btn_add;
    GtkWidget *btn_export;
    GtkWidget *btn_lock;
    struct kbmk_configwindow *configwindow;
    struct kbmk_keybutton *moved_keybutton;
    uint8_t locked;
    SLL_LIST(kbmk_keybutton_p) *layout;
    SLL_LIST(kbmk_keyboard_p) *keyboards;
} kbmk_mainwindow_t;

kbmk_mainwindow_t *kbmk_mainwindow_new();
void kbmk_mainwindow_delete(kbmk_mainwindow_t *win);
void kbmk_mainwindow_load_file(kbmk_mainwindow_t *mainwindow, char *filename);
void kbmk_mainwindow_save_file(kbmk_mainwindow_t *mainwindow, char *filename);
void kbmk_mainwindow_export_file(kbmk_mainwindow_t *mainwindow, char *filename);
void kbmk_mainwindow_list_keyboard(kbmk_mainwindow_t *mainwindow);

static void btn_load_clicked(GtkWidget *wid, kbmk_mainwindow_t *win);
static void btn_save_clicked(GtkWidget *wid, kbmk_mainwindow_t *win);
static void btn_add_clicked(GtkWidget *wid, kbmk_mainwindow_t *win);
static void ch_keyboard_changed(GtkComboBox *widget, kbmk_mainwindow_t *win);
static void ch_layout_changed(GtkComboBox *widget, kbmk_mainwindow_t *win);
static void grd_layout_motion_event(GtkWidget *wid, GdkEvent *event, kbmk_mainwindow_t *win);
static void btn_export_clicked(GtkWidget *wid, kbmk_mainwindow_t *win);
static void btn_lock_clicked(GtkWidget *wid, kbmk_mainwindow_t *win);

SLL_DEFINE_H(kbmk_keyboard_p);
SLL_DEFINE_H(kbmk_keybutton_p);


#endif // KBMK_MAINWINDOW_H
