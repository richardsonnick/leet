CXX = g++
CXX_FLAGS = -std=c++20 -MMD -Iinclude -Wall -g -O0
TARGET = leet
SRCS = src/main.cpp
OBJS = $(patsubst src/%.cpp,obj/%.o,$(SRCS))
DEPS = $(patsubst src/%.cpp,obj/%.d,$(SRCS))

GTEST_DIR = third_party/googletest/googletest
GTEST_FLAGS = -isystem $(GTEST_DIR)/include
GTEST_LIB = third_party/libgtest.a
GTEST_MAIN_LIB = third_party/libgtest_main.a
TEST_SRCS = $(wildcard tests/*.cpp)
TEST_OBJS = $(patsubst tests/%.cpp,obj/test_%.o,$(TEST_SRCS))
TEST_TARGET = leet_test


all: $(TARGET)

-include $(DEPS)

$(TARGET) : $(OBJS)
		$(CXX) $(CXX_FLAGS) $(OBJS) -o $(TARGET)


obj/%.o: src/%.cpp
		$(CXX) $(CXX_FLAGS) -c $< -o $@

third_party/googletest:
		git clone https://github.com/google/googletest.git third_party/googletest --depth=1

$(GTEST_LIB): third_party/googletest
		$(CXX) $(CXX_FLAGS) $(GTEST_FLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc -o obj/gtest-all.o
		ar -rv $@ obj/gtest-all.o

$(GTEST_MAIN_LIB): third_party/googletest
		$(CXX) $(CXX_FLAGS) $(GTEST_FLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest_main.cc -o obj/gtest_main.o
		ar -rv $@ obj/gtest_main.o

obj/test_%.o: tests/%.cpp
		$(CXX) $(CXX_FLAGS) $(GTEST_FLAGS) -MMD -c $< -o $@

$(TEST_TARGET): $(TEST_OBJS) $(GTEST_LIB) $(GTEST_MAIN_LIB)
		$(CXX) $(CXX_FLAGS) $(TEST_OBJS) $(GTEST_LIB) $(GTEST_MAIN_LIB) -lpthread -o $@

test: $(TEST_TARGET)
		./$(TEST_TARGET)

tags:
		ctags -R .

compile_commands.json:
		bear -- $(MAKE) clean all test

clean:
		rm ./obj/*
