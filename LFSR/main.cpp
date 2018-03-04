#include <iostream>
#include <algorithm>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::swap;

int main()
{
	int NrOfCoeffs = 0;
	int NrOfXor = 0;
	int degree = 0;
	int period = 0;
	int *coeffs;
	int *init_state;
	int *curr_state;
	int *next_state;
	int *xor_result;
	int *output;
	int *next_output;
	int *autocorrelation;

	cout << "Podaj liczbe wspolczynnikow wielomianu: " << endl;
	cin >> NrOfCoeffs;
	coeffs = new int[NrOfCoeffs];

	cout << "Podaj wartosci wspolczynnikow wielomianu: " << endl;
	for (int i = NrOfCoeffs - 1; i >= 0; i--)
	{
		cin >> coeffs[i];
		if (coeffs[i] < 0) cout << "Nieprawidlowa wartosc, zacznij od nowa" << endl;
		if (coeffs[i] > degree) degree = coeffs[i];
	}

	for (int i = 0; i < NrOfCoeffs; i++)
		for (int j = 1; j < NrOfCoeffs - i; j++)
			if (coeffs[j - 1] > coeffs[j])
				swap(coeffs[j - 1], coeffs[j]);

	cout << "Wspolczynniki wielomianu:\t";
	for (int k = NrOfCoeffs - 1; k >= 0; k--)
		cout << coeffs[k] << "\t";
	cout << endl;

	cout << "Stopien wielomianu = " << degree << endl;

	period = pow(2, degree) - 1;
	cout << "Okres generowanej sekwencji: " << period << endl;

	init_state = new int[degree];
	curr_state = new int[degree];
	output = new int[period];

	cout << "Podaj stan poczatkowy rejestru [0/1]: " << endl;
	for (int i = degree - 1; i >= 0; i--)
	{
		cin >> init_state[i];
		if (!(init_state[i] != 1 ^ init_state[i] != 0)) cout << "Nieprawidlowa wartosc, zacznij od nowa" << endl;
		curr_state[i] = init_state[i];
	}

	next_state = new int[degree];
	NrOfXor = NrOfCoeffs - 2;
	xor_result = new int[NrOfXor];

	for (int i = 0; i < period; i++)
	{
		cout << "\nStan LFSR nr " << i << " :\t";
		for (int k = degree - 1; k >= 0; k--)
			cout << curr_state[k] << "\t";

		output[i] = curr_state[coeffs[0]];
		if (output[i] == 0) output[i] = -1;
		cout << "Wyjscie LFSR nr " << i << ":\t" << output[i] << endl;

		xor_result[0] = curr_state[coeffs[1]] xor curr_state[coeffs[0]];

		if (NrOfCoeffs > 3)
			for (int j = 1; j < NrOfXor; j++)
				xor_result[j] = curr_state[coeffs[j + 1]] xor xor_result[j - 1];

		next_state[degree - 1] = xor_result[NrOfXor - 1];
		for (int j = degree - 2; j >= 0; j--)
			next_state[j] = curr_state[j + 1];

		for (int k = degree - 1; k >= 0; k--)
			curr_state[k] = next_state[k];
	}
	cout << endl;
	next_output = new int[period];
	int sum;
	autocorrelation = new int[period * 2];

	for (int i = 0; i < period * 2; i++)
	{
		sum = 0;

		for (int j = 0; j < period; j++)
			next_output[(i + j) % period] = output[(j)];

		for (int k = 0; k < period; k++)
			sum += output[k] * next_output[k];

		autocorrelation[i] = sum;
		cout << "Autokorelacja nr " << i << ":\t" << autocorrelation[i] << endl;
	}

	delete[] autocorrelation;
	delete[] next_output;
	delete[] output;
	delete[] xor_result;
	delete[] next_state;
	delete[] curr_state;
	delete[] init_state;
	delete[] coeffs;

	system("pause");

	return 0;
}

