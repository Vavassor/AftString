#include "../Utility/test.h"


static bool fuzz_assign(Test* test)
{
    AftMaybeString garble =
            make_random_string(&test->generator, &test->allocator);
    ASSERT(garble.valid);

    AftString string;
    aft_string_initialise_with_allocator(&string, &test->allocator);
    bool assigned = aft_string_assign(&string, &garble.value);

    bool matched = aft_strings_match(&garble.value, &string);

    bool destroyed_garble = aft_string_destroy(&garble.value);
    bool destroyed_string = aft_string_destroy(&string);
    ASSERT(destroyed_garble);
    ASSERT(destroyed_string);

    return assigned && matched;
}

static bool test_add_end(Test* test)
{
    const char* chicken = u8"курица";
    const char* egg = u8"蛋";

    AftMaybeString outer = aft_string_copy_c_string_with_allocator(chicken, &test->allocator);
    AftStringSlice inner = aft_string_slice_from_c_string(egg);
    ASSERT(outer.valid);

    bool combined = aft_string_add(&outer.value, inner, string_size(chicken));
    ASSERT(combined);

    const char* contents = aft_string_get_contents_const(&outer.value);
    bool contents_match = strings_match(contents, u8"курица蛋");
    bool size_correct = aft_string_get_count(&outer.value) == string_size(contents);
    bool result = contents_match && size_correct;

    aft_string_destroy(&outer.value);

    return result;
}

static bool test_add_middle(Test* test)
{
    const char* chicken = u8"курица";
    const char* egg = u8"蛋";

    AftMaybeString outer = aft_string_copy_c_string_with_allocator(chicken, &test->allocator);
    AftStringSlice inner = aft_string_slice_from_c_string(egg);
    ASSERT(outer.valid);

    bool combined = aft_string_add(&outer.value, inner, 4);
    ASSERT(combined);

    const char* contents = aft_string_get_contents_const(&outer.value);
    bool contents_match = strings_match(contents, u8"ку蛋рица");
    bool size_correct = aft_string_get_count(&outer.value) == string_size(contents);
    bool result = contents_match && size_correct;

    aft_string_destroy(&outer.value);

    return result;
}

static bool test_add_self_middle(Test* test)
{
    const char* chicken = u8"курица";

    AftMaybeString string = aft_string_copy_c_string_with_allocator(chicken, &test->allocator);
    ASSERT(string.valid);
    AftStringSlice slice = aft_string_slice_from_string(&string.value);

    bool combined = aft_string_add(&string.value, slice, 4);
    ASSERT(combined);

    const char* contents = aft_string_get_contents_const(&string.value);
    bool contents_match = strings_match(contents, u8"кукурицарица");
    bool size_correct = aft_string_get_count(&string.value) == string_size(contents);
    bool result = contents_match && size_correct;

    aft_string_destroy(&string.value);

    return result;
}

static bool test_add_start(Test* test)
{
    const char* chicken = u8"курица";
    const char* egg = u8"蛋";

    AftMaybeString outer = aft_string_copy_c_string_with_allocator(chicken, &test->allocator);
    AftStringSlice inner = aft_string_slice_from_c_string(egg);
    ASSERT(outer.valid);

    bool combined = aft_string_add(&outer.value, inner, 0);
    ASSERT(combined);

    const char* contents = aft_string_get_contents_const(&outer.value);
    bool contents_match = strings_match(contents, u8"蛋курица");
    bool size_correct = aft_string_get_count(&outer.value) == string_size(contents);
    bool result = contents_match && size_correct;

    aft_string_destroy(&outer.value);

    return result;
}

