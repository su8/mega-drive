use MySpecialLib::IO;	# Our IO library that reads/writes encrypted data to the filesystem

use constant RETURN_SUCCESS => 0;
use constant RETURN_FAILURE => 1;

# All global variables and arrays maintain their state throughout the life of the PerlInterpreter object in the C code
# Very cool and what allows this solution to work

my $data_out = '';
my @data_in_array = ();
my $fh_in = undef;
my $fh_out = undef;


# Each subroutine name matches one that the C code calls

#
# Attempts to instantiate a file object to see if service is available
#
sub perl_env_check_service {

        my $ret_val = RETURN_SUCCESS;

        if (MySpecialLib::IO->test() == 0) {
                $ret_val = RETURN_FAILURE;
        }

        return $ret_val;
}


#
#  Takes the incoming data stream and appends it to the data_out buffer 
#
sub perl_env_file_write {

        my $data_str = shift;

        $data_out .= $data_str;

        return RETURN_SUCCESS;
}


#
#  Writes the ongoing data_out contents to the filename specified and closes it
#
sub perl_env_file_close {

        my $filename = shift;

        eval {
                $fh_out = MySpecialLib::IO->new('>', $filename, 'Writing file');
                if (not defined($fh_out)) {
                        return RETURN_FAILURE;
                }

                $fh_out->print($data_out);
                $fh_out->close();

        };
        if ($@) {
                return RETURN_FAILURE;
        }

        $data_out = "";
        return RETURN_SUCCESS;
}


#
#  Opens the file specified
#
sub perl_env_file_open {

        my $filename = shift;

        eval
        {
           my $fh_in = MySpecialLib::IO->open('<', $filename, 'Reading file $filename');
           *FIN = *$fh_in;
           @data_in_array = <FIN>;
           $fh_in->close();
        };
        if ($@)
        {
           return RETURN_FAILURE;
        }

        return RETURN_SUCCESS;
}


#
#  Returns the next line of the data_in contents
#
sub perl_env_file_read_line {

        my $out_buffer = shift @data_in_array;

        return $out_buffer;
}
