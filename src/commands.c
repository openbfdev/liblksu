/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
 */

#define MODULE_NAME "liblksu-commands"
#define bfdev_log_fmt(fmt) MODULE_NAME ": " fmt

#include <command.h>
#include <stdint.h>
#include <bfdev.h>
#include <errno.h>
#include <sys/prctl.h>
#include <lksu/kernel.h>

static inline int
lksu_syscall(struct lksu_message *msg)
{
    return prctl(LKSU_SYSCALL_CTLKEY, (uintptr_t)msg);
}

DEFINE_COMMAND(enable)
{
    struct lksu_message msg;

    if (argc != 2) {
        bfdev_log_err("Usage: enable token\n");
        return -EINVAL;
    }

    msg.func = LKSU_ENABLE;
    strncpy(msg.token, argv[1], LKSU_TOKEN_LEN);

    return lksu_syscall(&msg);
}

DEFINE_COMMAND(disable)
{
    struct lksu_message msg;

    if (argc != 2) {
        bfdev_log_err("Usage: disable token\n");
        return -EINVAL;
    }

    msg.func = LKSU_DISABLE;
    strncpy(msg.token, argv[1], LKSU_TOKEN_LEN);

    return lksu_syscall(&msg);
}

DEFINE_COMMAND(flush)
{
    struct lksu_message msg;

    if (argc != 2) {
        bfdev_log_err("Usage: flush token\n");
        return -EINVAL;
    }

    msg.func = LKSU_FLUSH;
    strncpy(msg.token, argv[1], LKSU_TOKEN_LEN);

    return lksu_syscall(&msg);
}

DEFINE_COMMAND(g_hidden_add)
{
    struct lksu_message msg;

    if (argc != 3) {
        bfdev_log_err("Usage: g_hidden_add token path\n");
        return -EINVAL;
    }

    msg.func = LKSU_GLOBAL_HIDDEN_ADD;
    msg.args.g_hidden = argv[2];
    strncpy(msg.token, argv[1], LKSU_TOKEN_LEN);

    return lksu_syscall(&msg);
}

DEFINE_COMMAND(g_hidden_remove)
{
    struct lksu_message msg;

    if (argc != 3) {
        bfdev_log_err("Usage: g_hidden_remove token path\n");
        return -EINVAL;
    }

    msg.func = LKSU_GLOBAL_HIDDEN_REMOVE;
    msg.args.g_hidden = argv[2];
    strncpy(msg.token, argv[1], LKSU_TOKEN_LEN);

    return lksu_syscall(&msg);
}

DEFINE_COMMAND(g_uid_add)
{
    struct lksu_message msg;

    if (argc != 3) {
        bfdev_log_err("Usage: g_uid_add token uid\n");
        return -EINVAL;
    }

    msg.func = LKSU_GLOBAL_UID_ADD;
    msg.args.g_uid = atoi(argv[2]);
    strncpy(msg.token, argv[1], LKSU_TOKEN_LEN);

    return lksu_syscall(&msg);
}

DEFINE_COMMAND(g_uid_remove)
{
    struct lksu_message msg;

    if (argc != 3) {
        bfdev_log_err("Usage: g_uid_remove token uid\n");
        return -EINVAL;
    }

    msg.func = LKSU_GLOBAL_UID_REMOVE;
    msg.args.g_uid = atoi(argv[2]);
    strncpy(msg.token, argv[1], LKSU_TOKEN_LEN);

    return lksu_syscall(&msg);
}

DEFINE_COMMAND(token_add)
{
    struct lksu_message msg;

    if (argc != 3) {
        bfdev_log_err("Usage: token_add token token_to_add\n");
        return -EINVAL;
    }

    msg.func = LKSU_TOKEN_ADD;
    strncpy(msg.args.token, argv[2], LKSU_TOKEN_LEN);
    strncpy(msg.token, argv[1], LKSU_TOKEN_LEN);

    return lksu_syscall(&msg);
}

DEFINE_COMMAND(token_remove)
{
    struct lksu_message msg;

    if (argc != 3) {
        bfdev_log_err("Usage: token_remove token token_to_remove\n");
        return -EINVAL;
    }

    msg.func = LKSU_TOKEN_REMOVE;
    strncpy(msg.args.token, argv[2], LKSU_TOKEN_LEN);
    strncpy(msg.token, argv[1], LKSU_TOKEN_LEN);

    return lksu_syscall(&msg);
}
