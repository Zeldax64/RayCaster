# SiGAPI Makefile
# TODO: Fix makefile compiling all files again when make all is executed

# Compiler variable
CXX = g++
# Read about -g flag in CFLAGS
CFLAGS = -c -Wall -g
CPPFLAGS = -I ./src
GL = -lGL -lGLU -lglut
LIBS = $(GL)
RM = rm -f

SRCDIR = src

PROG = SiGAPI

# Function to find files in subfolders
subdirs = $(filter-out $1,$(sort $(dir $(wildcard $1*/))))
rfind = $(wildcard $1$2) $(foreach d,$(call subdirs,$1),$(call rfind,$d,$2))
######################################

# Find all *.cpp files in ./src folder
SOURCES := $(call rfind,$(SRCDIR)/,*.cpp)
# Create *.o list of files from SOURCES in subfolders
OBJ := $(patsubst %.cpp, %.o, $(SOURCES))
OBJS := $($SOURCES .c = .o)

.PHONY: run
run: all
	@echo "----- STARTING PROGRAM -----"
	./$(PROG)

# Compile all program
all: $(PROG)

$(PROG): $(OBJ)
	$(CXX) -o $(PROG) $(OBJ) $(LIBS)

# Compilation wildcard
%.o: %.cpp %.h
	$(CXX) $(CPPFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	$(RM) $(PROG) $(OBJ)

help:
	@echo "src: $(SOURCES)"
	@echo "-------------------"
	@echo "objects: $(OBJS)"
