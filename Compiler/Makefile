CC = g++
FLAGS = -W -Wall -pedantic -std=c++17 -O3 

TARGET = compiler

FLEX = flex
BISON = bison

SRC_DIR = src
OBJ_DIR = build
OUT_DIR = ./

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) $(OBJ_DIR)/lexer.o $(OBJ_DIR)/parser.o

debug: FLAGS := $(FLAGS) -D DEBUG
debug: all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) -o $(OUT_DIR)/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/parser.c $(SRC_DIR)/lexer.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -x c++ $(FLAGS) -c $< -o $@

$(SRC_DIR)/lexer.c: $(SRC_DIR)/lexer.l
	$(FLEX) -o $@ $<

$(SRC_DIR)/parser.c: $(SRC_DIR)/parser.y
	$(BISON) -d -o $@ $<

clean:
	rm -f $(OUT_DIR)$(TARGET)
	rm -f $(OBJ_DIR)/*.o
	rm -f $(SRC_DIR)/parser.c $(SRC_DIR)/parser.h $(SRC_DIR)/lexer.c

cleanall: clean
	rm -f compiler
