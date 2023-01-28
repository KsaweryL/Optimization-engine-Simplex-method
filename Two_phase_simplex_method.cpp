#include <iostream>
#include <string>

#define N 2			//no. of variables

using namespace std;

void Show_function_table(float function_table[3][N + 5])			//used to print the current simplex table
{
	cout << endl << endl << "               ";
	for (int i = 0; i < N; i++)
	{
		cout << "x" << i + 1 << "  ";
	}
	cout << "S1  S2  A1  A2  Value of the var.";

	for (int i = 0; i < 3; i++)
	{
		cout << endl;
		if (i > 0) cout << "Variable no." << i << " | ";
		if (i == 0) cout << "               ";
		for (int j = 0; j < N + 5; j++)
		{
			if (function_table[i][j] < 0 || function_table[i][j] > 9) cout << function_table[i][j] << "| ";
			else cout << function_table[i][j] << " | ";
		}
	}
}

void Simplex_method(float function_table[3][N + 5], int det, int& Var1, int& Var2, string solution[])		//the simplex method
{
	int det2 = 0;

	int variable_column_delete = 0;

	while (1)
	{
		float partial_solution_table[N + 4];

		for (int i = 0; i < N + 4; i++)						//zj and cj
		{
			partial_solution_table[i] = 0;
		}

		Show_function_table(function_table);

		cout << endl << "               ";
		for (int i = 0; i < N + 4 - variable_column_delete; i++)						//zj and cj
		{

			float Z_minus_C = Var1 * function_table[1][i] + Var2 * function_table[2][i] - function_table[0][i];
			partial_solution_table[i] = Z_minus_C;
			Z_minus_C = 0;

			cout << partial_solution_table[i] << "   ";
		}


		int entering_variable = 0;				//identyfing entering variable
		for (int i = 1; i < N + 4 - variable_column_delete; i++)
		{
			if (partial_solution_table[i] < partial_solution_table[entering_variable]) entering_variable = i;
		}


		int leaving_variable = 1;				//identyfing the leaving variable
		if (function_table[1][6] / function_table[1][entering_variable] < 0) leaving_variable = 2;
		if (function_table[2][6] / function_table[2][entering_variable] <
			function_table[1][6] / function_table[1][entering_variable] &&
			function_table[2][6] / function_table[2][entering_variable] >= 0) leaving_variable = 2;

		float key_element = 0;					// the key element also known as the pivot element
		if (leaving_variable == 1)key_element = function_table[1][entering_variable];
		if (leaving_variable == 2)key_element = function_table[2][entering_variable];

		variable_column_delete++;

		float next_table[3][N + 5];	//the next table

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < N + 5; j++) next_table[i][j] = 0;
		}
		for (int i = 0; i < N + 5; i++)
		{
			next_table[0][i] = function_table[0][i];
			next_table[leaving_variable][i] = function_table[leaving_variable][i] / key_element;
		}
		cout << endl << endl;

		int change_values_row = 1;
		if (leaving_variable == change_values_row) change_values_row = 2;

		for (int i = 0; i < N + 5; i++) {
			next_table[change_values_row][i] = function_table[change_values_row][i] - (function_table[change_values_row][entering_variable] * function_table[leaving_variable][i]) / key_element;
		}

		char entering_variable_str[3];			//created for the user to have clearer output
		char leaving_variable_str[] = { "Variable no.1" };
		entering_variable_str[2] = NULL;
		if (leaving_variable == 1) leaving_variable_str[12] = '1';
		if (leaving_variable == 2) leaving_variable_str[12] = '2';

		if (entering_variable == N || entering_variable == N + 1) entering_variable_str[0] = 'S';   //S
		if (entering_variable == N + 2 || entering_variable == N + 3)entering_variable_str[0] = 'A';  //A
		if (entering_variable < N)  entering_variable_str[0] = 'x';										//x

		if (entering_variable % 2 == 0 && entering_variable >= N) entering_variable_str[1] = '1';				//x1, x3, x5 (number 0, 2, 4 in array)
		if (entering_variable % 2 != 0 && entering_variable >= N) entering_variable_str[1] = '2';

		if (entering_variable_str[0] == 'x')entering_variable_str[1] = entering_variable + 49;


		cout << endl << "Leaving variable: " << leaving_variable_str << endl << "Entering variable: " << entering_variable_str<<endl		//the output
			<< "The value of the pivot element: "<<key_element<<endl;

		for (int i = 0; i < N; i++)
		{
			if (leaving_variable == i + 1) solution[i] = entering_variable_str;
		}
	
		det2 = 1;
		for (int j = 0; j < N + 4; j++)			//the stop condition when there is still a nagetive number in partial_solution_table
		{
			if (partial_solution_table[j] < 0) det2 = 0;
		}

		if (det2 == 1) {
			cout << "\nThe stop condition no.1" << endl;
			if (det == 2) {
				cout << endl << "The final solution: \n";
				
				for (int i = 0; i < N; i++)
				{
					cout << solution[i] << " = " << function_table[i + 1][N + 4]<<endl;
				}
			} break;
		}

		Show_function_table(next_table);

		if (leaving_variable == 2) Var2 = function_table[0][entering_variable];
		if (leaving_variable == 1) Var1 = function_table[0][entering_variable];
		cout << endl;
	
		for (int i = 0; i < N + 4; i++)	 partial_solution_table[i] = 0;					//zj and cj

		cout << "               ";
		for (int i = 0; i < N + 4 - variable_column_delete; i++)						//zj and cj
		{
			partial_solution_table[i] = 0;
			float Z_minus_C = Var1 * next_table[1][i] + Var2 * next_table[2][i] - next_table[0][i];
			partial_solution_table[i] = Z_minus_C;
			Z_minus_C = 0;

			cout << partial_solution_table[i] << "   ";
		}
		cout << endl;
		for (int i = 0; i < 3; i++)							//making next_table the function_table
		{
			for (int j = 0; j < N + 5; j++) function_table[i][j] = next_table[i][j];
		}

		if (leaving_variable == 1) leaving_variable_str[12] = '1';
		if (leaving_variable == 2) leaving_variable_str[12] = '2';

		if (entering_variable == N || entering_variable == N + 1) entering_variable_str[0] = 'S';   //S
		if (entering_variable == N + 2 || entering_variable == N + 3)entering_variable_str[0] = 'A';  //A
		if (entering_variable < N)  entering_variable_str[0] = 'x';										//x

		if (entering_variable % 2 == 0 && entering_variable >= N) entering_variable_str[1] = '1';				//x1, x3, x5 (number 0, 2, 4 in array)
		if (entering_variable % 2 != 0 && entering_variable >= N) entering_variable_str[1] = '2';

		if (entering_variable_str[0] == 'x')entering_variable_str[1] = entering_variable + 49;

		cout << endl << "Leaving variable: " << leaving_variable_str << endl << "Entering variable: " << entering_variable_str << endl
			<< "The value of the pivot element: " << key_element << endl;

		for (int i = 0; i < N; i++)
		{
			if (leaving_variable == i + 1) solution[i] = entering_variable_str;
		}
		

		det2 = 1;
		for (int j = 0; j < N + 4; j++)			//the stop condition when there is still a nagetive number in partial_solution_table
		{
			if (partial_solution_table[j] < 0) det2 = 0;
		}

		if (det2 == 1) {
			cout << "\nThe stop condition no.2" << endl;
				if (det == 2) {
					cout << endl << "The final solution: \n";
						for (int i = 0; i < N; i++)
						{
							cout << solution[i] << " = " << function_table[i + 1][N + 4] << endl;
						}
				} break;
		}

	}

}

