use strict;
use warnings;

# use IO::Compress::Zip qw(:all);
use IO::Uncompress::Unzip qw(unzip $UnzipError);

  # zip [ glob("test.tar") ] => "test_zip.zip"
  #   or die "some problem: $ZipError" ;

for my $input ( glob "test23*") {
  my $output = $input;
  $output =~ s/.zip//;
  unzip $input => $output
    or die "some problem: $UnzipError";
}
