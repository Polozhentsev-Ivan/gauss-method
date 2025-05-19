PROJECT = main
LIBPROJECT = $(PROJECT).a
TESTPROJECT = main_test

SRC_DIR = src
TEST_DIR = tests
INC_DIR = include

CXX = g++
A = ar
AFLAGS = crs

# Добавляем путь к Eigen, если он установлен в системе
EIGEN_PATH = /usr/include/eigen3
CXXFLAGS = -Wall -Werror -std=c++17 -g -Wpedantic -I$(INC_DIR) -I$(EIGEN_PATH)
LDXXFLAGS = $(CXXFLAGS) -lpthread
LDGTESTFLAGS = $(CXXFLAGS) -lgtest -lgtest_main -lpthread

SRC = $(wildcard $(SRC_DIR)/*.cpp)

APP_SRC = $(SRC_DIR)/main.cpp
LIB_SRC = $(filter-out $(APP_SRC), $(SRC))
LIB_OBJ = $(LIB_SRC:.cpp=.o)
APP_OBJ = $(APP_SRC:.cpp=.o)

TEST_SRC = $(TEST_DIR)/main_test.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)


DEPS = $(wildcard $(INC_DIR)/*.h)

.PHONY: all test check clean cleanall

all: $(PROJECT)


$(PROJECT): $(APP_OBJ) $(LIBPROJECT)
	$(CXX) -o $@ $(APP_OBJ) $(LIBPROJECT) $(LDXXFLAGS)



$(LIBPROJECT): $(LIB_OBJ)
	$(A) $(AFLAGS) $@ $^


$(TESTPROJECT): $(TEST_OBJ) $(LIBPROJECT)
	$(CXX) -o $@ $(TEST_OBJ) $(LIBPROJECT) $(LDGTESTFLAGS)


test: $(TESTPROJECT)
	@./$(TESTPROJECT)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(APP_OBJ) $(LIB_OBJ) $(TEST_OBJ)

cleanall: clean
	rm -f $(PROJECT) $(LIBPROJECT) $(TESTPROJECT)