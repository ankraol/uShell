#include "header.h"

static void hdl(int sig) {
    sig = sig + 1 - 1;
}

int main(void) {
    int exit = 0;

    signal(SIGINT, hdl);
    signal(SIGTSTP, hdl);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    exit = mx_ush_loop();
    // system("leaks -q ush");
    return exit;
}


