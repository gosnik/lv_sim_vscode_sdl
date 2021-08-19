#
# Makefile
# WARNING: relies on invocation setting current working directory to Makefile location
# This is done in .vscode/task.json
#
MAKEFLAGS 			:= -j $(shell nproc)
SRC_EXT      		:= c
OBJ_EXT				:= o
SRC_DIR				:= src
#CC 					:= $(CXX)


SRC_DIR				:= ./
WORKING_DIR			:= ./build
BUILD_DIR			:= $(WORKING_DIR)/obj
BIN_DIR				:= $(WORKING_DIR)/bin
UI_DIR 				:= ui

WARNINGS 			:= -Wall -Wextra \
						-Wshadow -Wundef -Wmaybe-uninitialized -Wmissing-prototypes -Wno-discarded-qualifiers \
						-Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized \
						-Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default  \
					  	-Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated  \
						-Wempty-body -Wshift-negative-value -Wstack-usage=2048 \
            			-Wtype-limits -Wsizeof-pointer-memaccess -Wpointer-arith -fpermissive

CFLAGS := -MMD -MP -O0 -g $(WARNINGS)
CXXFLAGS:= -MMD -MP -O0 -g -std=c++17

# Add simulator define to allow modification of source
DEFINES				:= -D SIMULATOR=1 -D LV_BUILD_TEST=0 -D LV_LVGL_H_INCLUDE_SIMPLE=1

# Include simulator inc folder first so lv_conf.h from custom UI can be used instead
INC 				:= -I./ui/simulator/inc/ -I./ -I./lvgl/ -I./main/include -I./qtvault/include
LDFLAGS 			:= -lSDL2 -lm -lpthread
BIN 				:= $(BIN_DIR)/demo

COMPILE				= $(CC) $(CFLAGS) $(INC) $(DEFINES)

# Automatically include all source files
SRCS := $(shell find lv_drivers -type f -name '*.c' -o -name '*.cpp' -not -path '*/\.*')
SRCS += $(shell find lvgl -type f -name '*.c' -o -name '*.cpp' -not -path '*/\.*')
SRCS += $(shell find main -type f -name '*.c' -o -name '*.cpp' -not -path '*/\.*')
SRCS += $(shell find qtvault/src/menu -type f -name '*.c' -o -name '*.cpp' -not -path '*/\.*')
SRCS += $(shell find qtvault/src/util -type f -name '*.c' -o -name '*.cpp' -not -path '*/\.*')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

$(BIN): $(OBJS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(DEFINES) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INC) $(DEFINES) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
