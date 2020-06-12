#!/bin/bash

set -euxo pipefail

git checkout master
rm -rfv ./build
mkdir -p /tmp/LinearAlgebraDocs
rm -rfv /tmp/LinearAlgebraDocs
./build.sh /tmp/LinearAlgebraDocs
git checkout gh-pages
rm -rf *
cp -r /tmp/LinearAlgebraDocs/docs/doxygen_docs/html/* ./
git add *
git commit -a -m "Updated documentation."
git rebase --autosquash HEAD~1
git push origin -f
git checkout master
