////use strict;  use warnings;
using std::cout;  using std::endl;

// VERSION 0.1.4

#ifndef __CPP__INCLUDED__RPerl__DataStructure__Hash_cpp
#define __CPP__INCLUDED__RPerl__DataStructure__Hash_cpp 1

#include <RPerl/DataStructure/Hash.h>		// -> NULL (relies on <unordered_map> being included via Inline::CPP's AUTO_INCLUDE config option)

// convert from (Perl SV containing reference to (Perl HV of (Perl SVs containing IVs))) to (C++ std::unordered_map of ints)
int__hash_ref XS_unpack_int__hash_ref(SV* input_hv_ref)
{
	printf("in CPPOPS_CPPTYPES XS_unpack_int__hash_ref(), top of subroutine\n");

    HV* input_hv;
    int input_hv_num_keys;
    int i;
    HE* input_hv_entry;
    SV* input_hv_key;
    SV* input_hv_value;
    int__hash_ref output_unordered_map;

	if (SvROK(input_hv_ref) && (SvTYPE(SvRV(input_hv_ref)) == SVt_PVHV)) { input_hv = (HV*)SvRV(input_hv_ref); }
	else { croak("in CPPOPS_CPPTYPES XS_unpack_int__hash_ref(), input_hv_ref was not an HV ref, croaking"); }

	input_hv_num_keys = hv_iterinit(input_hv);
	printf("in CPPOPS_CPPTYPES XS_unpack_int__hash_ref(), have input_hv_num_keys = %d\n", input_hv_num_keys);

	// UNORDERED MAP ENTRY ASSIGNMENT, OPTION A, SUBSCRIPT, KNOWN SIZE: unordered_map has programmer-provided const size or compiler-guessable size,
	// reserve() ahead of time to avoid resizing and rehashing in for() loop
	output_unordered_map.reserve((size_t)input_hv_num_keys);

	for (i = 0;  i < input_hv_num_keys;  ++i)  // incrementing iteration, iterator i not actually used in loop body
	{
		// does not utilize i in entry retrieval
		input_hv_entry = hv_iternext(input_hv);

		if (input_hv_entry != NULL)
		{
			input_hv_key = hv_iterkeysv(input_hv_entry);
			input_hv_value = hv_iterval(input_hv, input_hv_entry);

			// UNORDERED MAP ENTRY ASSIGNMENT, OPTION A, SUBSCRIPT, KNOWN SIZE: l-value subscript notation with no further reserve(); does not utilize i in assignment
			if (SvIOKp(input_hv_value)) { output_unordered_map[SvPV_nolen(input_hv_key)] = SvIV(input_hv_value); }
//			else { croak("in CPPOPS_CPPTYPES XS_unpack_int__hash_ref(), input_hv_value '%s' at key '%s' and index %d was not an int, croaking", SvPV_nolen(input_hv_value), SvPV_nolen(input_hv_key), i); }  // index is for internal use, doesn't appear in Pure-Perl output
//			else { croak("in CPPOPS_CPPTYPES XS_unpack_int__hash_ref(), input_hv_value '%s' at key '%s' was not an int, croaking", SvPV_nolen(input_hv_value), SvPV_nolen(input_hv_key), i); }  // values is of unknown type, do not attempt to print
			else { croak("in CPPOPS_CPPTYPES XS_unpack_int__hash_ref(), input_hv_value at key '%s' was not an int, croaking", SvPV_nolen(input_hv_key), i); }
		}
		else { croak("in CPPOPS_CPPTYPES XS_unpack_int__hash_ref(), input_hv_entry at index %d was undef and/or NULL, croaking", i); }
	}

	printf("in CPPOPS_CPPTYPES XS_unpack_int__hash_ref(), after for() loop, have output_unordered_map.size() = %d\n", output_unordered_map.size());
	printf("in CPPOPS_CPPTYPES XS_unpack_int__hash_ref(), bottom of subroutine\n");

	return(output_unordered_map);
}


// convert from (C++ std::unordered_map of ints) to (Perl SV containing reference to (Perl HV of (Perl SVs containing IVs)))
void XS_pack_int__hash_ref(SV* output_hv_ref, int__hash_ref input_unordered_map)
{
	printf("in CPPOPS_CPPTYPES XS_pack_int__hash_ref(), top of subroutine\n");

	HV* output_hv = newHV();  // initialize output hash to empty
	int input_unordered_map_num_keys = input_unordered_map.size();
	int__hash_ref__const_iterator i;
	SV* temp_sv_pointer;

	printf("in CPPOPS_CPPTYPES XS_pack_int__hash_ref(), have input_unordered_map_num_keys = %d\n", input_unordered_map_num_keys);

	if (input_unordered_map_num_keys > 0)
	{
		for (i = input_unordered_map.begin();  i != input_unordered_map.end();  ++i)
			{ hv_store(output_hv, (const char*)((i->first).c_str()), (U32)((i->first).size()), newSViv(i->second), (U32)0); }
	}
	else warn("in CPPOPS_CPPTYPES XS_pack_int__hash_ref(), hash was empty, returning empty hash via newHV()");

	temp_sv_pointer = newSVrv(output_hv_ref, NULL);	  // upgrade output stack SV to an RV
	SvREFCNT_dec(temp_sv_pointer);		 // discard temporary pointer
	SvRV(output_hv_ref) = (SV*)output_hv;	   // make output stack RV point at our output HV

	printf("in CPPOPS_CPPTYPES XS_pack_int__hash_ref(), bottom of subroutine\n");
}


