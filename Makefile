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
NAC_DIR = src/nac

SOURCES = main.cpp $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(SRC_DIR)/backends/imgui_impl_sdl2.cpp $(SRC_DIR)/backends/imgui_impl_sdlrenderer.cpp
SOURCES += $(NAC_DIR)/nac.cpp $(NAC_DIR)/renderer.cpp $(NAC_DIR)/window.cpp $(NAC_DIR)/interface.cpp $(NAC_DIR)/texture.cpp

# Create an output directory for generated objects
OBJS = $(addprefix $(OUT)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))


# Set libraries and flags for each architecture
ifeq (${BUILD_TARGET},web)
EMS += -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s DISABLE_EXCEPTION_CATCHING=1
CPPFLAGS = -I$(IMGUI_DIR) -I$(SRC_DIR)/backends -I$(NAC_DIR) -g -Wall -Wformat -Os -DIMGUI_DISABLE_FILE_FUNCTIONS $(EMS)
LIBS += $(EMS)
LDFLAGS += -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=0 -s ASSERTIONS=1 -s --shell-file shell_minimal.html --use-preload-plugins --preload-file $(NAC_DIR)/textures@/

else ifeq (${BUILD_TARGET},windows)
CXXFLAGS = -std=c++11 -I$(IMGUI_DIR) -I$(SRC_DIR)/backends -I$(NAC_DIR) -g -Wall -Wformat -Dmain=SDL_main -I/usr/local/cross-tools/i686-w64-mingw32/include/SDL2 
CXXFLAGS += -I/usr/local/x86_64-w64-mingw32/include
LIBS = -L/usr/local/cross-tools/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -Wl,--dynamicbase -Wl,--nxcompat -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid
CFLAGS = $(CXXFLAGS)

else ifeq (${BUILD_TARGET},windows64)
CXXFLAGS = -std=c++11 -I$(IMGUI_DIR) -I$(SRC_DIR)/backends -I$(NAC_DIR) -g -Wall -Wformat -Dmain=SDL_main -I/usr/local/cross-tools/x86_64-w64-mingw32/include/SDL2/
CXXFLAGS += -I/usr/local/x86_64-w64-mingw32/include
LIBS = -L/usr/local/cross-tools/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2 -mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid
CFLAGS = $(CXXFLAGS)

else ifeq (${BUILD_TARGET},linux)
CXXFLAGS = -std=c++11 -I$(IMGUI_DIR) -I$(SRC_DIR)/backends -I$(NAC_DIR) -g -Wall -Wformat -I/usr/local/include/SDL2
LIBS = -L/usr/local/lib /usr/local/lib/libSDL2.a /usr/local/lib/libSDL2_image.a -lm -lpthread -lrt
CFLAGS = $(CXXFLAGS)
endif


# Universal build targets for all sources
$(shell mkdir -p $(OUT))
$(shell cp -r $(NAC_DIR)/textures/* $(OUT))

$(OUT)/%.o:%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OUT)/%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OUT)/%.o:$(SRC_DIR)/backends/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
$(OUT)/%.o:$(NAC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
all: $(OUT)/$(EXE)
	@echo Build complete for $(EXE)
serve: all
	python3 -m http.server -d $(OUT)
$(OUT)/$(EXE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)
clean:
	rm -f $(OUT)/*