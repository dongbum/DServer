#include "../define.h"

ConfigManager::ConfigManager(void)
{

}


ConfigManager::~ConfigManager(void)
{
	ptree_.clear();
}


bool ConfigManager::Initialize(std::string file_name)
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


ConfigManager::INI_Value ConfigManager::GetValue(std::string section_name, std::string key_name, bool to_upper_case /* = false */)
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
