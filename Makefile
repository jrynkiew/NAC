##---------------------------------------------------------------------
## Start of WEB BUILDER
##---------------------------------------------------------------------

ifeq (${WEB_BUILDER},1)

OUT = generated/web
CC = emcc
CXX = em++
WEB_DIR = web
EXE = index.html
IMGUI_DIR = src
SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_sdl.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
OBJS = $(addprefix $(OUT)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
UNAME_S := $(shell uname -s)

EMS += -s USE_SDL=2 -s WASM=1
EMS += -s ALLOW_MEMORY_GROWTH=1
EMS += -s DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=0
EMS += -s ASSERTIONS=1

USE_FILE_SYSTEM ?= 0
ifeq ($(USE_FILE_SYSTEM), 0)
EMS += -s NO_FILESYSTEM=1 -DIMGUI_DISABLE_FILE_FUNCTIONS
endif
ifeq ($(USE_FILE_SYSTEM), 1)
LDFLAGS += --no-heap-copy --preload-file ../../misc/fonts@/fonts
endif

CPPFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CPPFLAGS += -Wall -Wformat -Os
CPPFLAGS += $(EMS)
LIBS += $(EMS)
LDFLAGS += --shell-file shell_minimal.html

$(shell mkdir -p $(OUT)) 

$(OUT)/%.o:%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(OUT)/%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(OUT)/%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

%.o:../libs/gl3w/GL/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

all: $(OUT)/$(EXE)
	@echo Build complete for $(EXE)

$(OUT):
	mkdir $@

serve: all
	python3 -m http.server -d $(OUT)

$(OUT)/$(EXE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)
	rm -r $(OUT)

##---------------------------------------------------------------------
## Start of WINDOWS BUILDER
##---------------------------------------------------------------------

else ifeq (${WINDOWS_BUILDER},1)

CXX = i686-w64-mingw32-g++
COMMAND_LINK_SOLVER=$(CXX) -Wl,-r -o $@ $^
OUT = generated/windows
WINDOWS_DIR = bin
EXE = example_glfw_opengl3
IMGUI_DIR = src
SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
OBJS = $(addprefix $(OUT)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
UNAME_S := $(shell uname -s)
WINDOWS_GL_LIBS = -lglfw3 -lopengl32 -limm32

CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wformat
LIBS =

SOURCES += ${MINGW}/share/glad/glad.c
CXXFLAGS += -I${MINGW}/include/ -DIMGUI_IMPL_OPENGL_LOADER_GLAD

ECHO_MESSAGE = "Windows"
LIBS += $(WINDOWS_GL_LIBS) `pkg-config --static --libs glfw3`

CXXFLAGS += `pkg-config --cflags glfw3` -I/usr/local/x86_64-w64-mingw32/include
CFLAGS = $(CXXFLAGS)

$(shell mkdir -p $(OUT)) 

$(OUT)/%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT)/%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT)/%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT)/%.o:${MINGW}/share/glad/%.c
	$(CXX) $(CFLAGS) -c -o $@ $<

all: $(OUT)/$(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(OUT)/$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
	rm -r $(OUT)

else
	
##---------------------------------------------------------------------
## Start of LINUX BUILDER
##---------------------------------------------------------------------

EXE = example_glfw_opengl3
IMGUI_DIR = src
OUT = generated/linux
WINDOWS_DIR = linux
SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
OBJS = $(addprefix $(OUT)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL

CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wformat

SOURCES += /usr/local/share/gl3w/gl3w.c
CXXFLAGS += -I/usr/local/include/gl3w -DIMGUI_IMPL_OPENGL_LOADER_GL3W

LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

CXXFLAGS += `pkg-config --cflags glfw3`
CFLAGS = $(CXXFLAGS)

$(shell mkdir -p $(OUT)) 

$(OUT)/%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT)/%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT)/%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT)/%.o:/usr/local/share/gl3w/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OUT)/$(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(OUT)/$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
	rm -r $(OUT)

endif