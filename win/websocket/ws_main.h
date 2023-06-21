/* NetHack ws_main.h */
/* Copyright (c) Karl-Heinz Ruskowski, 2022 */
/* NetHack may be freely redistributed.  See license for details. */

extern void websocket_init_nhwindows(int* argcp, char** argv);
extern void websocket_player_selection(void);
extern void websocket_askname(void);
extern void websocket_get_nh_event(void);
extern void websocket_exit_nhwindows(const char *str);
extern void websocket_suspend_nhwindows(const char *str);
extern void websocket_resume_nhwindows(void);
extern winid websocket_create_nhwindow(int type);
extern void websocket_clear_nhwindow(winid wid);
extern void websocket_display_nhwindow(winid wid, BOOLEAN_P block);
extern void websocket_destroy_nhwindow(winid wid);
extern void websocket_curs(winid wid, int x, int y);
extern void websocket_putstr(winid wid, int attr, const char *text);
extern void websocket_display_file(const char *filename, BOOLEAN_P must_exist);
extern void websocket_start_menu(winid wid);
extern void websocket_add_menu(winid wid, int glyph, const ANY_P * identifier,
                            CHAR_P accelerator, CHAR_P group_accel, int attr,
                            const char *str, BOOLEAN_P presel);
extern void websocket_end_menu(winid wid, const char *prompt);
extern int websocket_select_menu(winid wid, int how, MENU_ITEM_P **selected);
extern void websocket_update_inventory(void);
extern void websocket_mark_synch(void);
extern void websocket_wait_synch(void);
extern void websocket_cliparound(int x, int y);
extern void websocket_print_glyph(winid wid, XCHAR_P x, XCHAR_P y,
                               int glyph, int bkglyph);
extern void websocket_raw_print(const char *str);
extern void websocket_raw_print_bold(const char *str);
extern int websocket_nhgetch(void);
extern int websocket_nh_poskey(int *x, int *y, int *mod);
extern void websocket_nhbell(void);
extern int websocket_doprev_message(void);
extern char websocket_yn_function(const char *question, const char *choices,
                               CHAR_P def);
extern void websocket_getlin(const char *question, char *input);
extern int websocket_get_ext_cmd(void);
extern void websocket_number_pad(int state);
extern void websocket_delay_output(void);
extern void websocket_start_screen(void);
extern void websocket_end_screen(void);
extern void websocket_outrip(winid wid, int how);
extern void ws_genl_outrip(winid tmpwin, int how, time_t when);
extern void websocket_preference_update(const char *pref);
extern void curs_reset_windows(boolean, boolean);

char *websocket_getmsghistory(BOOLEAN_P);
void websocket_putmsghistory(const char *, BOOLEAN_P);
extern void websocket_status_init(void);
extern void websocket_status_finish(void);
extern void websocket_status_update(int, genericptr_t, int, int, int,
                                 unsigned long *);
extern void websocket_outrip(winid wid, int how);
