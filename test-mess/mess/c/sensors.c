#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sensors/sensors.h>
/* rm test;gcc -Wall -Wextra -O2 test.c -o test -lsensors;./test */
/* #if SENSORS_API_VERSION >= 0x400 && SENSORS_API_VERSION <= 0x499 */
/* #endif */

int main(void){
	int a = 0, b = 0, c = 0;
	const sensors_chip_name * chip;
	const sensors_feature * features;
	const sensors_subfeature * subfeatures;
	double value;
	char *label = NULL;
	
	if (0 != sensors_init(NULL))
	  return 0;

	while ((chip = sensors_get_detected_chips(NULL, &a)))
	{
		b = 0;
		while ((features = sensors_get_features(chip, &b)))
		{
			c = 0;
			while ((subfeatures = sensors_get_all_subfeatures(chip, features, &c)))
			{
        switch(subfeatures->type) {
          case SENSORS_SUBFEATURE_IN_INPUT:
          case SENSORS_SUBFEATURE_FAN_INPUT:
          case SENSORS_SUBFEATURE_TEMP_INPUT:
          {
            sensors_get_value(chip, subfeatures->number, &value);
            label = sensors_get_label(chip, features);
            printf("%.2f\n", value);
            if (NULL != label) {
              printf("%s\n", label);
              free(label);
            }
            break;
          }
          default:
            continue;

        }
			}
		}
	}
	
	return 0;
}
