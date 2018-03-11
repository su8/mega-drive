use strict;
use warnings;


# open(FILE, "ps -f|");
# while (<FILE>) 
# {
# ($uid,$pid,$ppid,$restofline) = split;
# print "the process id is :$pid";
# }
# __END__
#
# opendir(PROC,"/proc") or die "Unable to open /proc:$!\n";
# while (defined($_= readdir(PROC))){
#     next if ($_ eq "." or $_ eq "..");
#     next unless /^\d+$/; # filter out any random non-pid files
#     print "$_\t". getpwuid((lstat "/proc/$_")[4])."\n";
# }
# closedir(PROC);
# my $string = " Manual page gcc(1) line 192312321/3231232 ";
# my @arr = split(/\s+/, $string);
# my @nn = join( ' ', split(' ')) for $string;
# my @arr2 = split(' ', join(' ', @arr));
# $string =~ s/^\s*(.*)\s*$/$1/;
# my @arr = split(/\s+/,$string);
# if ($strn =~ /\d+$/) {
#   print "yup";
# }
# print "s: \n", $arr2[3];
#print $ENV{"HOME"};
#print $ENV{"HOME"} . "/man2pdf";
my $s="st\$#@~!&*()\[\];,:?^`\\\/dl,ib.h(3)";
$s =~   s/(?!\.|\-)[[:punct:]]//g;
print "$s\n";
