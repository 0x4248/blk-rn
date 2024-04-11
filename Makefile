# BLK-RN
# A lightweight bulk rename tool for Linux
# Github: https://www.github.com/0x4248/blk-rn
# Licence: GNU General Public License v3.0
# By: 0x4248
TEST_MODE = -1
TEST_ARGS = -v
RUN_ARGS = -v

all: compile run

compile:
	g++ -o blk-rn src/blkrn.cpp --std=gnu++17

clean:
	rm -f blk-rn

clean_tests:
	rm -rf tests/

test-generate: clean_tests
	python3 generate_tests.py $(TEST_MODE)

run:
	./blk-rn $(RUN_ARGS)

test: clean compile test-generate
	./blk-rn $(TEST_ARGS)
