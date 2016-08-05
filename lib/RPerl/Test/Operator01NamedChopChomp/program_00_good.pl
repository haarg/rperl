#!/usr/bin/perl

# [[[ PREPROCESSOR ]]]
# <<< EXECUTE_SUCCESS: 'howdy' >>>
# <<< EXECUTE_SUCCESS: 'howdy' >>>
# <<< EXECUTE_SUCCESS: 'howdyhowdyhowdhowd' >>>

# [[[ HEADER ]]]
use RPerl;
use strict;
use warnings;
our $VERSION = 0.001_000;

# [[[ CRITICS ]]]
## no critic qw(ProhibitUselessNoCritic ProhibitMagicNumbers RequireCheckedSyscalls)  # USER DEFAULT 1: allow numeric values & print operator
## no critic qw(RequireInterpolationOfMetachars)  # USER DEFAULT 2: allow single-quoted control characters & sigils

# [[[ OPERATIONS ]]]
my string $foo = 'howdy' . "\n";
print $foo;
print $foo;

chop $foo;    # newline character removed
print $foo;
print $foo;

chop $foo;    # 'y' character removed
print $foo;
print $foo;

