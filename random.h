#ifndef EVENTS_H
#define EVENTS_H

namespace encounter{
        void wildAnimalEncounter(int choice, int difficulty, int &health, int &food, int &water);
        void treasureEncounter(int choice, int difficulty, int &health, int &food, int &water);
        void trapEncounter(int choice, int difficulty, int &health, int &food, int &water);
        void waterSpringEncounter(int difficulty, int &health, int &food, int &water);
        void berryBushEncounter(int difficulty, int &health, int &food, int &water);
        void weatherEncounter(int difficulty, int &health, int &food, int &water);
        void empty(int difficulty, int &health, int &food, int &water);
}

#endif
