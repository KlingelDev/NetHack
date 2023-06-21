/* NetHack ws_main.c */
/* Copyright (c) Karl-Heinz Ruskowski, 2022 */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "ws_main.h"
#include "ws_init.h"

int input_socket;

/* Interface for websocket */
struct window_procs websocket_procs = {
    "websocket",
    (WC_ALIGN_MESSAGE | WC_ALIGN_STATUS | WC_COLOR | WC_INVERSE
     | WC_HILITE_PET | WC_PERM_INVENT | WC_POPUP_DIALOG),
    (WC2_DARKGRAY | WC2_HITPOINTBAR | WC2_HILITE_STATUS
     | WC2_FLUSH_STATUS | WC2_TERM_SIZE | WC2_STATUSLINES
     | WC2_WINDOWBORDERS | WC2_PETATTR | WC2_GUICOLOR
     | WC2_SUPPRESS_HIST),
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, /* color availability */
    websocket_init_nhwindows,
    websocket_player_selection,
    websocket_askname,
    websocket_get_nh_event,
    websocket_exit_nhwindows,
    websocket_suspend_nhwindows,
    websocket_resume_nhwindows,
    websocket_create_nhwindow,
    websocket_clear_nhwindow,
    websocket_display_nhwindow,
    websocket_destroy_nhwindow,
    websocket_curs,
    websocket_putstr,
    genl_putmixed,
    websocket_display_file,
    websocket_start_menu,
    websocket_add_menu,
    websocket_end_menu,
    websocket_select_menu,
    genl_message_menu,
    websocket_update_inventory,
    websocket_mark_synch,
    websocket_wait_synch,
#ifdef CLIPPING
    websocket_cliparound,
#endif
#ifdef POSITIONBAR
    wsdummy_update_position_bar,
#endif
    websocket_print_glyph,
    websocket_raw_print,
    websocket_raw_print_bold,
    websocket_nhgetch,
    websocket_nh_poskey,
    websocket_nhbell,
    websocket_doprev_message,
    websocket_yn_function,
    websocket_getlin,
    websocket_get_ext_cmd,
    websocket_number_pad,
    websocket_delay_output,
#ifdef CHANGE_COLOR
    wsdummy_change_color,
#ifdef MAC /* old OS 9, not OSX */
    (void (*)(int)) 0,
    (short (*)(winid, char *)) 0,
#endif
    wsdummy_get_color_string,
#endif
    websocket_start_screen,
    websocket_end_screen,
    genl_outrip,
    websocket_preference_update,
    websocket_getmsghistory,
    websocket_putmsghistory,
    websocket_status_init,
    websocket_status_finish,
    genl_status_enablefield,
    websocket_status_update,
    genl_can_suspend_yes,
};


void
websocket_init_nhwindows(int *argcp UNUSED,
                         char **argv UNUSED)
{
    /* printf("init_nhwindows\n"); */
    /* input_socket = websocket_create_input(); */
    /*  */
    /* int s2, t, len; */
    /* struct sockaddr_un remote; */
    /* char str[100]; */
    /* int s = input_socket; */
    /* for(;;) { */
    /*     int done, n; */
    /*     printf("Waiting for a connection...\n"); */
    /*     t = sizeof(remote); */
    /*     if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) { */
    /*         perror("accept"); */
    /*         exit(1); */
    /*     } */
    /*  */
    /*     printf("Connected.\n"); */
    /*  */
    /*     done = 0; */
    /*     do { */
    /*         n = recv(s2, str, 100, 0); */
    /*         if (n <= 0) { */
    /*             if (n < 0) perror("recv"); */
    /*             done = 1; */
    /*         } */
    /*  */
    /*         if (!done)  */
    /*             if (send(s2, str, n, 0) < 0) { */
    /*                 perror("send"); */
    /*                 done = 1; */
    /*             } */
    /*     } while (!done); */
    /*  */
    /*     close(s2); */
    /* } */
}