// convert from (Perl SV containing reference to (Perl HV of (Perl SVs containing NVs))) to (C++ std::unordered_map of long doubles)
number__hash_ref XS_unpack_number__hash_ref(SV* input_hv_ref)
{
	printf("in CPPOPS_CPPTYPES XS_unpack_number__hash_ref(), top of subroutine\n");

    HV* input_hv;
    int input_hv_num_keys;
    int i;
    HE* input_hv_entry;
    SV* input_hv_key;
    SV* input_hv_value;
    number__hash_ref output_unordered_map;

	if (SvROK(input_hv_ref) && (SvTYPE(SvRV(input_hv_ref)) == SVt_PVHV)) { input_hv = (HV*)SvRV(input_hv_ref); }
	else { croak("in CPPOPS_CPPTYPES XS_unpack_number__hash_ref(), input_hv_ref was not an HV ref, croaking"); }

	input_hv_num_keys = hv_iterinit(input_hv);
	printf("in CPPOPS_CPPTYPES XS_unpack_number__hash_ref(), have input_hv_num_keys = %d\n", input_hv_num_keys);

	// UNORDERED MAP ENTRY ASSIGNMENT, OPTION A, SUBSCRIPT, KNOWN SIZE: unordered_map has programmer-provided const size or compiler-guessable size,
	// reserve() ahead of time to avoid resizing and rehashing in for() loop
	output_unordered_map.reserve((size_t)input_hv_num_keys);

	for (i = 0;  i < input_hv_num_keys;  ++i)  // incrementing iteration, iterator i not actually used in loop body
	{
		// does not utilize i in entry retrieval
		input_hv_entry = hv_iternext(input_hv);

		if (input_hv_entry != NULL)
		{
			input_hv_key = hv_iterkeysv(input_hv_entry);
			input_hv_value = hv_iterval(input_hv, input_hv_entry);

			// UNORDERED MAP ENTRY ASSIGNMENT, OPTION A, SUBSCRIPT, KNOWN SIZE: l-value subscript notation with no further reserve(); does not utilize i in assignment
			if (SvNOKp(input_hv_value) || SvIOKp(input_hv_value)) { output_unordered_map[SvPV_nolen(input_hv_key)] = SvNV(input_hv_value); }
//			else { croak("in CPPOPS_CPPTYPES XS_unpack_number__hash_ref(), input_hv_value '%s' at key '%s' and index %d was not a number, croaking", SvPV_nolen(input_hv_value), SvPV_nolen(input_hv_key), i); }
			else { croak("in CPPOPS_CPPTYPES XS_unpack_number__hash_ref(), input_hv_value at key '%s' was not a number, croaking", SvPV_nolen(input_hv_key), i); }
		}
		else { croak("in CPPOPS_CPPTYPES XS_unpack_number__hash_ref(), input_hv_entry at index %d was undef and/or NULL, croaking", i); }
	}

	printf("in CPPOPS_CPPTYPES XS_unpack_number__hash_ref(), after for() loop, have output_unordered_map.size() = %d\n", output_unordered_map.size());
	printf("in CPPOPS_CPPTYPES XS_unpack_number__hash_ref(), bottom of subroutine\n");

	return(output_unordered_map);
}


// convert from (C++ std::unordered_map of long doubles) to (Perl SV containing reference to (Perl HV of (Perl SVs containing NVs)))
void XS_pack_number__hash_ref(SV* output_hv_ref, number__hash_ref input_unordered_map)
{
	printf("in CPPOPS_CPPTYPES XS_pack_number__hash_ref(), top of subroutine\n");

	HV* output_hv = newHV();  // initialize output hash to empty
	int input_unordered_map_num_keys = input_unordered_map.size();
	number__hash_ref__const_iterator i;
	SV* temp_sv_pointer;

	printf("in CPPOPS_CPPTYPES XS_pack_number__hash_ref(), have input_unordered_map_num_keys = %d\n", input_unordered_map_num_keys);

	if (input_unordered_map_num_keys > 0)
	{
		for (i = input_unordered_map.begin();  i != input_unordered_map.end();  ++i)
			{ hv_store(output_hv, (const char*)((i->first).c_str()), (U32)((i->first).size()), newSVnv(i->second), (U32)0); }
	}
	else warn("in CPPOPS_CPPTYPES XS_pack_number__hash_ref(), hash was empty, returning empty hash via newHV()");

	temp_sv_pointer = newSVrv(output_hv_ref, NULL);	  // upgrade output stack SV to an RV
	SvREFCNT_dec(temp_sv_pointer);		 // discard temporary pointer
	SvRV(output_hv_ref) = (SV*)output_hv;	   // make output stack RV point at our output HV

	printf("in CPPOPS_CPPTYPES XS_pack_number__hash_ref(), bottom of subroutine\n");
}


