/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/configuration/blob/main/LICENSE.txt
*/

#include "ConfigurationTests.hpp"
#include "Ishiko/Configuration/Configuration.hpp"

using namespace Ishiko;

ConfigurationTests::ConfigurationTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Configuration tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("set test 1", SetTest1);
    append<HeapAllocationErrorsTest>("valueOrDefault test 1", ValueOrDefaultTest1);
    append<HeapAllocationErrorsTest>("valueOrNull test 1", ValueOrNullTest1);
}

void ConfigurationTests::ConstructorTest1(Test& test)
{
    Configuration configuration;

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.size(), 0);
    ISHIKO_TEST_PASS();
}

void ConfigurationTests::SetTest1(Test& test)
{
    Configuration configuration;

    configuration.set("option1", "value1");

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(configuration.value("option1"), "value1");
    ISHIKO_TEST_PASS();
}

void ConfigurationTests::ValueOrDefaultTest1(Test& test)
{
    Configuration configuration;

    configuration.set("option1", "value1");

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(configuration.valueOrDefault("option1", "default1"), "value1");
    ISHIKO_TEST_FAIL_IF_NEQ(configuration.valueOrDefault("option2", "default2"), "default2");
    ISHIKO_TEST_PASS();
}

void ConfigurationTests::ValueOrNullTest1(Test& test)
{
    Configuration configuration;

    configuration.set("option1", "value1");

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.size(), 1);

    const std::string* valuePointer1 = configuration.valueOrNull("option1");

    ISHIKO_TEST_ABORT_IF_EQ(valuePointer1, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(*valuePointer1, "value1");

    const std::string* valuePointer2 = configuration.valueOrNull("option2");

    ISHIKO_TEST_FAIL_IF_NEQ(valuePointer2, nullptr);
    ISHIKO_TEST_PASS();
}
