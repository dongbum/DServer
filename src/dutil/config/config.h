#pragma once

class ConfigManager
{
private:
	static std::shared_ptr<ConfigManager> instance_;

public:
	static std::shared_ptr<ConfigManager> GetInstance(void);
	static void ReleaseInstance(void);

public:
	using INI_Key = std::pair<std::string, std::string>;
	using INI_Value = std::string;
	using INI_Container = std::map<INI_Key, INI_Value>;

	enum CONFIG_FILE_TYPE
	{
		CONFIG_FILE_TYPE_INI = 0,
		CONFIG_FILE_TYPE_JSON,
		CONFIG_FILE_TYPE_MAX,
	};

public:
	ConfigManager(void);
	virtual ~ConfigManager(void);
	

	bool			Initialize(const std::string& file_name);
	int32_t			GetInt32(const std::string& section_name, const std::string& key_name);
	std::string		GetString(const std::string& section_name, const std::string& key_name, bool to_upper_case = false);
	bool			GetBool(const std::string& section_name, const std::string& key_name);
	
private:
	ConfigManager::INI_Value GetValue(const std::string& section_name, const std::string& key_name, bool to_upper_case = false);

private:
	boost::property_tree::ptree ptree_;
	INI_Container ini_data_;

};