// convert from (Perl SV containing reference to (Perl HV of (Perl SVs containing PVs))) to (C++ std::unordered_map of strings)
string__hash_ref XS_unpack_string__hash_ref(SV* input_hv_ref)
{
	printf("in CPPOPS_CPPTYPES XS_unpack_string__hash_ref(), top of subroutine\n");

    HV* input_hv;
    int input_hv_num_keys;
    int i;
    HE* input_hv_entry;
    SV* input_hv_key;
    SV* input_hv_value;
    string__hash_ref output_unordered_map;

	if (SvROK(input_hv_ref) && (SvTYPE(SvRV(input_hv_ref)) == SVt_PVHV)) { input_hv = (HV*)SvRV(input_hv_ref); }
	else { croak("in CPPOPS_CPPTYPES XS_unpack_string__hash_ref(), input_hv_ref was not an HV ref, croaking"); }

	input_hv_num_keys = hv_iterinit(input_hv);
	printf("in CPPOPS_CPPTYPES XS_unpack_string__hash_ref(), have input_hv_num_keys = %d\n", input_hv_num_keys);

	// UNORDERED MAP ENTRY ASSIGNMENT, OPTION A, SUBSCRIPT, KNOWN SIZE: unordered_map has programmer-provided const size or compiler-guessable size,
	// reserve() ahead of time to avoid resizing and rehashing in for() loop
	output_unordered_map.reserve((size_t)input_hv_num_keys);

	for (i = 0;  i < input_hv_num_keys;  ++i)  // incrementing iteration, iterator i not actually used in loop body
	{
		// does not utilize i in entry retrieval
		input_hv_entry = hv_iternext(input_hv);

		if (input_hv_entry != NULL)
		{
			input_hv_key = hv_iterkeysv(input_hv_entry);
			input_hv_value = hv_iterval(input_hv, input_hv_entry);

			// UNORDERED MAP ENTRY ASSIGNMENT, OPTION A, SUBSCRIPT, KNOWN SIZE: l-value subscript notation with no further reserve(); does not utilize i in assignment
			if (SvPOKp(input_hv_value)) { output_unordered_map[SvPV_nolen(input_hv_key)] = SvPV_nolen(input_hv_value); }
//			else { croak("in CPPOPS_CPPTYPES XS_unpack_string__hash_ref(), input_hv_value '%s' at key '%s' and index %d was not a string, croaking", SvPV_nolen(input_hv_value), SvPV_nolen(input_hv_key), i); }
			else { croak("in CPPOPS_CPPTYPES XS_unpack_string__hash_ref(), input_hv_value at key '%s' was not a string, croaking", SvPV_nolen(input_hv_key), i); }
		}
		else { croak("in CPPOPS_CPPTYPES XS_unpack_string__hash_ref(), input_hv_entry at index %d was undef and/or NULL, croaking", i); }
	}

	printf("in CPPOPS_CPPTYPES XS_unpack_string__hash_ref(), after for() loop, have output_unordered_map.size() = %d\n", output_unordered_map.size());
	printf("in CPPOPS_CPPTYPES XS_unpack_string__hash_ref(), bottom of subroutine\n");

	return(output_unordered_map);
}


// convert from (C++ std::unordered_map of strings) to (Perl SV containing reference to (Perl HV of (Perl SVs containing PVs)))
void XS_pack_string__hash_ref(SV* output_hv_ref, string__hash_ref input_unordered_map)
{
	printf("in CPPOPS_CPPTYPES XS_pack_string__hash_ref(), top of subroutine\n");

	HV* output_hv = newHV();  // initialize output hash to empty
	int input_unordered_map_num_keys = input_unordered_map.size();
	string__hash_ref__const_iterator i;
	SV* temp_sv_pointer;

	printf("in CPPOPS_CPPTYPES XS_pack_string__hash_ref(), have input_unordered_map_num_keys = %d\n", input_unordered_map_num_keys);

	if (input_unordered_map_num_keys > 0)
	{
		for (i = input_unordered_map.begin();  i != input_unordered_map.end();  ++i)
			{ hv_store(output_hv, (const char*)((i->first).c_str()), (U32)((i->first).size()), newSVpv((i->second).c_str(), 0), (U32)0); }
	}
	else warn("in CPPOPS_CPPTYPES XS_pack_string__hash_ref(), hash was empty, returning empty hash via newHV()");

	temp_sv_pointer = newSVrv(output_hv_ref, NULL);	  // upgrade output stack SV to an RV
	SvREFCNT_dec(temp_sv_pointer);		 // discard temporary pointer
	SvRV(output_hv_ref) = (SV*)output_hv;	   // make output stack RV point at our output HV

	printf("in CPPOPS_CPPTYPES XS_pack_string__hash_ref(), bottom of subroutine\n");
}


