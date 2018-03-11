/*

 * sensor_readwrite.c

 *

 * compile: cc sensor_readwrite.c -lthread -lpicl -o sensor_readwrite

 */

#include <stdio.h>

#include <picl.h>

 

#define HI_POWEROFF_THRESHOLD   "HighPowerOffThreshold"

#define HI_SHUTDOWN_THRESHOLD   "HighShutdownThreshold"

#define HI_WARNING_THRESHOLD    "HighWarningThreshold"

#define LO_POWEROFF_THRESHOLD   "LowPowerOffThreshold"

#define LO_SHUTDOWN_THRESHOLD   "LowShutdownThreshold"

#define LO_WARNING_THRESHOLD    "LowWarningThreshold"

#define CURRENT_TEMPERATURE     "Temperature"

 

static int

get_child_by_name(picl_nodehdl_t nodeh, char *name, picl_nodehdl_t *resulth)

{

        picl_nodehdl_t  childh;

        picl_nodehdl_t  nexth;

        char            propname[PICL_PROPNAMELEN_MAX];

        picl_errno_t    rc;

 

        /* look up first child node */

        rc = picl_get_propval_by_name(nodeh, PICL_PROP_CHILD, &childh,

                                        sizeof (picl_nodehdl_t));

        if (rc != PICL_SUCCESS) {

                return (rc);

        }

 

        /* step through child nodes looking for named node */

        while (rc == PICL_SUCCESS) {

                rc = picl_get_propval_by_name(childh, PICL_PROP_NAME,

                                                propname, sizeof (propname));

                if (rc != PICL_SUCCESS) {

                        return (rc);

                }

 

                if (name && strcmp(propname, name) == 0) {

                        /* yes - got it */

                        *resulth = childh;

                        return (PICL_SUCCESS);

                }

 

                if (get_child_by_name(childh, name, resulth) == PICL_SUCCESS) {

                        return (PICL_SUCCESS);

                }

 

                /* get next child node */

                rc = picl_get_propval_by_name(childh, PICL_PROP_PEER,

                                        &nexth, sizeof (picl_nodehdl_t));

                if (rc != PICL_SUCCESS) {

                        return (rc);

                }

                childh = nexth;

        }

        return (rc);

}

 

void

get_sensor_thresholds(picl_nodehdl_t nodeh)

{

        int8_t  threshold;

 

        if (picl_get_propval_by_name(nodeh, HI_POWEROFF_THRESHOLD,

                &threshold, sizeof (threshold)) != PICL_SUCCESS) {

                fprintf(stderr, "Failed to read high power-off threshold.");

        } else

                fprintf(stdout, "High power-off threshold = %d\n", threshold);

 

        if (picl_get_propval_by_name(nodeh, HI_SHUTDOWN_THRESHOLD,

                &threshold, sizeof (threshold)) != PICL_SUCCESS) {

                fprintf(stderr, "Failed to read high shutdown threshold.");

        } else

                fprintf(stdout, "High shutdown threshold = %d\n", threshold);

 

        if (picl_get_propval_by_name(nodeh, HI_WARNING_THRESHOLD,

                &threshold, sizeof (threshold)) != PICL_SUCCESS) {

                fprintf(stderr, "Failed to read high warning threshold.");

        } else

                fprintf(stdout, "High warning threshold = %d\n", threshold);

 

        if (picl_get_propval_by_name(nodeh, LO_POWEROFF_THRESHOLD,

                &threshold, sizeof (threshold)) != PICL_SUCCESS) {

                fprintf(stderr, "Failed to read low power-off threshold.");

        } else

                fprintf(stdout, "Low shutdown threshold = %d\n", threshold);

 

        if (picl_get_propval_by_name(nodeh, LO_SHUTDOWN_THRESHOLD,

                &threshold, sizeof (threshold)) != PICL_SUCCESS) {

                fprintf(stderr, "Failed to read low shutdown threshold.");

        } else

                fprintf(stdout, "Low shutdown threshold = %d\n", threshold);

 

        if (picl_get_propval_by_name(nodeh, LO_WARNING_THRESHOLD,

                &threshold, sizeof (threshold)) != PICL_SUCCESS) {

                fprintf(stderr, "Failed to read low warning threshold.");

        } else

                fprintf(stderr, "Low warning threshold = %d\n", threshold);

}

 

void

set_sensor_thresholds(picl_nodehdl_t nodeh, char *threshold, int8_t value)

{

        int8_t  new_value = value;

 

        if (picl_set_propval_by_name(nodeh, threshold, &new_value,

                                sizeof (new_value)) != PICL_SUCCESS)

                fprintf(stderr, "Failed to set *s\n", threshold);

}

 

int

main(void)

{

        int     warning_temp;

        int8_t  temp;

        char    *sensor = "CPU-sensor";

 

        picl_nodehdl_t  rooth;

        picl_nodehdl_t  platformh;

        picl_nodehdl_t  childh;

 

        if (picl_initialize() != PICL_SUCCESS) {

                fprintf(stderr, "Failed to initialise picl\n");

                return (1);

        }

        if (picl_get_root(&rooth) != PICL_SUCCESS) {

                fprintf(stderr, "Failed to get root node\n");

                picl_shutdown();

                return (1);

        }

        if (get_child_by_name(rooth, "platform", &platformh) != PICL_SUCCESS) {

                fprintf(stderr, "Failed to get platform node\n");

                picl_shutdown();

                return (1);

        }

 

        if (get_child_by_name(platformh, sensor, &childh) != PICL_SUCCESS) {

                fprintf(stderr, "Failed to get %s sensor.", sensor);

                picl_shutdown();

                return (1);

        }

 

        get_sensor_thresholds(childh);

 

        /* Read current sensor temperature */

        if (picl_get_propval_by_name(childh, CURRENT_TEMPERATURE,

                &temp, sizeof (temp)) != PICL_SUCCESS) {

                fprintf(stderr, "Failed to read current temperature\n");

        } else

                fprintf(stdout, "Current temperature = %d\n", temp);

 

        set_sensor_threshold(childh, HI_WARNING_THRESHOLD, temp+5);

 

        picl_shutdown();

        return (0);

 }

