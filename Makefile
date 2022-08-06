.DEFAULT_GOAL := package-all

.ONESHELL:
.SILENT: 

SHELL        = /bin/bash

.PHONY: new-soln
new-soln:
	read -p "Assignment : " n_a
	read -p "Question   : " n_q
	dirname=$$(printf "Assignment-%02d" $$n_a)
	if [[ ! -d $$dirname ]]; then mkdir -p $$dirname; fi
	filename=$$(printf "A%02d_Q%02d_NA19B001.cpp" $$n_a $$n_q)
	pushd $$dirname > /dev/null
	if [[ -f $$filename ]]; then
		echo "$$filename already exists!"
	else
		sed "s/{{FILENAME}}/$$filename/g" ../soln-template.cpp > $$filename
	fi
	popd > /dev/null
	nvim $$dirname/$$filename

.PHONY: package-all
package-all: clean
	for dirname in `find . -name Assignment-* -type d | sed 's|^./||'`; do
		packed="CS2705-$${dirname}_NA19B001"
		zip -r $$packed $$dirname
	done

.PHONY: clean
clean:
	find . -name a.out -type f -delete
	find . -maxdepth 1 -name *.zip -type f -delete
