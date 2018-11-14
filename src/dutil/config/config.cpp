#include "../define.h"

ConfigManager::ConfigManager(void)
{

}


ConfigManager::~ConfigManager(void)
{
	ptree_.clear();
}


bool ConfigManager::Initialize(const std::string& file_name)
{
	std::cout << file_name << " Loading..." << std::endl;

	try
	{
		boost::property_tree::ini_parser::read_ini(file_name, ptree_);

		std::cout << "Load complete" << std::endl;
	}
	catch (boost::property_tree::ini_parser_error& error)
	{
		std::cout << "Load failed : " << error.message() << std::endl;
		return false;
	}

	return true;
}


ConfigManager::INI_Value ConfigManager::GetValue(const std::string& section_name, const std::string& key_name, bool to_upper_case /* = false */)
{
	try
	{
		ConfigManager::INI_Value result = ptree_.get<ConfigManager::INI_Value>(section_name + "." + key_name);
		if (to_upper_case)
			std::transform(result.begin(), result.end(), result.begin(), toupper);

		return result;
	}
	catch (boost::property_tree::ptree_bad_path& error)
	{
		std::cout << "GetValue failed : " << error.what() << std::endl;
		exit(1);
	}
}

int32_t ConfigManager::GetInt32(const std::string& section_name, const std::string& key_name)
{
	return std::stoi(GetValue(section_name, key_name));
}

std::string ConfigManager::GetString(const std::string& section_name, const std::string& key_name, bool to_upper_case /* = false */)
{
	return GetValue(section_name, key_name, to_upper_case);
}

bool ConfigManager::GetBool(const std::string& section_name, const std::string& key_name)
{
	if ("TRUE" == GetValue(section_name, key_name, true))
		return true;
	else if ("FALSE" == GetValue(section_name, key_name, true))
		return false;
	else
	{
		std::cout << "GetValue failed : " << std::endl;
		exit(1);
	}
}
