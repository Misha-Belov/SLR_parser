BUILD_DIR = build
CMAKE = cmake
CMAKE_FLAGS = ..

.PHONY: all clean rebuild

# Обработка аргумента TESTING (по умолчанию OFF)
ifeq ($(TESTING), ON)
    TEST_FLAG = -DENABLE_TESTS=ON
else
    TEST_FLAG = -DENABLE_TESTS=OFF
endif

all: $(BUILD_DIR)/Makefile
	@$(MAKE) -C $(BUILD_DIR)

$(BUILD_DIR)/Makefile:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) $(CMAKE_FLAGS) $(TEST_FLAG)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all