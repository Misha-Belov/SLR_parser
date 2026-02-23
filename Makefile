# Makefile для сборки проекта через CMake
# Цели:
#   make         - собрать проект (инкрементально)
#   make clean   - удалить папку сборки
#   make rebuild - полностью пересобрать проект (clean + all)

BUILD_DIR = build
CMAKE = cmake
CMAKE_FLAGS = ..
TARGET = slr_parser

.PHONY: all clean rebuild

# Сборка проекта (инкрементальная)
all: $(BUILD_DIR)/Makefile
	@$(MAKE) -C $(BUILD_DIR)

# Создание файлов сборки, если их нет
$(BUILD_DIR)/Makefile:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) $(CMAKE_FLAGS)

# Полная очистка
clean:
	rm -rf $(BUILD_DIR)

# Полная пересборка
rebuild: clean all