static bool test_append(Test* test)
{
    const char* a = u8"a猫🍌";
    const char* b = u8"a猫🍌";
    AftMaybeString base =
            aft_string_copy_c_string_with_allocator(a, &test->allocator);
    AftMaybeString extension =
                aft_string_copy_c_string_with_allocator(b, &test->allocator);
    ASSERT(base.valid);
    ASSERT(extension.valid);

    bool appended = aft_string_append(&base.value, &extension.value);
    ASSERT(appended);

    const char* combined = aft_string_get_contents_const(&base.value);
    bool contents_match = strings_match(combined, u8"a猫🍌a猫🍌");
    bool size_correct =
            aft_string_get_count(&base.value) == string_size(combined);
    bool result = contents_match && size_correct;

    aft_string_destroy(&base.value);
    aft_string_destroy(&extension.value);

    return result;
}

static bool test_append_nothing(Test* test)
{
    const char* a = "a";
    AftMaybeString base =
            aft_string_copy_c_string_with_allocator(a, &test->allocator);
    ASSERT(base.valid);

    AftString extension;
    aft_string_initialise_with_allocator(&extension, &test->allocator);

    bool appended = aft_string_append(&base.value, &extension);
    ASSERT(appended);

    const char* combined = aft_string_get_contents_const(&base.value);
    bool contents_match = strings_match(combined, a);
    bool size_correct =
            aft_string_get_count(&base.value) == string_size(combined);
    bool result = contents_match && size_correct;

    aft_string_destroy(&base.value);
    aft_string_destroy(&extension);

    return result;
}

static bool test_append_nothing_to_nothing(Test* test)
{
    AftString base;
    aft_string_initialise_with_allocator(&base, &test->allocator);
    AftString extension;
    aft_string_initialise_with_allocator(&extension, &test->allocator);

    bool appended = aft_string_append(&base, &extension);
    ASSERT(appended);

    const char* combined = aft_string_get_contents_const(&base);
    bool size_correct =
            aft_string_get_count(&base) == string_size(combined);
    bool result = size_correct;

    aft_string_destroy(&base);
    aft_string_destroy(&extension);

    return result;
}

static bool test_append_self(Test* test)
{
    const char* a = u8"a猫🍌";
    AftMaybeString base =
            aft_string_copy_c_string_with_allocator(a, &test->allocator);
    ASSERT(base.valid);

    bool appended = aft_string_append(&base.value, &base.value);
    ASSERT(appended);

    const char* combined = aft_string_get_contents_const(&base.value);
    bool contents_match = strings_match(combined, u8"a猫🍌a猫🍌");
    bool size_correct =
            aft_string_get_count(&base.value) == string_size(combined);
    bool result = contents_match && size_correct;

    aft_string_destroy(&base.value);

    return result;
}

static bool test_append_to_nothing(Test* test)
{
    const char* b = "a";
    AftString base;
    aft_string_initialise_with_allocator(&base, &test->allocator);

    AftMaybeString extension =
            aft_string_copy_c_string_with_allocator(b, &test->allocator);
    ASSERT(extension.valid);

    bool appended = aft_string_append(&base, &extension.value);
    ASSERT(appended);

    const char* combined = aft_string_get_contents_const(&base);
    bool contents_match = strings_match(combined, b);
    bool size_correct = aft_string_get_count(&base) == string_size(combined);
    bool result = contents_match && size_correct;

    aft_string_destroy(&base);
    aft_string_destroy(&extension.value);

    return result;
}

static bool test_append_c_string(Test* test)
{
    const char* a = u8"👌🏼";
    const char* b = u8"🙋🏾‍♀️";
    AftMaybeString base =
            aft_string_copy_c_string_with_allocator(a, &test->allocator);
    ASSERT(base.valid);

    bool appended = aft_string_append_c_string(&base.value, b);
    ASSERT(appended);

    const char* combined = aft_string_get_contents_const(&base.value);
    bool contents_match = strings_match(combined, u8"👌🏼🙋🏾‍♀️");
    bool size_correct =
            aft_string_get_count(&base.value) == string_size(combined);
    bool result = contents_match && size_correct;

    aft_string_destroy(&base.value);

    return result;
}