#define ROLE flags.initrole
#define RACE flags.initrace
#define GEND flags.initgend
#define ALGN flags.initalign

void websocket_player_selection()
{
    printf("player_selection\n");
    if (1) {
        if (ROLE == ROLE_NONE)
            ROLE = ROLE_RANDOM;
        if (RACE == ROLE_NONE)
            RACE = ROLE_RANDOM;
        if (GEND == ROLE_NONE)
            GEND = ROLE_RANDOM;
        if (ALGN == ROLE_NONE)
            ALGN = ROLE_RANDOM;
    }
    return;
}

/* Ask the user for a player name. */
void
websocket_askname()
{
    printf("askname\n");
}

void
websocket_get_nh_event()
{
    printf("get_nh_event\n");
}

void
websocket_exit_nhwindows(const char *str)
{
    printf("exit_nhwindows\n");
}

/* Prepare the window to be suspended. */
void
websocket_suspend_nhwindows(const char *str UNUSED)
{
    printf("suspend_nhwindows\n");
}

/* Restore the windows after being suspended. */
void
websocket_resume_nhwindows()
{
    printf("resume_nhwindows\n");
}

/*  Create a window of type "type" which can be
        NHW_MESSAGE     (top line)
        NHW_STATUS      (bottom lines)
        NHW_MAP         (main dungeon)
        NHW_MENU        (inventory or other "corner" windows)
        NHW_TEXT        (help/text, full screen paged window)
*/
winid
websocket_create_nhwindow(int type)
{
    printf("create_nhwindow %i\n", (int) type);
    struct wswin *newwin;
    int i, rowoffset;
    int newid;

    for (newid = 0; newid < MAXWIN; ++newid)
        if(wins[newid] == 0) break;
    if(newid == MAXWIN) {
        panic("No window slots!");
        return WIN_ERR;
    }

    newwin = (struct wswin *) alloc(sizeof (struct wswin));
    wins[newid] = newwin;

    newwin->type = type;
    newwin->flags = 0;
    newwin->active = FALSE;

    switch(type) {
        case NHW_MESSAGE:
            printf("create window NHW_MESSAGE\n");
            /* websocket_create_message_window(newid); */
            break;
        break;
        case NHW_STATUS:
            printf("create window NHW_STATUS\n");
            websocket_create_status_window(newid);
            break;
        case NHW_MAP:
            printf("create window NHW_MAP %ix%i\n", ROWNO, COLNO);
            /* newwin->offx = 0; */
            /* newwin->offy = 1; */
            /* newwin->rows = ROWNO; */
            /* newwin->cols = COLNO; */
            /* newwin->maxrow = 0; #<{(| no buffering done -- let gbuf do it |)}># */
            /* newwin->maxcol = 0; */
            websocket_create_map_window(newid);
            break;
        case NHW_MENU:
            printf("create window NHW_MENU\n");
            websocket_create_menu_window(newid);
            break;
        case NHW_TEXT:
            printf("create window NHW_TEXT\n");
            websocket_create_text_window(newid);
            break;
        default:
            panic("Tried to create window type %d\n", (int) type);
            return WIN_ERR;
    }

    return newid;
}

/* Clear the given window, when asked to. */
void
websocket_clear_nhwindow(winid wid)
{
    printf("clear_nhwindow %i\n", (int) wid);
    /* register struct wswin *cw = 0; */
    /* if (wid == WIN_ERR || (cw = wins[wid]) == (struct wswin *) 0) */
    /*     panic("display panic", wid); */
    /*  */
    /* switch(cw->type) { */
    /*     case NHW_MESSAGE: */
    /*         printf("clear window NHW_MESSAGE\n"); */
    /*         break; */
    /*     case NHW_STATUS: */
    /*         printf("clear window NHW_STATUS\n"); */
    /*         break; */
    /*     case NHW_MAP: */
    /*         printf("clear window NHW_MAP\n"); */
    /*         break; */
    /*     case NHW_MENU: */
    /*         printf("clear window NHW_MENU\n"); */
    /*         break; */
    /*     case NHW_TEXT: */
    /*         printf("clear window NHW_TEXT\n"); */
    /*         break; */
    /* } */
    /*  */
    /* //register struct WinDesc *cw = 0; */
    /* //cw->curx = cw->cury = 0; */
}

