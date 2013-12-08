#!/usr/bin/perl
use strict;
use warnings;
use version; our $VERSION = qv('0.3.1');

# SUPPRESS OUTPUT FROM INDIVIDUAL TESTS, EXCLUDING TESTS INSIDE BEGIN{} BLOCKS
# order is BEGIN, UNITCHECK, CHECK, INIT, END; CHECK here suppresses Inline compile output from including HelperFunctions_cpp.pm from INIT in Array.pm
CHECK {
    open( STDOUT, '>', '/dev/null' )
        || croak('Error redirecting stdout, croaking');
    open( STDERR, '>', '/dev/null' )
        || croak('Error redirecting stderr, croaking');
}

use Test::More tests => 121;
use Test::Exception;
use Carp;

BEGIN {
    diag(
        "\n[[[ Beginning Array Type Pre-Test Loading, RPerl Type System ]]]\n "
    );
}

BEGIN {
    lives_ok(
        sub {    ## PERLTIDY BUG blank newline

            package main;
            our $RPERL_INCLUDE_PATH = '/tmp/RPerl-latest/lib';
        },
        q{package main; our $RPERL_INCLUDE_PATH = '/tmp/RPerl-latest/lib';} ## no critic qw(RequireInterpolationOfMetachars)  ## RPERL allow single-quoted sigils
    );
}    # NEED REMOVE hard-coded path

BEGIN {
    lives_ok(
        sub { use lib $main::RPERL_INCLUDE_PATH . '/CPAN/'; },
        q{use lib $main::RPERL_INCLUDE_PATH . '/CPAN/';} ## no critic qw(RequireInterpolationOfMetachars)  ## RPERL allow single-quoted sigils
    );
    lives_and( sub { use_ok('MyConfig'); }, q{use_ok('MyConfig') lives} );
}    # RPerl's MyConfig.pm

BEGIN {
    lives_ok(
        sub { use lib $main::RPERL_INCLUDE_PATH; },
        q{use lib $main::RPERL_INCLUDE_PATH;} ## no critic qw(RequireInterpolationOfMetachars)  ## RPERL allow single-quoted sigils
    );
    lives_and( sub { use_ok('RPerl'); }, q{use_ok('RPerl') lives} );
    lives_ok(
        sub {
            use base ('RPerl');
            $RPerl::INCLUDE_PATH = $main::RPERL_INCLUDE_PATH;
        },
        q{use base ('RPerl');  $RPerl::INCLUDE_PATH = $main::RPERL_INCLUDE_PATH;} ## no critic qw(RequireInterpolationOfMetachars)  ## RPERL allow single-quoted sigils
    );
}    # RPerl system files

BEGIN {
    lives_and( sub { use_ok('Data::Dumper'); },
        q{use_ok('Data::Dumper') lives} );
    lives_ok(
        sub {
            our $AUTOLOAD;

            sub AUTOLOAD { ## no critic qw(ProhibitAutoloading RequireArgUnpacking)  ## RPERL SYSTEM allow autoload  ## RPERL SYSTEM allow read-only @_
                croak(
                    "Error autoloading, AUTOLOAD purposefully disabled for debugging, have \$AUTOLOAD = '$AUTOLOAD' and \@_ = \n"
                        . Dumper( \@_ )
                        . ', croaking' );
            }
        },
        q{our $AUTOLOAD;  sub AUTOLOAD {...}} ## no critic qw(RequireInterpolationOfMetachars)  ## RPERL allow single-quoted sigils
    );
}

