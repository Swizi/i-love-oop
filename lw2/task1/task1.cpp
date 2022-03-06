#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <sstream>

using namespace std;

vector<string> split(const string& s, char delim)
{
	vector<string> elems;
	istringstream iss(s);
	string item;
	while (getline(iss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

bool is_positive(double value)
{
	return value > 0;
}

double round(double val)
{
	if (val < 0) return ceil(val - 0.5);
	return floor(val + 0.5);
}

int positive_binary_operation(double sum, double val)
{
	return is_positive(val) ? sum + round(val * 1000.0) / 1000.0 : sum;
}

vector<double> read_vector(bool& was_error)
{
	string input_num = "";
	string input_string = "";

	getline(cin, input_string);

	vector<string> input_string_vector = split(input_string, ' ');
	vector<double> num_vector = vector<double>(input_string_vector.size());

	transform(input_string_vector.begin(), input_string_vector.end(), num_vector.begin(), [&](const string& string_value) {
		double double_value = 0;
		try
		{
			double_value = stod(string_value);
		}
		catch (std::exception& e)
		{
			was_error = true;
		}
		return double_value;
		});

	return num_vector;
}

vector<double> modify_vector(vector<double> num_vector)
{
	double sum = accumulate(num_vector.begin(), num_vector.end(), 0, positive_binary_operation);
	int n = count_if(num_vector.begin(), num_vector.end(), is_positive);

	double arithmetic_mean = 0;
	if (n != 0) {
		arithmetic_mean = sum / n;
	}

	vector<double> modified_vector = vector<double>(num_vector.size());

	transform(num_vector.begin(), num_vector.end(), modified_vector.begin(), [&](const double& val) { return val + arithmetic_mean; });

	return modified_vector;
}

void print_vector(vector<double> num_vector)
{
	for (int i = 0; i < num_vector.size(); i++) {
		cout << num_vector[i];
		if (i != num_vector.size() - 1)
		{
			cout << " ";
		}
	}

	cout << endl;
}

int main()
{
	bool was_error = false;
	vector<double> num_vector = read_vector(was_error);

	if (was_error) {
		cout << "Incorrect input numbers" << endl;
		return 1;
	}

	num_vector = modify_vector(num_vector);
	sort(num_vector.begin(), num_vector.end());
	print_vector(num_vector);

	return 0;
}
