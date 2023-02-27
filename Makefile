# set the compiler
ifeq (${BUILD_TARGET},web)
OUT = generated/web
CXX = em++
EXE = index.html
else ifeq (${BUILD_TARGET},windows)
OUT = generated/windows
CXX = i686-w64-mingw32-g++
EXE = nac
else ifeq (${BUILD_TARGET},windows64)
OUT = generated/windows64
CXX = x86_64-w64-mingw32-g++
EXE = nac
else ifeq (${BUILD_TARGET},linux)
OUT = generated/linux
CXX = g++
EXE = nac
endif

# set the sources - same for all architectures
SRC_DIR = src
IMGUI_DIR = src/imgui
SOURCES = main.cpp $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(SRC_DIR)/backends/imgui_impl_sdl2.cpp $(SRC_DIR)/backends/imgui_impl_sdlrenderer.cpp
# SOURCES += $(IMGUI_DIR)/nac/nac.cpp $(IMGUI_DIR)/nac/renderer.cpp $(IMGUI_DIR)/nac/window.cpp

# Create an output directory for generated objects
OBJS = $(addprefix $(OUT)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))


# Set libraries and flags for each architecture
ifeq (${BUILD_TARGET},web)
EMS += -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=1
CPPFLAGS = -I$(IMGUI_DIR) -I$(SRC_DIR)/backends -I$(SRC_DIR)/nac -g -Wall -Wformat -Os -DIMGUI_DISABLE_FILE_FUNCTIONS $(EMS)
LIBS += $(EMS)
LDFLAGS += -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=0 -s ASSERTIONS=1 -s NO_FILESYSTEM=1 --shell-file shell_minimal.html

else ifeq (${BUILD_TARGET},windows)
CXXFLAGS = -std=c++11 -I$(IMGUI_DIR) -I$(SRC_DIR)/backends -I$(SRC_DIR)/nac -g -Wall -Wformat -Dmain=SDL_main -I/usr/local/cross-tools/i686-w64-mingw32/include/SDL2
CXXFLAGS += -I/usr/local/x86_64-w64-mingw32/include
LIBS = -L/usr/local/cross-tools/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -Wl,--dynamicbase -Wl,--nxcompat -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid
CFLAGS = $(CXXFLAGS)

else ifeq (${BUILD_TARGET},windows64)
CXXFLAGS = -std=c++11 -I$(IMGUI_DIR) -I$(SRC_DIR)/backends -I$(SRC_DIR)/nac -g -Wall -Wformat -Dmain=SDL_main -I/usr/local/cross-tools/x86_64-w64-mingw32/include/SDL2/
CXXFLAGS += -I/usr/local/x86_64-w64-mingw32/include
LIBS = -L/usr/local/cross-tools/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid
CFLAGS = $(CXXFLAGS)

else ifeq (${BUILD_TARGET},linux)
CXXFLAGS = -std=c++11 -I$(IMGUI_DIR) -I$(SRC_DIR)/backends -I$(SRC_DIR)/nac -g -Wall -Wformat -I/usr/local/include/SDL2
LIBS = -L/usr/local/lib /usr/local/lib/libSDL2.a -lm -lpthread -lrt
CFLAGS = $(CXXFLAGS)
endif


# Universal build targets for all sources
$(shell mkdir -p $(OUT)) 
$(OUT)/%.o:%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OUT)/%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OUT)/%.o:$(SRC_DIR)/backends/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OUT)/%.o:$(SRC_DIR)/nac/%.cpp
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


# # Use a differemt g++ compiler for each build architecture
# ifeq (${BUILD_TARGET},web)
# OUT = generated/web
# CXX = em++
# EXE = index.html
# else ifeq (${BUILD_TARGET},windows)
# OUT = generated/windows
# CXX = i686-w64-mingw32-g++
# EXE = nac
# else ifeq (${BUILD_TARGET},windows64)
# OUT = generated/windows64
# CXX = x86_64-w64-mingw32-g++
# EXE = nac
# else ifeq (${BUILD_TARGET},linux)
# OUT = generated/linux
# CXX = g++
# EXE = nac
# endif


