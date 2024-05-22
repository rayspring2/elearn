
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wall -I./include #-fsanitize=address -fsanitize=undefined


SRCDIR = src
OBJDIR = obj
#BINDIR = .
EXECUTABLE = UTms.out #$(BINDIR)/
MEDIA_PATH = ./files/

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(wildcard $(SRCDIR)/*.hpp)
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(MEDIA_PATH)

clean:
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE) majors.csv courses.csv professors.csv students.csv
