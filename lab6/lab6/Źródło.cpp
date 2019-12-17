#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <utility>

bool comparator(int x, int y) {
	return (x > y);
}

int main() {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 10);
	std::poisson_distribution<int> distributionPoisson(5.0);
	std::vector<int> Random(100);
	std::vector<std::pair<double, double>> RandomPoisson(100);
	std::generate_n(Random.begin(), 100, [distribution,&generator]()->int {return distribution(generator); });
	std::generate_n(RandomPoisson.begin(), 100, [distributionPoisson, &generator]()->double {return distributionPoisson(generator); });
	//std::generate_n(RandomPoisson.begin(), 100, [distributionPoisson, &generator]()->double {return distributionPoisson(generator); });
	
	{
	std::cout << "Pierwotny wektor:" << std::endl;
	for (int i : Random) {
		std::cout <<i << "\t";
	}
	std::cout << "\n\n";

	std::cout << "Posortowany:" << std::endl;
	std::sort(Random.begin(), Random.end());//
	for (int i : Random) {
		std::cout << i << "\t";
	}
	std::cout << "\n\n";

	std::cout << "unique:" << std::endl;
	auto last = std::unique(Random.begin(), Random.end());//
	for (int i : Random) {
		std::cout << i << "\t";
	}
	std::cout << "\n\n";
	
	std::cout << "Wynik:" << std::endl;
	Random.erase(last, Random.end());
	for (int i : Random) {
		std::cout << i << "\t";
	}
	std::cout << "\n\n";
	
	std::cout << "Odwrotna kolejnosc:" << std::endl;
	reverse(Random.begin(), Random.end());
	for (int i : Random) {
		std::cout << i << "\t";
	}
	std::cout << "\n\n";

	std::cout << "find()\n";
	std::vector<int>::iterator it;
	it = find(Random.begin(), Random.end(), 2);
	if (it != Random.end()) std::cout << "Found!\n\n";
	else std::cout << "404\n\n";

	
	std::cout << "binary_search()\n";
	if(std::binary_search(Random.begin(), Random.end(), 2, comparator))std::cout << "Found!\n\n";
	else std::cout << "404\n\n";
	}
	
	std::cout << "Poisson:" << std::endl;
	for (std::pair<double, double> i : RandomPoisson) {
		std::cout << i.first << "\t" << i.second << "\n";
	}
	std::cout << "\n\n";



	return 0;
}