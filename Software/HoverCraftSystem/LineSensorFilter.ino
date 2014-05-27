// Front variables
// USING
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

void fr_setup_Calibration(){

	fr_calWhite = 2499;

	fr_weights[15] = 0.766;
	fr_weights[14] = 0.982;
	fr_weights[13] = 0.918;
	fr_weights[12] = 1.047;
	fr_weights[11] = 1.026;
	fr_weights[10] = 0.985;
	fr_weights[9] = 1.054;
	fr_weights[8] = 0.796;
	fr_weights[7] = 1.130;
	fr_weights[6] = 0.857;
	fr_weights[5] = 1.218;
	fr_weights[4] = 1.427;
	fr_weights[3] = 0.988;
	fr_weights[2] = 0.962;
	fr_weights[1] = 1.03;
	fr_weights[0] = 1.186;



	for (int i = 0; i < 16; i++){
		fr_weighted_RAW[i] =(double)(frLS_RAW[i] * fr_weights[i]);

	}
	

}

void re_setup_Calibration(){

	re_calWhite = 2657;

	re_weights[0] = 0.80;
	re_weights[1] = 0.96;
	re_weights[2] = 0.84;
	re_weights[3] = 1.35;
	re_weights[4] = 1.13;
	re_weights[5] = 0.93;
	re_weights[6] = 1.17;
	re_weights[7] = 1.30;
	re_weights[8] = 0.79;
	re_weights[9] = 1.29;
	re_weights[10] = 0.99;
	re_weights[11] = 0.89;
	re_weights[12] = 0.95;
	re_weights[13] = 0.99;
	re_weights[14] = 1.06;
	re_weights[15] = 0.9;


	for (int i = 0; i < 16; i++){
		re_weighted_RAW[i] = (double)(reLS_RAW[i] * re_weights[i]);

	}
}

void fr_filterLoop(){


	fr_setup_Calibration();


	for (int i = 0; i < 16; i++){
		fr_sorted_RAW[i] = fr_weighted_RAW[i];
	}

	fr_quick_sort(fr_sorted_RAW, 0, 15);


	//for (int i = 0; i < 16; i++)
	//{
	//	Serial.print(fr_sorted_RAW[i]);
	//	Serial.print(" - ");
	//}
	//Serial.println(" ");

	int fr_lowest_two = 0, fr_highest_two = 0;

	fr_lowest_two = (fr_sorted_RAW[0] + fr_sorted_RAW[1]) / 2;

	fr_highest_two = (fr_sorted_RAW[14] + fr_sorted_RAW[15]) / 2;

	int fr_line_exist = 0;
	double fr_spridning;

	fr_spridning = (double)(fr_highest_two - fr_lowest_two) / fr_highest_two;

	if (fr_spridning > fr_black_val){
		fr_line_exist = 1;
	}
	else{
		fr_line_exist = 0;
	}

	//Serial.print("FRONT:  Spridning: ");
	//Serial.print(fr_spridning);
	//Serial.print("   Line Exist: ");
	//Serial.print(fr_line_exist);
	//Serial.println(); 

	//for (int i = 0; i < 16; i++)
	//{
	//	Serial.print(fr_weighted_RAW[i]);
	//	Serial.print(" - ");
	//}
	//Serial.println(" ");
	//Serial.println(fr_lowest_two);
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

	//for (int i = 0; i < 16; i++)
	//{
	//	Serial.print(fr_OneZeroValues[i]);
	//	Serial.print(" - ");
	//}
	//Serial.println(" ");

	vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);

	int counter = 0;

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


	if (counter){
		min_index = (temp / counter) + 1;
	}
	else{
		min_index = 0;
	}
	
	if (min_index && counter){
		if (min_index > 10 && !min_index){

			panic_mode = 1;
		}

		else if (min_index < 3 && !min_index){
			panic_mode = 0;
		}
	}
	

	//Serial.println("PANIC MODE:");
	//Serial.println(panic_mode);
	//Serial.println();
	//Serial.println("MIN INDEX:");
	//Serial.println(min_index);
	//Serial.println();

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


	/*else if (!fr_line_exist){
		
		if (panic_mode){
			frRM_PIDInput = 0;
			frLM_PIDInput = 8;
		}
		else if (!panic_mode){
			frRM_PIDInput = 8;
			frLM_PIDInput = 0;
		}

	}*/

}


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


void re_filterLoop(){

	re_setup_Calibration();

	for (int i = 0; i < 16; i++){
		re_sorted_RAW[i] = re_weighted_RAW[i];
	}



	re_quick_sort(re_sorted_RAW, 0, 15);

	int re_lowest_two = 0, re_highest_two = 0;

	re_lowest_two = (re_sorted_RAW[0] + re_sorted_RAW[1]) / 2;

	re_highest_two = (re_sorted_RAW[14] + re_sorted_RAW[15]) / 2;

	int re_line_exist = 0;
	double re_spridning;

	re_spridning = (double)(re_highest_two - re_lowest_two) / re_highest_two;

	if (re_spridning > re_black_val){
		re_line_exist = 1;
	}
	else{
		re_line_exist = 0;
	}

	//Serial.print("REAR:  Spridning: ");
	//Serial.print(re_spridning);
	//Serial.print("   Line Exist: ");
	//Serial.print(re_line_exist);
	//Serial.println();

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

	if (min_index < 3){
		re_panic_left = 1;
		re_panic_right = 0;
	}
	else if (min_index > 14){
		re_panic_left = 0;
		re_panic_right = 1;
	}

	if (counter == 0){

		if (re_panic_right){
			min_index = 1;
		}

		if (re_panic_left){
			min_index = 16;
		}
	}

	//Serial.println(min_index);
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
	

	/*	Serial.print("Right - ");
	Serial.print(reRM_PIDInput);
	Serial.print(" - Left");
	Serial.println(reLM_PIDInput);*/


}


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