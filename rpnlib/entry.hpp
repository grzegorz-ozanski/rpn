#pragma once
#include <string>
#include <algorithm>
namespace rpn {
	class EntryInfo {
	public:
		std::string name;
		std::string info;

		EntryInfo(const std::string& name, const std::string& info) : name(name), info(info) {}
		virtual ~EntryInfo() = default;
		virtual std::string get_info() const {
			return info;
		}
	};

	template <typename T>
	class EntryRegistry {
	public:
		static const std::vector<T> all;
		static bool contains(const Token& token) {
			return find(token) != nullptr;
		}
		static const T* find(const Token& token) {
			auto it = std::find_if(all.begin(), all.end(), [&](const auto& entry) {
				return entry.name == token.get_token();
				});
			return it != all.end() ? &(*it) : nullptr;
		}
	};
}