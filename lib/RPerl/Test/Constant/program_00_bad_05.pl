#!/usr/bin/perl
# [[[ TEST : 'ERROR ECVPARP00' ]]]
# [[[ TEST : 'unexpected token:  ,' ]]]
# [[[ HEADER ]]]
use strict;
use warnings;
use RPerl;
our $VERSION = 0.001_000;

# [[[ CONSTANTS ]]]
## no critic qw(ProhibitConstantPragma ProhibitMagicNumbers)  # USER DEFAULT 3: allow constants
use constant PI  => my number $TYPED_PI  = 3.141_59;
use constant PIE => my string $TYPED_PIE = 'pecan',

# [[[ OPERATIONS ]]]
my integer $i = 2 + 2;