/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
 */

#ifndef _LOCAL_COMMAND_H_
#define _LOCAL_COMMAND_H_

#include <bfdev.h>
#include <bfdev/stringify.h>

typedef int
(*command_handle)(int argc, const char *argv[]);

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

#define DEFINE_COMMAND(func)                        \
static int                                          \
__##func##_handle(int argc, const char *argv[]);    \
                                                    \
static struct command_struct                        \
__##func##_command = {                              \
    .name = __bfdev_stringify(func),                \
    .handle = __##func##_handle,                    \
};                                                  \
                                                    \
static __bfdev_ctor void                            \
__##func##_init(void)                               \
{                                                   \
    command_register(&__##func##_command);          \
}                                                   \
                                                    \
static int                                          \
__##func##_handle(int argc, const char *argv[])

#endif /* _LOCAL_COMMAND_H_ */
