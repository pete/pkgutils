/*
 * pkgutils
 *
 * Copyright (c) 2000-2005 Per Liden
 * Copyright (c) 2007 by CRUX team (http://crux.nu)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

#include "pkg_package_entry.h"

PkgPackageEntry *
pkg_package_entry_new (const char *name, size_t name_len)
{
	PkgPackageEntry *entry;

	if (name_len == (size_t) -1)
		name_len = strlen (name);

	entry = malloc (sizeof (PkgPackageEntry) + name_len + 2);
	if (!entry)
		return NULL;

	entry->name[0] = '/';
	memcpy (&entry->name[1], name, name_len + 1);

	entry->name_len = name_len + 1;
	entry->refcount = 1;
	entry->archive_entry = NULL;

	return entry;
}

void
pkg_package_entry_ref (PkgPackageEntry *entry)
{
	entry->refcount++;
}

void
pkg_package_entry_unref (PkgPackageEntry *entry)
{
	if (--entry->refcount)
		return;

	if (entry->archive_entry)
		archive_entry_free (entry->archive_entry);

	free (entry);
}

PKG_API
mode_t
pkg_package_entry_get_mode (PkgPackageEntry *entry)
{
	return archive_entry_mode (entry->archive_entry);
}

PKG_API
uid_t
pkg_package_entry_get_uid (PkgPackageEntry *entry)
{
	return archive_entry_uid (entry->archive_entry);
}

PKG_API
gid_t
pkg_package_entry_get_gid (PkgPackageEntry *entry)
{
	return archive_entry_gid (entry->archive_entry);
}

PKG_API
int64_t
pkg_package_entry_get_size (PkgPackageEntry *entry)
{
	return archive_entry_size (entry->archive_entry);
}

PKG_API
dev_t
pkg_package_entry_get_dev (PkgPackageEntry *entry)
{
	return archive_entry_rdev (entry->archive_entry);
}

PKG_API
const char *
pkg_package_entry_get_symlink_target (PkgPackageEntry *entry)
{
	return archive_entry_symlink (entry->archive_entry);
}