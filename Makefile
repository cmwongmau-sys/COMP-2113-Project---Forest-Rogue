CXX = g++
CXXFLAGS = -I Source/Header/Slate -I Source/Header/Slate/Sprites -I Source/Header/Slate/Widgets -c
TARGET = display.o

SOURCES = Source/Script/Slate/Widgets/GameScreens.cpp \
          Source/Script/Slate/Sprites/SpritesCore.cpp \
          Source/Script/Slate/Widgets/WidgetsCore.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ld -r $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
