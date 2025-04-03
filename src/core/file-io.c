#include "../../include/file_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COL_SIZE 10
#define MAX_ROW_SIZE 1000

FILE *loadFile(const char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Error Opening %s\n", file_name);
        return NULL;
    }
    printf("Loaded %s\n", file_name);
    return file;
}

char *readCsvLine(FILE *file)
{
    char *line = malloc(MAX_ROW_SIZE * sizeof(char));
    if (line == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    if (fgets(line, MAX_ROW_SIZE, file) == NULL)
    {
        free(line);
        return NULL;
    }
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    return line;
}

CsvRow *getRow(char *csvLine, const char delimiter)
{
    CsvRow *csv_row = malloc(sizeof(CsvRow));
    if (csv_row == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    csv_row->columns_count = 0;

    int columns_capacity = 10;
    csv_row->columns = malloc(columns_capacity * sizeof(char *));
    if (csv_row->columns == NULL)
    {
        free(csv_row);
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    char delim_str[2] = {delimiter, '\0'};
    char *token = strtok(csvLine, delim_str);
    int i = 0;
    while (token != NULL)
    {
        if (i >= columns_capacity)
        {
            columns_capacity *= 2;
            char **temp = realloc(csv_row->columns, columns_capacity * sizeof(char *));
            if (temp == NULL)
            {
                for (int j = 0; j < i; j++)
                    free(csv_row->columns[j]);
                free(csv_row->columns);
                free(csv_row);
                exit(EXIT_FAILURE);
            }
            csv_row->columns = temp;
        }
        csv_row->columns[i] = strdup(token);
        if (csv_row->columns[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(csv_row->columns[j]);
            free(csv_row->columns);
            free(csv_row);
            exit(EXIT_FAILURE);
        }
        i++;
        csv_row->columns_count++;
        token = strtok(NULL, delim_str);
    }
    return csv_row;
}

void appendRow(CsvData *data, CsvRow *row)
{
    data->rows = realloc(data->rows, (data->rows_count + 1) * sizeof(CsvRow *));
    if (data->rows == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    data->rows[data->rows_count] = row;
    data->rows_count++;
}