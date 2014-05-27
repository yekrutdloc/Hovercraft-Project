// Front variables
int fr_ADCwithMiddle[17];
int fr_sorted_ADCwithMiddle[17];
int fr_OneZeroValues[17];
int fr_OneArray[17];
double fr_LinePosition;
double frRM_PIDInput;
double frLM_PIDInput;
double* pfrRM_PIDInput = &frRM_PIDInput;
double* pfrLM_PIDInput = &frLM_PIDInput;

// Rear variables
int re_ADCwithMiddle[17];
int re_sorted_ADCwithMiddle[17];
int re_OneZeroValues[17];
int re_OneArray[17];
double re_LinePosition;
double reRM_PIDInput;
double reLM_PIDInput;
double* preRM_PIDInput = &reRM_PIDInput;
double* preLM_PIDInput = &reLM_PIDInput;

void fr_filterLoop(){
	int middle_value = (frLS_RAW[7] + frLS_RAW[8]) / 2;

	for (int j = 0; j < 8; j++) {
		fr_ADCwithMiddle[j] = frLS_RAW[j];
	}

	fr_ADCwithMiddle[8] = middle_value;

	for (int j = 9; j < 17; j++) {
		fr_ADCwithMiddle[j] = frLS_RAW[j - 1];
	}

	for (int i = 0; i < 17; i++){
		fr_sorted_ADCwithMiddle[i] = fr_ADCwithMiddle[i];
	}

	fr_quick_sort(fr_sorted_ADCwithMiddle, 0, 16);

	int lowest_three, highest_three = 0;

	for (int i = 0; i < 2; i++){
		lowest_three = lowest_three + fr_sorted_ADCwithMiddle[i];
	}

	lowest_three = lowest_three / 3;

	for (int i = 14; i < 17; i++){
		highest_three = highest_three + fr_sorted_ADCwithMiddle[i];
	}

	highest_three = highest_three / 3;

	int line_exist = 0;
	double spridning;

	spridning = (double)(highest_three - lowest_three) / highest_three;

	//Serial.print("Spridning: ");
	//Serial.println(spridning);

	if (spridning > 0.31){
		line_exist = 1;
	}
	else{
		line_exist = 0;
	}

	//Serial.print("Line Exist: ");
	//Serial.println(line_exist);

	if (line_exist){

		for (int i = 0; i < 17; i++){
			if (fr_ADCwithMiddle[i] < (fr_sorted_ADCwithMiddle[16] * 0.69)){
				fr_OneZeroValues[i] = 1;
			}

			else{
				fr_OneZeroValues[i] = 0;
			}
		}

	}

	else{

		for (int i = 0; i < 17; i++){

			fr_OneZeroValues[i] = 0;

		}

	}

	vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);

	int counter = 0;

	for (int i = 0; i < 17; i++){
		if (fr_OneZeroValues[i] == 1){
			fr_OneArray[counter] = i;
			counter++;
		}
	}

	int temp = 0;

	for (int i = 0; i < counter; i++){
		temp = temp + fr_OneArray[i];
	}

	int min_index = temp / counter;

	int last_turn;

	if (min_index < 3){
		last_turn = 0;
	}
	else if (min_index > 13){
		last_turn = 1;
	}

	if (counter == 0){
		//if (!last_turn){
		//	min_index = 3;
		//}
		//else if(last_turn){
		//	min_index = 13;
		//}

		min_index = 8;
	}



	//Serial.println(min_index);

	if (min_index > 9){
		frRM_PIDInput = min_index;
		frLM_PIDInput = 8;
	}
	if (min_index < 9){
		frRM_PIDInput = 8;
		frLM_PIDInput = -1 * (min_index - 16);
	}

	/*	Serial.print("Right - ");
	Serial.print(frRM_PIDInput);
	Serial.print(" - Left");
	Serial.println(frLM_PIDInput);*/
}


void fr_quick_sort(int fr_sorted_ADCwithMiddle[17], int low, int high)
{
	int pivot, j, temp, i;
	if (low < high)
	{
		pivot = low;
		i = low;
		j = high;

		while (i < j)
		{
			while ((fr_sorted_ADCwithMiddle[i] <= fr_sorted_ADCwithMiddle[pivot]) && (i < high))
			{
				i++;
			}

			while (fr_sorted_ADCwithMiddle[j] > fr_sorted_ADCwithMiddle[pivot])
			{
				j--;
			}

			if (i < j)
			{
				temp = fr_sorted_ADCwithMiddle[i];
				fr_sorted_ADCwithMiddle[i] = fr_sorted_ADCwithMiddle[j];
				fr_sorted_ADCwithMiddle[j] = temp;
			}
		}

		temp = fr_sorted_ADCwithMiddle[pivot];
		fr_sorted_ADCwithMiddle[pivot] = fr_sorted_ADCwithMiddle[j];
		fr_sorted_ADCwithMiddle[j] = temp;
		fr_quick_sort(fr_sorted_ADCwithMiddle, low, j - 1);
		fr_quick_sort(fr_sorted_ADCwithMiddle, j + 1, high);
	}
}


