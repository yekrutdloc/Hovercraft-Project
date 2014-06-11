/**
LineSensorFilter.ino

Purpose: Code to filter recieved data from LineSensorRead through
		 individual calibration values extracted from calculations in MatLab.
		 Normalisation algorithms are used with help from a quicksort
		algorith. 
		 Might contain uninplemented codesnippets and declerations. 

@author Hisham Ramish
@author Hamit Sen
@author Haisam El-Hajj Moussa
*/

int fr_sorted_RAW[16], re_sorted_RAW[16];

double fr_black_val = 0.10, re_black_val = 0.15;

double fr_weights_RAW[16], re_weights_RAW[16];
double fr_weighted_RAW[16], re_weighted_RAW[16];

double fr_calWhite, re_calWhite;

int panic_mode = 0;

double min_index;

double fr_weights[16], re_weights[16];

int fr_OneZeroValues[16];
int re_OneZeroValues[16];

int fr_OneArray[16];
int re_OneArray[16];

double frRM_PIDInput;
double frLM_PIDInput;
double* pfrRM_PIDInput = &frRM_PIDInput;
double* pfrLM_PIDInput = &frLM_PIDInput;

double reRM_PIDInput;
double reLM_PIDInput;
double* preRM_PIDInput = &reRM_PIDInput;
double* preLM_PIDInput = &reLM_PIDInput;


/**
Function to cycle through RAW-values from ADC for front sensor 
with predetermined and calculated gain-values
*/
void fr_setup_Calibration(){

//Averaged target value for front sensor 
	fr_calWhite = 2502;

//Calculated individual Gain-values from MatLab for front sensor
	fr_weights[15] = 1.3301;
	fr_weights[14] = 0.9669;
	fr_weights[13] = 1.0812;
	fr_weights[12] = 0.9353;
	fr_weights[11] = 0.9389;
	fr_weights[10] = 0.9469;
	fr_weights[9] = 0.9493;
	fr_weights[8] = 1.1651;
	fr_weights[7] = 0.8582;
	fr_weights[6] = 1.1052;
	fr_weights[5] = 0.8167;
	fr_weights[4] = 0.7627;
	fr_weights[3] = 0.9469;
	fr_weights[2] = 0.9805;
	fr_weights[1] = 1.0005;
	fr_weights[0] = 0.8;

	for (int i = 0; i < 16; i++){
		fr_weighted_RAW[i] = (double)(frLS_RAW[i] / fr_weights[i]);
	}
}

/**
Function to cycle through RAW-values from ADC for rear sensor
with predetermined and calculated gain-values
*/
void re_setup_Calibration(){

//Averaged target value for rear sensor 
	re_calWhite = 2108;

//Calculated individual Gain-values from MatLab for rear sensor
	re_weights[0] = 1.2273;
	re_weights[1] = 1.0557;
	re_weights[2] = 1.2250;
	re_weights[3] = 0.7280;
	re_weights[4] = 0.8830;
	re_weights[5] = 1.0732;
	re_weights[6] = 0.8849;
	re_weights[7] = 0.7673;
	re_weights[8] = 1.2131;
	re_weights[9] = 0.7834;
	re_weights[10] = 0.9969;
	re_weights[11] = 1.0983;
	re_weights[12] = 1.0367;
	re_weights[13] = 1.0225;
	re_weights[14] = 0.9471;
	re_weights[15] = 1.0576;

	for (int i = 0; i < 16; i++){
		re_weighted_RAW[i] = (double)(reLS_RAW[i] / re_weights[i]);
	}
}

/**
Function with the purpose of a software extrapolation of a black line on a white background
Uses 
*/
void fr_filterLoop(){

	fr_setup_Calibration();

	// Create new array for sorting
	for (int i = 0; i < 16; i++){
		fr_sorted_RAW[i] = fr_weighted_RAW[i];
	}

	fr_quick_sort(fr_sorted_RAW, 0, 15);

	int fr_lowest_two = 0, fr_highest_two = 0;

	// Average value of the lowest and highest two values
	fr_lowest_two = (fr_sorted_RAW[0] + fr_sorted_RAW[1]) / 2;
	fr_highest_two = (fr_sorted_RAW[14] + fr_sorted_RAW[15]) / 2;

	int fr_line_exist = 0;
	double fr_spridning;

	// Calculating deviation between the averages of the 
	// highest two values and the lowest two values
	fr_spridning = (double)(fr_highest_two - fr_lowest_two) / fr_highest_two;

	if (fr_spridning > fr_black_val){
		fr_line_exist = 1;
	}
	else{
		fr_line_exist = 0;
	}

	// Loops to fill array with 1s and 0s depending on where the black line is
	if (fr_line_exist){

		for (int i = 0; i < 16; i++){
			if (fr_weighted_RAW[i] < fr_lowest_two){
				fr_OneZeroValues[i] = 1;
			}

			else{
				fr_OneZeroValues[i] = 0;
			}
		}

	}

	else{

		for (int i = 0; i < 16; i++){
			fr_OneZeroValues[i] = 0;
		}

	}

	vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);

	int counter = 0;

	// Checks how many and where the 1s are
	for (int i = 0; i < 16; i++){
		if (fr_OneZeroValues[i] == 1){
			fr_OneArray[counter] = i;
			counter++;
		}
	}

	int temp = 0;

	for (int i = 0; i < counter; i++){
		temp = temp + fr_OneArray[i];
	}

	// Sets min_index to where the averaged black line is
	if (counter){
		min_index = (temp / counter) + 1;
	}
	else{
		min_index = 0;
	}

	// Unimplemented panic mode codesnippet
	if (min_index && counter){
		if (min_index > 10 && !min_index){

			panic_mode = 1;
		}

		else if (min_index < 3 && !min_index){
			panic_mode = 0;
		}
	}

	// Sets global pointers for PID/Motorcontrol depending on what motor should run
	if (fr_line_exist){

		if (min_index < 9){
			frRM_PIDInput = min_index;
			frLM_PIDInput = 8;
		}
		if (min_index > 8){
			frRM_PIDInput = 8;
			frLM_PIDInput = -1 * (min_index - 17);
		}

	}

}

