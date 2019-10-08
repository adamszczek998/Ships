#pragma once
#include "Distance.h"
#include "Circle.h"


enum polozenie { rozlaczne_zewnetrznie, styczne_zew, przecinajace_sie, styczne_wew, rozlaczne_wew, wspolsrodkowe };

polozenie circlesLocation();