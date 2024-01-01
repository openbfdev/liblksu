/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
 */

#ifndef _LOCAL_EXPORT_H_
#define _LOCAL_EXPORT_H_

#undef hidden
# define hidden __bfdev_visibility("hidden")

#undef export
# define export __bfdev_visibility("default")

#endif /* _LOCAL_EXPORT_H_ */