static bool test_append_char(Test* test)
{
    const char* a = u8"👌🏼";
    AftMaybeString base = aft_string_copy_c_string_with_allocator(a, &test->allocator);
    ASSERT(base.valid);

    bool appended = aft_string_append_char(&base.value, 'Z');
    ASSERT(appended);

    const char* combined = aft_string_get_contents_const(&base.value);
    bool contents_match = strings_match(combined, u8"👌🏼Z");
    bool size_correct = aft_string_get_count(&base.value) == string_size(combined);
    bool result = contents_match && size_correct;

    aft_string_destroy(&base.value);

    return result;
}

static bool test_assign(Test* test)
{
    const char* reference = u8"a猫🍌";
    AftMaybeString original =
            aft_string_copy_c_string_with_allocator(reference,
                    &test->allocator);

    AftString string;
    aft_string_initialise_with_allocator(&string, &test->allocator);
    bool assigned = aft_string_assign(&string, &original.value);

    bool matched = aft_strings_match(&original.value, &string);

    bool destroyed_original = aft_string_destroy(&original.value);
    bool destroyed_string = aft_string_destroy(&string);
    ASSERT(destroyed_original);
    ASSERT(destroyed_string);

    return assigned && matched;
}

static bool test_assign_self(Test* test)
{
    const char* reference = u8"a猫🍌";
    AftMaybeString string =
            aft_string_copy_c_string_with_allocator(reference,
                    &test->allocator);

    bool assigned = aft_string_assign(&string.value, &string.value);

    const char* contents = aft_string_get_contents_const(&string.value);
    bool contents_match = strings_match(contents, reference);
    bool size_correct =
            aft_string_get_count(&string.value) == string_size(reference);
    bool result = assigned && contents_match;

    aft_string_destroy(&string.value);

    return result;
}

static bool test_assign_nothing(Test* test)
{
    const char* reference = u8"a猫🍌";
    AftMaybeString string =
                aft_string_copy_c_string_with_allocator(reference,
                        &test->allocator);
    AftString empty;
    aft_string_initialise_with_allocator(&empty, &test->allocator);
    ASSERT(string.valid);

    bool assigned = aft_string_assign(&string.value, &empty);
    ASSERT(assigned);

    const char* contents =
                aft_string_get_contents_const(&string.value);
    bool no_contents = strings_match(contents, "");
    bool size_correct = aft_string_get_count(&string.value) == 0;
    bool allocator_intact = string.value.allocator == empty.allocator;
    bool result = no_contents && size_correct && allocator_intact;

    aft_string_destroy(&string.value);
    aft_string_destroy(&empty);

    return result;
}

static bool test_copy(Test* test)
{
    const char* reference = u8"a猫🍌";

    AftMaybeString original = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    AftMaybeString copy = aft_string_copy_with_allocator(&original.value, &test->allocator);
    ASSERT(original.valid);
    ASSERT(copy.valid);

    const char* original_contents = aft_string_get_contents_const(&original.value);
    const char* copy_contents = aft_string_get_contents_const(&copy.value);

    int original_count = aft_string_get_count(&original.value);
    int copy_count = aft_string_get_count(&copy.value);
    bool size_correct = original_count == copy_count;
    bool result = strings_match(original_contents, copy_contents)
            && size_correct;

    aft_string_destroy(&original.value);
    aft_string_destroy(&copy.value);

    return result;
}

static bool test_copy_c_string(Test* test)
{
    const char* reference = u8"a猫🍌";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    const char* contents = aft_string_get_contents_const(&string.value);

    bool result = string.valid && strings_match(contents, reference);

    aft_string_destroy(&string.value);

    return result;
}

static bool test_copy_c_string_empty(Test* test)
{
    const char* reference = "";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);

    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = string.valid && strings_match(contents, reference);

    aft_string_destroy(&string.value);

    return result;
}

