int main(void) {
  unsigned int x = 0;

  for (x = 0; x < 2; x++) {
    if (1 == x) {
      goto the_moon;
    }
  }

the_moon:
  return 0;
}
