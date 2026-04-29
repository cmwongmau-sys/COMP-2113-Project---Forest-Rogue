CXX = g++

sprites.o: SpritesCore.cpp SpritesCore.h
	$(CXX) -c $< -o $@

widgets.o: WidgetsCore.cpp WidgetsCore.h SpritesCore.h
	$(CXX) -c $< -o $@

screens.o: GameScreens.cpp GameScreens.h WidgetsCore.h SpritesCore.h
	$(CXX) -c $< -o $@

random.o: random.cpp random.h GameScreens.h WidgetsCore.h SpritesCore.h
	$(CXX) -c $< -o $@

display.o: simple_display.cpp simple_display.h
	$(CXX) -c $< -o $@

event.o: event_generation.cpp event_generation.h
	$(CXX) -c $< -o $@

file.o: file_switch.cpp file_switch.h
	$(CXX) -c $< -o $@

main.o: main.cpp file_switch.h random.h event_generation.h simple_display.h GameScreens.h WidgetsCore.h SpritesCore.h
	$(CXX) -c $< -o $@

game: main.o random.o screens.o file.o display.o event.o widgets.o sprites.o
	$(CXX) $^ -o $@
clean:
	rm -f game main.o random.o screens.o file.o display.o event.o widgets.o sprites.o

.PHONY: clean
