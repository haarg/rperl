#!/usr/bin/perl

# Learning RPerl, Section 4.4: Subroutine Arguments

# [[[ PREPROCESSOR ]]]
# <<< EXECUTE_SUCCESS: 'have $arg1 * $arg2 = 12.875' >>>
# <<< EXECUTE_SUCCESS: 'have $arg3 x $arg1 = over and over and over and over and over and' >>>

# [[[ HEADER ]]]
use RPerl;
use strict;
use warnings;
our $VERSION = 0.001_000;

# [[[ CRITICS ]]]
## no critic qw(ProhibitUselessNoCritic ProhibitMagicNumbers RequireCheckedSyscalls)  # USER DEFAULT 1: allow numeric values & print operator
## no critic qw(RequireInterpolationOfMetachars)  # USER DEFAULT 2: allow single-quoted control characters & sigils

# [[[ SUBROUTINES ]]]
our void $foo_args = sub {
    # PERLTIDY BUG, failure to put a space between $arg3 and closing )
#    (my integer $arg1, my number $arg2, my string $arg3) = @ARG;
    ( my integer $arg1, my number $arg2, my string $arg3 ) = @ARG;
    print 'have $arg1 * $arg2 = ', number_to_string($arg1 * $arg2), "\n";
    print 'have $arg3 x $arg1 = ', ($arg3 x $arg1), "\n";
};

# [[[ OPERATIONS ]]]
foo_args(5, 2.575, 'over and ');
