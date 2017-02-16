#include <stdio.h>
#include <stdlib.h>

//Preprocessor constant definitions
#define NUMBER_OF_DATAPOINTS 1440
#define INPUT_BUFFER 64
#define INPUT_DATA_FILE "../sortedData.dat"

//Function prototypes...
void loadFileData(float arrayToStoreData[], size_t arraySize);
void categorizeData(float sourceDataArray[], int sourceArraySize, int frequencyDistributionArray[5]);
void displayDataToUser(int frequencyDistributionDataArray[5], float sourceDataArray[], size_t sourceArraySize);

int main() {

    float windSpeedData[NUMBER_OF_DATAPOINTS];    //An array of floats for my windSpeedData
    int frequencyDistribution[5] = {0}; //Declare an array to hold frequency counters and initialise all values to 0

    //Populate my array with data from a file...
    loadFileData(windSpeedData, NUMBER_OF_DATAPOINTS);

    //Categorise my data into 5 equal buckets...
    categorizeData(windSpeedData, NUMBER_OF_DATAPOINTS, frequencyDistribution);

    //Output the data in an informative way...
    displayDataToUser(frequencyDistribution, windSpeedData, NUMBER_OF_DATAPOINTS);

    return 0;
}

/**
 * Function loadFileData
 * This function is tasked with reading in the content of a datafile containing wind speeds.
 * The data is in the format... '3.9758' and each line is a separate record.
 *
 * @param arrayToStoreData - A memory reference to the data array to be populated.
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

            //Read in the next line in the file...
            fscanf(inputPtr, "%s", buffer);

        }   //Back to the while condition

        fclose(inputPtr); //When finished, Close the file.

    }//End if/else

}//End function loadFileData

/**
 * Function categorizeData
 * This function counts the frequency of the data points, split into 5 groups, relating to the max recorded value.
 *
 * @param sourceDataArray - The data array being analysed
 * @param sourceArraySize - The size of the data array
 * @param frequencyDistributionArray - An array with 5 buckets, containing frequency counters
 */
void categorizeData(float sourceDataArray[],
                    int sourceArraySize,
                    int frequencyDistributionArray[]) {


    //If my data was not already sorted by the previous exercise, then I'd have to iterate through
    //the list to identify the min and max values. But since it is already sorted, then...
    //float min = sourceDataArray[0];   //The min value is the first item in my sorted list.
    float max = sourceDataArray[sourceArraySize - 1]; //The max value is the last value. 1440 data items, numbered 0 -> 1439.

    //**** NOTE **** - If my data wasn't sorted, comment-out the line above and un-comment the line below...
    //float max = 0.0;  //A variable to hold the max value identified when iterating through the array.

    for(size_t index = 0; index < sourceArraySize; index++){
        //**** NOTE **** - If my data wasn't sorted, un-comment the line below...
        //if(sourceDataArray[index] > max) max = sourceDataArray[index];    //If the value is greater than 'max', update 'max'.

        if (sourceDataArray[index] > max * 0.8){        //If the value is within 80% of the 'max' value...
            frequencyDistributionArray[4]++;
        }else if(sourceDataArray[index] > max * 0.6){   //If the value is within 60% and 80% of the 'max' value...
            frequencyDistributionArray[3]++;
        }else if(sourceDataArray[index] > max * 0.4){   //If the value is within 40% and 60% of the 'max' value...
            frequencyDistributionArray[2]++;
        }else if(sourceDataArray[index] > max * 0.2){   //If the value is within 20% and 40% of the 'max' value...
            frequencyDistributionArray[1]++;
        }else{                                          //If the value is less than 20% of the 'max' value...
            frequencyDistributionArray[0]++;
        }//End if/else
    }//End of for

}//End function categorizeData

/**
 * Function displayDataToUser
 * This function takes in an array of frequency distribution data and presents the data in an informative format
 *
 * @param frequencyDistributionDataArray - The frequency data to be displayed
 * @param sourceDataArray - A reference to the original source data
 * @param arrayDataSize - The source data array size
 */
void displayDataToUser(int frequencyDistributionDataArray[5], float sourceDataArray[], size_t arrayDataSize) {

    //If my data was not already sorted by the previous exercise, then I'd have to iterate through
    //the list to identify the min and max values. But since it is already sorted, then...
    float min = sourceDataArray[0];   //The min value is the first item in my sorted list.
    float max = sourceDataArray[arrayDataSize - 1]; //The max value is the last value. 1440 data items, numbered 0 -> 1439.

    int sampleCount = 0;    //Should be 1440 for this exercise, But could be different if this function was processing other arrays.

    //Output data to the user...
    puts("\nHistogram showing Distribution of wind speeds on 22nd September 2013\n");
    //puts("           each '*' represents up to 10 measurements\n\n");
    printf("Minimum recorded wind speed was: %6.3f m/s.\n", min);
    printf("Maximum recorded wind speed was: %6.3f m/s.\n\n", max);
    printf("%9s%12s\n", "% of MAX", "Frequency");
    for (int index = 0; index < 5; index++){    //Iterate through my frequency distribution data
        sampleCount+=frequencyDistributionDataArray[index]; //Add the frequency count to the sampleCounter

        //Bar label. Displays range details and frequency being represented...
        printf("%2d  -> %3d%8d   |", 100 - (20 * (index + 1)), 100 - (20 * index), frequencyDistributionDataArray[index]);

        //Generate Histogram bar...
        for (int count = 1; count < frequencyDistributionDataArray[index]; count+=10) {
            printf("%s", "*");	//Print an '*' for every 10 samples recorded.
        }//End of for

        puts("");   //At the end of the Histogram bar, move to the next line
    } //Move to the next frequency counter and repeat to generate the next bar

    //Print some legend and reading aids
    printf("%11s%7d", "Total: ", sampleCount);
    printf("%4s%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d\n",  "", 5, 1, 1, 2, 2, 3, 3, 4, 4, 5);
    printf("%22s%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d\n", "", 0, 0, 5, 0, 5, 0, 5, 0, 5, 0);
    printf("%27s%5d%5d%5d%5d%5d%5d%5d%5d%5d\n",    "",    0, 0, 0, 0, 0, 0, 0, 0, 0);
    printf("%76s", "Frequency - each '*' represents up to 10 measurements\n\n");

}//End of function displayDataToUser
