#!/usr/bin/awk -f
@load "filefuncs";
{
  gsub(/\"/,"");
  for (x=1; x < NF; x++) {
    if (match($x,/march|cache/)) {
      cflagz[$x]++;
    } else if (match($x,/mpopcnt|m3dnow|msse|mssse|maes/)) {
      x86[substr($x,3)]++;
    } else if (match($x,/mcx16|mabm|mlzcnt|msahf/)) {
      x86[substr($x,2)]++;
    }
  }
}
function concatMe(arr) {
  ret="";
  for (x in arr) {
    str=(match(x,/cache/) ? "--param"" "x : x);
    ret=ret" "str;
  }
  return ret;
}
END {
  PROCINFO["sorted_in"]="@ind_str_asc";
  cpuf="/proc/cpuinfo";
  if (0 == stat(cpuf, buf)) {
    while (0 != (getline cur_line < cpuf)) {
      if (match(cur_line, "flags")) {
        split(cur_line, arr, " ");
        if (0 != arr_len=length(arr)) {
          for (x=1; x < arr_len; x++) {
            if (match(arr[x],/mmxext|3dnowext/)) {
              x86[arr[x]]++;
            }
          }
        }
        break;
      }
    }
    close(cpuf);
  }

  if (0 != length(x86)) {
    printf("CPU_FLAGS_X86=\"...%s\"\n",concatMe(x86));
  }

  if (0 != length(cflagz)) {
    printf("CFLAGS=\"...%s\"\n",concatMe(cflagz));
  }
}