void Simplex_method_2nd_phase(float first_phase_table[3][N + 5], float function_table[3][N + 5], int det, int& Var1, int& Var2, string solution[])
{
	cout << endl << endl << "The second phase: " << endl << endl;
	for (int j = 0; j < N; j++)
	{
		first_phase_table[0][j] = function_table[0][j];
	}

	Simplex_method(first_phase_table, det, Var1, Var2, solution);

}

void Two_phase_simplex_method(float function_table[3][N + 5])
{
	//we look for A1 and A2
	float first_phase_table[3][N + 5];
	string solution[N];		//for the solution

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < N + 5; j++)
		{
			first_phase_table[i][j] = 0;
			first_phase_table[i][j] = function_table[i][j];
		}
	}

	for (int j = 0; j < N + 5; j++)
	{
		first_phase_table[0][j] = 0;
	}

	if (function_table[1][N + 2] != 0) first_phase_table[0][N + 2] = -function_table[1][N + 2];
	if (function_table[2][N + 3] != 0) first_phase_table[0][N + 3] = -function_table[2][N + 3];


	int A1 = 0, A2 = 0;
	A1 = first_phase_table[0][N + 2];
	A2 = first_phase_table[0][N + 3];
	int det = 1;									//determines the points the first phase
	Simplex_method(first_phase_table, det, A1, A2, solution);
	det = 2;									//determines the points in the second phase
	Simplex_method_2nd_phase(first_phase_table, function_table, det, A1, A2, solution);

	for (int i = 1; i < N+1; i++)
	{
		int indicator = 0;
		for (int j = 0; j < N; j++)
		{
			if (solution[j][0] == 'x'&& solution[j][1] == i + 48) indicator++;
		}
		if(indicator == 0) cout << "x" << i << " = 0" << endl;
	}
	

}