/* -- Display the window on the screen.  If there is data
                   pending for output in that window, it should be sent.
                   If blocking is TRUE, display_nhwindow() will not
                   return until the data has been displayed on the screen,
                   and acknowledged by the user where appropriate.
                -- All calls are blocking in the tty window-port.
                -- Calling display_nhwindow(WIN_MESSAGE,???) will do a
                   --more--, if necessary, in the tty window-port.
*/
void
websocket_display_nhwindow(winid wid, BOOLEAN_P block)
{
    printf("display_nhwindow %i\n", (int) wid);
    /* register struct wswin *cw = 0; */
    /*  */
    /* if (wid == WIN_ERR || (cw = wins[wid]) == (struct wswin *) 0) */
    /*     panic("display panic", wid); */
    /*  */
    /* switch(cw->type) { */
    /*     case NHW_MESSAGE: */
    /*         printf("display window NHW_MESSAGE\n"); */
    /*         break; */
    /*     case NHW_STATUS: */
    /*         printf("display window NHW_STATUS\n"); */
    /*         break; */
    /*     case NHW_MAP: */
    /*         printf("display window NHW_MAP\n"); */
    /*         break; */
    /*     case NHW_MENU: */
    /*         printf("display window NHW_MENU\n"); */
    /*         break; */
    /*     case NHW_TEXT: */
    /*         printf("display window NHW_TEXT\n"); */
    /*         break; */
    /* } */
}

/* Destroy will dismiss the window if the window has not
 * already been dismissed.
*/
void
websocket_destroy_nhwindow(winid wid)
{
    printf("destroy_nhwindows %i\n", (int) wid);

    register struct wswin *cw = 0;

    if (wid == WIN_ERR || (cw = wins[wid]) == (struct wswin *) 0)
        panic("PANIC!", wid);

    free((genericptr_t) cw);
    wins[wid] = 0; /* available for re-use */
}

/* Next output to window will start at (x,y), also moves
 displayable cursor to (x,y).  For backward compatibility,
 1 <= x < cols, 0 <= y < rows, where cols and rows are
 the size of window.
*/
void
websocket_curs(winid wid, int x, int y)
{
    printf("websocket_curs %i\n", (int) wid);
}

/*
putstr(window, attr, str)
                -- Print str on the window with the given attribute.  Only
                   printable ASCII characters (040-0126) must be supported.
                   Multiple putstr()s are output on separate lines.
                   Attributes can be one of
                        ATR_NONE (or 0)
                        ATR_ULINE
                        ATR_BOLD
                        ATR_BLINK
                        ATR_INVERSE
                   If a window-port does not support all of these, it may map
                   unsupported attributes to a supported one (e.g. map them
                   all to ATR_INVERSE).  putstr() may compress spaces out of
                   str, break str, or truncate str, if necessary for the
                   display.  Where putstr() breaks a line, it has to clear
                   to end-of-line.
                -- putstr should be implemented such that if two putstr()s
                   are done consecutively the user will see the first and
                   then the second.  In the tty port, pline() achieves this
                   by calling more() or displaying both on the same line.
*/
void
websocket_putstr(winid wid, int attr, const char *text)
{
    printf("putstr %i\n", wid);
    printf(text);
}

/* Display the file named str.  Complain about missing files
                   iff complain is TRUE.
*/
void
websocket_display_file(const char *filename, BOOLEAN_P must_exist)
{
    printf("display_file %s\n", filename);
}

