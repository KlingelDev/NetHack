/* NetHack ws_init.c */
/* Copyright (c) Karl-Heinz Ruskowski, 2022 */
/* NetHack may be freely redistributed.  See license for details. */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#ifndef WEBSOCKETDIR
#define WEBSOCKETDIR "~/nswebsocket"
#endif

#include "hack.h"

#include "ws_init.h"
#include "ws_socket.h"

int websocket_create_input(void) {
    printf("websocket_create_input\n");
    int socket;
    socket = create_socket(socket, "input.sock");
    return socket;

}

void websocket_create_message_window(int wid) {
    printf("websocket_create_message_window\n");
    struct wswin *msgwin;
    msgwin = wins[wid];

    int s;

    s = create_socket(s, "message.sock");

    msgwin->socket = s;
}

void websocket_create_menu_window(int wid) {
    printf("websocket_create_menu_window\n");
    struct wswin *menuwin;
    menuwin = wins[wid];

    int s;

    //s = create_socket(s, "menu.sock");

    menuwin->socket = s;
}

void websocket_create_map_window(int wid) {
    printf("websocket_create_map_window\n");
    struct wswin *mapwin;
    mapwin = wins[wid];

    int s;

    //s = create_socket(s, "map.sock");

    mapwin->socket = s;
}

void websocket_create_status_window(int wid) {
    printf("websocket_create_status_window\n");
    struct wswin *mapwin;
    mapwin = wins[wid];

    int s;

    s = create_socket(s, "status.sock");

    mapwin->socket = s;
}

void websocket_create_text_window(int wid) {
    printf("websocket_create_text_window\n");
    struct wswin *mapwin;
    mapwin = wins[wid];

    int s;

    s = create_socket(s, "text.sock");

    mapwin->socket = s;
}
