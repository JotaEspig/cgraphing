CC = clang-11
CC_FLAGS = -fPIC -I./include/ `sdl2-config --libs --cflags` --std=c99 -Wall -lm
CC_TEST_FLAGS = -I./include/ `sdl2-config --libs --cflags` -L./lib -lcgraphing -Wall -lm

TARGET_DIR = lib
TARGET = libcgraphing.so

TEST_DIR = tests
TEST_TARGET_DIR = $(TEST_DIR)/bin
TEST_TARGET = cgraphing-test

SRC_DIR = src
SRC = $(shell find ./$(SRC_DIR) -name "*.c")
OBJ_DIR = obj
OBJ = $(patsubst ./$(SRC_DIR)/%.c, ./$(OBJ_DIR)/%.o, $(filter %.c, $(SRC)))

TEST_SRC = $(shell find ./$(TEST_DIR) -name "*.c")
TEST_OBJ = $(patsubst ./$(TEST_DIR)/%.c, ./$(OBJ_DIR)/%.o, $(TEST_SRC))

DEBUG_TOOL = gdb

$(TARGET): dir $(OBJ)
	@printf "\e[1;33m==== Compiling library ====\e[0m\n"
	$(CC) -shared -o ./$(TARGET_DIR)/$(TARGET) $(OBJ) $(CC_FLAGS)
	@printf "\e[1;31m==== Finished compiling library ====\e[0m\n\n"

test: $(TARGET)
	@printf "\e[1;33m==== Compiling tests ====\e[0m\n"
	$(CC) -c $(TEST_SRC) $(CC_TEST_FLAGS)
	@mv *.o ./obj/
	$(CC) -o ./$(TEST_TARGET_DIR)/$(TEST_TARGET) $(TEST_OBJ) $(CC_TEST_FLAGS)
	@printf "\e[1;31m==== Finished compiling tests ====\e[0m\n\n"
	@printf "\e[1;33mRunning...\e[0m\n\n"

	@LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:./lib" \
	./$(TEST_TARGET_DIR)/$(TEST_TARGET)


debug: CC_FLAGS += -g3 -fsanitize=address,undefined
debug: CC_TEST_FLAGS += -g3 -fsanitize=address,undefined
debug: clean $(TARGET)
	@printf "\e[1;33m==== Compiling tests ====\e[0m\n"
	$(CC) -c $(TEST_SRC) $(CC_TEST_FLAGS)
	@mv *.o ./obj/
	$(CC) -o ./$(TEST_TARGET_DIR)/$(TEST_TARGET) $(TEST_OBJ) $(CC_TEST_FLAGS)
	@printf "\e[1;31m==== Finished compiling tests ====\e[0m\n\n"
	@printf "\e[1;33mRunning...\e[0m\n\n"

	@LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:./lib" \
	$(DEBUG_TOOL) ./$(TEST_TARGET_DIR)/$(TEST_TARGET)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(OBJ_EXTERNAL): $(OBJ_DIR)/%.o
	$(CC) $(CC_FLAGS) -c -o $@ $<

.PHONY: dir
dir:
	@if [ ! -d $(TARGET_DIR) ]; then mkdir $(TARGET_DIR); fi
	@if [ ! -d $(TEST_TARGET_DIR) ]; then mkdir -p $(TEST_TARGET_DIR); fi
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi

.PHONY: clean
clean: dir
	-rm ./$(TARGET_DIR)/* 2> /dev/null
	-rm ./$(TEST_TARGET_DIR)/* 2> /dev/null
	-rm ./$(OBJ_DIR)/* 2> /dev/null
