#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

int getnumber(int& input1, int& input2);
int run_test1(int input);
int run_test2(int input);
int run_test3(int input);
int run_test4(int input);
int get_intdigit(int int_input);


int main()
{
	int input_correct = 0;
	int input1, input2;
	while (input_correct == 0)
	{
		getnumber(input1, input2);
		if ((input1 > 0 and input1 <= 10000000) and (input2 > 0 and input2 < 5))
		{
			input_correct = 1;
		}
	}
	switch(input2){
		case 1 :
			run_test1(input1);
			break;
		case 2 :
			run_test2(input1);
			break;
		case 3 :
			run_test3(input1);
			break;
		case 4 :
			run_test4(input1);
			break;
		default :
			cout << "check again." << endl;
	}

	return 0;
}

int getnumber(int& input1, int&input2)
{
	cout << "Please enter the integer and the test number: ";
	cin >> input1 >> input2;
	if (cin.fail())
	{
		cout << "error occurred" << endl;
		cin.clear();
		cin.sync();
	}
//	cout << input1 << " " << input2 << endl;
	return 0;
}

int run_test1(int input1)
{
	float delta_root;
	delta_root = sqrt(1+8*input1);
	float upi = pow(10, -6.0);
	if ((delta_root - (int)delta_root < upi) and (delta_root - (int)delta_root > -upi))
		cout << 1 << endl;
	else
		cout << 0 << endl;

	return 0;
}

int run_test2(int input1)
{
	string input1_str = to_string(input1);
	int str_len = input1_str.length();
	string rev_str(str_len, '0');

	for (int i = 0; i < str_len ; i ++)
		rev_str[i] = input1_str[str_len - i - 1];
//	cout << "output string is " << rev_str << " input is " << input1_str << endl;
	if (rev_str.compare(input1_str) == 0)
		cout << 1 << endl;
	else
		cout << 0 << endl;

	return 0;
}

int run_test3(int input1)
{
	int oneCount = 0;
    while (input1)
    {
        oneCount += (input1 & 1); 
        input1 = input1 >> 1;
    }
    if ((oneCount % 2) == 1)
    cout << 1 << endl;
    else
    cout << 0 << endl;

	return 0;
}

int run_test4(int input1)
{
	int input = input1;
	// get factor list
	int factor_list[24] = {0};
	int primeCount = 0;
	int testing = 1;
	while (testing == 1)
	{
		for (int i = 2; i <= input; i ++)
		{
			if (input % i == 0)
			{
//				cout << i << "*";
				factor_list[primeCount] = i;
				primeCount ++;
				input /= i;
				break;
			}
		}
		if (input == 1)
			testing = 0;
	}
	// get non rep factor list and rep count
	int nonrep_factor_list[24] = {0};
	int rep_count[24] = {0};
	int inserting_label = 0;
	nonrep_factor_list[inserting_label] = factor_list[0];
	inserting_label ++;
	for (int i = 0; i < 24; i ++)
	{
		if (factor_list[i] == 0)
			break;
		for (int j = 0; j < inserting_label; j ++)
		{
			if (factor_list[i] == nonrep_factor_list[j])
			{
				rep_count[j] ++;
				break;
			}
			if (j == inserting_label - 1)
			{
				nonrep_factor_list[inserting_label] = factor_list[i];
				inserting_label ++;
			}
		}
	}
	// sum up
	int sum_of_factors = 0;
	for (int i = 0; i < inserting_label; i ++)
		sum_of_factors += get_intdigit(nonrep_factor_list[i]);
	int sum_of_exp = 0;
	for (int i = 0; i < inserting_label; i ++)
	{
		if (rep_count[i] > 1 and rep_count[i] < 10)
			sum_of_exp ++;
		else if (rep_count[i] >= 10)
			sum_of_exp = sum_of_exp + 2;
	}
	int fact_digit = sum_of_exp + sum_of_factors;
	int number_digit = get_intdigit(input1);
//	cout << "factors digit = " << fact_digit << " number digit = " << number_digit << endl;
	if (number_digit < fact_digit)
	{
//		cout << "a wasteful number is found: " << input1 << ", " << fact_digit << ">" << number_digit << endl;
		cout << 1 << endl;
	}
	else
		cout << 0 << endl;

	return 0;
}

int get_intdigit(int int_input)
{
	int digit = 0;
	while(int_input)
	{
		int_input /= 10;
		digit ++;
	}
	return digit;
}