static bool test_destroy(Test* test)
{
    const char* reference = "Moist";
    AftMaybeString original =
            aft_string_copy_c_string_with_allocator(reference,
                    &test->allocator);
    ASSERT(original.valid);

    bool destroyed = aft_string_destroy(&original.value);

    int post_count = aft_string_get_count(&original.value);

    return destroyed
            && post_count == 0
            && original.value.allocator == &test->allocator;
}

static bool test_ends_with(Test* test)
{
    const char* a = u8"Wow a猫🍌";
    const char* b = u8"a猫🍌";
    AftStringSlice string = aft_string_slice_from_c_string(a);
    AftStringSlice ending = aft_string_slice_from_c_string(b);

    bool result = aft_string_slice_ends_with(string, ending);

    return result;
}

static bool test_ends_with_missing(Test* test)
{
    const char* a = u8"Wow a猫🍌";
    const char* b = u8"猫";
    AftStringSlice string = aft_string_slice_from_c_string(a);
    AftStringSlice ending = aft_string_slice_from_c_string(b);

    bool result = !aft_string_slice_ends_with(string, ending);

    return result;
}

static bool test_ends_with_nothing(Test* test)
{
    const char* a = u8"a猫🍌";
    AftStringSlice string = aft_string_slice_from_c_string(a);
    AftStringSlice ending = aft_string_slice_from_c_string("");

    bool result = aft_string_slice_ends_with(string, ending);

    return result;
}

static bool test_ends_with_self(Test* test)
{
    const char* a = u8"a猫🍌";
    AftStringSlice slice = aft_string_slice_from_c_string(a);

    bool result = aft_string_slice_ends_with(slice, slice);

    return result;
}

static bool test_find_first_char(Test* test)
{
    const char* a = "a A AA s";
    int known_index = 2;
    AftStringSlice slice = aft_string_slice_from_c_string(a);

    AftMaybeInt index = aft_string_slice_find_first_char(slice, 'A');

    bool result = index.value == known_index;

    return result;
}

static bool test_find_first_char_missing(Test* test)
{
    const char* a = "a A AA s";
    AftStringSlice slice = aft_string_slice_from_c_string(a);

    AftMaybeInt index = aft_string_slice_find_first_char(slice, 'X');

    bool result = !index.valid && index.value == 0;

    return result;
}

static bool test_find_first_string(Test* test)
{
    const char* a = u8"وَالشَّمْسُ تَجْرِي لِمُسْتَقَرٍّ لَّهَا ذَٰلِكَ تَقْدِيرُ الْعَزِيزِ الْعَلِيمِ";
    const char* b = u8"الْعَ";
    int known_index = 112;

    AftStringSlice string = aft_string_slice_from_c_string(a);
    AftStringSlice target = aft_string_slice_from_c_string(b);

    AftMaybeInt index = aft_string_slice_find_first_string(string, target);

    bool result = index.value == known_index;

    return result;
}

static bool test_find_first_string_missing(Test* test)
{
    const char* a = u8"وَالشَّمْسُ تَجْرِي لِمُسْتَقَرٍّ لَّهَا ذَٰلِكَ تَقْدِيرُ الْعَزِيزِ الْعَلِيمِ";
    const char* b = "lies";

    AftStringSlice string = aft_string_slice_from_c_string(a);
    AftStringSlice target = aft_string_slice_from_c_string(b);

    AftMaybeInt index = aft_string_slice_find_first_string(string, target);

    bool result = !index.valid;

    return result;
}

static bool test_find_first_string_self(Test* test)
{
    const char* a = u8"وَالشَّمْسُ تَجْرِي لِمُسْتَقَرٍّ لَّهَا ذَٰلِكَ تَقْدِيرُ الْعَزِيزِ الْعَلِيمِ";
    AftStringSlice slice = aft_string_slice_from_c_string(a);

    AftMaybeInt index = aft_string_slice_find_first_string(slice, slice);

    bool result = index.valid && index.value == 0;

    return result;
}