/**
 Simple quicksort algorithm function from first year studies in ComputerScience
*/
void fr_quick_sort(int fr_sorted_RAW[16], int low, int high)
{
	int pivot, j, temp, i;
	if (low < high)
	{
		pivot = low;
		i = low;
		j = high;

		while (i < j)
		{
			while ((fr_sorted_RAW[i] <= fr_sorted_RAW[pivot]) && (i < high))
			{
				i++;
			}

			while (fr_sorted_RAW[j] > fr_sorted_RAW[pivot])
			{
				j--;
			}

			if (i < j)
			{
				temp = fr_sorted_RAW[i];
				fr_sorted_RAW[i] = fr_sorted_RAW[j];
				fr_sorted_RAW[j] = temp;
			}
		}

		temp = fr_sorted_RAW[pivot];
		fr_sorted_RAW[pivot] = fr_sorted_RAW[j];
		fr_sorted_RAW[j] = temp;
		fr_quick_sort(fr_sorted_RAW, low, j - 1);
		fr_quick_sort(fr_sorted_RAW, j + 1, high);
	}
}

/**
Function with the purpose of a software extrapolation of a black line on a white background
Uses
*/
void re_filterLoop(){

	re_setup_Calibration();

	// Create new array for sorting
	for (int i = 0; i < 16; i++){
		re_sorted_RAW[i] = re_weighted_RAW[i];
	}

	re_quick_sort(re_sorted_RAW, 0, 15);

	int re_lowest_two = 0, re_highest_two = 0;

	// Average value of the lowest and highest two values
	re_lowest_two = (re_sorted_RAW[0] + re_sorted_RAW[1]) / 2;
	re_highest_two = (re_sorted_RAW[14] + re_sorted_RAW[15]) / 2;

	int re_line_exist = 0;
	double re_spridning;

	// Calculating deviation between the averages of the 
	// highest two values and the lowest two values
	re_spridning = (double)(re_highest_two - re_lowest_two) / re_highest_two;

	if (re_spridning > re_black_val){
		re_line_exist = 1;
	}
	else{
		re_line_exist = 0;
	}

	// Loops to fill array with 1s and 0s depending on where the black line is
	if (re_line_exist){

		for (int i = 0; i < 16; i++){
			if (re_weighted_RAW[i] < re_lowest_two){
				re_OneZeroValues[i] = 1;
			}

			else{
				re_OneZeroValues[i] = 0;
			}
		}

	}

	else{

		for (int i = 0; i < 16; i++){
			re_OneZeroValues[i] = 0;
		}

	}

	vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);

	int counter = 0;

	for (int i = 0; i < 16; i++){
		if (re_OneZeroValues[i] == 1){
			re_OneArray[counter] = i;
			counter++;
		}
	}

	int temp = 0;

	for (int i = 0; i < counter; i++){
		temp = temp + re_OneArray[i];
	}

	int min_index = (temp / counter) + 1;

	int re_panic_left, re_panic_right;

	// Sets min_index to where the averaged black line is
	if (counter){
		min_index = (temp / counter) + 1;
	}
	else{
		min_index = 0;
	}

	// Unimplemented panic mode codesnippet
	if (min_index && counter){
		if (min_index > 10 && !min_index){

			panic_mode = 1;
		}

		else if (min_index < 3 && !min_index){
			panic_mode = 0;
		}
	}

	// Sets global pointers for PID/Motorcontrol depending on what motor should run
	if (re_line_exist){

		if (min_index < 9){
			reLM_PIDInput = min_index;
			reRM_PIDInput = 8;
		}
		if (min_index > 8){
			reLM_PIDInput = 9;
			reRM_PIDInput = -1 * (min_index - 17);
		}
	}

}

/**
 Simple quicksort algorithm function from first year studies in ComputerScience
*/
void re_quick_sort(int re_sorted_RAW[16], int low, int high)
{
	int pivot, j, temp, i;
	if (low < high)
	{
		pivot = low;
		i = low;
		j = high;

		while (i < j)
		{
			while ((re_sorted_RAW[i] <= re_sorted_RAW[pivot]) && (i < high))
			{
				i++;
			}

			while (re_sorted_RAW[j] > re_sorted_RAW[pivot])
			{
				j--;
			}

			if (i < j)
			{
				temp = re_sorted_RAW[i];
				re_sorted_RAW[i] = re_sorted_RAW[j];
				re_sorted_RAW[j] = temp;
			}
		}

		temp = re_sorted_RAW[pivot];
		re_sorted_RAW[pivot] = re_sorted_RAW[j];
		re_sorted_RAW[j] = temp;
		re_quick_sort(re_sorted_RAW, low, j - 1);
		re_quick_sort(re_sorted_RAW, j + 1, high);
	}
}