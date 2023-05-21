build:
	cmake --build ./build
.PHONY: build

test:
	./build/UNIT_TESTS
.PHONY: test
