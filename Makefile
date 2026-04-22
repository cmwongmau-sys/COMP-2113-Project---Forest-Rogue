CXX = g++
CXXFLAGS = -I Source/Header/Slate -I Source/Header/Slate/Sprites -I Source/Header/Slate/Widgets
TARGET = ForestRogue

SOURCES = Source/Script/Slate/Widgets/GameScreens.cpp \
          Source/Script/Slate/Sprites/SpritesCore.cpp \
          Source/Script/Slate/Widgets/WidgetsCore.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