static bool test_find_last_char(Test* test)
{
    const char* a = "a A AA s";
    int known_index = 5;

    AftStringSlice string = aft_string_slice_from_c_string(a);

    AftMaybeInt index = aft_string_slice_find_last_char(string, 'A');

    bool result = index.value == known_index;

    return result;
}

static bool test_find_last_char_missing(Test* test)
{
    const char* a = "a A AA s";

    AftStringSlice string = aft_string_slice_from_c_string(a);

    AftMaybeInt index = aft_string_slice_find_last_char(string, '\n');

    bool result = !index.valid && index.value == 0;

    return result;
}

static bool test_find_last_string(Test* test)
{
    const char* a = u8"My 1st page הדף מספר 2 שלי My 3rd page";
    const char* b = u8"My";
    int known_index = 37;

    AftStringSlice string = aft_string_slice_from_c_string(a);
    AftStringSlice target = aft_string_slice_from_c_string(b);

    AftMaybeInt index = aft_string_slice_find_last_string(string, target);

    bool result = (index.value == known_index);

    return result;
}

static bool test_find_last_string_missing(Test* test)
{
    const char* a = u8"My 1st page הדף מספר 2 שלי My 3rd page";
    const char* b = "egap";

    AftStringSlice string = aft_string_slice_from_c_string(a);
    AftStringSlice target = aft_string_slice_from_c_string(b);

    AftMaybeInt index = aft_string_slice_find_last_string(string, target);

    bool result = !index.valid;

    return result;
}

static bool test_find_last_string_self(Test* test)
{
    const char* a = u8"My 1st page הדף מספר 2 שלי My 3rd page";
    AftStringSlice slice = aft_string_slice_from_c_string(a);

    AftMaybeInt index = aft_string_slice_find_last_string(slice, slice);

    bool result = index.valid && index.value == 0;

    return result;
}

static bool test_get_contents(Test* test)
{
    const char* reference = "Test me in the most basic way possible.";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);

    char* contents = aft_string_get_contents(&string.value);

    bool result = contents && strings_match(contents, reference);

    aft_string_destroy(&string.value);

    return result;
}

static bool test_get_contents_const(Test* test)
{
    const char* original = u8"👌🏼";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(original, &test->allocator);
    ASSERT(string.valid);

    const char* after = aft_string_get_contents_const(&string.value);

    bool result = after && strings_match(original, after);

    aft_string_destroy(&string.value);

    return result;
}

static bool test_initialise(Test* test)
{
    AftString string;
    aft_string_initialise_with_allocator(&string, &test->allocator);
    return string.allocator == &test->allocator
            && aft_string_get_count(&string) == 0;
}

static bool test_iterator_next(Test* test)
{
    const char* reference = u8"Бума́га всё сте́рпит.";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);

    AftCodepointIterator it;
    aft_codepoint_iterator_set_string(&it, aft_string_slice_from_string(&string.value));
    aft_codepoint_iterator_next(&it);

    int before_index = aft_codepoint_iterator_get_index(&it);
    AftMaybeChar32 next = aft_codepoint_iterator_next(&it);
    int after_index = aft_codepoint_iterator_get_index(&it);

    bool result = next.valid
            && next.value == U'у'
            && before_index == 2
            && after_index == 4;

    aft_string_destroy(&string.value);

    return result;
}

static bool test_iterator_prior(Test* test)
{
    const char* reference = u8"Бума́га всё сте́рпит.";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);

    AftCodepointIterator it;
    aft_codepoint_iterator_set_string(&it, aft_string_slice_from_string(&string.value));
    aft_codepoint_iterator_end(&it);
    aft_codepoint_iterator_prior(&it);

    int before_index = aft_codepoint_iterator_get_index(&it);
    AftMaybeChar32 prior = aft_codepoint_iterator_prior(&it);
    int after_index = aft_codepoint_iterator_get_index(&it);

    bool result = prior.valid
            && prior.value == U'т'
            && before_index == 38
            && after_index == 36;

    aft_string_destroy(&string.value);

    return result;
}