/* Start using window as a menu.  You must call start_menu()
   before add_menu().  After calling start_menu() you may not
   putstr() to the window.  Only windows of type NHW_MENU may
   be used for menus.
*/
void
websocket_start_menu(winid wid)
{
    /* register struct wswin *cw = 0; */
    /*  */
    /* if (wid == WIN_ERR || (cw = wins[wid]) == (struct wswin *) 0) */
    /*     panic("display panic", wid); */
    /*  */
    /* switch(cw->type) { */
    /*     case NHW_MESSAGE: */
    /*         printf("start_menu NHW_MESSAGE\n"); */
    /*         break; */
    /*     case NHW_STATUS: */
    /*         printf("start_menu NHW_STATUS\n"); */
    /*         break; */
    /*     case NHW_MAP: */
    /*         printf("start_menu NHW_MAP\n"); */
    /*         break; */
    /*     case NHW_MENU: */
    /*         printf("start_menu NHW_MENU\n"); */
    /*         break; */
    /*     case NHW_TEXT: */
    /*         printf("start_menu NHW_TEXT\n"); */
    /*         break; */
    /* } */
}

/*
add_menu(winid wid, int glyph, const anything identifier,
                                char accelerator, char groupacc,
                                int attr, char *str, boolean preselected)
                -- Add a text line str to the given menu window.  If identifier
                   is 0, then the line cannot be selected (e.g. a title).
                   Otherwise, identifier is the value returned if the line is
                   selected.  Accelerator is a keyboard key that can be used
                   to select the line.  If the accelerator of a selectable
                   item is 0, the window system is free to select its own
                   accelerator.  It is up to the window-port to make the
                   accelerator visible to the user (e.g. put "a - " in front
                   of str).  The value attr is the same as in putstr().
                   Glyph is an optional glyph to accompany the line.  If
                   window port cannot or does not want to display it, this
                   is OK.  If there is no glyph applicable, then this
                   value will be NO_GLYPH.
                -- All accelerators should be in the range [A-Za-z].
                -- It is expected that callers do not mix accelerator
                   choices.  Either all selectable items have an accelerator
                   or let the window system pick them.  Don't do both.
                -- Groupacc is a group accelerator.  It may be any character
                   outside of the standard accelerator (see above) or a
                   number.  If 0, the item is unaffected by any group
                   accelerator.  If this accelerator conflicts with
                   the menu command (or their user defined alises), it loses.
                   The menu commands and aliases take care not to interfere
                   with the default object class symbols.
                -- If you want this choice to be preselected when the
                   menu is displayed, set preselected to TRUE.
*/
void
websocket_add_menu(winid wid, int glyph, const ANY_P * identifier,
                CHAR_P accelerator, CHAR_P group_accel, int attr,
                const char *str, BOOLEAN_P presel)
{
    printf("websocket_add_menu %i, %i, %s\n", (int) wid, glyph, str);
}

/*
end_menu(window, prompt)
                -- Stop adding entries to the menu and flushes the window
                   to the screen (brings to front?).  Prompt is a prompt
                   to give the user.  If prompt is NULL, no prompt will
                   be printed.
                ** This probably shouldn't flush the window any more (if
                ** it ever did).  That should be select_menu's job.  -dean
*/
void
websocket_end_menu(winid wid, const char *prompt)
{
    /* register struct wswin *cw = 0; */
    /*  */
    /* if (wid == WIN_ERR || (cw = wins[wid]) == (struct wswin *) 0) */
    /*     panic("display panic", wid); */
    /*  */
    /* switch(cw->type) { */
    /*     case NHW_MESSAGE: */
    /*         printf("end_menu NHW_MESSAGE\n"); */
    /*         break; */
    /*     case NHW_STATUS: */
    /*         printf("end_menu NHW_STATUS\n"); */
    /*         break; */
    /*     case NHW_MAP: */
    /*         printf("end_menu NHW_MAP\n"); */
    /*         break; */
    /*     case NHW_MENU: */
    /*         printf("end_menu NHW_MENU\n"); */
    /*         break; */
    /*     case NHW_TEXT: */
    /*         printf("start_menu NHW_TEXT\n"); */
    /*         break; */
    /* } */
}