//# [[[ STRINGIFY ]]]
//# [[[ STRINGIFY ]]]
//# [[[ STRINGIFY ]]]

# ifdef __PERL__TYPES

// convert from (Perl SV containing RV to (Perl HV of (Perl SVs containing IVs))) to Perl-parsable (Perl SV containing PV)
SV* stringify_int__hash_ref(SV* input_hv_ref)
{
	printf("in CPPOPS_PERLTYPES stringify_int__hash_ref(), top of subroutine\n");

    HV* input_hv;
    int input_hv_num_keys;
    int i;
    HE* input_hv_entry;
    SV* input_hv_key;
    SV* input_hv_value;
    SV* output_sv = newSV(0);
    bool i_is_0 = 1;

	if (SvROK(input_hv_ref) && (SvTYPE(SvRV(input_hv_ref)) == SVt_PVHV)) { input_hv = (HV*)SvRV(input_hv_ref); }
	else { croak("in CPPOPS_PERLTYPES stringify_int__hash_ref(), input_hv_ref was not an HV ref, croaking"); }

	input_hv_num_keys = hv_iterinit(input_hv);
	printf("in CPPOPS_PERLTYPES stringify_int__hash_ref(), have input_hv_num_keys = %d\n", input_hv_num_keys);

	sv_setpvn(output_sv, "{", 1);

	for (i = 0;  i < input_hv_num_keys;  ++i)  // incrementing iteration, iterator i not actually used in loop body
	{
		// does not utilize i in entry retrieval
		input_hv_entry = hv_iternext(input_hv);

		if (input_hv_entry != NULL)
		{
			input_hv_key = hv_iterkeysv(input_hv_entry);
			input_hv_value = hv_iterval(input_hv, input_hv_entry);

			if (SvIOKp(input_hv_value))
			{
				if (i_is_0)
				{
					sv_catpvf(output_sv, "'%s' => %d", SvPV_nolen(input_hv_key), (int)SvIV(input_hv_value));
					i_is_0 = 0;
				}
				else
				{
					sv_catpvf(output_sv, ", '%s' => %d", SvPV_nolen(input_hv_key), (int)SvIV(input_hv_value));
				}
			}
//			else { croak("in CPPOPS_PERLTYPES stringify_int__hash_ref(), input_hv_value '%s' at key '%s' and index %d was not an int, croaking", SvPV_nolen(input_hv_value), SvPV_nolen(input_hv_key), i); }
			else { croak("in CPPOPS_PERLTYPES stringify_int__hash_ref(), input_hv_value at key '%s' was not an int, croaking", SvPV_nolen(input_hv_key)); }
		}
		else { croak("in CPPOPS_PERLTYPES stringify_int__hash_ref(), input_hv_entry at index %d was undef and/or NULL, croaking", i); }
	}

	sv_catpvn(output_sv, "}", 1);

	printf("in CPPOPS_PERLTYPES stringify_int__hash_ref(), after for() loop, have output_sv =\n%s\n", SvPV_nolen(output_sv));
	printf("in CPPOPS_PERLTYPES stringify_int__hash_ref(), bottom of subroutine\n");

	return(output_sv);
}

