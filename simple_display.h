#ifndef SIMPLE_DISPLAY_H
#define SIMPLE_DISPLAY_H

#include <string>
#include <vector>

void startScreen(int health, int food, int water);
void DrawStaticFrame(const std::string& bannerText, const std::vector<std::string>& content);
void DrawZone(int zone);

#endif // SCREEN_DISPLAY_H
