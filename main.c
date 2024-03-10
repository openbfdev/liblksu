/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
 */

#include <stdio.h>
#include <lksu/liblksu.h>

int main(int argc, const char *argv[])
{
    int retval;

    retval = liblksu_exec(argc - 1, argv + 1);
    if (retval) {
        printf("failed: %d\n", retval);
        return retval;
    }

    printf("success\n");
    return 0;
}