static bool test_iterator_set_string(Test* test)
{
    const char* reference = "9876543210";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    AftStringSlice slice = aft_string_slice_from_string(&string.value);
    ASSERT(string.valid);

    AftCodepointIterator it;
    aft_codepoint_iterator_set_string(&it, slice);
    AftStringSlice got = aft_codepoint_iterator_get_string(&it);

    bool result =
            aft_string_slice_start(got) == aft_string_slice_start(slice)
            && aft_string_slice_count(got) == aft_string_slice_count(slice)
            && aft_codepoint_iterator_get_index(&it) == 0;

    aft_string_destroy(&string.value);

    return result;
}

static bool test_remove_end(Test* test)
{
    const char* reference = "9876543210";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);

    aft_string_remove(&string.value, 7, 10);
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = strings_match(contents, "9876543");

    aft_string_destroy(&string.value);

    return result;
}

static bool test_remove_everything(Test* test)
{
    const char* reference = "9876543210";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);

    aft_string_remove(&string.value, 0, aft_string_get_count(&string.value));

    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = strings_match(contents, "");

    aft_string_destroy(&string.value);

    return result;
}

static bool test_remove_middle(Test* test)
{
    const char* reference = "9876543210";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);

    aft_string_remove(&string.value, 3, 6);
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = strings_match(contents, "9873210");

    aft_string_destroy(&string.value);

    return result;
}

static bool test_remove_nothing(Test* test)
{
    const char* reference = "9876543210";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);

    aft_string_remove(&string.value, 3, 3);
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = strings_match(contents, "9876543210");

    aft_string_destroy(&string.value);

    return result;
}

static bool test_remove_nothing_from_nothing(Test* test)
{
    AftString string;
    aft_string_initialise_with_allocator(&string, &test->allocator);

    aft_string_remove(&string, 0, 0);
    const char* contents = aft_string_get_contents_const(&string);
    bool result = strings_match(contents, "");

    aft_string_destroy(&string);

    return result;
}

static bool test_remove_start(Test* test)
{
    const char* reference = "9876543210";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);

    aft_string_remove(&string.value, 0, 3);
    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = strings_match(contents, "6543210");

    aft_string_destroy(&string.value);

    return result;
}

static bool test_replace(Test* test)
{
    const char* reference = "9876543210";
    const char* insert = "abc";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    AftStringSlice replacement = aft_string_slice_from_c_string(insert);
    ASSERT(string.valid);

    bool replaced = aft_string_replace(&string.value, 3, 6, replacement);
    ASSERT(replaced);

    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = strings_match(contents, "987abc3210");

    aft_string_destroy(&string.value);

    return result;
}

static bool test_replace_everything(Test* test)
{
    const char* reference = "9876543210";
    const char* insert = "abcdefghij";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    AftStringSlice replacement = aft_string_slice_from_c_string(insert);
    ASSERT(string.valid);

    bool replaced = aft_string_replace(&string.value, 0, aft_string_get_count(&string.value), replacement);
    ASSERT(replaced);

    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = strings_match(contents, insert);

    aft_string_destroy(&string.value);

    return result;
}

static bool test_replace_nothing(Test* test)
{
    const char* insert = "abcdef";
    AftString string;
    aft_string_initialise_with_allocator(&string, &test->allocator);
    AftStringSlice replacement = aft_string_slice_from_c_string(insert);

    bool replaced = aft_string_replace(&string, 0, 0, replacement);

    const char* contents = aft_string_get_contents_const(&string);
    bool contents_match = strings_match(contents, insert);
    bool size_correct = aft_string_get_count(&string) == string_size(insert);
    bool result = replaced && contents_match && size_correct;

    aft_string_destroy(&string);

    return result;
}

