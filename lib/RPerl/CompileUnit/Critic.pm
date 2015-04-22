# [[[ HEADER ]]]
package RPerl::CompileUnit::Critic;
use strict;
use warnings;
use RPerl;
our $VERSION = 0.001_000;

# [[[ OO INHERITANCE ]]]
use parent qw(RPerl::CompileUnit);
use RPerl::CompileUnit;

# [[[ CRITICS ]]]
## no critic qw(ProhibitUselessNoCritic ProhibitMagicNumbers RequireCheckedSyscalls)  # USER DEFAULT 1: allow numeric values & print operator
## no critic qw(RequireInterpolationOfMetachars)  # USER DEFAULT 2: allow single-quoted control characters & sigils

# [[[ OO PROPERTIES ]]]
our hash_ref $properties = {};

# [[[ OO METHODS ]]]

our string__hash_ref__method $ast_to_rperl__generate = sub {
    ( my object $self, my string__hash_ref $modes) = @_;
    my string__hash_ref $rperl_source_group = { PMC => q{} };

#    RPerl::diag( 'in Critic->ast_to_rperl__generate(), received $self = ' . "\n" . RPerl::Parser::rperl_ast__dump($self) . "\n" );
    
    my string $no_critic_qw = $self->{children}->[0];
    my object $critic_words = $self->{children}->[1];
    my string $right_parenthesis = $self->{children}->[2];
    
    $rperl_source_group->{PMC} .= $no_critic_qw;
    foreach my object $critic_word (@{$critic_words->{children}}) {
        $rperl_source_group->{PMC} .= $critic_word->{attr} . ' ';
    }
    chop $rperl_source_group->{PMC};  # remove extra trailing space
    $rperl_source_group->{PMC} .= $right_parenthesis . "\n";

    return $rperl_source_group;
};

our string__hash_ref__method $ast_to_cpp__generate__CPPOPS_PERLTYPES = sub {
    ( my object $self, my string__hash_ref $modes) = @_;
    my string__hash_ref $cpp_source_group
        = { CPP => q{<<< RP::CU::C DUMMY CPPOPS_PERLTYPES SOURCE CODE >>>} . "\n" };

    #...
    return $cpp_source_group;
};

our string__hash_ref__method $ast_to_cpp__generate__CPPOPS_CPPTYPES = sub {
    ( my object $self, my string__hash_ref $modes) = @_;
    my string__hash_ref $cpp_source_group
        = { CPP => q{<<< RP::CU::C DUMMY CPPOPS_PERLTYPES SOURCE CODE >>>}
            . "\n" };

    #...
    return $cpp_source_group;
};

1;    # end of class