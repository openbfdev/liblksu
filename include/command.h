/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
 */

#ifndef _LOCAL_COMMAND_H_
#define _LOCAL_COMMAND_H_

#include <bfdev.h>
#include <bfdev/stringify.h>

typedef int
(*command_handle)(int argc, char *argv[]);

struct command_struct {
    const char *name;
    command_handle handle;
    struct bfdev_list_head list;
};

extern struct command_struct *
command_find(const char *name);

extern int
command_register(struct command_struct *cmd);

extern int
command_unregister(struct command_struct *cmd);

#define DEFINE_COMMAND(name)                \
static int                                  \
__command_##name(int argc, char *argv[]);   \
                                            \
static struct command_struct                \
__##name##command = {                       \
    .name = __bfdev_stringify(name),        \
    .handle = __command_##name,             \
}                                           \
                                            \
static __bfdev_ctor void                    \
{                                           \
    command_register(&__##name##command);   \
}                                           \
                                            \
static int                                  \
__command_##name(int argc, char *argv[])

#endif /* _LOCAL_COMMAND_H_ */
