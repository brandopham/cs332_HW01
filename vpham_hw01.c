#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024

struct listing
{
    char *first, *last, *major, *degree, *TA, *advisor;
    float gpa;
    int credit;
};

struct listing getfields(char *line)
{
    struct listing item;

    item.first = strdup(strtok(line, ","));
    item.last = strdup(strtok(NULL, ","));
    item.major = strdup(strtok(NULL, ","));
    item.degree = strdup(strtok(NULL, ","));
    item.gpa = atof(strtok(NULL, ","));
    item.credit = atoi(strtok(NULL, ","));
    item.TA = strdup(strtok(NULL, ","));
    item.advisor = strdup(strtok(NULL, ","));

    return item;
}
void displayStruct(struct listing item)
{
    printf("First : %s\n", item.first);
    printf("Last : %s\n", item.last);
    printf("Major : %s\n", item.major);
    printf("Degree : %s\n", item.degree);
    printf("GPA : %f\n", item.gpa);
    printf("Credit : %d\n", item.credit);
    printf("TA: %s\n", item.TA);
    printf("Advisor: %s\n", item.advisor);
}

void displayDegrees(struct listing list_items[], int count)
{
    char *degrees[5];
    int i, j = 0;
    for (i = 1; i < count; i++)
    {
        if (j == 0)
        {
            degrees[j] = list_items[i].degree;
            j++;
        }
        else
        {
            if (degrees[j] != NULL)
            {
                if (strcmp(list_items[i].degree, degrees[j]) != 0)
                {
                    degrees[j] = list_items[i].degree;
                    j++;
                }
            }
            else
            {
                int check = 0;
                int a;
                for (a = 0; a < 5; a++)
                {
                    if (degrees[a] != NULL)
                    {
                        if (strcmp(list_items[i].degree, degrees[a]) == 0)
                        {
                            check = 1;
                        }
                    }
                }
                if (check == 0)
                {
                    degrees[j] = list_items[i].degree;
                    j++;
                }
            }
        }
    }

    printf("Degrees:\n");
    int k;
    for (k = 0; k < 5; k++)
    {
        if (degrees[k] != NULL)
        {
            printf("%s\n", degrees[k]);
        }
    }
}

void displayGPA(struct listing list_items[], int count)
{
    float first = 0.0, second = 0.0, third = 0.0;
    int firstIndex = 0, secondIndex = 0, thirdIndex = 0;

    int i;
    for (i = 1; i < count; i++)
    {
        if (first < list_items[i].gpa)
        {
            first = list_items[i].gpa;
            firstIndex = i;
        }
    }

    int j;
    for (j = 1; j < count; j++)
    {
        if (second < list_items[j].gpa && list_items[j].gpa != first)
        {
            second = list_items[j].gpa;
            secondIndex = j;
        }
    }

    int k;
    for (k = 1; k < count; k++)
    {
        if (third < list_items[k].gpa && list_items[k].gpa != first && list_items[k].gpa != second)
        {
            third = list_items[k].gpa;
            thirdIndex = k;
        }
    }

    printf("First highest: %s %s; GPA: %0.2f\n", list_items[firstIndex].first, list_items[firstIndex].last, first);
    printf("Second highest: %s %s; GPA: %0.2f\n", list_items[secondIndex].first, list_items[secondIndex].last, second);
    printf("Third highest: %s %s; GPA: %0.2f\n", list_items[thirdIndex].first, list_items[thirdIndex].last, third);
}

void displayAverageCredits(struct listing list_items[], int count)
{
    int i;
    float total = 0;
    for (i = 1; i < count; i++)
    {
        total += list_items[i].credit;
        // printf("Credit Hours for %s %s: %d\n", list_items[i].first, list_items[i].last, list_items[i].credit);
    }

    float realCount = count - 1;
    float average = total / realCount;

    printf("Average Credit Hours for All Students: %0.2f\n", average);
}

