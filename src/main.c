#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE_READ_ERROR -1
#define FILE_WRITE_ERROR -2
#define MAX_CMD_OPT 7
#define CMD_OPT_IN_FILE "-i"
#define CMD_OPT_IN_POS 1
#define CMD_OPT_IN_VAL_POS 2
#define CMD_OPT_OUT_FILE "-o"
#define CMD_OPT_OUT_POS 3
#define CMD_OPT_OUT_VAL_POS 4
#define CMD_OPT_IN_SIZE "-s"
#define CMD_OPT_SIZE_POS 5
#define CMD_OPT_SIZE_VAL_POS 6
#define ARRAYSIZE(x) (sizeof(x) / sizeof((x)[0]))
#define ASC 1
#define DESC 2
int readIntArrayFromFile(const char *inputFilePath, int dataBuffer[], int dataBufferSize);
int writeIntArrayToFile(const char *outputFilePath, int dataBuffer[], int dataBufferSize);
void bubbleSortIntArray(int unsortedArray[], size_t arraySize, int sortOrder);

/* Declare your function(s) below*/

/* End of function(s) declaretion */
int main(int argc, char const *argv[])
{
    if (argc != MAX_CMD_OPT)
    {
        printf("usage: %s -i input_filename -o output_filename -s input_data_size\n", argv[0]);
        exit(1);
    }
    else
    {
        //printf("%s - %s - %s - %s - %s - %s\n",argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
        if ((strcmp(argv[CMD_OPT_IN_POS], "-i") == 0) &&
            (strcmp(argv[CMD_OPT_OUT_POS], "-o") == 0) &&
            ((strcmp(argv[CMD_OPT_SIZE_POS], "-s") == 0)))
        {
            if ((strlen(argv[CMD_OPT_IN_VAL_POS]) > 0) && (strlen(argv[CMD_OPT_OUT_VAL_POS]) > 0))
            {
                const char *inputFilePath = argv[CMD_OPT_IN_VAL_POS];
                const char *outputFilePath = argv[CMD_OPT_OUT_VAL_POS];
                char *p;
                int size = strtol(argv[CMD_OPT_SIZE_VAL_POS], &p, 10);
                if (size > 0)
                {
                    int dataBuffer[size];
                    int readCount = readIntArrayFromFile(inputFilePath, dataBuffer, size);
                    if (readCount <= 0)
                    {
                        printf("File Read Error, ERR_CODE : %d", readCount);
                        exit(1);
                    }
                    /* Put Your Code Below*/
                    bubbleSortIntArray(dataBuffer, ARRAYSIZE(dataBuffer), ASC);
                    for (int i = 0; i < size; i++)
                    {
                        printf("[%d] = %d\n", i, dataBuffer[i]);
                    }
                    /* END */
                    int writeCount = writeIntArrayToFile(outputFilePath, dataBuffer, size);
                    if (writeCount <= 0)
                    {
                        printf("File Write Error, ERR_CODE : %d", writeCount);
                        exit(1);
                    }
                }
                else
                {
                    printf("Data size should be greater then 0.\n");
                    exit(1);
                }
            }
            else
            {
                printf("Input/Output or both filepath missing.\n");
                exit(1);
            }
        }
        else
        {
            printf("usage: %s -i input_filename -o output_filename -s input_data_size\n", argv[0]);
            exit(1);
        }
    }

    return 0;
}
int readIntArrayFromFile(const char *inputFilePath, int dataBuffer[], int dataBufferSize)
{
    FILE *fp;
    int readCount = 0;
    fp = fopen(inputFilePath, "rb");
    if (fp == NULL)
    {
        return FILE_READ_ERROR;
    }
    readCount = fread(dataBuffer, sizeof(int), dataBufferSize, fp);
    fclose(fp);
    return readCount;
}
int writeIntArrayToFile(const char *outputFilePath, int dataBuffer[], int dataBufferSize)
{
    FILE *fp;
    int writeCount = 0;
    fp = fopen(outputFilePath, "wb");
    if (fp == NULL)
    {
        return FILE_WRITE_ERROR;
    }
    writeCount = fwrite(dataBuffer, sizeof(int), dataBufferSize, fp);
    fclose(fp);
    return writeCount;
}
/* Define your own function(s) below*/
void bubbleSortIntArray(int unsortedArray[], size_t arraySize, int sortOrder)
{
    int temp;
    size_t size = arraySize;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            /* code */
            //for ascending sort
            if (sortOrder == ASC)
            {
                if (unsortedArray[i] > unsortedArray[j])
                {
                    //swap
                    temp = unsortedArray[j];
                    unsortedArray[j] = unsortedArray[i];
                    unsortedArray[i] = temp;
                }
            }
            //for desending sort
            else
            {
                if (unsortedArray[j] > unsortedArray[i])
                {
                    //swap
                    temp = unsortedArray[i];
                    unsortedArray[i] = unsortedArray[j];
                    unsortedArray[j] = temp;
                }
            }
        }
    }
}