// cmdapp: main.c: A program to test the cmdapp library.
// Copyright (C) 2021 Ethan Uppal. All rights reserved.

#include "cmdapp.h"
#include <stdio.h>

static void setup_options(cmdapp_t* app, cmdopt_t* file, cmdopt_t* eval) {
    cmdopt_t* file_confl[] = { eval, NULL };
    cmdopt_t* eval_confl[] = { file, NULL };
    cmdapp_set(
        app,
        'f',
        "file",
        CMDOPT_TAKESARG,
        file_confl /* either accepts file or in-command text. */,
        "Does nothing with a file",
        file
    );
    cmdapp_set(
        app,
        'e',
        "eval",
        CMDOPT_TAKESARG,
        eval_confl /* either accepts file or in-command text. */,
        "Does nothing with a script",
        eval
    );
}

void handle_options(cmdopt_t* file, cmdopt_t* eval) {
    if (cmdopt_exists(*file)) {
        printf("file - %s\n", file->value);
    } else if (cmdopt_exists(*eval)) {
        printf("eval - %s\n", eval->value);
    }
}

void myproc(void *data, cmdopt_t* option, const char* arg) {
//    if (is_plain_arg) {
//        printf("arg: %s\n", arg);
//    } else {
//        printf("-%c%s\n", option->shorto, option->value);
//    }
}

int main(int argc, char* argv[]) {
    cmdapp_t app;
    const char* custom_synopses[] = {
        "subcommand [OPTION]...",
        "[OPTION]... FILE...",
        NULL
    };
    const cmdapp_info_t info = {
        .program = "main",
        // .synopses = NULL, // so it's automatic
        .synopses = custom_synopses,
        .version = "1.0",
        .author = "Ethan Uppal",
        .year = 2021,
        .description = "A program that does nothing.",
        .help_des_offset = 20,
        .ver_extra =
        "You may only use this program once BOTH cats and pigs have ascended into cyperspace.\n"
        "There is NO WARRANTY, to the extent permitted by law.\n"
    };
    cmdapp_init(&app, argc, argv, CMDAPP_MODE_SHORTARG, &info);
    cmdapp_enable_procedure(&app, myproc, NULL);
    cmdopt_t file, eval;
    setup_options(&app, &file, &eval);

    if (cmdapp_run(&app) == EXIT_SUCCESS) {
        handle_options(&file, &eval);
    } else {
        return 1;
    }

    cmdapp_destroy(&app);

    return 0;
}
