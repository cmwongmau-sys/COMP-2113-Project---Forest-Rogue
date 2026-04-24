#ifndef EVENTS_H
#define EVENTS_H

namespace encounter {
    void bearEncounter(int difficulty, int &health, int &food, int &water);
    void treasureEncounter(int difficulty, int &health, int &food, int &water);
    void trapEncounter(int difficulty, int &health, int &food, int &water);
    void waterSpringEncounter(int difficulty, int &health, int &food, int &water);
    void berryBushEncounter(int difficulty, int &health, int &food, int &water);
    void weatherEncounter(int difficulty, int &health, int &food, int &water);
    void emptyEncounter(int difficulty, int &health, int &food, int &water);
}

#endif
