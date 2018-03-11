# cpuorakle
Obtain some safe cpu flags for use in Gentoo. I've added it to 3 Gentoo wiki pages as well.

# Usage

```bash
# The script used to fit into 1 line at the beginning

chmod +x cpuorakle.awk
gcc '-###' -march=native -x c - 2>&1 | ./cpuorakle.awk
```

Sample output:

```bash
CPU_FLAGS_X86="... sse2 mcx16 sse3 mmxext 3dnow msahf 3dnowext mlzcnt sse4a mabm popcnt sse " 
CFLAGS="... --param l1-cache-size=64 -march=amdfam10 --param l1-cache-line-size=64 --param l2-cache-size=512 "
```

mmx, -O2, -pipe are included in vanilla **make.conf**

# No avx\* ?

I'm not sure how stable avx\* flags are since I don't have intel cpu. This along with the following quote is the reason not to include them in first place.

>GCC depresses SSEx instructions when -mavx is used. Instead, it generates new AVX instructions or AVX equivalence for all SSEx instructions when needed.

# Snafu ?!

Quoting one person:

>your sample output contains lots of faults regarding the CPU\_FLAGS\_X86="" line. It should only contain CPU Flags which also exist as USE-Flags.

Some other programs will detect avx512\* cpu instructions that doesn't exist as CPU\_FLAGS\_X86 USE flags at this point. Including those **existing** cpu instructions as CPU\_FLAGS\_X86 USE flags won't break the system. In case they are added upstream, all users that have included them in their configs will be able to leverage them.
