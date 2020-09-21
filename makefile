CXX			:= g++
SRC_DIR		:= src
OBJ_DIR		:= obj
BIN_DIR		:= bin

EXE			:= $(BIN_DIR)/main
SRC			:= $(wildcard $(SRC_DIR)/*.cpp)
OBJ			:= $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS	:= -std=c++11 -Ilib/glm/ -Iinclude -MMD -MP
CFLAGS		:= -Wall
LDFLAGS		:=
LDLIBS 		:= -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS) | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)