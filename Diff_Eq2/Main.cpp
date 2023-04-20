#include<iostream>
#include <fstream>
#include<cmath>
void Insert_In_File(double* new_array, size_t count, std::fstream& stream)
{
	if (stream.is_open())
	{
		for (size_t i = 0; i < count; i++)
			stream << new_array[i] << " ";
		stream << "\n";
		stream << "\n";
	}
	else
		throw "The file isn't exist";
}


double Get_New_Point_In_Time(double prev_point, double curr_point, double next_point, double deltaT, double deltaX, double sigma)
{
	double tmp = 0.0;
	tmp = prev_point - 2 * curr_point + next_point;

	return((sigma * deltaT) / (deltaX * deltaX) * tmp + curr_point);
}
int main()
{
	double X_max = 0.0;
	double deltaX = 0.0;
	double T_max = 0.0;
	double deltaT = 0.0;
	double sigma = 0.0;
	size_t count = 0;
	double time = 0.0;
	double tmp = 0.0;
	const double PI = 3.141592653589793;
	int i = 1;


	std::fstream f;
	f.open("initial.txt", std::fstream::in | std::fstream::out);

	std::ifstream f_in;
	f_in.open("const_initial.txt");
	if (f_in.is_open())
	{
		f_in >> X_max;
		f_in >> deltaX;
		f_in >> T_max;
		f_in >> deltaT;
		f_in >> sigma;
	}
	else
		throw "file wasn't opened";
	f_in.close();

	if (X_max == 0.0 || deltaX == 0.0)
		throw "count = 0 or count is infinity";

	double* temp_array = nullptr;
	count = static_cast<size_t>((int)(X_max / deltaX)) + 1;
	temp_array = new double[count];

	double* curr_array = nullptr;
	curr_array = new double[count];

	double* tmp_buffer = nullptr;
	tmp_buffer = new double[count];



	for (size_t q = 0; q < count; q++)
		temp_array[q] = sin(PI * deltaX * q);

	temp_array[count - 1] = 0.0;


	Insert_In_File(temp_array, count, f);

	while (time < T_max)
	{
		time = deltaT * i;

		for (size_t q = 1; q < count; q++)
		{
			//curr_array[q] = Get_New_Point_In_Time(temp_array[q - 1], temp_array[q], temp_array[q + 1], deltaT, deltaX, sigma);
			tmp = temp_array[q - 1] - 2 * temp_array[q] + temp_array[q + 1];
			curr_array[q] = ((sigma * deltaT) / (deltaX * deltaX) * tmp + temp_array[q]);
		}

		curr_array[0] = 0.0;
		curr_array[count - 1] = 0.0;

		tmp_buffer = temp_array;
		temp_array = curr_array;
		curr_array = tmp_buffer;

		//if (i % 10000 == 0)
		//	Insert_In_File(main_array, count, f);
		i++;
	}

	Insert_In_File(curr_array, count, f);
	f.close();
	delete[] temp_array;
	return 0;
}