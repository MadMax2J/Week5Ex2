#include <stdio.h>
#include <stdlib.h>

//Preprocessor constant definitions
#define NUMBER_OF_DATAPOINTS 1440
#define INPUT_BUFFER 64
#define INPUT_DATA_FILE "../sortedData.dat"

void loadFileData(float arrayToStoreData[], size_t arraySize);
void categorizeData(float sourceDataArray[], int sourceArraySize, int frequencyDistributionArray[5]);
void displayDataToUser(int frequencyDistributionDataArray[5], float sourceDataArray[], size_t sourceArraySize);

int main() {

    float windSpeedData[NUMBER_OF_DATAPOINTS];    //An array of floats for my windSpeedData
    int frequencyDistribution[5] = {0}; //Declare an array to hold frequency counters and initialise all values to 0


    loadFileData(windSpeedData, NUMBER_OF_DATAPOINTS);  //Populate my array with data from a file

    categorizeData(windSpeedData, NUMBER_OF_DATAPOINTS, frequencyDistribution); //Categorise my data into 5 equal buckets.

    displayDataToUser(frequencyDistribution, windSpeedData, NUMBER_OF_DATAPOINTS);

    return 0;
}

void displayDataToUser(int frequencyDistributionDataArray[5], float sourceDataArray[], size_t arrayDataSize) {

    //If my data was not already sorted by the previous exercise, then I'd have to iterate through
    //the list to identify the min and max values. But since it is already sorted, then...
    float min = sourceDataArray[0];   //The min value is the first item in my sorted list.
    float max = sourceDataArray[arrayDataSize - 1]; //The max value is the last value. 1440 data items, numbered 0 -> 1439.

    int sampleCount = 0;    //Should be 1440 for this exercise, But could be different if this function was processing other arrays.

    ////TESTING
    //printf("The minimum wind speed was %.3f m/s\n The maximum MAX data was %f.\n", min, max);


    puts("\nHistogram showing Distribution of wind speeds on 22nd September 2013");
    puts("           each '*' represents up to 10 measurements\n\n");
    printf("Minimum recorded wind speed was: %6.3f m/s.\n", min);
    printf("Maximum recorded wind speed was: %6.3f m/s.\n\n", max);
    printf("%9s%12s\n", "% of MAX", "Frequency");
    for (int x = 0; x < 5; x++){
        sampleCount+=frequencyDistributionDataArray[x];
        printf("%2d  -> %3d%8d   |", 100 - (20 * (x + 1)), 100 - (20 * x), frequencyDistributionDataArray[x]);		//Bar label. Contains the number being represented.
        for (int count = 1; count < frequencyDistributionDataArray[x]; count+=10) {	//Repeat num(x) times...
            printf("%s", "*");							//Print an '*'
        }//End of for
        puts("");
    }


    printf("%11s%7d", "Total: ", sampleCount);
    printf("%4s%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d\n",  "", 5, 1, 1, 2, 2, 3, 3, 4, 4, 5);
    printf("%22s%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d\n", "", 0, 0, 5, 0, 5, 0, 5, 0, 5, 0);
    printf("%27s%5d%5d%5d%5d%5d%5d%5d%5d%5d\n",    "",    0, 0, 0, 0, 0, 0, 0, 0, 0);

}

void categorizeData(float sourceDataArray[],
                    int sourceArraySize,
                    int frequencyDistributionArray[]) {


    //If my data was not already sorted by the previous exercise, then I'd have to iterate through
    //the list to identify the min and max values. But since it is already sorted, then...
    //float min = sourceDataArray[0];   //The min value is the first item in my sorted list.
    float max = sourceDataArray[sourceArraySize - 1]; //The max value is the last value. 1440 data items, numbered 0 -> 1439.
    //float max = 0.0;

    ////TESTING
//    printf("The minimum wind speed was %.3f m/s\n The maximum MAX data was %f.\n", min, max);



    for(size_t index = 0; index < sourceArraySize; index++){
        //if(sourceDataArray[index] > max) max = sourceDataArray[index];
        if (sourceDataArray[index] > max * 0.8){
            frequencyDistributionArray[4]++;
        }else if(sourceDataArray[index] > max * 0.6){
            frequencyDistributionArray[3]++;
        }else if(sourceDataArray[index] > max * 0.4){
            frequencyDistributionArray[2]++;
        }else if(sourceDataArray[index] > max * 0.2){
            frequencyDistributionArray[1]++;
        }else{
            frequencyDistributionArray[0]++;
        }
    }


}

/**
 * Function loadFileData
 * This function is tasked with reading in the content of a datafile containing wind speeds in a comma separated format.
 * The data is in the format... 9/22/2013,00:01,3.9758
 *
 * @param windSpeeds - A memory reference to the data array to be populated.
 * @param arraySize - The size of the array to control bounds
 */
void loadFileData(float arrayToStoreData[], size_t arraySize) {

    FILE *inputPtr;     //A pointer to an input file

    //Try open the file...
    if ((inputPtr = fopen(INPUT_DATA_FILE, "r")) == NULL) { //Opening Failed?
        puts("FATAL ERROR! - The file could not be opened!");
        exit(1);    //Quit the program

    } else {    //Opening Success!
        size_t index = 0;                   //A counter to iterate through the array.
        char buffer[INPUT_BUFFER] = "";     //A buffer to accept a line read in from the input file.

        fscanf(inputPtr, "%s", buffer);     //Read in the first line of the file
        while (!feof(inputPtr) && index < arraySize) {  //Once there is data and we have'nt exceeded our array bounds...

            //Strings are in the following format... "3.9758"
            arrayToStoreData[index++] = strtof(buffer, NULL);
            //arrayToStoreData[index++] = strtof((strtok(NULL, " ,")), NULL);   //Store the 3rd token, as a float, into the array.

            ////TESTING
            //printf("Data %d is: %f\n", index - 1, arrayToStoreData[index-1]);

            fscanf(inputPtr, "%s", buffer);    //Read in the next line in the file

        }   //Back to the while condition

        //If the inputPtr contains the EOF character, the while loop finishes and we add the last piece of data...
        //strtok(buffer, " ,");   //Dump first token, ie. '9/22/2013'
        //strtok(NULL, " ,");    //Dump next token, ie. '00:01'
        //arrayToStoreData[index] = strtof(buffer, NULL);     //Store the 3rd token, as a float, into the array.

        ////TESTING
        //printf("Data %d is: %f\n", index, arrayToStoreData[index]);

        fclose(inputPtr); //When finished, Close the file.
    }//End if/else

}//End function loadFileData
