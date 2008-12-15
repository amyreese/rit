
########
# Makefile options for building Automata
########

# Project Configuration

.DEFAULT_GOAL	= all

DOCS_DIR	= doc
TEMP_DIR	= tmp
OBJECTS_DIR	= tmp
SOURCES_DIR	= src
LUA_SOURCE_DIR	= src/lua
OPT_SOURCE_DIR	= src/options
TARGET_DIR	= .

TARGET		= automata
TARGET_CONTROL	= automata.lua
RELEASE		= automata-1.0.tgz
RELEASE_DIR	= automata-1.0

OBJECTS		:= $(patsubst $(SOURCES_DIR)/%.cpp,$(OBJECTS_DIR)/%.o,$(wildcard $(SOURCES_DIR)/*.cpp))
LUA_OBJECTS	:= $(patsubst $(LUA_SOURCE_DIR)/%.c,$(OBJECTS_DIR)/%.o,$(wildcard $(LUA_SOURCE_DIR)/*.c))
OPT_OBJECTS	:= $(patsubst $(OPT_SOURCE_DIR)/%.C,$(OBJECTS_DIR)/%.o,$(wildcard $(OPT_SOURCE_DIR)/*.C))

# Compiler Options

CC		= gcc
CXX		= g++
CFLAGS		= -pipe -W -O2
CXXFLAGS	= -pipe -W -O2
INCPATH		= -I. -I$(SOURCES_DIR) -I$(LUA_SOURCE_DIR) -I$(OPT_SOURCE_DIR) -I/usr/include
LINK		= g++
LFLAGS		=
LIBS		= -L$(LIBS_DIR) -L/usr/lib -lpthread

# Release Options

MKDIR		= mkdir -p 
CP		= cp -a
TAR		= tar czf
TARFLAGS	= --exclude=".*" 
PWD		= $(shell pwd)

########
# Rules
########

.PHONY : fresh
fresh : cleanall all

.PHONY : all
all : directories $(TARGET)
	cp $(SOURCES_DIR)/$(TARGET_CONTROL) $(TARGET_DIR)/

.PHONY : directories
directories : 
	$(MKDIR) $(TARGET_DIR)
	$(MKDIR) $(OBJECTS_DIR)

$(TARGET) : $(OBJECTS) $(LUA_OBJECTS) $(OPT_OBJECTS) 
	$(LINK) $(LFLAGS) -o $(TARGET_DIR)/$@ $(LIBS) $(OBJECTS) $(LUA_OBJECTS) $(OPT_OBJECTS) 

$(OBJECTS) : $(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

$(LUA_OBJECTS) : $(OBJECTS_DIR)/%.o : $(LUA_SOURCE_DIR)/%.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

$(OPT_OBJECTS) : $(OBJECTS_DIR)/%.o : $(OPT_SOURCE_DIR)/%.C
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.PHONY : cleanall
cleanall : clean 
	-rm -f $(LUA_OBJECTS) $(OPT_OBJECTS) 

.PHONY : clean
clean : relclean
	-rm -f $(OBJECTS) $(TARGET) $(TARGET_CONTROL)

.PHONY : release
release : relclean
	$(MKDIR) $(RELEASE_DIR)
	$(CP) $(PWD)/$(SOURCES_DIR) $(RELEASE_DIR)/ 
	$(CP) $(PWD)/$(DOCS_DIR) $(RELEASE_DIR)/
	$(CP) $(PWD)/Makefile $(RELEASE_DIR)/
	$(TAR) $(RELEASE) $(TARFLAGS) $(RELEASE_DIR)
	rm -rf $(RELEASE_DIR)

.PHONY : relclean
relclean : 
	-rm -rf $(RELEASE_DIR) $(RELEASE)