static bool test_replace_nothing_with_nothing(Test* test)
{
    AftString string;
    aft_string_initialise_with_allocator(&string, &test->allocator);
    AftStringSlice replacement = aft_string_slice_from_c_string("");

    bool replaced = aft_string_replace(&string, 0, 0, replacement);

    const char* contents = aft_string_get_contents_const(&string);
    bool result = replaced && strings_match(contents, "");

    aft_string_destroy(&string);

    return result;
}

static bool test_replace_self_middle(Test* test)
{
    const char* reference = "9876543210";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);
    AftStringSlice slice = aft_string_slice_from_string(&string.value);

    bool replaced = aft_string_replace(&string.value, 3, 6, slice);
    ASSERT(replaced);

    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = strings_match(contents, "98798765432103210");

    aft_string_destroy(&string.value);

    return result;
}

static bool test_replace_with_nothing(Test* test)
{
    const char* reference = "9876543210";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    AftStringSlice replacement = aft_string_slice_from_c_string("");
    ASSERT(string.valid);

    bool replaced = aft_string_replace(&string.value, 3, 6, replacement);
    ASSERT(replaced);

    const char* contents = aft_string_get_contents_const(&string.value);
    bool result = strings_match(contents, "9873210");

    aft_string_destroy(&string.value);

    return result;
}

static bool test_reserve(Test* test)
{
    AftString string;
    aft_string_initialise_with_allocator(&string, &test->allocator);
    int requested_cap = 100;

    bool reserved = aft_string_reserve(&string, requested_cap);
    int cap = aft_string_get_capacity(&string);
    bool result = reserved && cap == requested_cap;

    aft_string_destroy(&string);

    return result;
}

static bool test_starts_with(Test* test)
{
    const char* a = u8"a猫🍌 Wow";
    const char* b = u8"a猫🍌";
    AftStringSlice string = aft_string_slice_from_c_string(a);
    AftStringSlice ending = aft_string_slice_from_c_string(b);

    bool result = aft_string_slice_starts_with(string, ending);

    return result;
}

static bool test_starts_with_missing(Test* test)
{
    const char* a = u8"a猫🍌 Wow";
    const char* b = u8"🍌W";
    AftStringSlice string = aft_string_slice_from_c_string(a);
    AftStringSlice beginning = aft_string_slice_from_c_string(b);

    bool result = !aft_string_slice_starts_with(string, beginning);

    return result;
}

static bool test_starts_with_nothing(Test* test)
{
    const char* a = u8"a猫🍌 ";
    const char* b = "";
    AftStringSlice string = aft_string_slice_from_c_string(a);
    AftStringSlice beginning = aft_string_slice_from_c_string(b);

    bool result = aft_string_slice_starts_with(string, beginning);

    return result;
}

static bool test_starts_with_self(Test* test)
{
    const char* a = u8"a猫🍌 ";
    AftStringSlice slice = aft_string_slice_from_c_string(a);

    bool result = aft_string_slice_starts_with(slice, slice);

    return result;
}

static bool test_c_string_copy_string(Test* test)
{
    const char* reference = "It's okay.";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);

    char* copy = aft_c_string_copy_string_with_allocator(&string.value, &test->allocator);
    bool result = strings_match(copy, reference);

    aft_string_destroy(&string.value);
    aft_c_string_deallocate_with_allocator(&test->allocator, copy);

    return result;
}

static bool test_c_string_copy_string_empty(Test* test)
{
    const char* reference = "";
    AftMaybeString string = aft_string_copy_c_string_with_allocator(reference, &test->allocator);
    ASSERT(string.valid);

    char* copy = aft_c_string_copy_string_with_allocator(&string.value, &test->allocator);
    bool result = strings_match(copy, reference);

    aft_string_destroy(&string.value);
    aft_c_string_deallocate_with_allocator(&test->allocator, copy);

    return result;
}


