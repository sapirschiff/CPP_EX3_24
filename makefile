# Define compiler and compiler flags
CC = g++
CFLAGS = -std=c++11 -Wall

# Define source files
GAME_SRCS = catan.cpp Board.cpp Hexagon.cpp Vertex.cpp Edge.cpp DevelopCard.cpp Player.cpp Card.cpp AdvancementCard.cpp 
TEST_SRCS = Test.cpp Board.cpp Hexagon.cpp Vertex.cpp Edge.cpp DevelopCard.cpp Player.cpp Card.cpp AdvancementCard.cpp 

# Define object files
GAME_OBJS = $(GAME_SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Define executable
GAME_EXEC = catan
TEST_EXEC = test

# Rule to build executable
$(GAME_EXEC): $(GAME_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build executable
$(TEST_EXEC): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(GAME_OBJS) $(TEST_OBJS) $(GAME_EXEC) $(TEST_EXEC)

.PHONY: clean all

all: $(GAME_EXEC) $(TEST_EXEC)