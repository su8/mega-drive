#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sensors/sensors.h>
/* rm test;gcc -Wall -Wextra -O2 test.c -o test -lsensors;./test */
/* #if SENSORS_API_VERSION >= 0x400 && SENSORS_API_VERSION <= 0x499 */
/* According to libsensors(3)
 * this should be the correct order and values */
/* #endif */

int main(void){
  int nr = 0, nr2 = 0, nr3 = 0;
  const sensors_chip_name *chip;
  const sensors_feature *features;
  const sensors_subfeature *subfeatures;
  double value = 0.0;
  /* char *label = NULL; */
	
  if (0 != sensors_init(NULL))
  return 0;

	while (NULL != (chip = sensors_get_detected_chips(NULL, &nr)))
	{
		nr2 = 0;
		while (NULL != (features = sensors_get_features(chip, &nr2)))
		{
			nr3 = 0;
			while (NULL != (subfeatures = sensors_get_all_subfeatures(chip, features, &nr3)))
			{
        switch(subfeatures->type) {
          case SENSORS_SUBFEATURE_IN_INPUT:
          case SENSORS_SUBFEATURE_FAN_INPUT:
          case SENSORS_SUBFEATURE_TEMP_INPUT:
          {
            if (0 != (sensors_get_value(chip, subfeatures->number, &value)))
              break;
            /* label = sensors_get_label(chip, features); */
            printf("%.2f\n", value);
            /* if (NULL != label) { */
            /*   printf("%s\n", label); */
            /*   free(label); */
            /* } */
            break;
          }
          default:
            continue;

        }
			}
		}
	}
	sensors_cleanup();
	
	return 0;
}
