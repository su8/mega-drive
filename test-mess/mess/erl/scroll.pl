#! perl

# Offer more scrolling functions.
#
# Available commands are `(up|down)-(page|halfpage|fixed)`, `top` and `bottom`.
#
# Usage example:
#   URxvt.keysym.M-Page_Up:   perl:scroll:up-halfpage
#   URxvt.keysym.M-Page_Down: perl:scroll:down-halfpage
#   URxvt.keysym.Home:        perl:scroll:top
#   URxvt.keysym.End:         perl:scroll:bottom
#
# Optional settings:
#   URxvt.scroll.increment: number of lines for fixed-height scrolling (default 5)
#   URxvt.scroll.keepLines: number of lines from the previous page to keep visible
#                           when scrolling a whole page (default 1)

use List::Util qw(min max);

sub on_start {
	my ($self) = @_;

	$self->{increment} = $self->x_resource('scroll.increment') || 5;
	$self->{keeplines} = $self->x_resource('scroll.keepLines') || 1;

	()
}

sub on_user_command {
	my ($self, $cmd) = @_;
	
	$cmd =~ s/^scroll:// || return ();

	my $new_line;

	if ($cmd eq "top") {
		$new_line = $self->top_row;
	}
	elsif ($cmd eq "bottom") {
		$new_line = 0;
	}
	else {
		$cmd =~ /(\w*)-(\w*)/ || return 1;

		my $increment;

		if    ($2 eq "fixed")    {$increment = $self->{increment};}
		elsif ($2 eq "page")     {$increment = $self->nrow - $self->{keeplines};}
		elsif ($2 eq "halfpage") {$increment = int($self->nrow / 2);}
		else {return 1;}

		if    ($1 eq "up")   {$new_line = max($self->view_start-$increment, $self->top_row);}
		elsif ($1 eq "down") {$new_line = min($self->view_start+$increment, 0);}
		else {return 1;}
	}

	$self->view_start($new_line);
	$self->want_refresh;
	
	1
}
