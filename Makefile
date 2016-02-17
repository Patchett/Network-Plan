# Kyle Barron-Kraus <kbarronk>

BIN_NAME = netplan

SOURCES = netplan.cpp UndirectedGraph.cpp Vertex.cpp Edge.cpp

CXX = g++
CXX_FLAGS = -std=c++11 -Wall -Wextra -g -O2
LD_FLAGS = -g -O2

BUILD_PATH = build

OBJECTS = $(SOURCES:%.cpp=$(BUILD_PATH)/%.o)
DEP_FILES = $(OBJECTS:.o=.d)

.PHONY: all
all: $(BIN_NAME)

$(BUILD_PATH):
	@echo "Creating directory: $(BUILD_PATH)"
	@mkdir -p $(BUILD_PATH)

$(BUILD_PATH)/%.o: %.cpp | $(BUILD_PATH)
	@echo "Compiling: $< -> $@"
	@$(CXX) $(CXX_FLAGS) -MP -MMD -c -o $@ $<

$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $(BIN_NAME)"
	@$(CXX) $(LD_FLAGS) $(OBJECTS) -o $@

-include $(DEP_FILES)

.PHONY: clean
clean:
	@$(RM) -rv $(BIN_NAME) $(BUILD_PATH) *~ core *.core
