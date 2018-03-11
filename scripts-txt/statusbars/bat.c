int getbattery(char *status, size_t size) {
    FILE *fd;
    int now, full, bat;
    char stat[12];

    fd = fopen("/sys/class/power_supply/BAT0/charge_now", "r");
    fscanf(fd, "%d", &now);
    fclose(fd);

    fd = fopen("/sys/class/power_supply/BAT0/charge_full", "r");
    fscanf(fd, "%d", &full);
    fclose(fd);

    fd = fopen("/sys/class/power_supply/BAT0/status", "r");
    fscanf(fd, "%s", stat);
    fclose(fd);

    bat = 100 * now / full;

    if(strncmp(stat, "Discharging", 11) == 0) {
        if(bat < 20) {
            return snprintf(status, size, "\x08""B\x05%d%%", bat);
        } else if(bat > 80) {
            return snprintf(status, size, "\x08""B\x06%d%%", bat);
        } else {
            return snprintf(status, size, "\x08""B\x07%d%%", bat);
    }
    } else if(strncmp(stat, "Charging", 8) == 0) {
        return snprintf(status, size, "\x08""B\x06""AC\x02%d%%", bat);
    } else {
        return snprintf(status, size, "\x08""B\x02""AC");
    }
}
