#if 1
#include "parser.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Weather {
    struct Current_condition {
        char *FeelsLikeC;
        char *FeelsLikeF;
        char *cloudcover;
        char *humidity;
        char *localObsDateTime;
        char *observation_time;
        char *precipInches;
        char *precipMM;
        char *pressure;
        char *pressureInches;
        char *temp_C;
        char *temp_F;
        char *uvIndex;
        char *visibility;
        char *visibilityMiles;
        char *weatherCode;
        struct WeatherDesc {
            char *value;
        } *weatherDesc;
        struct WeatherIconUrl {
            char *value;
        } *weatherIconUrl;
        char *winddir16Point;
        char *winddirDegree;
        char *windspeedKmph;
        char *windspeedMiles;
    } *current_condition;
};

static void callback(enum NanoJSONCError error, const char *const key, const char *const value, const char *const parentKey, void *object) {
    if (error != NO_ERROR)
    {
        //printf("%s\n", nanojsonc_error_desc(error));
        return;
    } // guard statement

    struct Weather **weather = object;

    if (*weather == NULL) {
        *weather = malloc(sizeof(struct Weather));
        **weather = (struct Weather){0}; // Initialize all members to 0
    }

    //if (strcmp(parentKey, "data[current_condition]") == 0) {
    if (strcmp(parentKey, "data[current_condition][0]") == 0) {
        if ((*weather)->current_condition == NULL) {
            (*weather)->current_condition = malloc(sizeof(struct Current_condition));
            *(*weather)->current_condition = (struct Current_condition){0};
        }
        if (strcmp(key, "FeelsLikeC") == 0) (*weather)->current_condition->FeelsLikeC = strdup(value);
        if (strcmp(key, "FeelsLikeF") == 0) (*weather)->current_condition->FeelsLikeF = strdup(value);
        if (strcmp(key, "cloudcover") == 0) (*weather)->current_condition->cloudcover = strdup(value);
        if (strcmp(key, "humidity") == 0) (*weather)->current_condition->humidity = strdup(value);
        if (strcmp(key, "localObsDateTime") == 0) (*weather)->current_condition->localObsDateTime = strdup(value);
        if (strcmp(key, "observation_time") == 0) (*weather)->current_condition->observation_time = strdup(value);
        if (strcmp(key, "precipInches") == 0) (*weather)->current_condition->precipInches = strdup(value);
        if (strcmp(key, "precipMM") == 0) (*weather)->current_condition->precipMM = strdup(value);
        if (strcmp(key, "pressure") == 0) (*weather)->current_condition->pressure = strdup(value);
        if (strcmp(key, "pressureInches") == 0) (*weather)->current_condition->pressureInches = strdup(value);
        if (strcmp(key, "temp_C") == 0) (*weather)->current_condition->temp_C = strdup(value);
        if (strcmp(key, "temp_F") == 0) (*weather)->current_condition->temp_F = strdup(value);
        if (strcmp(key, "uvIndex") == 0) (*weather)->current_condition->uvIndex = strdup(value);
        if (strcmp(key, "visibility") == 0) (*weather)->current_condition->visibility = strdup(value);
        if (strcmp(key, "visibilityMiles") == 0) (*weather)->current_condition->visibilityMiles = strdup(value);
        if (strcmp(key, "weatherCode") == 0) (*weather)->current_condition->weatherCode = strdup(value);
        if (strcmp(key, "winddir16Point") == 0) (*weather)->current_condition->winddir16Point = strdup(value);
        if (strcmp(key, "winddirDegree") == 0) (*weather)->current_condition->winddirDegree = strdup(value);
        if (strcmp(key, "windspeedKmph") == 0) (*weather)->current_condition->windspeedKmph = strdup(value);
    }
    if (strcmp(parentKey, "data[current_condition][0][weatherDesc][0]") == 0) {
        if ((*weather)->current_condition->weatherDesc == NULL) {
            (*weather)->current_condition->weatherDesc = malloc(sizeof(struct WeatherDesc));
            *(*weather)->current_condition->weatherDesc = (struct WeatherDesc){0};
        }
        if (strcmp(key, "value") == 0) (*weather)->current_condition->weatherDesc->value = strdup(value);
    }
}

