#!/bin/sh
# ensure that cp --preserve=link --link doesn't waste heap

# Copyright (C) 2008-2013 Free Software Foundation, Inc.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

. "${srcdir=.}/tests/init.sh"; path_prepend_ ./src
print_ver_ cp
expensive_
require_ulimit_v_

a=$(printf %031d 0)
b=$(printf %031d 1)
(mkdir $a \
   && cd $a \
   && seq --format=%031g 10000 |xargs touch \
   && seq --format=d%030g 10000 |xargs mkdir ) || framework_failure_
cp -al $a $b || framework_failure_
mkdir e || framework_failure_
mv $a $b e || framework_failure_

# Increased from 20000 to 22000 in 2012, for pre-F18 rawhide.
(ulimit -v 22000; cp -al e f) || fail=1

Exit $fail
