TARGET := quark 

SOURCE_DIR := source
OBJECT_DIR := obj

SOURCE_FILES := $(wildcard $(SOURCE_DIR)/*.cc)
OBJECT_FILES := $(patsubst $(SOURCE_DIR)/%.cc,$(OBJECT_DIR)/%.o,$(SOURCE_FILES))

CC := g++

COMPILER_FLAGS := -Wall -D X11_SESSION
LINKER_FLAGS := -lSDL2_image -lSDL2

all: $(OBJECT_FILES) 
	$(CC) $(OBJECT_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(TARGET)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cc
	@mkdir -p $(@D)
	$(CC) -c $< $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

clean:
	rm -rf $(OBJECT_DIR) $(TARGET)

$(shell mkdir -p $(OBJECT_DIR))
