#pragma once

class ConfigManager : public boost::serialization::singleton<ConfigManager>
{
public:
	typedef std::pair<std::string, std::string> INI_Key;
	typedef std::string INI_Value;
	typedef std::map<INI_Key, INI_Value> INI_Container;

	enum CONFIG_FILE_TYPE
	{
		CONFIG_FILE_TYPE_INI = 0,
		CONFIG_FILE_TYPE_JSON,
		CONFIG_FILE_TYPE_MAX,
	};

	ConfigManager(void);
	virtual ~ConfigManager(void);

	bool			Initialize(std::string file_name);
	int32_t			GetInt32(std::string section_name, std::string key_name);
	std::string		GetString(std::string section_name, std::string key_name, bool to_upper_case = false);
	bool			GetBool(std::string section_name, std::string key_name);
	
private:
	ConfigManager::INI_Value GetValue(std::string section_name, std::string key_name, bool to_upper_case = false);

public:
	static ConfigManager& GetMutableInstance(void) { return ConfigManager::get_mutable_instance(); }

private:
	boost::property_tree::ptree ptree_;
	INI_Container ini_data_;

};


#define CONFIG_MANAGER_INSTANCE ConfigManager::GetMutableInstance()
