FILE := src/glad.c
OBJECT_FILE := build/glad.o
LIBRARY := dist/libGLAD.a

$(OBJECT_FILE): $(FILE)
	mkdir -p bin-int
	gcc -c -Iinclude $^ -o $@

$(LIBRARY): $(OBJECT_FILE)
	mkdir -p bin
	ar rcs $@ $^

clean:
	rm -rf build
	rm -rf dist

build: $(LIBRARY)
