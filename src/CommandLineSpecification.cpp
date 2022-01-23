/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/config/blob/main/LICENSE.txt
*/

#include "CommandLineSpecification.h"

namespace Ishiko
{
namespace Configuration
{

void CommandLineSpecification::addNamedOption(const std::string& name, const OptionDetails& details)
{
    m_options.emplace(name, details);
}

bool CommandLineSpecification::find(const std::string& name, OptionDetails& details) const
{
    std::map<std::string, OptionDetails>::const_iterator it = m_options.find(name);
    if (it != m_options.end())
    {
        details = it->second;
        return true;
    }
    else
    {
        return false;
    }
}

}
}