void weather_free(struct Weather **weather) {
    free((*weather)->current_condition->weatherDesc);
    (*weather)->current_condition->weatherDesc = NULL;
    free((*weather)->current_condition);
    (*weather)->current_condition = NULL;
    free(*weather);
    *weather = NULL;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
       char gorod[] = "Moscow";
       char pogoda[] = "curl -sLo file8.txt https://wttr.in/Moscow?format=j1";
       char pogoda_Paris[] = "curl -sLo file9.txt https://wttr.in/Paris?format=j1";
       char enter_gorod[] = "curl -sLo file10.txt https://wttr.in/London?format=j1";
       char *moscow[] = {"curl", "-sLo Moscow.json https://wttr.in/Moscow?format=j1", 0};
       system("help");
       system("cd");
       //system("CHCP 1251");
       system("CHCP ");
       system("cd C:");
       system("cd /D G:\English");
       //system("cmd");
       //system("help cd");
       //system("CMD");
       system("curl --help");
       system("curl -OL https://wttr.in/Moscow?format=j1");
       system("curl -sLo file1.txt https://wttr.in/Moscow?format=j1");
       system("curl -sLo file2.txt https://wttr.in/city?format=j1");
       system("curl -sLo file3.txt https://wttr.in/ogorod?format=j1");
       system("curl -sLo file4.txt https://wttr.in/54?format=j1");
       system("curl -sLo file5.txt https://wttr.in/200?format=j1");
       system("curl -sLo file6.txt https://wttr.in/params=gorod?format=j1");
       system("curl -sLo file7.txt https://wttr.in/params={gorod}?format=j1");
       //system("pause");
       //_wsystem("");
       system(pogoda);
       system(pogoda_Paris);
       system(enter_gorod);
       //system(moscow);
       char *args[] = {"echo" , "Hello, Linux!", 0};
       char *args1[] = {"curl", "-sLo", "file11.txt", "https://wttr.in/Moscow?format=j1", 0};
       char *args2[] = {"curl", "-sLo file13.txt https://wttr.in/Paris?format=j1", 0};
       //execvp("echo", args);
       //printf("execvp() failed. Error: %s\n", strerror(errno));
       system("path");
       //execvp("curl -sLo", args1);
       //printf("execvp() failed. Error: %s\n", strerror(errno));
       //execvp("C:\Windows\System32\curl.exe", args1);
       //printf("execvp() failed. Error: %s\n", strerror(errno));
      // execvp("curl", args2);
       //printf("execvp() failed. Error: %s\n", strerror(errno));
       //execvp("curl", args2);
       //printf("execvp() failed. Error: %s\n", strerror(errno));
      // execvp("curl", args2);
       //printf("execvp() failed. Error: %s\n", strerror(errno));
       puts("\n\n");
       //execvp("curl", moscow);
       //printf("execvp() failed. Error: %s\n", strerror(errno));
       //system("curl -OL https://docs.google.com/spreadsheets/d/1gVudHOA1mDkjLiRLobs95OJmBOzBQrHj/edit?gid=922040824#gid=922040824");
       //system("curl -sLo abon.xlsx https://docs.google.com/spreadsheets/d/1gVudHOA1mDkjLiRLobs95OJmBOzBQrHj/edit?gid=922040824#gid=922040824");

        //FILE *file = fopen("example3.json", "rb");
    FILE *file = fopen("Moscow.json", "rb");
    //FILE *file = fopen("Moscow1.json", "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: %d: %s\n", errno, strerror(errno));
        return errno;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error seeking file");
        fclose(file);
        return errno;
    }
    long len = ftell(file);
    rewind(file);

    char *buffer = (char *) malloc(len + 1);
    if (buffer == NULL) {
        fclose(file);
        perror("Error allocating memory");
        return ENOMEM;
    }

    size_t bytes_read = fread(buffer, 1, len, file);
    if (bytes_read != (size_t) len) {
        if (feof(file)) {
            perror("Error: end of file reached before reading expected bytes.");
            fclose(file);
            free(buffer);
            return EIO;
        } else if (ferror(file)) {
            perror("Error reading the file");
            fclose(file);
            free(buffer);
            return errno;
        }
    }
    buffer[len] = '\0';
    fclose(file);

    struct Weather *weather = NULL;
    nanojsonc_parse_object(buffer, "data", &weather, callback);
    //verify(weather);

    #if 0
    //printf("%s %s %d\n", person->name->first, person->name->last, person->age);

    person_free(&weather);
    #endif // 0
    printf("%s %s %s %sKmph\n", weather->current_condition->weatherDesc->value, weather->current_condition->temp_C,
           weather->current_condition->winddir16Point, weather->current_condition->windspeedKmph);
    weather_free(&weather);
    free(buffer);
    }
    if(argc >= 2)
    {
       system("curl -sLo file7.txt https://wttr.in/params=argv[1]?format=j1");
    }
    printf("Hello world!\n");
    return 0;
}
#endif