/*
int select_menu(winid window, int how, menu_item **selected)
                -- Return the number of items selected; 0 if none were chosen,
                   -1 when explicitly cancelled.  If items were selected, then
                   selected is filled in with an allocated array of menu_item
                   structures, one for each selected line.  The caller must
                   free this array when done with it.  The "count" field
                   of selected is a user supplied count.  If the user did
                   not supply a count, then the count field is filled with
                   -1 (meaning all).  A count of zero is equivalent to not
                   being selected and should not be in the list.  If no items
                   were selected, then selected is NULL'ed out.  How is the
                   mode of the menu.  Three valid values are PICK_NONE,
                   PICK_ONE, and PICK_N, meaning: nothing is selectable,
                   only one thing is selectable, and any number valid items
                   may selected.  If how is PICK_NONE, this function should
                   never return anything but 0 or -1.
                -- You may call select_menu() on a window multiple times --
                   the menu is saved until start_menu() or destroy_nhwindow()
                   is called on the window.
                -- Note that NHW_MENU windows need not have select_menu()
                   called for them. There is no way of knowing whether
                   select_menu() will be called for the window at
                   create_nhwindow() time.
*/
int
websocket_select_menu(winid wid, int how, MENU_ITEM_P ** selected)
{
    printf("websocket_select_menu %i\n", (int) wid);
}

void
websocket_update_inventory(void)
{
    printf("websocket_update_inv\n");
}

/*
mark_synch()    -- Don't go beyond this point in I/O on any channel until
                   all channels are caught up to here.  Can be an empty call
                   for the moment
*/
void
websocket_mark_synch()
{
    printf("websocket_mark_synch\n");
}

/*
wait_synch()    -- Wait until all pending output is complete (*flush*() for
                   streams goes here).
                -- May also deal with exposure events etc. so that the
                   display is OK when return from wait_synch().
*/
void
websocket_wait_synch()
{
    /* [do we need 'if (counting) websocket_count_window((char *)0);' here?] */
    printf("websocket_wait_synch\n");
}

/*
cliparound(x, y)-- Make sure that the user is more-or-less centered on the
                   screen if the playing area is larger than the screen.
                -- This function is only defined if CLIPPING is defined.
*/
void
websocket_cliparound(int x, int y)
{
    printf("websocket_cliparound\n");
}

/*
print_glyph(window, x, y, glyph, bkglyph)
                -- Print the glyph at (x,y) on the given window.  Glyphs are
                   integers at the interface, mapped to whatever the window-
                   port wants (symbol, font, color, attributes, ...there's
                   a 1-1 map between glyphs and distinct things on the map).
                   bkglyph is to render the background behind the glyph.
                   It's not used here.
*/
void
websocket_print_glyph(winid wid, XCHAR_P x, XCHAR_P y, int glyph,
                   int bkglyph UNUSED)
{   printf("print glyph\n");
    register struct wswin *cw = 0;
    if (wid == WIN_ERR || (cw = wins[wid]) == (struct wswin *) 0)
        panic("display panic\n", wid);

    switch(cw->type) {
        case NHW_MESSAGE:
            printf("print glyph NHW_MESSAGE\n");
            printf("xy:%u,%u \"%i - %i\"\n", (int) wid, x,y, glyph, bkglyph);
            break;
        case NHW_STATUS:
            printf("print glyph NHW_STATUS\n");
            printf("xy:%u,%u \"%i - %i\"\n", (int) wid, x,y, glyph, bkglyph);
            break;
        case NHW_MAP:
            printf("print glyph NHW_MAP\n");
            printf("xy:%u,%u \"%i - %i\"\n", (int) wid, x,y, glyph, bkglyph);
            break;
        case NHW_MENU:
            printf("print glyph NHW_MENU\n");
            printf("xy:%u,%u \"%i - %i\"\n", (int) wid, x,y, glyph, bkglyph);
            break;
        case NHW_TEXT:
            printf("print glyph NHW_TEXT\n");
            printf("xy:%u,%u \"%i - %i\"\n", (int) wid, x,y, glyph, bkglyph);
            break;
    }
}

