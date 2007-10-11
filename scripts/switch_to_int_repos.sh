#!/bin/sh

# Note: This script should only be run from within the scripts/ directory.

# This script is designed to switch from the subverion repositories external
# url to the internal private network based url. This is provided that so the
# developers working on the project could trivially switch to the internal
# subversion repository url when working within the private network after
# previously working external to the private network.

source ./common.sh

cd ../
svn switch --relocate ${EXT_URL} ${INT_URL}