int main(int argc, const char** argv)
{
    Suite suite = {0};

    add_test(&suite, fuzz_assign, "Fuzz Assign");
    add_test(&suite, test_add_end, "Add End");
    add_test(&suite, test_add_middle, "Add Middle");
    add_test(&suite, test_add_self_middle, "Add Self Middle");
    add_test(&suite, test_add_start, "Add Start");
    add_test(&suite, test_append, "Append");
    add_test(&suite, test_append_nothing, "Append Nothing");
    add_test(&suite, test_append_nothing_to_nothing, "Append Nothing To Nothing");
    add_test(&suite, test_append_self, "Append Self");
    add_test(&suite, test_append_to_nothing, "Append To Nothing");
    add_test(&suite, test_append_c_string, "Append C String");
    add_test(&suite, test_append_char, "Append Char");
    add_test(&suite, test_assign, "Assign");
    add_test(&suite, test_assign_nothing, "Assign Nothing");
    add_test(&suite, test_assign_self, "Assign Self");
    add_test(&suite, test_c_string_copy_string, "C String Copy String");
    add_test(&suite, test_c_string_copy_string_empty, "C String Copy String Empty");
    add_test(&suite, test_copy, "Copy");
    add_test(&suite, test_copy_c_string, "Copy C String");
    add_test(&suite, test_copy_c_string_empty, "Copy C String Empty");
    add_test(&suite, test_destroy, "Destroy");
    add_test(&suite, test_ends_with, "Ends With");
    add_test(&suite, test_ends_with_missing, "Ends With Missing");
    add_test(&suite, test_ends_with_nothing, "Ends With Nothing");
    add_test(&suite, test_ends_with_self, "Ends With Self");
    add_test(&suite, test_find_first_char, "Find First Char");
    add_test(&suite, test_find_first_char_missing, "Find First Char Missing");
    add_test(&suite, test_find_first_string, "Find First String");
    add_test(&suite, test_find_first_string_missing, "Find First String Missing");
    add_test(&suite, test_find_first_string_self, "Find First String Self");
    add_test(&suite, test_find_last_char, "Find Last Char");
    add_test(&suite, test_find_last_char_missing, "Find Last Char Missing");
    add_test(&suite, test_find_last_string, "Find Last String");
    add_test(&suite, test_find_last_string_missing, "Find Last String Missing");
    add_test(&suite, test_find_last_string_self, "Find Last String Self");
    add_test(&suite, test_get_contents, "Get Contents");
    add_test(&suite, test_get_contents_const, "Get Contents Const");
    add_test(&suite, test_initialise, "Initialise");
    add_test(&suite, test_iterator_next, "Iterator Next");
    add_test(&suite, test_iterator_prior, "Iterator Prior");
    add_test(&suite, test_iterator_set_string, "Iterator Set String");
    add_test(&suite, test_remove_end, "Remove End");
    add_test(&suite, test_remove_everything, "Remove Everything");
    add_test(&suite, test_remove_middle, "Remove Middle");
    add_test(&suite, test_remove_nothing, "Remove Nothing");
    add_test(&suite, test_remove_nothing_from_nothing, "Remove Nothing From Nothing");
    add_test(&suite, test_remove_start, "Remove Start");
    add_test(&suite, test_replace, "Replace");
    add_test(&suite, test_replace_everything, "Replace Everything");
    add_test(&suite, test_replace_nothing, "Replace Nothing");
    add_test(&suite, test_replace_nothing_with_nothing, "Replace Nothing With Nothing");
    add_test(&suite, test_replace_self_middle, "Replace Self Middle");
    add_test(&suite, test_replace_with_nothing, "Replace With Nothing");
    add_test(&suite, test_reserve, "Reserve");
    add_test(&suite, test_starts_with, "Starts With");
    add_test(&suite, test_starts_with_missing, "Starts With Missing");
    add_test(&suite, test_starts_with_nothing, "Starts With Nothing");
    add_test(&suite, test_starts_with_self, "Starts With Self");

    bool success = run_tests(&suite);
    return !success;
}