void displayCSGPA(struct listing list_items[], int count)
{
    char *department = "Computer Science";

    int i;
    float total = 0.0, realCount = 0.0;
    for (i = 1; i < count; i++)
    {
        if (strcmp(list_items[i].major, department) == 0)
        {
            // printf("Credit Hours for %s %s in the %s major: %d\n", list_items[i].first, list_items[i].last, list_items[i].major, list_items[i].credit);
            total += list_items[i].credit;
            realCount++;
        }
    }

    float average = total / realCount;

    printf("Average Credit Hours for CS Department: %0.2f\n", average);
}

// void displayDepartments(struct listing list_items[], int count)
// {
//     int maxDepartments = 15, maxAdvisors = 15;
//     char *departments[maxDepartments];
//     char *advisors[maxAdvisors];
    
//     int check = 0;
//     int depCount = 0;
//     int advCount = 0;

//     int a;
//     for (a = 0; a < maxDepartments; a++)
//     {
//         departments[a] = "";
//         advisors[a] = "";
//     }

//     int i, j;
//     for (i = 1; i < count; i++)
//     {
//         // printf("Department: %s\n", list_items[i].major);
//         for (j = 0; j < maxDepartments; j++)
//         {
//             // printf("Dep Array: %s\n", departments[j]);
//             if (departments[j] != "")
//             {
//                 if (strcmp(list_items[i].major, departments[j]) == 0)
//                 {
//                     // printf("Made it; Major: %s\n", list_items[i].major);
//                     // printf("list_items[%d].major: %s, departments[%d]: %s\n", i, list_items[i].major, j, departments[j]);
//                     check = 1;
//                 }
//             }
//         }

//         // printf("Dep Count: %d, Department: %s\n", depCount, list_items[i].major);
//         if (check == 0)
//         {
//             departments[depCount] = list_items[i].major;
//             depCount++;
//         }

//         check = 0;
//     }


//     i = 0, j = 0, check = 0;
//     for (i = 1; i < count; i++)
//     {
//         // printf("Department: %s\n", list_items[i].major);
//         for (j = 0; j < maxAdvisors; j++)
//         {

//             // printf("Dep Array: %s\n", departments[j]);
//             if (advisors[j] != "")
//             {
//                 char *adv = list_items[i].advisor;
//                 printf("%s\n", adv);
//                 int length = strlen(adv);
//                 adv[strcspn(adv, "\n")] = 0;
                
//                 if (strcmp(adv, advisors[j]) == 0)
//                 {
//                     // printf("Made it; Major: %s\n", list_items[i].major);
//                     // printf("list_items[%d].major: %s, departments[%d]: %s\n", i, list_items[i].major, j, departments[j]);
//                     check = 1;
//                 }
//             }
//         }

//         // printf("Dep Count: %d, Department: %s\n", depCount, list_items[i].major);
//         if (check == 0)
//         {
//             char *adv = list_items[i].advisor;
//             int length = strlen(adv);
//             adv[strcspn(adv, "\n")] = 0;

//             advisors[advCount] = adv;
//             advCount++;
//         }

//         check = 0;
//     }

//     int b;
//     for (b = 0; b < maxDepartments; b++)
//     {
//         if (departments[b] != "")
//         {
//             printf("Departments: %s\n", departments[b]);
//         }
//     }

//     int c;
//     for (b = 0; b < maxDepartments; b++)
//     {
//         if (advisors[b] != "")
//         {
//             printf("Advisors: %s\n", advisors[b]);
//         }
//     }
// }

int main(int argc, char *args[])
{
    struct listing list_items[22555];
    char line[LINESIZE];
    int i, count;
    FILE *fptr = fopen("studentsdataset.csv", "r");
    if (fptr == NULL)
    {
        printf("Error reading input file students_dataset_1.csv\n");
        exit(-1);
    }
    count = 0;
    while (fgets(line, LINESIZE, fptr) != NULL)
    {
        list_items[count++] = getfields(line);
    }

    fclose(fptr);

    displayDegrees(list_items, count);
    displayGPA(list_items, count);
    displayAverageCredits(list_items, count);
    displayCSGPA(list_items, count);
    // displayDepartments(list_items, count);

    return 0;
}

// https://uab.instructure.com/courses/1579059/files/folder/lecture?preview=69969179
// this is linked to lecture slides, I used his example to do this porject.
