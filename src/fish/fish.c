#include <fish/fish.h>

void move_fish(Fish* fish, unsigned long delta_time) { fish->x += delta_time * fish->speed; }