void re_filterLoop(){
	int middle_value = (reLS_RAW[7] + reLS_RAW[8]) / 2;

	for (int j = 0; j < 8; j++) {
		re_ADCwithMiddle[j] = reLS_RAW[j];
	}

	re_ADCwithMiddle[8] = middle_value;

	for (int j = 9; j < 17; j++) {
		re_ADCwithMiddle[j] = reLS_RAW[j - 1];
	}

	//for (int i = 0; i < 17; i++)
	//{
	//	Serial.print(re_ADCwithMiddle[i]);
	//	Serial.print(" - ");
	//}
	//Serial.println(" ");

	for (int i = 0; i < 17; i++){
		re_sorted_ADCwithMiddle[i] = re_ADCwithMiddle[i];
	}

	re_quick_sort(re_sorted_ADCwithMiddle, 0, 16);

	int lowest_three, highest_three = 0;

	for (int i = 0; i < 2; i++){
		lowest_three = lowest_three + re_sorted_ADCwithMiddle[i];
	}

	lowest_three = lowest_three / 3;

	for (int i = 14; i < 17; i++){
		highest_three = highest_three + re_sorted_ADCwithMiddle[i];
	}

	highest_three = highest_three / 3;

	int line_exist = 0;
	double spridning;

	spridning = (double)(highest_three - lowest_three) / highest_three;

	//Serial.print("Spridning: ");
	//Serial.println(spridning);

	if (spridning > 0.40){
		line_exist = 1;
	}
	else{
		line_exist = 0;
	}

	//Serial.print("Line Exist: ");
	//Serial.println(line_exist);

	if (line_exist){

		for (int i = 0; i < 17; i++){
			if (re_ADCwithMiddle[i] < (re_sorted_ADCwithMiddle[16] * 0.55)){
				re_OneZeroValues[i] = 1;
			}

			else{
				re_OneZeroValues[i] = 0;
			}
		}

	}

	else{

		for (int i = 0; i < 17; i++){

			re_OneZeroValues[i] = 0;

		}

	}

	//for (int i = 0; i < 16; i++)
	//{
	//	Serial.print(re_OneZeroValues[i]);
	//	Serial.print(" - ");
	//}
	//Serial.println(" ");

	vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);

	int counter = 0;

	for (int i = 0; i < 17; i++){
		if (re_OneZeroValues[i] == 1){
			re_OneArray[counter] = i;
			counter++;
		}
	}

	int temp = 0;

	for (int i = 0; i < counter; i++){
		temp = temp + re_OneArray[i];
	}

	int min_index = temp / counter;


	int last_turn;

	if (min_index < 2){
		last_turn = 0;
	}
	else if (min_index > 13){
		last_turn = 1;
	}

	if (counter == 0){

		//if (last_turn){
		//	min_index = 13;
		//}
		//else if(!last_turn){
		//	min_index = 3;
		//}

		min_index = 8;
	}



	//Serial.println(min_index);

	if (min_index > 9){
		reRM_PIDInput = min_index;
		reLM_PIDInput = 8;
	}
	if (min_index < 9){
		reRM_PIDInput = 8;
		reLM_PIDInput = -1 * (min_index - 16);
	}

	/*		Serial.print("Right - ");
	Serial.print(reRM_PIDInput);
	Serial.print(" - Left");
	Serial.println(reLM_PIDInput);*/

}


void re_quick_sort(int re_sorted_ADCwithMiddle[17], int low, int high)
{
	int pivot, j, temp, i;
	if (low < high)
	{
		pivot = low;
		i = low;
		j = high;

		while (i < j)
		{
			while ((re_sorted_ADCwithMiddle[i] <= re_sorted_ADCwithMiddle[pivot]) && (i < high))
			{
				i++;
			}

			while (re_sorted_ADCwithMiddle[j] > re_sorted_ADCwithMiddle[pivot])
			{
				j--;
			}

			if (i < j)
			{
				temp = re_sorted_ADCwithMiddle[i];
				re_sorted_ADCwithMiddle[i] = re_sorted_ADCwithMiddle[j];
				re_sorted_ADCwithMiddle[j] = temp;
			}
		}

		temp = re_sorted_ADCwithMiddle[pivot];
		re_sorted_ADCwithMiddle[pivot] = re_sorted_ADCwithMiddle[j];
		re_sorted_ADCwithMiddle[j] = temp;
		re_quick_sort(re_sorted_ADCwithMiddle, low, j - 1);
		re_quick_sort(re_sorted_ADCwithMiddle, j + 1, high);
	}
}