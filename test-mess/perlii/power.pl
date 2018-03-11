#  Source - http://perldoc.perl.org/Time/Piece.html

use strict;
use warnings;
use Time::Piece;

sub uzer_func {
  my $t = localtime;
  my $rett = sprintf("%s %s %d", "Hello", $t->cdate, 123);

  return $rett;
}
