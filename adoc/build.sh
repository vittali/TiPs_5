#!/bin/zsh
asciidoctor -D ../build **/*.adoc
rsync -a --verbose --perms --times  --prune-empty-dirs --delete-after images ../build

#linkcheck -e --no-show-redirects http://localhost:8080/TiPs_5/index.html