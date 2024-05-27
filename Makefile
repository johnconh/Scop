NAME = scop

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -Ilibs/glew/include -DGLEW_STATIC
LDFLAGS =-Llibs/glew/lib -lGLEW -lGLU -lglfw -lGL -lX11 -lXrandr -lpthread -lXi -ldl

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/$(NAME)

## Colors:
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
YELLOW = \033[0;93m

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@printf "$(BLUE)Compiling: $< ...$(DEF_COLOR)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN)Done!$(DEF_COLOR)"

run: $(EXECUTABLE)
	@LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PWD)/libs/glew/lib $(EXECUTABLE)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)$(NAME) object files removed!$(DEF_COLOR)"

fclean: clean	
	@rm -rf $(BIN_DIR)
	@echo "$(YELLOW)$(NAME) removed!$(DEF_COLOR)"

re: fclean all run

.PHONY: all fclean clean re run