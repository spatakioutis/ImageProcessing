CC = g++
CFLAGS = -Wall -g -fsanitize=address
#CFLAGS = -Wall -g 
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = ImageProcessor

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	@rm -f $(OBJECTS)
	@echo "\n --------Compilation successful!----------\n"

%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -f $(OBJECTS)

.PHONY: all clean
