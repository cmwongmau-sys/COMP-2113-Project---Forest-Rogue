CXX = g++

CXXFLAGS = -I Source/Header/Slate -I Source/Header/Slate/Sprites -I Source/Header/Slate/Widgets -I Source/Header/Slate

vpath %.cpp Source/Script/Slate/Widgets Source/Script/Slate/Sprites
vpath %.h Source/Header/Slate Source/Header/Slate/Widgets Source/Header/Slate/Sprites

sprites.o: SpritesCore.cpp SpritesCore.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

widgets.o: WidgetsCore.cpp WidgetsCore.h SpritesCore.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

screens.o: GameScreens.cpp GameScreens.h WidgetsCore.h SpritesCore.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

random.o: random.cpp random.h GameScreens.h WidgetsCore.h SpritesCore.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

display.o: simple_display.cpp simple_display.h
	$(CXX) -c $< -o $@

event.o: event_generation.cpp event_generation.h
	$(CXX) -c $< -o $@

file.o: file.cpp file.h
	$(CXX) -c $< -o $@

main.o: main.cpp file.h random.h event_generation.h simple_display.h GameScreens.h WidgetsCore.h SpritesCore.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

game: main.o random.o screens.o file.o display.o event.o widgets.o sprites.o
	$(CXX) $^ -o $@
clean:
	rm -f game main.o random.o screens.o file.o display.o event.o widgets.o sprites.o

.PHONY: clean