void F2(float function_table[3][N + 5])
{
	function_table[0][0] = -12;
	function_table[0][1] = -20;

	function_table[1][0] = 6;
	function_table[1][1] = 8;
	function_table[1][2] = -1;
	function_table[1][4] = 1;
	function_table[1][6] = 100;

	function_table[2][0] = 7;
	function_table[2][1] = 12;
	function_table[2][3] = -1;
	function_table[2][5] = 1;
	function_table[2][6] = 120;

}

void F1(float function_table[3][N + 5])
{
	function_table[0][0] = 3;
	function_table[0][1] = 1;

	function_table[1][0] = 3;
	function_table[1][1] = 4;
	function_table[1][4] = 1;
	function_table[1][2] = 1;
	function_table[1][6] = 24;

	function_table[2][0] = 1;
	function_table[2][1] = -1;
	function_table[2][3] = -1;
	function_table[2][5] = 1;
	function_table[2][6] = 1;


}

void F3(float function_table[3][N + 5])			//function from the labolatories, defined as initial matrix. It searches for points for which function -5x1 - 6x2 ha smaximal value
{
	function_table[0][0] = -5;
	function_table[0][1] = -6;

	function_table[1][0] = 1;
	function_table[1][1] = 1;
	function_table[1][2] = 1;
	function_table[1][6] = 16;

	function_table[2][0] = 1;
	function_table[2][1] = -1;
	function_table[2][3] = -1;
	function_table[2][5] = 1;
	function_table[2][6] = 3;

}

void F4(float function_table[3][N + 5])
{
	function_table[0][0] = 1;
	function_table[0][1] = 1;

	function_table[1][0] = 2;
	function_table[1][1] = 3;
	function_table[1][2] = 1;
	function_table[1][6] = 12;

	function_table[2][0] = 2;
	function_table[2][1] = 1;
	function_table[2][2] = 1;
	function_table[2][6] = 8;

}

void F5_3_variables(float function_table[3][N + 5])		//3 dimensional function
{
	function_table[0][0] = -23;
	function_table[0][1] = -6;
	function_table[0][2] = 12;

	function_table[1][0] = -1;
	function_table[1][1] = 1;
	function_table[1][2] = 3;
	function_table[1][3] = 1;
	function_table[1][7] = 24;

	function_table[2][0] = 3;
	function_table[2][1] = -1;
	function_table[2][2] = -2;
	function_table[2][4] = -1;
	function_table[2][6] = 1;
	function_table[2][7] = 12;

}


int main()
{
	float function_table[3][N + 5];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++) function_table[i][j] = 0;
	}



	F3(function_table);		// in order to change the function, the name has to be changed to f.e F1 instead of F3

	cout << "\n\n";
	Two_phase_simplex_method(function_table);
	return 0;
}