// convert from (Perl SV containing RV to (Perl HV of (Perl SVs containing NVs))) to Perl-parsable (Perl SV containing PV)
SV* stringify_number__hash_ref(SV* input_hv_ref)
{
	printf("in CPPOPS_PERLTYPES stringify_number__hash_ref(), top of subroutine\n");

    HV* input_hv;
    int input_hv_num_keys;
    int i;
    HE* input_hv_entry;
    SV* input_hv_key;
    SV* input_hv_value;
    SV* output_sv = newSV(0);
    bool i_is_0 = 1;
	ostringstream temp_stream;
	temp_stream.precision(std::numeric_limits<double>::digits10);

	if (SvROK(input_hv_ref) && (SvTYPE(SvRV(input_hv_ref)) == SVt_PVHV)) { input_hv = (HV*)SvRV(input_hv_ref); }
	else { croak("in CPPOPS_PERLTYPES stringify_number__hash_ref(), input_hv_ref was not an HV ref, croaking"); }

	input_hv_num_keys = hv_iterinit(input_hv);
	printf("in CPPOPS_PERLTYPES stringify_number__hash_ref(), have input_hv_num_keys = %d\n", input_hv_num_keys);

	temp_stream << "{";

	for (i = 0;  i < input_hv_num_keys;  ++i)  // incrementing iteration, iterator i not actually used in loop body
	{
		// does not utilize i in entry retrieval
		input_hv_entry = hv_iternext(input_hv);

		if (input_hv_entry != NULL)
		{
			input_hv_key = hv_iterkeysv(input_hv_entry);
			input_hv_value = hv_iterval(input_hv, input_hv_entry);

			if (SvNOKp(input_hv_value) || SvIOKp(input_hv_value))  // DEV NOTE: cast int to number
			{
				if (i_is_0)
				{
					temp_stream << "'" << SvPV_nolen(input_hv_key) << "' => " << (long double)SvNV(input_hv_value);
					i_is_0 = 0;
				}
				else
				{
					temp_stream << ", '" << SvPV_nolen(input_hv_key) << "' => " << (long double)SvNV(input_hv_value);
				}
			}
//			else { croak("in CPPOPS_PERLTYPES stringify_number__hash_ref(), input_hv_value '%s' at key '%s' and index %d was not a number, croaking", SvPV_nolen(input_hv_value), SvPV_nolen(input_hv_key), i); }
			else { croak("in CPPOPS_PERLTYPES stringify_number__hash_ref(), input_hv_value at key '%s' was not a number, croaking", SvPV_nolen(input_hv_key)); }
		}
		else { croak("in CPPOPS_PERLTYPES stringify_number__hash_ref(), input_hv_entry at index %d was undef and/or NULL, croaking", i); }
	}

	temp_stream << "}";
	sv_setpv(output_sv, (char *)(temp_stream.str().c_str()));

	printf("in CPPOPS_PERLTYPES stringify_number__hash_ref(), after for() loop, have output_sv =\n%s\n", SvPV_nolen(output_sv));
	printf("in CPPOPS_PERLTYPES stringify_number__hash_ref(), bottom of subroutine\n");

	return(output_sv);
}

// convert from (Perl SV containing RV to (Perl HV of (Perl SVs containing PVs))) to Perl-parsable (Perl SV containing PV)
SV* stringify_string__hash_ref(SV* input_hv_ref)
{
	printf("in CPPOPS_PERLTYPES stringify_string__hash_ref(), top of subroutine\n");

    HV* input_hv;
    int input_hv_num_keys;
    int i;
    HE* input_hv_entry;
    SV* input_hv_key;
    SV* input_hv_value;
    SV* output_sv = newSV(0);
    bool i_is_0 = 1;

	if (SvROK(input_hv_ref) && (SvTYPE(SvRV(input_hv_ref)) == SVt_PVHV)) { input_hv = (HV*)SvRV(input_hv_ref); }
	else { croak("in CPPOPS_PERLTYPES stringify_string__hash_ref(), input_hv_ref was not an HV ref, croaking"); }

	input_hv_num_keys = hv_iterinit(input_hv);
	printf("in CPPOPS_PERLTYPES stringify_string__hash_ref(), have input_hv_num_keys = %d\n", input_hv_num_keys);

	sv_setpvn(output_sv, "{", 1);

	for (i = 0;  i < input_hv_num_keys;  ++i)  // incrementing iteration, iterator i not actually used in loop body
	{
		// does not utilize i in entry retrieval
		input_hv_entry = hv_iternext(input_hv);

		if (input_hv_entry != NULL)
		{
			input_hv_key = hv_iterkeysv(input_hv_entry);
			input_hv_value = hv_iterval(input_hv, input_hv_entry);

			if (SvPOKp(input_hv_value))
			{
				if (i_is_0)
				{
					sv_catpvf(output_sv, "'%s' => '%s'", SvPV_nolen(input_hv_key), SvPV_nolen(input_hv_value));
					i_is_0 = 0;
				}
				else
				{
					sv_catpvf(output_sv, ", '%s' => '%s'", SvPV_nolen(input_hv_key), SvPV_nolen(input_hv_value));
				}
			}
//			else { croak("in CPPOPS_PERLTYPES stringify_string__hash_ref(), input_hv_value '%s' at key '%s' and index %d was not a string, croaking", SvPV_nolen(input_hv_value), SvPV_nolen(input_hv_key), i); }
			else { croak("in CPPOPS_PERLTYPES stringify_string__hash_ref(), input_hv_value at key '%s' was not a string, croaking", SvPV_nolen(input_hv_key)); }
		}
		else { croak("in CPPOPS_PERLTYPES stringify_string__hash_ref(), input_hv_entry at index %d was undef and/or NULL, croaking", i); }
	}

	sv_catpvn(output_sv, "}", 1);

	printf("in CPPOPS_PERLTYPES stringify_string__hash_ref(), after for() loop, have output_sv =\n%s\n", SvPV_nolen(output_sv));
	printf("in CPPOPS_PERLTYPES stringify_string__hash_ref(), bottom of subroutine\n");

	return(output_sv);
}

