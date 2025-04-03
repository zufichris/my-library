#ifndef FILE_IO_H
#define FILE_IO_H

typedef struct
{
    char **columns;
    int columns_count;
} CsvRow;

typedef struct
{
    CsvRow **rows;
    int rows_count;
    char *delimiter;
    char *filePath;
    int capacity;
} CsvData;

FILE *loadFile(const char *file_name);
CsvRow *readRow(const char *file_name);
void appendRow(CsvData *, CsvRow *);

#endif