/*
raw_print(str)  -- Print directly to a screen, or otherwise guarantee that
                   the user sees str.  raw_print() appends a newline to str.
                   It need not recognize ASCII control characters.  This is
                   used during startup (before windowing system initialization
                   -- maybe this means only error startup messages are raw),
                   for error messages, and maybe other "msg" uses.  E.g.
                   updating status for micros (i.e, "saving").
*/
void
websocket_raw_print(const char *str)
{
    printf("websocket_raw_print %s\n", str);
}

/*
raw_print_bold(str)
            -- Like raw_print(), but prints in bold/standout (if possible).
*/
void
websocket_raw_print_bold(const char *str)
{
    printf("websocket_raw_print_bold: %s\n", str);
}

/*
int nhgetch()   -- Returns a single character input from the user.
                -- In the tty window-port, nhgetch() assumes that tgetch()
                   will be the routine the OS provides to read a character.
                   Returned character _must_ be non-zero.
*/
int
websocket_nhgetch()
{
    /* printf("getch!\n"); */
    /* int i; */
    /* i = tgetch(); */
    /* if (!i) */
    /*     i = '\033'; #<{(| map NUL to ESC since nethack doesn't expect NUL |)}># */
    /* else if (i == EOF) */
    /*     i = '\033'; #<{(| same for EOF |)}># */
    /* return i; */
}

/*
int nh_poskey(int *x, int *y, int *mod)
                -- Returns a single character input from the user or a
                   a positioning event (perhaps from a mouse).  If the
                   return value is non-zero, a character was typed, else,
                   a position in the MAP window is returned in x, y and mod.
                   mod may be one of

                        CLICK_1         -- mouse click type 1
                        CLICK_2         -- mouse click type 2

                   The different click types can map to whatever the
                   hardware supports.  If no mouse is supported, this
                   routine always returns a non-zero character.
*/
int
websocket_nh_poskey(int *x, int *y, int *mod)
{
    printf("websocket_nh_poskey\n");
}

/*
nhbell()        -- Beep at user.  [This will exist at least until sounds are
                   redone, since sounds aren't attributable to windows anyway.]
*/
void
websocket_nhbell()
{
    printf("websocket_nhbell\n");
}

/*
doprev_message()
                -- Display previous messages.  Used by the ^P command.
                -- On the tty-port this scrolls WIN_MESSAGE back one line.
*/
int
websocket_doprev_message()
{
    printf("websocket_doprev_messagel\n");
}

/*
char yn_function(const char *ques, const char *choices, char default)
                -- Print a prompt made up of ques, choices and default.
                   Read a single character response that is contained in
                   choices or default.  If choices is NULL, all possible
                   inputs are accepted and returned.  This overrides
                   everything else.  The choices are expected to be in
                   lower case.  Entering ESC always maps to 'q', or 'n',
                   in that order, if present in choices, otherwise it maps
                   to default.  Entering any other quit character (SPACE,
                   RETURN, NEWLINE) maps to default.
                -- If the choices string contains ESC, then anything after
                   it is an acceptable response, but the ESC and whatever
                   follows is not included in the prompt.
                -- If the choices string contains a '#' then accept a count.
                   Place this value in the global "yn_number" and return '#'.
                -- This uses the top line in the tty window-port, other
                   ports might use a popup.
*/
char
websocket_yn_function(const char *question, const char *choices, CHAR_P def)
{
    printf("websocket_yn_function\n");
}

