# Use a differemt g++ compiler for each build architecture
ifeq (${BUILD_TARGET},web)
OUT = generated/web
CXX = em++
EXE = index.html
else ifeq (${BUILD_TARGET},windows)
OUT = generated/windows
CXX = i686-w64-mingw32-g++
EXE = example_glfw_opengl3
else ifeq (${BUILD_TARGET},linux)
OUT = generated/linux
EXE = example_glfw_opengl3
endif


# Sources - same for all architectures
IMGUI_DIR = src
SOURCES = main.cpp $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
# SOURCES += $(IMGUI_DIR)/backends/renderer.cpp

# Use a different backend for Emscripten builds
ifeq (${BUILD_TARGET},web)
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp 
# SOURCES += $(IMGUI_DIR)/backends/imgui_impl_sdl.cpp
else
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp 
endif


# Create an output directory for generated objects
OBJS = $(addprefix $(OUT)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))


# Set libraries and flags for each architecture
ifeq (${BUILD_TARGET},web)
# EMS += -s USE_SDL=2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=0 -s ASSERTIONS=1
EMS +=  -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -std=c++1z -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=0 -s ASSERTIONS=1
USE_FILE_SYSTEM ?= 0
ifeq ($(USE_FILE_SYSTEM), 0)
EMS += -s NO_FILESYSTEM=1 -DIMGUI_DISABLE_FILE_FUNCTIONS
else ifeq ($(USE_FILE_SYSTEM), 1)
LDFLAGS += --no-heap-copy --preload-file ../../misc/fonts@/fonts
endif
CPPFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -Wall -Wformat -Os $(EMS)
LIBS += $(EMS)
LDFLAGS += --shell-file shell_minimal.html
else ifeq (${BUILD_TARGET},windows)
SOURCES += ${MINGW}/share/glad/glad.c
CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -g -Wall -Wformat -I${MINGW}/include/ -DIMGUI_IMPL_OPENGL_LOADER_GLAD `pkg-config --cflags glfw3`
CXXFLAGS += -I/usr/local/x86_64-w64-mingw32/include
LIBS = -lglfw3 -lopengl32 -limm32 `pkg-config --static --libs glfw3`
CFLAGS = $(CXXFLAGS)
else ifeq (${BUILD_TARGET},linux)
SOURCES += /usr/share/glad/glad.c
# SOURCES += /usr/local/share/gl3w/gl3w.c
CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -g -Wall -Wformat -I/usr/include/glad -DIMGUI_IMPL_OPENGL_LOADER_GLAD `pkg-config --cflags glfw3`
# CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I/usr/local/include/gl3w -DIMGUI_IMPL_OPENGL_LOADER_GL3W -g -Wall -Wformat `pkg-config --cflags glfw3`
# LIBS += -lGL `pkg-config --static --libs glfw3` 
LIBS = -lglfw3 `pkg-config --static --libs glfw3`
CFLAGS = $(CXXFLAGS)
endif


# Universal build targets for all sources
$(shell mkdir -p $(OUT)) 
$(OUT)/%.o:%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OUT)/%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OUT)/%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
all: $(OUT)/$(EXE)
	@echo Build complete for $(EXE)
serve: all
	python3 -m http.server -d $(OUT)
$(OUT)/$(EXE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)
clean:
	rm -rf $(OBJS)
	rm -r $(OUT)


# GL Loader compilation for Windows and Linux (Emscripten has it's own loader)
ifeq (${BUILD_TARGET},windows)
$(OUT)/%.o:${MINGW}/share/glad/%.c
	$(CXX) $(CFLAGS) -c -o $@ $<
else ifeq (${BUILD_TARGET},linux)
# $(OUT)/%.o:/usr/local/share/gl3w/%.c
$(OUT)/%.o:/usr/share/glad/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
endif
