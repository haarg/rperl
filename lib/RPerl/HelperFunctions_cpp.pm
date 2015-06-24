# [[[ HEADER ]]]
package RPerl::HelperFunctions_cpp;
use strict;
use warnings;
use RPerl::Config; # get Carp, English, $RPerl::INCLUDE_PATH without 'use RPerl;'

#use RPerl;  # DEV NOTE: need to use HelperFunctions in RPerl::DataStructure::Array for type checking SvIOKp() etc; remove dependency on RPerl void_method type so HelperFunctions can be loaded by RPerl type system
our $VERSION = 0.002_030;

# [[[ CRITICS ]]]
## no critic qw(ProhibitStringyEval) # SYSTEM DEFAULT 1: allow eval()

# [[[ INCLUDES ]]]
use RPerl::Inline;

# [[[ SUBROUTINES ]]]
#our void_method $cpp_load = sub {  # DEV NOTE: remove dependency on RPerl
sub cpp_load {
    my $need_load_cpp = 0;
    if (    ( exists $main::{'RPerl__HelperFunctions__MODE_ID'} )
        and ( defined &{ $main::{'RPerl__HelperFunctions__MODE_ID'} } ) )
    {
#        RPerl::diag "in HelperFunctions_cpp::cpp_load, RPerl__HelperFunctions__MODE_ID() exists & defined\n";
#        RPerl::diag q{in HelperFunctions_cpp::cpp_load, have RPerl__HelperFunctions__MODE_ID() retval = '} . main::RPerl__HelperFunctions__MODE_ID() . "'\n";
        if ( $RPerl::MODES
            ->{ main::RPerl__HelperFunctions__MODE_ID() }->{ops} ne
            'CPP' )
        {
            $need_load_cpp = 1;
        }
    }
    else {
#        RPerl::diag "in HelperFunctions_cpp::cpp_load, RPerl__HelperFunctions__MODE_ID() does not exist or undefined\n";
        $need_load_cpp = 1;
    }

    if ($need_load_cpp) {

#        RPerl::diag "in HelperFunctions_cpp::cpp_load, need load CPP code\n";

#BEGIN { RPerl::diag "[[[ BEGIN 'use Inline' STAGE for 'RPerl/HelperFunctions.cpp' ]]]\n"x3; }
        my $eval_string = <<"EOF";
package main;
use RPerl::Inline;
use Inline (CPP => '$RPerl::INCLUDE_PATH/RPerl/HelperFunctions.cpp', \%RPerl::Inline::ARGS);
1;
EOF

        $RPerl::Inline::ARGS{ccflagsex} = $RPerl::Inline::CCFLAGSEX . $RPerl::TYPES_CCFLAG;
        $RPerl::Inline::ARGS{cppflags} = $RPerl::TYPES_CCFLAG;
#        RPerl::diag "in HelperFunctions_cpp::cpp_load(), CPP not yet loaded, about to call eval() on \$eval_string =\n<<< BEGIN EVAL STRING>>>\n" . $eval_string . "<<< END EVAL STRING >>>\n";
#        RPerl::diag "in HelperFunctions_cpp::cpp_load(), CPP not yet loaded, have \%RPerl::Inline::ARGS =\n" . Dumper(\%RPerl::Inline::ARGS) . "\n";

        eval $eval_string or croak( $OS_ERROR . "\n" . $EVAL_ERROR );
        if ($EVAL_ERROR) { croak($EVAL_ERROR); }

#RPerl::diag "[[[ END 'use Inline' STAGE for 'RPerl/HelperFunctions.cpp' ]]]\n"x3;
    }

#	else { RPerl::diag "in HelperFunctions_cpp::cpp_load(), CPP already loaded, DOING NOTHING\n"; }
}

1;
