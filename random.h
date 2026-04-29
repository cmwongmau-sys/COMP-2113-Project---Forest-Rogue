#ifndef EVENTS_H
#define EVENTS_H

namespace encounter{
        void bearEncounter(int difficulty, int &health, int &food, int &water);
        void treasureEncounter(int &health, int &food, int &water);
        void trapEncounter(int &health, int &food, int &water);
        void waterSpringEncounter(int &health, int &food, int &water);
        void berryBushEncounter(int &health, int &food, int &water);
        void weatherEncounter(int &health, int &food, int &water);
        void emptyEncounter(int &health, int &food, int &water);
}

#endif
