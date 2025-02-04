# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++17

# Source files
SRCS = MyCrackme09.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = MyCrackme09

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lgdi32 -luser32

# Compile each .cpp file to .o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean




# # Compiler
# CC = g++

# # Compiler flags
# CFLAGS = -Wall -std=c++17

# # Include directories for Google Test
# INCLUDES = -I D:/PROJECTS/HackingProgram_InjectDLL_MemoryScanner/HackingProgram_InjectDLL_MemoryScanner/packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn.1.8.1.7/build/native/include/gtest/ -I D:/PROJECTS/HackingProgram_InjectDLL_MemoryScanner/HackingProgram_InjectDLL_MemoryScanner/DEPENDENCIES/googletest-1.15.2/googlemock/include/gmock/

# # Library directories for Google Test
# LIBS = -L D:/PROJECTS/HackingProgram_InjectDLL_MemoryScanner/HackingProgram_InjectDLL_MemoryScanner/packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-static.1.8.1.7/lib/native/v140/windesktop/msvcstl/static/rt-static/x64/Release/ -lgtest -lgtest_main -pthread

# # Source files
# SRCS = SHELLCODE_Opcode_Generator.cpp

# # Object files
# OBJS = $(SRCS:.cpp=.o)

# # Executable name
# TARGET = SHELLCODE_Opcode_Generator

# # Default target
# all: $(TARGET)

# # Link object files to create the executable
# $(TARGET): $(OBJS)
	# $(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LIBS) -lgdi32 -luser32

# # Compile each .cpp file to .o
# %.o: %.cpp
	# $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# # Clean up build files
# clean:
	# rm -f $(OBJS) $(TARGET)

# # Phony targets
# .PHONY: all clean
