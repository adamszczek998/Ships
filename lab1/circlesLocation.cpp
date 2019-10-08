#include "circlesLocation.h"

polozenie circlesLocation(Point A, Point B, Circle Aa, Circle Bb) {
	double odleglosc = distance(A, B);
	double promienA = Circle::Aa.get_promien();
	double promienB = Circle::Bb.get_promien();
	if (odleglosc < promienA - promienB) return rozlaczne_wew;
	else if (odleglosc > promienA + promienB) return rozlaczne_zewnetrznie;
	else if (A.x == B.x && A.y == B.y) return wspolsrodkowe;
	else if (promienA - promienB < odleglosc&&odleglosc < promienA + promienB) return przecinajace_sie;
	else if (odleglosc == promienA + promienB) return styczne_zew;
	else if (odleglosc == promienA + promienB) return styczne_wew;
}


