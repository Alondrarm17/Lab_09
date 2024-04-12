/* Alondra Rodriguez Manzueta
COP 3502C: Lab assignment 9*/

#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 22

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// HashType
struct HashType
{
    struct Node* head;
};

// Node for linked list
struct Node
{
    struct RecordType data;
    struct Node* next;
};

// Compute the hash function
int hash(int x)
{
    return x % HASH_SIZE;
}

// Initializing hash table
void initializeHash(struct HashType hashArray[], int hashSz)
{
    for (int i = 0; i < hashSz; ++i)
    {
        hashArray[i].head = NULL;
    }
}

// Function to insert a record
void insertRecord(struct HashType hashArray[], int hashSz, struct RecordType record)
{
    int index = hash(record.id);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = record;
    newNode->next = hashArray[index].head;
    hashArray[index].head = newNode;
}

// Function to parse input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &(pRecord->id));
            fscanf(inFile, "%c ", &(pRecord->name));
            fscanf(inFile, "%d ", &(pRecord->order));
        }

        fclose(inFile);
    }

    return dataSz;
}

// Function to print the records
void printRecords(struct RecordType pData[], int dataSz)
{
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n");
}

// Function to display records in the hash structure
void displayRecordsInHash(struct HashType hashArray[], int hashSz)
{
    printf("Records in Hash:\n");
    for (int i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);
        struct Node* current = hashArray[i].head;
        while (current != NULL)
        {
            printf("%d, %c, %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    struct HashType hashArray[HASH_SIZE];
    int recordSz = 0;

    // Parse data from input file
    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize hash table
    initializeHash(hashArray, HASH_SIZE);

    // Insert records into hash table
    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashArray, HASH_SIZE, pRecords[i]);
    }

    // Display records in hash table
    displayRecordsInHash(hashArray, HASH_SIZE);

    // Free allocated memory
    free(pRecords);

    return 0;
}