# elif defined __CPP__TYPES

// convert from (C++ std::unordered_map of ints) to Perl-parsable (C++ std::string)
string stringify_int__hash_ref(int__hash_ref input_unordered_map)
{
	printf("in CPPOPS_CPPTYPES stringify_int__hash_ref(), top of subroutine\n");

	ostringstream output_stream;
	int__hash_ref__const_iterator i;
    bool i_is_0 = 1;

	output_stream << '{';

	for (i = input_unordered_map.begin();  i != input_unordered_map.end();  ++i)
	{
		if (i_is_0)
		{
			output_stream << "'" << (i->first).c_str() << "' => " << i->second;
			i_is_0 = 0;
		}
		else
		{
			output_stream << ", '" << (i->first).c_str() << "' => " << i->second;
		}
	}

	output_stream << '}';

	printf("in CPPOPS_CPPTYPES stringify_int__hash_ref(), after for() loop, have output_stream =\n%s\n", (char *)(output_stream.str().c_str()));
	printf("in CPPOPS_CPPTYPES stringify_int__hash_ref(), bottom of subroutine\n");

	return(output_stream.str());
}


// convert from (C++ std::unordered_map of long doubles) to Perl-parsable (C++ std::string)
string stringify_number__hash_ref(number__hash_ref input_unordered_map)
{
	printf("in CPPOPS_CPPTYPES stringify_number__hash_ref(), top of subroutine\n");

	ostringstream output_stream;
	number__hash_ref__const_iterator i;
    bool i_is_0 = 1;

	output_stream.precision(std::numeric_limits<double>::digits10);
	output_stream << '{';

	for (i = input_unordered_map.begin();  i != input_unordered_map.end();  ++i)
	{
		if (i_is_0)
		{
			output_stream << "'" << (i->first).c_str() << "' => " << i->second;
			i_is_0 = 0;
		}
		else
		{
			output_stream << ", '" << (i->first).c_str() << "' => " << i->second;
		}
	}

	output_stream << '}';

	printf("in CPPOPS_CPPTYPES stringify_number__hash_ref(), after for() loop, have output_stream =\n%s\n", (char *)(output_stream.str().c_str()));
	printf("in CPPOPS_CPPTYPES stringify_number__hash_ref(), bottom of subroutine\n");

	return(output_stream.str());
}


// convert from (C++ std::unordered_map of std::strings) to Perl-parsable (C++ std::string)
string stringify_string__hash_ref(string__hash_ref input_unordered_map)
{
	printf("in CPPOPS_CPPTYPES stringify_string__hash_ref(), top of subroutine\n");

	string output_string;
	string__hash_ref__const_iterator i;
    bool i_is_0 = 1;

	output_string = "{";

	for (i = input_unordered_map.begin();  i != input_unordered_map.end();  ++i)
	{
		if (i_is_0)
		{
			output_string += "'" + (string)(i->first).c_str() + "' => " + (string)(i->second);
			i_is_0 = 0;
		}
		else
		{
			output_string += ", '" + (string)(i->first).c_str() + "' => " + (string)(i->second);
		}
	}

	output_string += "}";

	printf("in CPPOPS_CPPTYPES stringify_string__hash_ref(), after for() loop, have output_string =\n%s\n", output_string.c_str());
	printf("in CPPOPS_CPPTYPES stringify_string__hash_ref(), bottom of subroutine\n");

	return(output_string);
}

# else

Purposefully_die_from_a_compile-time_error,_due_to_neither___PERL__TYPES_nor___CPP__TYPES_being_defined.__We_need_to_define_exactly_one!

# endif


//# [[[ TYPE TESTING ]]]
//# [[[ TYPE TESTING ]]]
//# [[[ TYPE TESTING ]]]

# ifdef __PERL__TYPES

SV* typetest___int__hash_ref__in___string__out(SV* lucky_numbers)
{
	HV* lucky_numbers_deref = (HV*)SvRV(lucky_numbers);
	int how_lucky = hv_iterinit(lucky_numbers_deref);
	int i;

	for (i = 0;  i < how_lucky;  ++i)
	{
		HE* lucky_number_entry = hv_iternext(lucky_numbers_deref);

		if (SvIOKp(hv_iterval(lucky_numbers_deref, lucky_number_entry))) {
			printf("in CPPOPS_PERLTYPES Hash::typetest___int__hash_ref__in___string__out(), have lucky number '%s' => %d, BARSTOOL\n",
					SvPV_nolen(hv_iterkeysv(lucky_number_entry)), (int)SvIV(hv_iterval(lucky_numbers_deref, lucky_number_entry)));
		}
//		else { printf("in CPPOPS_PERLTYPES Hash::typetest___int__hash_ref__in___string__out(), have lucky number '%s' => <NOT_AN_INT>, BARSTOOL\n", SvPV_nolen(*hv_iterkeysv(lucky_number_entry))); }
	}

	return(newSVpvf("%s%s", SvPV_nolen(stringify_int__hash_ref(lucky_numbers)), "CPPOPS_PERLTYPES"));
}


