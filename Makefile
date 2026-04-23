CXX = g++

CXXFLAGS = -I Source/Header/Slate -I Source/Header/Slate/Sprites -I Source/Header/Slate/Widgets -I Source/Header/Slate

vpath %.cpp Source/Script/Slate/Widgets Source/Script/Slate/Sprites
vpath %.h Source/Header/Slate Source/Header/Slate/Widgets Source/Header/Slate/Sprites

SpritesCore.o: SpritesCore.cpp SpritesCore.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

WidgetsCore.o: WidgetsCore.cpp WidgetsCore.h SpritesCore.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

GameScreens.o: GameScreens.cpp GameScreens.h WidgetsCore.h SpritesCore.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

SimpleDisplay.o: simple_display.cpp simple_display.h
	$(CXX) -c $< -o $@

EventGeneration.o: event_generation.cpp event_generation.h
	$(CXX) -c $< -o $@


.PHONY: clean
