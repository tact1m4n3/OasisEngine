CC = g++
AR = AR

SANDBOX_APP = bin/SandboxApp

OasisLIB = bin/libOasis.a
GlfwLIB = Oasis/vendor/glfw/dist/Debug-macosx-x86_64/GLFW/libGLFW.a
GladLIB = Oasis/vendor/glad/dist/libGLAD.a

STB_IMAGE_OBJ_FILES := bin-int/stb_image/stb_image.o

Oasis_SRC_FILES := $(shell find Oasis/src/Oasis -name *.cpp)
Oasis_OBJ_FILES := $(patsubst Oasis/src/Oasis/%.cpp, bin-int/Oasis/%.o, $(Oasis_SRC_FILES))

Sandbox_SRC_FILES := $(shell find Sandbox/src/Sandbox -name *.cpp)
Sandbox_OBJ_FILES := $(patsubst Sandbox/src/Sandbox/%.cpp, bin-int/Sandbox/%.o, $(Sandbox_SRC_FILES))

bin-int/stb_image/%.o: Oasis/vendor/stb_image/%.cpp
	mkdir -p $(dir $@) && \
	$(CC) -c -std=c++17 -o $@ $^

$(Oasis_OBJ_FILES) : bin-int/Oasis/%.o : $(Oasis_SRC_FILES)
	mkdir -p $(dir $@) && \
	$(CC) -c -std=c++17 -I Oasis/src -I Oasis/vendor/glad/include -I Oasis/vendor/glfw/include -I Oasis/vendor/glm -I Oasis/vendor/stb_image -D OASIS_MACOSX -D OASIS_DEBUG $(patsubst bin-int/Oasis/%.o, Oasis/src/Oasis/%.cpp, $@) -o $@

$(Sandbox_OBJ_FILES) : bin-int/Sandbox/%.o : $(Sandbox_SRC_FILES)
	mkdir -p $(dir $@) && \
	$(CC) -c -std=c++17 -I Oasis/src -I Oasis/vendor/glad/include -I Oasis/vendor/glfw/include -I Oasis/vendor/glm -I Oasis/vendor/stb_image -D OASIS_MACOSX -D OASIS_DEBUG $(patsubst bin-int/Sandbox/%.o, Sandbox/src/Sandbox/%.cpp, $@) -o $@

$(GladLIB):
	$(MAKE) -C Oasis/vendor/glad bin-int

$(OasisLIB): $(Oasis_OBJ_FILES)
	mkdir -p $(dir $@) && \
	$(AR) rcs $@ $^

$(SANDBOX_APP): $(GlfwLIB) $(GladLIB) $(STB_IMAGE_OBJ_FILES) $(OasisLIB) $(Sandbox_OBJ_FILES)
	mkdir -p $(dir $@) && \
	$(CC) -o $@ $^ -framework Cocoa -framework OpenGL -framework IOKit

run: $(SANDBOX_APP)
	./bin/SandboxApp

clean:
	rm -rf bin-int
	rm -rf bin