/*
getlin(const char *ques, char *input)
            -- Prints ques as a prompt and reads a single line of text,
               up to a newline.  The string entered is returned without the
               newline.  ESC is used to cancel, in which case the string
               "\033\000" is returned.
            -- getlin() must call flush_screen(1) before doing anything.
            -- This uses the top line in the tty window-port, other
               ports might use a popup.
*/
void
websocket_getlin(const char *question, char *input)
{
    printf("websocket_getlin\n");
}

/*
int get_ext_cmd(void)
            -- Get an extended command in a window-port specific way.
               An index into extcmdlist[] is returned on a successful
               selection, -1 otherwise.
*/
int
websocket_get_ext_cmd()
{
    printf("websocket_get_ext_cmd\n");
}


/*
number_pad(state)
            -- Initialize the number pad to the given state.
*/
void
websocket_number_pad(int state UNUSED)
{
    printf("websocket_number_pad\n");
}

/*
delay_output()  -- Causes a visible delay of 50ms in the output.
               Conceptually, this is similar to wait_synch() followed
               by a nap(50ms), but allows asynchronous operation.
*/
void
websocket_delay_output()
{
    printf("websocket_delay_output\n");
}

/*
start_screen()  -- Only used on Unix tty ports, but must be declared for
               completeness.  Sets up the tty to work in full-screen
               graphics mode.  Look at win/tty/termcap.c for an
               example.  If your window-port does not need this function
               just declare an empty function.
*/
void
websocket_start_screen()
{
    printf("websocket_start_screen\n");
}

/*
end_screen()    -- Only used on Unix tty ports, but must be declared for
               completeness.  The complement of start_screen().
*/
void
websocket_end_screen()
{
    printf("websocket_end_screen\n");
}

/*
outrip(winid, int)
            -- The tombstone code.  If you want the traditional code use
               genl_outrip for the value and check the #if in rip.c.
*/
void
websocket_outrip(winid wid UNUSED,
              int how UNUSED)
{
    printf("websocket_outrip %u\n", (int) wid);
}

/*
preference_update(preference)
                -- The player has just changed one of the wincap preference
                   settings, and the NetHack core is notifying your window
                   port of that change.  If your window-port is capable of
                   dynamically adjusting to the change then it should do so.
                   Your window-port will only be notified of a particular
                   change if it indicated that it wants to be by setting the
                   corresponding bit in the wincap mask.
*/
void
websocket_preference_update(const char *pref)
{
    printf("websocket_preference_update\n");
}

void
websocket_reset_windows(boolean redo_main, boolean redo_status)
{
    printf("websocket_reset_windows\n");
}

void
websocket_status_init()
{
    printf("websocket_status_init\n");
}

void
websocket_status_finish()
{
    printf("websocket_status_finish\n");
}

void
websocket_status_update(fldidx, ptr, chg, percent, color_and_attr, colormasks)
int fldidx, chg UNUSED,
    percent, color_and_attr;
genericptr_t ptr;
unsigned long *colormasks;
{
    printf("websocket_status_update\n");
}

char *
websocket_getmsghistory(init)
boolean init;
{
    printf("websocket_getmsghistory\n");
}

void
websocket_putmsghistory(msg, restoring_msghist)
const char *msg;
boolean restoring_msghist;
{
    printf("websocket_putmsghistory\n");
}

#ifdef POSITIONBAR
static void
wsdummy_update_position_bar(char *arg UNUSED)
{
    printf("websocket_update_position_bar\n");
}
#endif

#ifdef CHANGE_COLOR
static void
wsdummy_change_color(int a1 UNUSED, long a2 UNUSED, int a3 UNUSED)
{
    printf("wsdumm_change_color\n");
}

static char *
wsdummy_get_color_string(VOID_ARGS)
{
    printf("wsdumm_get_color_string\n");
    /* return (char *) 0; */
}
#endif
