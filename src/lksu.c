/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
 */

#define MODULE_NAME "lksu"
#define bfdev_log_fmt(fmt) MODULE_NAME ": " fmt

#include <lksu/liblksu.h>
#include <bfdev.h>
#include <errno.h>
#include <command.h>
#include <export.h>

static BFDEV_LIST_HEAD(commands);

static bool
command_exist(struct command_struct *cmd)
{
    struct command_struct *walk;

    bfdev_list_for_each_entry(walk, &commands, list) {
        if (walk == cmd)
            return true;
    }

    return false;
}

struct command_struct *
command_find(const char *name)
{
    struct command_struct *walk;

    bfdev_list_for_each_entry(walk, &commands, list) {
        if (!strcmp(walk->name, name))
            return walk;
    }

    return NULL;
}

int
command_register(struct command_struct *cmd)
{
    if (!cmd->name || !cmd->handle)
        return -EINVAL;

    if (command_find(cmd->name))
        return -EALREADY;

    bfdev_log_debug("register '%s'\n", cmd->name);
    bfdev_list_add(&commands, &cmd->list);

    return 0;
}

int
command_unregister(struct command_struct *cmd)
{
    if (!command_exist(cmd))
        return -ENOENT;

    bfdev_log_debug("unregister '%s'\n", cmd->name);
    bfdev_list_del(&cmd->list);

    return 0;
}

export int
liblksu_command(const char *name)
{
    struct command_struct *cmd;
    unsigned int argc;
    char **argv;
    int retval;

    argv = bfdev_argv_split(NULL, name, &argc);
    if (bfdev_unlikely(!argv))
        return -EINVAL;

    cmd = command_find(*argv);
    if (!cmd) {
        bfdev_argv_destory(NULL, argv);
        return -EINVAL;
    }

    retval = cmd->handle(argc, argv);
    bfdev_argv_destory(NULL, argv);

    return retval;
}
