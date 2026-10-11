# ffun packaging (see ffun/README.md, "Install").
#   make wheel   dist/ffun-<version>-py3-none-any.whl, with the current commit recorded in it
#   make dev     editable install into the active Python environment: "ffun" runs this checkout
#   make clean   remove the build outputs

PYTHON ?= python3

.PHONY: wheel dev clean clean-build

wheel:
	@commit=$$($(PYTHON) -c 'import sys; sys.path.insert(0, "ffun"); import support; print(support.ffun_commit() or "unknown")') && \
	echo "COMMIT = \"$$commit\"  # written by make wheel" > ffun/_build.py && \
	$(PYTHON) -m pip wheel --no-deps --no-cache-dir -w dist . ; \
	rc=$$?; rm -f ffun/_build.py; $(MAKE) --no-print-directory clean-build; exit $$rc

dev:
	$(PYTHON) -m pip install -e .

# setuptools' own outputs only; build/ itself is removed only when nothing else is in it
clean-build:
	rm -rf build/lib/ffun build/bdist.* ffun.egg-info
	-rmdir build/lib build 2>/dev/null

clean: clean-build
	rm -rf dist ffun/_build.py
