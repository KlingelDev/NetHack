/* NetHack ws_init.h */
/* Copyright (c) Karl-Heinz Ruskowski, 2022 */
/* NetHack may be freely redistributed.  See license for details. */

#define MAXWIN 8

extern struct wswin *wins[MAXWIN];
extern struct window_procs websocket_procs;

extern void websocket_create_message_window(int wid);
extern void websocket_create_menu_window(int wid);
extern void websocket_create_map_window(int wid);
extern void websocket_create_status_window(int wid);
extern void websocket_create_text_window(int wid);

extern int websocket_create_input(void);

/* menu structure */
typedef struct tty_mi {
    struct tty_mi *next;
    anything identifier; /* user identifier */
    long count;          /* user count */
    char *str;           /* description string (including accelerator) */
    int attr;            /* string attribute */
    boolean selected;    /* TRUE if selected by user */
    char selector;       /* keyboard accelerator */
    char gselector;      /* group accelerator */
} tty_menu_item;

struct wswin {
    int flags;           /* window flags */
    xchar type;          /* type of window */
    boolean active;      /* true if window is active */
    short offx, offy;    /* offset from topleft of display */
    long rows, cols;     /* dimensions */
    long curx, cury;     /* current cursor position */
    long maxrow, maxcol; /* the maximum size used -- for MENU wins */
    int socket;
    /* maxcol is also used by WIN_MESSAGE for */
    /* tracking the ^P command */
    short *datlen;         /* allocation size for *data */
    char **data;           /* window data [row][column] */
    char *morestr;         /* string to display instead of default */
    tty_menu_item *mlist;  /* menu information (MENU) */
    tty_menu_item **plist; /* menu page pointers (MENU) */
    long plist_size;       /* size of allocated plist (MENU) */
    long npages;           /* number of pages in menu (MENU) */
    long nitems;           /* total number of items (MENU) */
    short how;             /* menu mode - pick 1 or N (MENU) */
    char menu_ch;          /* menu char (MENU) */
};
