#!/bin/sh

DB=uggedal.db.tar.gz
REPO=/srv/http/pkg/x86_64

if [ $# -gt 0 ]; then
  _root=$1
else
  _root=$(dirname $0)
fi

find $_root -maxdepth 1 -type d | while read d; do
  find $d -maxdepth 1 -type f -name \*.pkg.tar.xz | sort -V | tail -n 1 | while read f; do
  
    name=$(basename $f)
    if [ ! -e $REPO/$name ]; then
      rm -f $REPO/$(echo $name | sed 's/^\([a-z0-9_-]*\)-[0-9].*$/\1/')*.pkg.tar.xz
      cp $f $REPO/$name
      repo-add $REPO/$DB $REPO/$name
    fi
  done
done
