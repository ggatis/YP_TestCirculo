# Name of the static library
LIBRARY_LIB_NAME := ggLib.a

# Directories
LIBRARY_DIR := $(USERPROFILE)/Documents/Arduino/ggLib

# Targets
#all: build_library copy_library compile
all: build_library copy_library

# Target to build the library
build_library:
	@$(MAKE) -C $(LIBRARY_DIR)

# Target to copy the built library to the Arduino project folder
copy_library:
	cp $(LIBRARY_DIR)/$(LIBRARY_LIB_NAME) $(LIBRARY_LIB_NAME)
	mkdir -p include
	cp -r $(INCLUDE_DIR)/include/* ./include/

.PHONY: all build_library copy_library