# loop 3 times, once for each mode: Pure-Perl, RPerl Perl-Data, and RPerl C-Data
for my $i ( 0 .. 2 ) {
    print "in 05_type_array.t, top of for() loop, have \$i = $i\n"
        or croak;    # no effect if suppressing output!
    my $OPS_TYPES;

    if ( $i == 0 ) {
        $OPS_TYPES = 'PERLOPS_PERLTYPES';
        diag(
            "\n[[[ Beginning RPerl's Pure-Perl Array Type Tests, RPerl Type System Using Perl Data Types & Perl Operations ]]]\n "
        );
        lives_and(
            sub {
                is( ops_number(), 'PERL', q{ops_number() returns 'PERL'} );
            },
            q{ops_number() lives}
        );
        lives_and(
            sub {
                is( types_number(), 'PERL',
                    q{types_number() returns 'PERL'} );
            },
            q{types_number() lives}
        );
        lives_and(
            sub { is( ops_string(), 'PERL', q{ops_string() returns 'PERL'} ) }
            ,
            q{ops_string() lives}
        );
        lives_and(
            sub {
                is( types_string(), 'PERL',
                    q{types_string() returns 'PERL'} );
            },
            q{types_string() lives}
        );
        lives_and(
            sub { is( ops_array(), 'PERL', q{ops_array() returns 'PERL'} ) },
            q{ops_array() lives}
        );
        lives_and(
            sub {
                is( types_array(), 'PERL', q{types_array() returns 'PERL'} );
            },
            q{types_array() lives}
        );
    }
    elsif ( $i == 1 ) {
        $OPS_TYPES = 'CPPOPS_PERLTYPES';
        diag(
            "\n[[[ Beginning RPerl's Perl-Data Mode Array Type Tests, RPerl Type System Using Perl Data Types & C++ Operations ]]]\n "
        );

        lives_ok(
            sub { types::types_enable('PERL') },
            q{types::types_enable('PERL') lives}
        );

        # Array: C++ use, load, link
        BEGIN {
            lives_and(
                sub { use_ok('RPerl::DataStructure::Array_cpp'); },
                q{use_ok('RPerl::DataStructure::Array_cpp') lives}
            );
        }
        lives_and(
            sub { require_ok('RPerl::DataStructure::Array_cpp'); },
            q{require_ok('RPerl::DataStructure::Array_cpp') lives}
        );
        lives_ok(
            sub { RPerl::DataStructure::Array_cpp::cpp_load(); },
            q{RPerl::DataStructure::Array_cpp::cpp_load() lives}
        );
        lives_ok(
            sub { RPerl::DataStructure::Array_cpp::cpp_link(); },
            q{RPerl::DataStructure::Array_cpp::cpp_link() lives}
        );
        lives_and(
            sub { is( ops_number(), 'CPP', q{ops_number() returns 'CPP'} ) },
            q{ops_number() lives}
        );
        lives_and(
            sub {
                is( types_number(), 'PERL',
                    q{types_number() returns 'PERL'} );
            },
            q{types_number() lives}
        );
        lives_and(
            sub { is( ops_string(), 'CPP', q{ops_string() returns 'CPP'} ) },
            q{ops_string() lives}
        );
        lives_and(
            sub {
                is( types_string(), 'PERL',
                    q{types_string() returns 'PERL'} );
            },
            q{types_string() lives}
        );
        lives_and(
            sub { is( ops_array(), 'CPP', q{ops_array() returns 'CPP'} ) },
            q{ops_array() lives} );
        lives_and(
            sub {
                is( types_array(), 'PERL', q{types_array() returns 'PERL'} );
            },
            q{types_array() lives}
        );
    }
    else {
        $OPS_TYPES = 'CPPOPS_CPPTYPES';
        diag(
            "\n[[[ Beginning RPerl's C-Data Mode Array Type Tests, RPerl Type System Using C++ Data Types & C++ Operations ]]]\n "
        );
        lives_ok(
            sub { types::types_enable('CPP') },
            q{types::types_enable('CPP') lives}
        );

        # force reload and relink
        $RPerl::DataStructure::Array_cpp::CPP_LOADED = 0;
        $RPerl::DataStructure::Array_cpp::CPP_LINKED = 0;

        # Array: C++ use, load, link
        lives_ok(
            sub { RPerl::DataStructure::Array_cpp::cpp_load(); },
            q{RPerl::DataStructure::Array_cpp::cpp_load() lives}
        );
        lives_ok(
            sub { RPerl::DataStructure::Array_cpp::cpp_link(); },
            q{RPerl::DataStructure::Array_cpp::cpp_link() lives}
        );
        lives_and(
            sub { is( ops_number(), 'CPP', q{ops_number() returns 'CPP'} ) },
            q{ops_number() lives}
        );
        lives_and(
            sub {
                is( types_number(), 'CPP', q{types_number() returns 'CPP'} );
            },
            q{types_number() lives}
        );
        lives_and(
            sub { is( ops_string(), 'CPP', q{ops_string() returns 'CPP'} ) },
            q{ops_string() lives}
        );
        lives_and(
            sub {
                is( types_string(), 'CPP', q{types_string() returns 'CPP'} );
            },
            q{types_string() lives}
        );
        lives_and(
            sub { is( ops_array(), 'CPP', q{ops_array() returns 'CPP'} ) },
            q{ops_array() lives} );
        lives_and(
            sub { is( types_array(), 'CPP', q{types_array() returns 'CPP'} ) }
            ,    ## PERLTIDY BUG comma on newline
            q{types_array() lives}
        );
    }

    # Int Array: stringify, create, manipulate
    throws_ok(    # AV00
        sub { stringify_int__array_ref(2) },
        "/$OPS_TYPES.*input_av_ref was not an AV ref/",
        q{stringify_int__array_ref(2) throws correct exception}
    );
    lives_and(    # AV01
        sub {
            is( stringify_int__array_ref( [2] ),
                '[2]',
                q{stringify_int__array_ref([2]) returns correct value} );
        },
        q{stringify_int__array_ref([2]) lives}
    );
    lives_and(    # AV02
        sub {
            is( stringify_int__array_ref(
                    [ 2, 2112, 42, 23, 877, 33, 1701 ] ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ),
                '[2, 2112, 42, 23, 877, 33, 1701]',
                q{stringify_int__array_ref([2, 2112, 42, 23, 877, 33, 1701]) returns correct value}
            );
        },
        q{stringify_int__array_ref([2, 2112, 42, 23, 877, 33, 1701]) lives}
    );
    throws_ok(                                         # AV03
        sub {
            stringify_int__array_ref( [ 2, 2112, 42.3, 23, 877, 33, 1701 ] ) ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ;    ## PERLTIDY BUG semicolon on newline
        },
        "/$OPS_TYPES.*input_av_element at index 2 was not an int/",
        q{stringify_int__array_ref([2, 2112, 42.3, 23, 877, 33, 1701]) throws correct exception}
    );
    throws_ok(       # AV04
        sub {
            stringify_int__array_ref( [ 2, 2112, '42', 23, 877, 33, 1701 ] ) ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ;    ## PERLTIDY BUG semicolon on newline
        },
        "/$OPS_TYPES.*input_av_element at index 2 was not an int/",
        q{stringify_int__array_ref([2, 2112, '42', 23, 877, 33, 1701]) throws correct exception}
    );
    lives_and(       # AV10
        sub {
            is( typetest___int__array_ref__in___string__out(
                    [ 2, 2112, 42, 23, 877, 33, 1701 ] ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ),
                '[2, 2112, 42, 23, 877, 33, 1701]' . $OPS_TYPES,
                q{typetest___int__array_ref__in___string__out([2, 2112, 42, 23, 877, 33, 1701]) returns correct value}
            );
        },
        q{typetest___int__array_ref__in___string__out([2, 2112, 42, 23, 877, 33, 1701]) lives}
    );
    throws_ok(                                         # AV11
        sub {
            typetest___int__array_ref__in___string__out(
                [ 2, 2112, 42, 23, 877, "abcdefg\n", 33, 1701 ] ); ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
        },
        "/$OPS_TYPES.*input_av_element at index 5 was not an int/",
        q{typetest___int__array_ref__in___string__out([2, 2112, 42, 23, 877, "abcdefg\n", 33, 1701]) throws correct exception} ## no critic qw(RequireInterpolationOfMetachars)  ## RPERL allow single-quoted newline
    );
    lives_and(    # AV12
        sub {
            is( typetest___int__array_ref__in___string__out(
                    [ 444, 33, 1701 ] ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ),
                '[444, 33, 1701]' . $OPS_TYPES,
                q{typetest___int__array_ref__in___string__out([444, 33, 1701]) returns correct value again, Perl stack still functioning properly}
            );
        },
        q{typetest___int__array_ref__in___string__out([444, 33, 1701]) lives}
    );
    lives_and(                        # AV20
        sub {
            is_deeply(
                typetest___int__in___int__array_ref__out(5), ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                [ 0, 5, 10, 15, 20 ], ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                q{typetest___int__in___int__array_ref__out(5) returns correct value}
            );
        },
        q{typetest___int__in___int__array_ref__out(5) lives}
    );

    # Number Array: stringify, create, manipulate
    throws_ok(                        # AV30
        sub { stringify_number__array_ref(2) },
        "/$OPS_TYPES.*input_av_ref was not an AV ref/",
        q{stringify_number__array_ref(2) throws correct exception}
    );
    lives_and(                        # AV31
        sub {
            is( stringify_number__array_ref( [2] ),
                '[2]',
                q{stringify_number__array_ref([2]) returns correct value} );
        },
        q{stringify_number__array_ref([2]) lives}
    );
    lives_and(                        # AV32
        sub {
            is( stringify_number__array_ref(
                    [ 2, 2112, 42, 23, 877, 33, 1701 ] ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ),
                '[2, 2112, 42, 23, 877, 33, 1701]',
                q{stringify_number__array_ref([2, 2112, 42, 23, 877, 33, 1701]) returns correct value}
            );
        },
        q{stringify_number__array_ref([2, 2112, 42, 23, 877, 33, 1701]) lives}
    );
    lives_and(                                         # AV33
        sub {
            is( stringify_number__array_ref(
                    [ 2.1, 2112.2, 42.3, 23, 877, 33, 1701 ] ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ),
                '[2.1, 2112.2, 42.3, 23, 877, 33, 1701]',
                q{stringify_number__array_ref([2.1, 2112.2, 42.3, 23, 877, 33, 1701]) returns correct value}
            );
        },
        q{stringify_number__array_ref([2.1, 2112.2, 42.3, 23, 877, 33, 1701]) lives}
    );
    lives_and(                                               # AV34
        sub {
            is( stringify_number__array_ref(
                    [   2.1234432112344321, 2112.4321, ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                        42.4567, 23.765444444444444444, ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                        877.5678, 33.876587658765875687658765, ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                        1701.6789 ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                    ]
                ),
                '[2.12344321123443, 2112.4321, 42.4567, 23.7654444444444, 877.5678, 33.8765876587659, 1701.6789]',
                q{stringify_number__array_ref([2.1234432112344321, 2112.4321, 42.4567, 23.765444444444444444, 877.5678, 33.876587658765875687658765, 1701.6789]) returns correct value}
            );
        },
        q{stringify_number__array_ref([2.1234432112344321, 2112.4321, 42.4567, 23.765444444444444444, 877.5678, 33.876587658765875687658765, 1701.6789]) lives}
    );
    throws_ok(                    # AV35
        sub {
            stringify_number__array_ref(
                [ 2, 2112, '42', 23, 877, 33, 1701 ] ); ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
        },
        "/$OPS_TYPES.*input_av_element at index 2 was not a number/",
        q{stringify_number__array_ref([2, 2112, '42', 23, 877, 33, 1701]) throws correct exception}
    );
    lives_and(                                          # AV40
        sub {
            is( typetest___number__array_ref__in___string__out(
                    [   2.1234432112344321, 2112.4321, ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                        42.4567, 23.765444444444444444, ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                        877.5678, 33.876587658765875687658765, ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                        1701.6789 ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                    ]
                ),
                '[2.12344321123443, 2112.4321, 42.4567, 23.7654444444444, 877.5678, 33.8765876587659, 1701.6789]'
                    . $OPS_TYPES,
                q{typetest___number__array_ref__in___string__out([2.1234432112344321, 2112.4321, 42.4567, 23.765444444444444444, 877.5678, 33.876587658765875687658765, 1701.6789]) returns correct value}
            );
        },
        q{typetest___number__array_ref__in___string__out([2.1234432112344321, 2112.4321, 42.4567, 23.765444444444444444, 877.5678, 33.876587658765875687658765, 1701.6789]) lives}
    );
    throws_ok(                    # AV41
        sub {
            typetest___number__array_ref__in___string__out(
                [   2.1234432112344321, 2112.4321, ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                    42.4567, 23.765444444444444444, ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                    877.5678, "abcdefg\n", ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                    33.876587658765875687658765, 1701.6789 ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ]
            );
        },
        "/$OPS_TYPES.*input_av_element at index 5 was not a number/",
        q{typetest___number__array_ref__in___string__out([2.1234432112344321, 2112.4321, 42.4567, 23.765444444444444444, 877.5678, "abcdefg\n", 33.876587658765875687658765, 1701.6789]) throws correct exception} ## no critic qw(RequireInterpolationOfMetachars)  ## RPERL allow single-quoted newline
    );
    lives_and(    # AV50
        sub {
            is_deeply(
                typetest___int__in___number__array_ref__out(5), ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                [ 0, 5.123456789, 10.246913578, 15.370370367, 20.493827156 ] ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ,    ## PERLTIDY BUG comma on newline
                q{typetest___int__in___number__array_ref__out(5) returns correct value}
            );
        },
        q{typetest___int__in___number__array_ref__out(5) lives}
    );

# String Array: stringify, create, manipulate
# DEV NOTE: all single-quotes replaced by double-quotes when passing through stringify, this is because Perl accepts both but C/C++ only accepts double-quotes for strings
    throws_ok(    # AV60
        sub { stringify_string__array_ref('Lone Ranger') },
        "/$OPS_TYPES.*input_av_ref was not an AV ref/",
        q{stringify_string__array_ref('Lone Ranger') throws correct exception}
    );
    lives_and(    # AV61
        sub {
            is( stringify_string__array_ref(
                    [   'Superman',      'Batman',
                        'Wonder Woman',  'Flash',
                        'Green Lantern', 'Aquaman',
                        'Martian Manhunter'
                    ]
                ),
                q{['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter']},
                q{stringify_string__array_ref(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter']) returns correct value}
            );
        },
        q{stringify_string__array_ref(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter']) lives}
    );
    lives_and(    # AV62
        sub {
            is( stringify_string__array_ref(
                    [   'Superman',          'Batman',
                        'Wonder Woman',      'Flash',
                        'Green Lantern',     'Aquaman',
                        'Martian Manhunter', '23'
                    ]
                ),
                q{['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', '23']},
                q{stringify_string__array_ref(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', '23']) returns correct value}
            );
        },
        q{stringify_string__array_ref(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', '23']) lives}
    );
    throws_ok(    # AV63
        sub {
            stringify_string__array_ref(
                [   'Superman',      'Batman',
                    'Wonder Woman',  'Flash',
                    'Green Lantern', 'Aquaman',
                    'Martian Manhunter', 23 ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ]
            );
        },
        "/$OPS_TYPES.*input_av_element at index 7 was not a string/",
        q{stringify_string__array_ref(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', 23]) throws correct exception}
    );
    lives_and(                              # AV64
        sub {
            is( stringify_string__array_ref(
                    [   'Superman',          'Batman',
                        'Wonder Woman',      'Flash',
                        'Green Lantern',     'Aquaman',
                        'Martian Manhunter', '-2112.23'
                    ]
                ),
                q{['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', '-2112.23']},
                q{stringify_string__array_ref(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', '-2112.23']) returns correct value}
            );
        },
        q{stringify_string__array_ref(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', '-2112.23']) lives}
    );
    lives_and(    # AV65
        sub {
            is( stringify_string__array_ref(
                    [   'Superman',      'Batman',
                        'Wonder Woman',  'Flash',
                        'Green Lantern', 'Aquaman',
                        "Martian Manhunter", "-2112.23" ## no critic qw(ProhibitInterpolationOfLiterals)  ## RPERL allow double-quoted test values
                    ]
                ),
                q{['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', '-2112.23']},
                q{stringify_string__array_ref(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', "Martian Manhunter", "-2112.23"]) returns correct value}
            );
        },
        q{stringify_string__array_ref(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', "Martian Manhunter", "-2112.23"]) lives}
    );
    throws_ok(                                          # AV66
        sub {
            stringify_string__array_ref(
                [   'Superman',      'Batman',
                    'Wonder Woman',  'Flash',
                    'Green Lantern', 'Aquaman',
                    'Martian Manhunter', -2112.23 ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ]
            );
        },
        "/$OPS_TYPES.*input_av_element at index 7 was not a string/",
        q{stringify_string__array_ref(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', -2112.23]) throws correct exception}
    );
    throws_ok(                                    # AV67
        sub {
            stringify_string__array_ref(
                [   'Wonder Woman',
                    'Flash',
                    'Green Lantern',
                    'Aquaman',
                    'Martian Manhunter',
                    { fuzz => 'bizz', bar => "stool!\n", bat => 24 }
                ]
            );
        },
        "/$OPS_TYPES.*input_av_element at index 5 was not a string/",
        q{stringify_string__array_ref(['Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', {fuzz => 'bizz', bar => "stool!\n", bat => 24}]) throws correct exception} ## no critic qw(RequireInterpolationOfMetachars)  ## RPERL allow single-quoted newline
    );
    lives_and(    # AV70
        sub {
            is( typetest___string__array_ref__in___string__out(
                    [   'Superman',      'Batman',
                        'Wonder Woman',  'Flash',
                        'Green Lantern', 'Aquaman',
                        'Martian Manhunter'
                    ]
                ),
                q{['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter']}
                    . $OPS_TYPES,
                q{typetest___string__array_ref__in___string__out(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter']) returns correct value}
            );
        },
        q{typetest___string__array_ref__in___string__out(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter']) lives}
    );
    throws_ok(    # AV71
        sub {
            typetest___string__array_ref__in___string__out(
                [   'Superman',      'Batman',
                    'Wonder Woman',  'Flash',
                    'Green Lantern', 'Aquaman',
                    'Martian Manhunter', 23 ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                ]
            );
        },
        "/$OPS_TYPES.*input_av_element at index 7 was not a string/",
        q{typetest___string__array_ref__in___string__out(['Superman', 'Batman', 'Wonder Woman', 'Flash', 'Green Lantern', 'Aquaman', 'Martian Manhunter', 23]) throws correct exception}
    );
    lives_and(                              # AV80
        sub {
            is_deeply(
                typetest___int__in___string__array_ref__out(5), ## no critic qw(ProhibitMagicNumbers)  ## RPERL allow numeric test values
                [   'Jeffy Ten! 0/4 ' . $OPS_TYPES,
                    'Jeffy Ten! 1/4 ' . $OPS_TYPES,
                    'Jeffy Ten! 2/4 ' . $OPS_TYPES,
                    'Jeffy Ten! 3/4 ' . $OPS_TYPES,
                    'Jeffy Ten! 4/4 ' . $OPS_TYPES,
                ],
                q{typetest___int__in___string__array_ref__out(5) returns correct value}
            );
        },
        q{typetest___int__in___string__array_ref__out(5) lives}
    );
}

#done_testing();
