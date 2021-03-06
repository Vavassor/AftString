#include "../Utility/test.h"

#include <float.h>
#include <math.h>

static bool test_default(Test* test)
{
    const uint64_t value = UINT64_C(0xffffffffffffffff);

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_uint64_with_allocator(value, &format, &test->allocator);

    const char* reference = "18446744073709551615";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_double(Test* test)
{
    const double value = 789.04;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "789.04";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_double_big(Test* test)
{
    const double value = 789040000000000000000.0;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "789040000000000000000";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_double_infinity(Test* test)
{
    const double value = -HUGE_VAL;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = u8"-∞";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_double_max(Test* test)
{
    const double value = DBL_MAX;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "168738177180919299881250404026184124858368";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_double_nan(Test* test)
{
    const double value = NAN;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "NaN";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_double_one(Test* test)
{
    const double value = 1.0;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "1";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_double_small(Test* test)
{
    const double value = 0.00000000000078904;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "0";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_double_zero(Test* test)
{
    const double value = 0.0;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "0";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_float_infinity(Test* test)
{
    const float value = -HUGE_VALF;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_float_with_allocator(value, &format, &test->allocator);

    const char* reference = u8"-∞";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_float_max(Test* test)
{
    const float value = FLT_MAX;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_float_with_allocator(value, &format, &test->allocator);

    const char* reference = "340282346638528859811704183484516925440";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_float_nan(Test* test)
{
    const float value = NAN;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_float_with_allocator(value, &format, &test->allocator);

    const char* reference = "NaN";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_int(Test* test)
{
    const int value = -7;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_int_with_allocator(value, &format, &test->allocator);

    const char* reference = "-7";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_int64(Test* test)
{
    const int64_t value = INT64_C(-9223372036854775807) - 1;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_int64_with_allocator(value, &format, &test->allocator);

    const char* reference = "-9223372036854775808";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_scientific_double(Test* test)
{
    const double value = 789.04;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_scientific_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "7.89E2";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_scientific_double_small(Test* test)
{
    const double value = 0.00000000000078904;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_scientific_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "7.89E-13";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_default_scientific_int(Test* test)
{
    const int value = 78940000;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_scientific_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_int_with_allocator(value, &format, &test->allocator);

    const char* reference = "7.894E7";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_double_max(Test* test)
{
    const double value = DBL_MAX;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.max_integer_digits = 309;
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference =
            "179769313486231570814527423731704356798070567525844996598917476803"
            "157260780028538760589558632766878171540458953514382464234321326889"
            "464182768467546703537516986049910576551282076245490090389328944075"
            "868508455133942304583236903222948165808559332123348274797826204144"
            "723168738177180919299881250404026184124858368";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_group_double(Test* test)
{
    const double values[2] = {7980400000000.14, 7980400000000.0};
    const char* references[2] = {"798,040,000,0000.14", "798,040,000,0000"};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.use_grouping = true;
    format.primary_grouping_size = 4;
    format.secondary_grouping_size = 3;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 2; case_index += 1)
    {
        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        result = result && string.valid && strings_match(references[case_index], contents);

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_hexadecimal(Test* test)
{
    const uint64_t value = UINT64_C(0xffffffffffffffff);

    AftBaseFormat format =
    {
        .base = 16,
        .use_uppercase = false,
    };
    AftMaybeString string = aft_ascii_from_uint64_with_allocator(value, &format, &test->allocator);

    const char* reference = "ffffffffffffffff";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);

    return result;
}

static bool test_max_fraction_digits_double(Test* test)
{
    const double value = 0.00000000000078904;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.max_fraction_digits = 17;
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "0.00000000000078904";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_max_integer_digits(Test* test)
{
    const int value = 123456789;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.max_integer_digits = 4;
    format.use_grouping = true;

    AftMaybeString string = aft_string_from_int_with_allocator(value, &format, &test->allocator);

    const char* reference = "6,789";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_max_integer_digits_double(Test* test)
{
    const double values[2] = {4124378904.041, 4124378904.0};
    const char* references[2] = {"2,437,8904.041", "2,437,8904"};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.min_integer_digits = 1;
    format.max_integer_digits = 8;
    format.use_grouping = true;
    format.primary_grouping_size = 4;
    format.secondary_grouping_size = 3;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 2; case_index += 1)
    {
        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_max_significant_digits(Test* test)
{
    const int value = 123456789;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.use_significant_digits = true;
    format.max_significant_digits = 4;
    format.min_significant_digits = 0;
    format.use_grouping = true;

    AftMaybeString string = aft_string_from_int_with_allocator(value, &format, &test->allocator);

    const char* reference = "123,400,000";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_min_fraction_digits(Test* test)
{
    const int value = 1234;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.min_fraction_digits = 3;

    AftMaybeString string = aft_string_from_int_with_allocator(value, &format, &test->allocator);

    const char* reference = "1234.000";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_min_fraction_digits_double(Test* test)
{
    const double values[3] = {0.78904, 1.78904, 78904.0};
    const char* references[3] = {"0.78904000", "1.78904000", "78904.00000000"};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.min_fraction_digits = 8;
    format.max_fraction_digits = 15;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 3; case_index += 1)
    {
        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_min_fraction_digits_scientific_double(Test* test)
{
    const double value = 0.00000000000078904;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_scientific_with_allocator(&format, &test->allocator);
    format.max_fraction_digits = 12;
    format.min_fraction_digits = 8;
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "7.89040000E-13";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}


static bool test_min_integer_digits(Test* test)
{
    const int value = 1234;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.min_integer_digits = 7;
    format.use_grouping = true;
    format.primary_grouping_size = 2;

    AftMaybeString string = aft_string_from_int_with_allocator(value, &format, &test->allocator);

    const char* reference = "00,012,34";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_min_integer_digits_double(Test* test)
{
    const double values[2] = {7890400.14, 7890400.0};
    const char* references[2] = {"000,789,0400.14", "000,789,0400"};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.min_integer_digits = 10;
    format.use_grouping = true;
    format.primary_grouping_size = 4;
    format.secondary_grouping_size = 3;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 2; case_index += 1)
    {
        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_min_significant_digits_int(Test* test)
{
    const int value = 123456789;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.use_significant_digits = true;
    format.max_significant_digits = 14;
    format.min_significant_digits = 14;
    format.use_grouping = true;

    AftMaybeString string = aft_string_from_int_with_allocator(value, &format, &test->allocator);

    const char* reference = "123,456,789.00000";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_min_significant_digits_double(Test* test)
{
    const double values[3] = {0.78904, 1.78904, 78904.0};
    const char* references[3] = {"0.78904000", "1.7890400", "78904.000"};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.use_significant_digits = true;
    format.min_significant_digits = 8;
    format.max_significant_digits = 15;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 3; case_index += 1)
    {
        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_min_significant_digits_scientific_double(Test* test)
{
    const double value = 0.00000000000078904;

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_scientific_with_allocator(&format, &test->allocator);
    format.use_significant_digits = true;
    format.max_significant_digits = 12;
    format.min_significant_digits = 7;
    ASSERT(defaulted);

    AftMaybeString string = aft_string_from_double_with_allocator(value, &format, &test->allocator);

    const char* reference = "7.890400E-13";
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(reference, contents);

    aft_string_destroy(&string.value);
    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_ceiling_double(Test* test)
{
    const double values[9] = {-1.0, -0.9999, -0.1875, -0.0002, 0.0, 0.0002, 0.1875, 0.9999, 1.0};
    const char* references[9] = {"-1", "-0.999", "-0.187", "0", "0", "0.001", "0.188", "1", "1"};
    const double increments[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_CEILING;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 9; case_index += 1)
    {
        format.rounding_increment_double = increments[case_index];

        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        result = result
                && string.valid
                && strings_match(references[case_index], contents);

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_ceiling_int(Test* test)
{
    const int values[11] = {20, 22, 24, 26, 28, 0, -20, -22, -24, -26, -28};
    const char* references[11] = {"24", "24", "24", "32", "32", "0", "-16", "-16", "-24", "-24", "-24"};
    const int increments[11] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_CEILING;

    bool result = true;

    for(int case_index = 0; case_index < 11; case_index += 1)
    {
        format.rounding_increment_int = increments[case_index];

        AftMaybeString string = aft_string_from_int_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_down_double(Test* test)
{
    const double values[9] = {-1.0, -0.9999, -0.1875, -0.0002, 0.0, 0.0002, 0.1875, 0.9999, 1.0};
    const char* references[9] = {"-1", "-0.999", "-0.187", "0", "0", "0", "0.187", "0.999", "1"};
    const double increments[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_DOWN;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 9; case_index += 1)
    {
        format.rounding_increment_double = increments[case_index];

        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        result = result
                && string.valid
                && strings_match(references[case_index], contents);

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_down_int(Test* test)
{
    const int values[11] = {20, 22, 24, 26, 28, 0, -20, -22, -24, -26, -28};
    const char* references[11] = {"16", "16", "24", "24", "24", "0", "-16", "-16", "-24", "-24", "-24"};
    const int increments[11] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_DOWN;

    bool result = true;

    for(int case_index = 0; case_index < 11; case_index += 1)
    {
        format.rounding_increment_int = increments[case_index];

        AftMaybeString string = aft_string_from_int_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_floor_double(Test* test)
{
    const double values[9] = {-1.0, -0.9999, -0.1875, -0.0002, 0.0, 0.0002, 0.1875, 0.9999, 1.0};
    const char* references[9] = {"-1", "-1", "-0.188", "-0.001", "0", "0", "0.187", "0.999", "1"};
    const double increments[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_FLOOR;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 9; case_index += 1)
    {
        format.rounding_increment_double = increments[case_index];

        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        result = result
                && string.valid
                && strings_match(references[case_index], contents);

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_floor_int(Test* test)
{
    const int values[11] = {20, 22, 24, 26, 28, 0, -20, -22, -24, -26, -28};
    const char* references[11] = {"16", "16", "24", "24", "24", "0", "-24", "-24", "-24", "-32", "-32"};
    const int increments[11] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_FLOOR;

    bool result = true;

    for(int case_index = 0; case_index < 11; case_index += 1)
    {
        format.rounding_increment_int = increments[case_index];

        AftMaybeString string = aft_string_from_int_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_half_down_double(Test* test)
{
    const double values[9] = {-1.0, -0.9999, -0.1875, -0.0002, 0.0, 0.0002, 0.1875, 0.9999, 1.0};
    const char* references[9] = {"-1", "-1", "-0.187", "0", "0", "0", "0.187", "1", "1"};
    const double increments[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_HALF_DOWN;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 9; case_index += 1)
    {
        format.rounding_increment_double = increments[case_index];

        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        result = result
                && string.valid
                && strings_match(references[case_index], contents);

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_half_down_int(Test* test)
{
    const int values[11] = {20, 22, 24, 26, 28, 0, -20, -22, -24, -26, -28};
    const char* references[11] = {"16", "24", "24", "24", "24", "0","-16", "-24", "-24", "-24", "-24"};
    const int increments[11] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_HALF_DOWN;

    bool result = true;

    for(int case_index = 0; case_index < 11; case_index += 1)
    {
        format.rounding_increment_int = increments[case_index];

        AftMaybeString string = aft_string_from_int_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_half_even_double(Test* test)
{
    const double values[9] = {-1.0, -0.9999, -0.1875, -0.0002, 0.0, 0.0002, 0.1875, 0.9999, 1.0};
    const char* references[9] = {"-1", "-1", "-0.188", "0", "0", "0", "0.188", "1", "1"};
    const double increments[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 6; case_index += 1)
    {
        format.rounding_increment_double = increments[case_index];

        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        result = result
                && string.valid
                && strings_match(references[case_index], contents);

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_half_even_int(Test* test)
{
    const int values[9] = {20, 24, 28, 32, 0, -20, -24, -28, -32};
    const char* references[9] = {"16", "24", "32", "32", "0", "-16", "-24", "-32", "-32"};
    const int increments[9] = {8, 8, 8, 8, 8, 8, 8, 8, 8};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 9; case_index += 1)
    {
        format.rounding_increment_int = increments[case_index];

        AftMaybeString string = aft_string_from_int_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_half_up_double(Test* test)
{
    const double values[9] = {-1.0, -0.9999, -0.1875, -0.0002, 0.0, 0.0002, 0.1875, 0.9999, 1.0};
    const char* references[9] = {"-1", "-1", "-0.188", "0", "0", "0", "0.188", "1", "1"};
    const double increments[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_HALF_UP;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 9; case_index += 1)
    {
        format.rounding_increment_double = increments[case_index];

        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        result = result
                && string.valid
                && strings_match(references[case_index], contents);

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_half_up_int(Test* test)
{
    const int values[7] = {20, 24, 28, 0, -20, -24, -28};
    const char* references[7] = {"24", "24", "32", "0", "-24", "-24", "-32"};
    const int increments[7] = {8, 8, 8, 8, 8, 8, 8};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_HALF_UP;

    bool result = true;

    for(int case_index = 0; case_index < 7; case_index += 1)
    {
        format.rounding_increment_int = increments[case_index];

        AftMaybeString string = aft_string_from_int_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_up_double(Test* test)
{
    const double values[9] = {-1.0, -0.9999, -0.1875, -0.0002, 0.0, 0.0002, 0.1875, 0.9999, 1.0};
    const char* references[9] = {"-1", "-1", "-0.188", "-0.001", "0", "0.001", "0.188", "1", "1"};
    const double increments[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_UP;
    ASSERT(defaulted);

    bool result = true;

    for(int case_index = 0; case_index < 9; case_index += 1)
    {
        format.rounding_increment_double = increments[case_index];

        AftMaybeString string = aft_string_from_double_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        result = result
                && string.valid
                && strings_match(references[case_index], contents);

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

static bool test_round_up_int(Test* test)
{
    const int values[11] = {20, 22, 24, 26, 28, 0, -20, -22, -24, -26, -28};
    const char* references[11] = {"24", "24", "24", "32", "32", "0", "-24", "-24", "-24", "-32", "-32"};
    const int increments[11] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

    AftDecimalFormat format;
    bool defaulted = aft_decimal_format_default_with_allocator(&format, &test->allocator);
    ASSERT(defaulted);
    format.rounding_mode = AFT_DECIMAL_FORMAT_ROUNDING_MODE_UP;

    bool result = true;

    for(int case_index = 0; case_index < 11; case_index += 1)
    {
        format.rounding_increment_int = increments[case_index];

        AftMaybeString string = aft_string_from_int_with_allocator(values[case_index], &format, &test->allocator);

        const char* contents = aft_string_get_contents_const(&string.value);
        bool contents_match = strings_match(references[case_index], contents);
        result = result && string.valid && contents_match;

        aft_string_destroy(&string.value);
    }

    aft_decimal_format_destroy(&format);

    return result;
}

int main(int argc, const char** argv)
{
    Suite suite = {0};

    add_test(&suite, test_default, "Test Default");
    add_test(&suite, test_default_double, "Test Default double");
    add_test(&suite, test_default_double_big, "Test Default double Big");
    add_test(&suite, test_default_double_infinity, "Test Default double Infinity");
    add_test(&suite, test_default_double_max, "Test Default double Max");
    add_test(&suite, test_default_double_nan, "Test Default double NaN");
    add_test(&suite, test_default_double_one, "Test Default double One");
    add_test(&suite, test_default_double_small, "Test Default double Small");
    add_test(&suite, test_default_double_zero, "Test Default double Zero");
    add_test(&suite, test_default_float_infinity, "Test Default float Infinity");
    add_test(&suite, test_default_float_max, "Test Default float Max");
    add_test(&suite, test_default_float_nan, "Test Default float NaN");
    add_test(&suite, test_default_int, "Test Default int");
    add_test(&suite, test_default_int64, "Test Default int64_t");
    add_test(&suite, test_default_scientific_double, "Test Default Scientific double");
    add_test(&suite, test_default_scientific_double_small, "Test Default Scientific double Small");
    add_test(&suite, test_default_scientific_int, "Test Default Scientific int");
    add_test(&suite, test_double_max, "Test double Max");
    add_test(&suite, test_group_double, "Test Group Double");
    add_test(&suite, test_hexadecimal, "Test Hexadecimal");
    add_test(&suite, test_max_fraction_digits_double, "Test Max Fraction Digits double");
    add_test(&suite, test_max_integer_digits, "Test Max Integer Digits");
    add_test(&suite, test_max_integer_digits_double, "Test Max Integer Digits double");
    add_test(&suite, test_max_significant_digits, "Test Max Significant Digits");
    add_test(&suite, test_min_fraction_digits, "Test Min Fraction Digits");
    add_test(&suite, test_min_fraction_digits_double, "Test Min Fraction Digits double");
    add_test(&suite, test_min_fraction_digits_scientific_double, "Test Min Fraction Digits Scientific double");
    add_test(&suite, test_min_integer_digits, "Test Min Integer Digits");
    add_test(&suite, test_min_integer_digits_double, "Test Min Integer Digits double");
    add_test(&suite, test_min_significant_digits_int, "Test Min Significant Digits int");
    add_test(&suite, test_min_significant_digits_double, "Test Min Significant Digits double");
    add_test(&suite, test_min_significant_digits_scientific_double, "Test Min Significant Digits Scientific double");
    add_test(&suite, test_round_ceiling_double, "Test Round Ceiling double");
    add_test(&suite, test_round_ceiling_int, "Test Round Ceiling int");
    add_test(&suite, test_round_down_double, "Test Round Down double");
    add_test(&suite, test_round_down_int, "Test Round Down int");
    add_test(&suite, test_round_floor_double, "Test Round Floor double");
    add_test(&suite, test_round_floor_int, "Test Round Floor int");
    add_test(&suite, test_round_half_down_double, "Test Round Half Down double");
    add_test(&suite, test_round_half_down_int, "Test Round Half Down int");
    add_test(&suite, test_round_half_even_double, "Test Round Half Even double");
    add_test(&suite, test_round_half_even_int, "Test Round Half Even int");
    add_test(&suite, test_round_half_up_double, "Test Round Half Up double");
    add_test(&suite, test_round_half_up_int, "Test Round Half Up int");
    add_test(&suite, test_round_up_double, "Test Round Up double");
    add_test(&suite, test_round_up_int, "Test Round Up int");

    bool success = run_tests(&suite);
    return !success;
}
