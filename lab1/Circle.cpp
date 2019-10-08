#include "Circle.h"

Circle::Circle(const Circle& kopia) : promien(kopia.promien), srodek(kopia.srodek) {}
Circle::Circle(double promien, double x, double y) : promien(promien), srodek(x, y) {}

polozenie circlesLocation (const Circle& Aa, const Circle& Bb) {
	double odleglosc = distance(Aa.get_srodek(), Bb.get_srodek());
	double promienA = Aa.get_promien();
	double promienB = Bb.get_promien();
	if (odleglosc < promienA - promienB) return rozlaczne_wew;
	else if (odleglosc > promienA + promienB) return rozlaczne_zewnetrznie;
	else if (Aa.get_srodek().x == Bb.get_srodek().x && Aa.get_srodek().y == Bb.get_srodek().y) return wspolsrodkowe;
	else if (promienA - promienB < odleglosc&&odleglosc < promienA + promienB) return przecinajace_sie;
	else if (odleglosc == promienA + promienB) return styczne_zew;
	else if (odleglosc == promienA + promienB) return styczne_wew;
}
