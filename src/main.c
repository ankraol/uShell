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
<<<<<<< HEAD
    // system("leaks -q ush");
=======
    //system("leaks -q ush");
>>>>>>> 1379583f4ab98e72ba4386f042ee1cdf430a89b4
    return exit;
}


