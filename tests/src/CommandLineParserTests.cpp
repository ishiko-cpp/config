// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "CommandLineParserTests.hpp"
#include "Ishiko/Configuration/CommandLineParser.hpp"

using namespace Ishiko;

CommandLineParserTests::CommandLineParserTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "CommandLineParser tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("parse test 1", ParseTest1);
    append<HeapAllocationErrorsTest>("parse test 2", ParseTest2);
    append<HeapAllocationErrorsTest>("parse test 3", ParseTest3);
    append<HeapAllocationErrorsTest>("parse test 4", ParseTest4);
    append<HeapAllocationErrorsTest>("parse test 5", ParseTest5);
    append<HeapAllocationErrorsTest>("parse test 6", ParseTest6);
    append<HeapAllocationErrorsTest>("parse test 7", ParseTest7);
    append<HeapAllocationErrorsTest>("parse test 8", ParseTest8);
    append<HeapAllocationErrorsTest>("parse test 9", ParseTest9);
}

void CommandLineParserTests::ConstructorTest1(Test& test)
{
    CommandLineParser parser;

    ISHIKO_TEST_PASS();
}

void CommandLineParserTests::ParseTest1(Test& test)
{
    CommandLineSpecification spec;
    spec.addPositionalOption(1, "option1", {CommandLineSpecification::OptionType::single_value});

    CommandLineParser parser;
    int argc = 2;
    const char* argv[] = {"dummy", "value1"};
    Configuration configuration;
    parser.parse(spec, argc, argv, configuration);

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.value("option1").asString(), "value1");
    ISHIKO_TEST_PASS();
}

void CommandLineParserTests::ParseTest2(Test& test)
{
    CommandLineSpecification spec;
    spec.addNamedOption("option1", {CommandLineSpecification::OptionType::single_value, "default"});

    CommandLineParser parser;
    int argc = 2;
    const char* argv[] = {"dummy", "--option1=value1"};
    Configuration configuration;
    parser.parse(spec, argc, argv, configuration);

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.value("option1").asString(), "value1");
    ISHIKO_TEST_PASS();
}

void CommandLineParserTests::ParseTest3(Test& test)
{
    CommandLineSpecification spec;
    spec.addNamedOption("option1", {CommandLineSpecification::OptionType::single_value, "default"});

    CommandLineParser parser;
    int argc = 3;
    const char* argv[] = {"dummy", "--option1=value1", "--option2=value2"};
    Configuration configuration;
    parser.parse(spec, argc, argv, configuration);

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.value("option1").asString(), "value1");
    ISHIKO_TEST_FAIL_IF_NEQ(configuration.value("option2").asString(), "value2");
    ISHIKO_TEST_PASS();
}

void CommandLineParserTests::ParseTest4(Test& test)
{
    CommandLineSpecification spec;

    CommandLineParser parser;
    int argc = 2;
    const char* argv[] = {"dummy", "--option1"};
    Configuration configuration;
    parser.parse(spec, argc, argv, configuration);

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.value("option1").asString(), "");
    ISHIKO_TEST_PASS();
}

void CommandLineParserTests::ParseTest5(Test& test)
{
    CommandLineSpecification spec;
    spec.addNamedOption("option1", "o", {CommandLineSpecification::OptionType::single_value, "default"});

    CommandLineParser parser;
    int argc = 2;
    const char* argv[] = {"dummy", "-o=value1"};
    Configuration configuration;
    parser.parse(spec, argc, argv, configuration);

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.value("option1").asString(), "value1");
    ISHIKO_TEST_PASS();
}

void CommandLineParserTests::ParseTest6(Test& test)
{
    CommandLineSpecification spec;
    spec.addPositionalOption(1, "command", {CommandLineSpecification::OptionType::single_value});
    spec.addCommand("command", "command1");

    CommandLineParser parser;
    int argc = 2;
    const char* argv[] = {"dummy", "command1"};
    Configuration configuration;
    parser.parse(spec, argc, argv, configuration);

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.value("command").asConfiguration().value("name").asString(), "command1");
    ISHIKO_TEST_PASS();
}

void CommandLineParserTests::ParseTest7(Test& test)
{
    CommandLineSpecification spec;
    spec.addPositionalOption(1, "command", {CommandLineSpecification::OptionType::single_value});
    CommandLineSpecification::CommandDetails& command_details = spec.addCommand("command", "command1");
    command_details.addPositionalOption(2, "command1_option1", {CommandLineSpecification::OptionType::single_value});

    CommandLineParser parser;
    int argc = 3;
    const char* argv[] = {"dummy", "command1", "value1"};
    Configuration configuration;
    parser.parse(spec, argc, argv, configuration);

    ISHIKO_TEST_FAIL_IF_NEQ(configuration.value("command").asConfiguration().value("name").asString(), "command1");
    ISHIKO_TEST_FAIL_IF_NEQ(configuration.value("command").asConfiguration().value("command1_option1").asString(),
        "value1");
    ISHIKO_TEST_PASS();
}

void CommandLineParserTests::ParseTest8(Test& test)
{
    CommandLineSpecification spec;
    spec.addPositionalOption(1, "command", {CommandLineSpecification::OptionType::single_value});
    CommandLineSpecification::CommandDetails& command_details = spec.addCommand("command", "command1", "subcommand1");

    CommandLineParser parser;
    int argc = 3;
    const char* argv[] = {"dummy", "command1", "subcommand1"};
    Configuration configuration;
    parser.parse(spec, argc, argv, configuration);

    const Configuration& command_configuration = configuration.value("command").asConfiguration();

    ISHIKO_TEST_FAIL_IF_NEQ(command_configuration.value("name").asString(), "command1");
    ISHIKO_TEST_FAIL_IF_NEQ(command_configuration.value("subcommand").asConfiguration().value("name").asString(),
        "subcommand1");
    ISHIKO_TEST_PASS();
}

void CommandLineParserTests::ParseTest9(Test& test)
{
    CommandLineSpecification spec;
    spec.addPositionalOption(1, "command", { CommandLineSpecification::OptionType::single_value });
    CommandLineSpecification::CommandDetails& command_details = spec.addCommand("command", "command1", "subcommand1");
    command_details.addPositionalOption(3, "subcommand1_option1", {CommandLineSpecification::OptionType::single_value});

    CommandLineParser parser;
    int argc = 4;
    const char* argv[] = {"dummy", "command1", "subcommand1", "value1"};
    Configuration configuration;
    parser.parse(spec, argc, argv, configuration);

    const Configuration& command_configuration = configuration.value("command").asConfiguration();

    ISHIKO_TEST_FAIL_IF_NEQ(command_configuration.value("name").asString(), "command1");
    ISHIKO_TEST_FAIL_IF_NEQ(command_configuration.value("subcommand").asConfiguration().value("name").asString(),
        "subcommand1");
    ISHIKO_TEST_FAIL_IF_NEQ(command_configuration.value("subcommand").asConfiguration().value("subcommand1_option1").asString(),
        "value1");
    ISHIKO_TEST_PASS();
}
