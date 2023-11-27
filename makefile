STD := -std=c++11
CXX := c++ $(STD)
SRCDIR := src
BUILDDIR := build
TARGET := test

SRCEXT := cc
SRCTREE := $(shell find $(SRCDIR) \! -path '*/\.*' -type d)
BUILDTREE := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCTREE)/%)
SOURCES := $(shell find $(SRCDIR) \! -path '*/\.*' -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CXXFLAGS = -Wall -g -O3
INC := -I include

TARCMD := tar --exclude='*.swp' -cf
TARNAME := sph_$(shell date "+%Y-%m-%d-%H%M").tar
TARFILES := src include makefile awk

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(TARGET) $(LIB)"; $(CXX) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo $(BUILDTREE) | xargs mkdir -p
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

tar:
	@echo " Tarring..."; 
	@echo " $(TARCMD) $(TARNAME) $(TARFILES)"; $(TARCMD) $(TARNAME) $(TARFILES)

.SILENT:

.PHONY: clean
