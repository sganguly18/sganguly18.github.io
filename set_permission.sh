#!/bin/bash

walk_dir () {
    shopt -s nullglob dotglob

    for pathname in "$1"/*; do
        if [ -d "$pathname" ]; then
	    chmod 711 "$pathname" 
            walk_dir "$pathname"
        else
            printf '%s\n' "$pathname"
	    chmod 644 "$pathname" 
        fi
    done
}

DIR=$1

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 DIRECTORY" >&2
  exit 1
fi
walk_dir "$DIR"
