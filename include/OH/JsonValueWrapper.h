#pragma once

#include <json/json.h>
#include "JsonHelper.h"
#include <mutex>

class JsonValueWrapper : public Json::Value
{
private:
	static std::mutex mOpMtx;
public:

	JsonValueWrapper();
	JsonValueWrapper(Json::Value& json);

	template<typename T>
	T get(const std::string& key, T def) const;

	template<typename T>
	void set(const std::string& key, T val); 

	const Json::Value& getJsonValue() const;

};

inline uint64_t JsonUint64Get(const JsonValueWrapper& val, const char* name)
{
	if (val[name].isUInt())
		return val.get<uint32_t>(name, 0);

	if (val[name].isUInt64())
		return val.get<uint64_t>(name, 0);

	if (val[name].isString())
		return strtoll(val[name].asCString(), nullptr, 16);

	return 0;
}


template<typename T>
inline T JsonValueWrapper::get(const std::string& key, T def) const
{
	std::lock_guard lck(mOpMtx);

	if (JSON_ASSERT(*this, key) == false)
		return def;

	return (*this)[key].as<T>();
}

template<typename T>
inline void JsonValueWrapper::set(const std::string& key, T val)
{
	std::lock_guard lck(mOpMtx);

	(*this)[key] = val;
}

/*template<>
inline std::string JsonValueWrapper::get(const std::string& key, std::string def)
{
	if (JSON_ASSERT(*this, key))
		return def;

	return (*this)[key].asString();
}

template<>
inline int JsonValueWrapper::get(const std::string& key, int def)
{
	if (JSON_ASSERT(*this, key))
		return def;

	return (*this)[key].asInt();
}
*/

