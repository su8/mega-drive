use strict;
use warnings;

my $variab = "9.21                                                        2016-06-30                                              urx)vt-kuake);*(1);(";


if ($variab =~ /\([^)]*\)/) {
$variab =~ s/\([^)]*\)//g;
$variab =~ s/(?!-)[[:punct:]]//g;
my @arr = split(/\s+/, $variab);
  print "\n", $arr[$#arr];
}