SV* typetest___int__in___int__hash_ref__out(int my_size)
{
	HV* output_hv = newHV();
	int i;
	char temp_key[30];

	for (i = 0;  i < my_size;  ++i)
	{
		sprintf(temp_key, "CPPOPS_PERLTYPES_funkey%d", i);
		hv_store(output_hv, (const char*)temp_key, (U32)strlen(temp_key), newSViv(i * 5), (U32)0);
		printf("in CPPOPS_PERLTYPES Hash::typetest___int__in___int__hash_ref__out(), setting entry '%s' => %d, BARBAT\n",
				temp_key, (int)SvIV(*hv_fetch(output_hv, (const char*)temp_key, (U32)strlen(temp_key), (I32)0)));
	}

	return(newRV_noinc((SV*) output_hv));
}


SV* typetest___number__hash_ref__in___string__out(SV* lucky_numbers)
{
	HV* lucky_numbers_deref = (HV*)SvRV(lucky_numbers);
	int how_lucky = hv_iterinit(lucky_numbers_deref);
	int i;

	for (i = 0;  i < how_lucky;  ++i)
	{
		HE* lucky_number_entry = hv_iternext(lucky_numbers_deref);

		if (SvNOKp(hv_iterval(lucky_numbers_deref, lucky_number_entry)) || SvIOKp(hv_iterval(lucky_numbers_deref, lucky_number_entry)))
		{
			printf("in CPPOPS_PERLTYPES Hash::typetest___number__hash_ref__in___string__out(), have lucky number '%s' => %Lf, BARSTOOP\n",
					SvPV_nolen(hv_iterkeysv(lucky_number_entry)), (long double)SvNV(hv_iterval(lucky_numbers_deref, lucky_number_entry)));
		}
//		else { printf("in CPPOPS_PERLTYPES Hash::typetest___number__hash_ref__in___string__out(), have lucky number '%s' => <NOT_A_NUMBER>, BARSTOOP\n", SvPV_nolen(*hv_iterkeysv(lucky_number_entry))); }
	}

	return(newSVpvf("%s%s", SvPV_nolen(stringify_number__hash_ref(lucky_numbers)), "CPPOPS_PERLTYPES"));
}


SV* typetest___int__in___number__hash_ref__out(int my_size)
{
	HV* output_hv = newHV();
	int i;
	char temp_key[30];

	for (i = 0;  i < my_size;  ++i)
	{
		sprintf(temp_key, "CPPOPS_PERLTYPES_funkey%d", i);
		hv_store(output_hv, (const char*)temp_key, (U32)strlen(temp_key), newSVnv(i * 5.123456789), (U32)0);
		printf("in CPPOPS_PERLTYPES Hash::typetest___int__in___number__hash_ref__out(), setting entry '%s' => %Lf, BARTAB\n",
				temp_key, (long double)SvNV(*hv_fetch(output_hv, (const char*)temp_key, (U32)strlen(temp_key), (I32)0)));
	}

	return(newRV_noinc((SV*) output_hv));
}


SV* typetest___string__hash_ref__in___string__out(SV* people)
{
	HV* people_deref = (HV*)SvRV(people);
	int how_crowded = hv_iterinit(people_deref);
	int i;

	for (i = 0;  i < how_crowded;  ++i)
	{
		HE* person_entry = hv_iternext(people_deref);

		if (SvPOKp(hv_iterval(people_deref, person_entry)))
		{
			printf("in CPPOPS_PERLTYPES Hash::typetest___string__hash_ref__in___string__out(), have person '%s' => '%s', BARSPOON\n",
					(char *)SvPV_nolen(hv_iterkeysv(person_entry)), (char *)SvPV_nolen(hv_iterval(people_deref, person_entry)));
		}
//		else { printf("in CPPOPS_PERLTYPES Hash::typetest___string__hash_ref__in___string__out(), have person '%s' => <NOT_A_STRING>, BARSPOON\n", SvPV_nolen(*hv_iterkeysv(person_entry))); }
	}

	return(newSVpvf("%s%s", SvPV_nolen(stringify_string__hash_ref(people)), "CPPOPS_PERLTYPES"));
}


