#!/usr/bin/env bash
recurse() {
    for file in $1/*; do
        if [ -d "$file" ] 
            then recurse $file
	elif [ -h "$file" -a ! -e "$file" -a `stat --format=%Y $file` -le $(( `date +%s` - 604800 )) ] 
            then echo "$file"
	fi
    done
}
recurse $1