#pragma once
#include <boost/any.hpp>
#include <memory>
#include <map>

namespace enginex {

	class AnyPtrContainer {
	public:
		template<typename ServiceType>
		void Set(const std::string &key, std::shared_ptr<ServiceType> ptr) {
			container[key] = ptr;
		}
		template<typename ServiceType>
		void Set(std::shared_ptr<ServiceType> ptr) {
			std::string key = typeid(ServiceType).raw_name();
			Set<ServiceType>(key, ptr);
		}

		template<typename ServiceType>
		void Set(const std::string &key, std::weak_ptr<ServiceType> ptr) {
			container[key] = ptr;
		}
		template<typename ServiceType>
		void Set(std::weak_ptr<ServiceType> ptr) {
			std::string key = typeid(ServiceType).raw_name();
			Set<ServiceType>(key, ptr);
		}

		template<typename ServiceType>
		std::shared_ptr<ServiceType> Get(const std::string &key) {
			std::shared_ptr<ServiceType> result;

			auto it = container.find(key);
			if (it != container.end()) {
				auto any = it->second;
				try {
					if (any.type() == typeid(std::shared_ptr<ServiceType>)) {
						result = boost::any_cast<std::shared_ptr<ServiceType>>(any);
					}
					else if (any.type() == typeid(std::weak_ptr<ServiceType>)) {
						auto weak = boost::any_cast<std::weak_ptr<ServiceType>>(any);
						result = weak.lock();
					}
				}
				catch (boost::bad_any_cast &) {
					//do nothing ,后面会返回一个空的share_ptr
				}
			}
			return result;
		}
		template<typename ServiceType>
		std::shared_ptr<ServiceType> Get() {
			std::string key = typeid(ServiceType).raw_name();
			return Get<ServiceType>(key);
		}
		void Delete(const std::string &key) {
			container.erase(key);
		}
		template<typename ServiceType>
		void Delete() {
			std::string key = typeid(ServiceType).raw_name();
			return Delete(key);
		}

		void DeleteAll() {
			container.clear();
		}

	private:
		std::map<std::string, boost::any> container;
	};

}//end namespace enginex {