SV* typetest___int__in___string__hash_ref__out(int my_size)
{
	HV* people = newHV();
	int i;
	char temp_key[30];

	for (i = 0;  i < my_size;  ++i)
	{
		sprintf(temp_key, "CPPOPS_PERLTYPES_funkey%d", i);
		hv_store(people, (const char*)temp_key, (U32)strlen(temp_key), newSVpvf("Jeffy Ten! %d/%d CPPOPS_PERLTYPES", i, (my_size - 1)), (U32)0);
		printf("in CPPOPS_PERLTYPES Hash::typetest___int__in___string__hash_ref__out(), have temp_key = '%s', just set another Jeffy, BARTAT\n", temp_key);
	}

	return(newRV_noinc((SV*) people));
}

# elif defined __CPP__TYPES

string typetest___int__hash_ref__in___string__out(int__hash_ref lucky_numbers) { int__hash_ref__const_iterator i;  for (i = lucky_numbers.begin();  i != lucky_numbers.end();  ++i) { printf("in CPPOPS_CPPTYPES Hash::typetest___int__hash_ref__in___string__out(), have lucky number '%s' => %d, BARSTOOL\n", (i->first).c_str(), i->second); }  return(stringify_int__hash_ref(lucky_numbers) + "CPPOPS_CPPTYPES"); }
int__hash_ref typetest___int__in___int__hash_ref__out(int my_size) { int__hash_ref new_unordered_map(my_size);  int i;  string temp_key;  for (i = 0;  i < my_size;  ++i) { temp_key = "CPPOPS_CPPTYPES_funkey" + std::to_string(i);  new_unordered_map[temp_key] = i * 5;  printf("in CPPOPS_CPPTYPES Hash::typetest___int__in___int__hash_ref__out(), setting entry '%s' => %d, BARSTOOL\n", temp_key.c_str(), new_unordered_map[temp_key]); }  return(new_unordered_map); }

//void typetest___number__hash_ref__in___void__out(number__hash_ref lucky_numbers) { number__hash_ref__const_iterator i;  for (i = lucky_numbers.begin();  i != lucky_numbers.end();  ++i) { printf("in CPPOPS_CPPTYPES Hash::typetest___number__hash_ref__in___void__out(), have lucky number '%s' => %Lf, BARSTOOL\n", (i->first).c_str(), i->second); } }
string typetest___number__hash_ref__in___string__out(number__hash_ref lucky_numbers) { number__hash_ref__const_iterator i;  for (i = lucky_numbers.begin();  i != lucky_numbers.end();  ++i) { printf("in CPPOPS_CPPTYPES Hash::typetest___number__hash_ref__in___string__out(), have lucky number '%s' => %Lf, BARSTOOL\n", (i->first).c_str(), i->second); }  return(stringify_number__hash_ref(lucky_numbers) + "CPPOPS_CPPTYPES"); }
number__hash_ref typetest___int__in___number__hash_ref__out(int my_size) { number__hash_ref new_unordered_map(my_size);  int i;  string temp_key;  for (i = 0;  i < my_size;  ++i) { temp_key = "CPPOPS_CPPTYPES_funkey" + std::to_string(i);  new_unordered_map[temp_key] = i * 5.123456789;  printf("in CPPOPS_CPPTYPES Hash::typetest___int__in___number__hash_ref__out(), setting entry '%s' => %Lf, BARSTOOL\n", temp_key.c_str(), new_unordered_map[temp_key]); }  return(new_unordered_map); }

//void typetest___string__hash_ref__in___void__out(string__hash_ref people) { string__hash_ref__const_iterator i;  for (i = people.begin();  i != people.end();  ++i) { printf("in CPPOPS_CPPTYPES Hash::typetest___string__hash_ref__in___void__out(), have person '%s' => '%s', STARBOOL\n", (i->first).c_str(), (i->second).c_str()); } }
string typetest___string__hash_ref__in___string__out(string__hash_ref people) { string__hash_ref__const_iterator i;  for (i = people.begin();  i != people.end();  ++i) { printf("in CPPOPS_CPPTYPES Hash::typetest___string__hash_ref__in___string__out(), have person '%s' => '%s', STARBOOL\n", (i->first).c_str(), (i->second).c_str()); }  return(stringify_string__hash_ref(people) + "CPPOPS_CPPTYPES"); }
string__hash_ref typetest___int__in___string__hash_ref__out(int my_size) { string__hash_ref people;  int i;  people.reserve((size_t)my_size);  for (i = 0;  i < my_size;  ++i) { people["Luker_key" + std::to_string(i)] = "Jeffy Ten! " + std::to_string(i) + "/" + std::to_string(my_size - 1); printf("in CPPOPS_CPPTYPES Hash::typetest___int__in___string__hash_ref__out(), bottom of for() loop, have i = %d, just set another Jeffy!\n", i); }  return(people); }

# endif

#endif