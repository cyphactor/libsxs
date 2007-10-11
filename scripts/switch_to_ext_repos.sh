#!/bin/sh

# Note: This script should only be run from within the scripts/ directory.

# This script is designed to switch from the subverion repositories internal
# private network based url to the external url. This is provided that so the
# developers working on the project could trivially switch to the external
# subversion repository url when working outside the private network after
# previously working inside the private network.

source ./common.sh

cd ../
svn switch --relocate ${INT_URL} ${EXT_URL}