# # Sources - same for all architectures
# IMGUI_DIR = src
# SOURCES = main.cpp $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
# SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp
# SOURCES += $(IMGUI_DIR)/nac/nac.cpp $(IMGUI_DIR)/nac/renderer.cpp $(IMGUI_DIR)/nac/window.cpp

# # Create an output directory for generated objects
# OBJS = $(addprefix $(OUT)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))


# # Set libraries and flags for each architecture
# ifeq (${BUILD_TARGET},web)
# EMS +=  -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=0 -s ASSERTIONS=1
# CPPFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(IMGUI_DIR)/nac -Wall -Wformat -Os $(EMS)
# LIBS += $(EMS)
# LDFLAGS += --shell-file shell_minimal.html

# else ifeq (${BUILD_TARGET},windows)
# SOURCES += ${MINGW}/share/glad/glad.c
# CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(IMGUI_DIR)/nac -g -Wall -Wformat -I${MINGW}/include/ -DIMGUI_IMPL_OPENGL_LOADER_GLAD `pkg-config --cflags glfw3`
# CXXFLAGS += -I/usr/local/x86_64-w64-mingw32/include
# LIBS = -lglfw3 -lopengl32 -limm32 `pkg-config --static --libs glfw3`
# CFLAGS = $(CXXFLAGS)

# else ifeq (${BUILD_TARGET},windows64)
# SOURCES += ${MINGW}/share/glad/glad.c
# CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(IMGUI_DIR)/nac -g -Wall -Wformat -I${MINGW}/include/ -DIMGUI_IMPL_OPENGL_LOADER_GLAD `pkg-config --cflags glfw3`
# CXXFLAGS += -I/usr/local/x86_64-w64-mingw32/include
# LIBS = -lglfw3 -lopengl32 -limm32 `pkg-config --static --libs glfw3`
# CFLAGS = $(CXXFLAGS)

# else ifeq (${BUILD_TARGET},linux)
# SOURCES += /usr/share/glad/glad.c
# CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(IMGUI_DIR)/nac -g -Wall -Wformat -I/usr/include/glad -DIMGUI_IMPL_OPENGL_LOADER_GLAD `pkg-config --cflags glfw3`
# LIBS = -lGL `pkg-config --static --libs glfw3`
# CFLAGS = $(CXXFLAGS)
# endif


# # Universal build targets for all sources
# $(shell mkdir -p $(OUT)) 
# $(OUT)/%.o:%.cpp
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
# $(OUT)/%.o:$(IMGUI_DIR)/%.cpp
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
# $(OUT)/%.o:$(IMGUI_DIR)/backends/%.cpp
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
# $(OUT)/%.o:$(IMGUI_DIR)/nac/%.cpp
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
# all: $(OUT)/$(EXE)
# 	@echo Build complete for $(EXE)
# serve: all
# 	python3 -m http.server -d $(OUT)
# $(OUT)/$(EXE): $(OBJS)
# 	$(CXX) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)
# clean:
# 	rm -rf $(OBJS)
# 	rm -r $(OUT)


# # GL Loader compilation for Windows and Linux (Emscripten has it's own loader)
# ifeq (${BUILD_TARGET},windows)
# $(OUT)/%.o:${MINGW}/share/glad/%.c
# 	$(CXX) $(CFLAGS) -c -o $@ $<
# else ifeq (${BUILD_TARGET},windows64)
# $(OUT)/%.o:${MINGW}/share/glad/%.c
# 	$(CXX) $(CFLAGS) -c -o $@ $<
# else ifeq (${BUILD_TARGET},linux)
# $(OUT)/%.o:/usr/share/glad/%.c
# 	$(CC) $(CFLAGS) -c -o $@ $<
# endif
