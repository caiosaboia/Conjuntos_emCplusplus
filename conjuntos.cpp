#include <iostream> //cout
#include <math.h> //Floor
#include <ctime> //Time
#include <vector> 

using namespace std;

class Conjunto {
	vector <int> V;
	int busca_binaria(int x);

public:
	bool vazio();
	int tamanho();
	void imprime();
	void apaga_tudo();
	bool pertece(int valor);
	bool push(int valor);
	void uniao(Conjunto& C1, Conjunto& C2);
	void intersecao(Conjunto& C1, Conjunto& C2);
}

; bool Conjunto::vazio() {
	if (V.size() == 0)
		return true;
	else
		return false;
}

int Conjunto::tamanho() {
	return V.size();
}

void Conjunto::apaga_tudo() {
	V.clear();
}

void Conjunto::imprime() {
	for (int i = 0; i < V.size(); i++) {
		cout << V[i] << " ";
	}
	cout << "\n";
}

int Conjunto::busca_binaria(int x) {
	int p = 0; int r = V.size() - 1;
	while (p <= r) {
		int q = (p + r) / 2;
		if (V[q] < x)
			p = q + 1;
		else if (V[q] > x)
			r = q - 1;
		else if (V[q] == x)
			return q;
	}
	return -1;
}

bool Conjunto::pertece(int x) {
	if (busca_binaria(x) < 0) return false;
	return true;
}


bool Conjunto::push(int valor) {
	if (pertece(valor)) return false;
	int i = V.size() - 1;
	V.push_back(valor);
	while ((i >= 0) && (V[i])) {
		V[i + 1] = V[i];
		i--;
	}
	V[i + 1] = valor;
	return true;
}

void Conjunto::uniao(Conjunto& C1, Conjunto& C2) {
	apaga_tudo(); int i, j;
	int n1 = C1.tamanho();
	int n2 = C2.tamanho();
	if (n1 == 0) {
		for (j = 0; j < n2; j++)
			V.push_back(C2.V[i]);
		return;
	}
	if (n2 == 0) {
		for (i = 0; i < n1; i++) V.push_back(C1.V[i]);
		return;
	}
	i = j = 0; int ultimo = min(C1.V[0], C2.V[0]);
	if (ultimo == C1.V[0]) i++; else j++;
	V.push_back(ultimo);

	while ((i < n1) || (j < n2)) {
		if ((j > n2) || ((i < n1) && (C1.V[i] <= C2.V[i]))) {
			if (C1.V[i] > ultimo) {
				V.push_back(C1.V[i]); ultimo = C1.V[i];
			}
			i++;
		}
		else {
			if (C2.V[j] > ultimo) {
				V.push_back(C2.V[j]); ultimo = C2.V[j];
			}
			j++;
		}
	}
}

void Conjunto::intersecao(Conjunto& C1, Conjunto& C2) {
	if (C1.tamanho() > C2.tamanho()) {
		intersecao(C2, C1);
		return;
	}
	apaga_tudo();
	for (int i = 0; i < C1.tamanho(); i++) {
		if (C2.pertece(C1.V[i])) {
			push(C1.V[i]);
		}
	}
}


int main() {
	Conjunto C;
	Conjunto B;
	Conjunto A;
	srand (time(NULL));
	for (int i = 0; i < 50; i++) {
		int x = rand() % 100;
		C.push(x);
	}
	for (int i = 0; i < 50; i++) {
		int x = rand() % 100;
		B.push(x);
	}

	cout << "Tamanho C: " << C.tamanho();
	cout << "\n";
	cout << "Tamanho B: " << B.tamanho();
	cout << "\n";

	cout << "Vetor 1: ";
	C.imprime();

	cout << "Vetor 2: ";
	B.imprime();

	cout << "uniao:";
	A.uniao(C, B);

	cout << "intersecao:"; A.intersecao(C, B);

}
