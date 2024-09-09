#include "parser.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *strdup(const char *str);

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
    struct Nearest_area {
        struct AreaName {
            char *value;
        } *areaName;
        struct Region {
            char *value;
        } *region;
    } *nearest_area;
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

    if (strcmp(parentKey, "data[nearest_area][0]") == 0) {
        if ((*weather)->nearest_area == NULL) {
            (*weather)->nearest_area = malloc(sizeof(struct Nearest_area));
            if((*weather)->nearest_area == NULL)
                printf("Failed to allocate memory.\n");
            *(*weather)->nearest_area = (struct Nearest_area){0};
        }
    }

    if (strcmp(parentKey, "data[nearest_area][0][areaName][0]") == 0) {
        if ((*weather)->nearest_area == NULL) {
            (*weather)->nearest_area = malloc(sizeof(struct Nearest_area));
            if((*weather)->nearest_area == NULL)
                printf("Failed to allocate memory.\n");
            *(*weather)->nearest_area = (struct Nearest_area){0};
        }
        if ((*weather)->nearest_area->areaName == NULL) {
            (*weather)->nearest_area->areaName = malloc(sizeof(struct AreaName));
            *(*weather)->nearest_area->areaName = (struct AreaName){0};
        }
        if (strcmp(key, "value") == 0) (*weather)->nearest_area->areaName->value = strdup(value);
    }

    if (strcmp(parentKey, "data[nearest_area][0][region][0]") == 0) {
        if ((*weather)->nearest_area->region == NULL) {
            (*weather)->nearest_area->region = malloc(sizeof(struct Region));
            *(*weather)->nearest_area->region = (struct Region){0};
        }
        if (strcmp(key, "value") == 0) (*weather)->nearest_area->region->value = strdup(value);
    }
}

void weather_free(struct Weather **weather) {
    free((*weather)->current_condition->weatherDesc);
    (*weather)->current_condition->weatherDesc = NULL;
    free((*weather)->current_condition);
    (*weather)->current_condition = NULL;
    free((*weather)->nearest_area->areaName);
    (*weather)->nearest_area->areaName = NULL;
    free((*weather)->nearest_area->region);
    (*weather)->nearest_area->region = NULL;
    free((*weather)->nearest_area);
    (*weather)->nearest_area = NULL;
    free(*weather);
    *weather = NULL;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
       printf("Only %d arguments have been entered, but there should be 1\n", argc - 1);
       goto end;
    }
    if(argc == 2)
    {
       char city[100] = {0};
       char file_city[100] = {0};
       sprintf(city, "curl -sLo %s.json https://wttr.in/%s?format=j1", argv[1], argv[1]);
       sprintf(file_city, "%s.json", argv[1]);
       if(system(city) != 0)
       {
          printf("Error. Failed to establish network connection!\n");
          exit(1);
       }
       FILE *file = fopen(file_city, "rb");

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

      argv[1][0] = toupper(argv[1][0]);
      if(strstr(weather->nearest_area->region->value, argv[1]) == NULL && strstr(weather->nearest_area->areaName->value, argv[1]) == NULL)
      {
          printf("Incorrect city name entered.\n");
          exit(1);
      }
      printf("Area name: %s\n", weather->nearest_area->areaName->value);
      printf("Region: %s\n", weather->nearest_area->region->value);
      printf("Date time weather measurements:%s\n", weather->current_condition->localObsDateTime);
      printf("Weather: %s, air temperature %sC, wind dir %s %s, wind speed %sKmph\n", weather->current_condition->weatherDesc->value, weather->current_condition->temp_C,
           weather->current_condition->winddir16Point, weather->current_condition->winddirDegree, weather->current_condition->windspeedKmph);
      weather_free(&weather);
      free(buffer);
    }
    end:
    printf("This program exits!\n");
    return 0;
}


