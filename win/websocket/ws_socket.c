/* NetHack ws_socket.c */
/* Copyright (c) Karl-Heinz Ruskowski, 2022 */
/* NetHack may be freely redistributed.  See license for details. */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "hack.h"

#include "ws_socket.h"

int create_socket(int s, char *socketname) {

    char sockpath[255];
    strcpy(sockpath, nh_getenv("WEBSOCKETDIR"));

    int s2, t, len;
    struct sockaddr_un local, remote;

    if((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;

    strcat(sockpath, socketname);

    strcpy(local.sun_path, sockpath);
    unlink(local.sun_path);
    printf("creating socket: %s\n", local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);

    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }

    if(listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }
    return s;

}
