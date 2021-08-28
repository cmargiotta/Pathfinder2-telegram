#ifndef PATHFINDER2_INVENTORY_ENTRY 
#define PATHFINDER2_INVENTORY_ENTRY

#include <string>
#include <cstdint>

namespace pathfinder2
{
	class inventory_entry {
		protected: 
			int					owner; 
			std::string 		name; 
			std::string			category;
			std::string			bulk_string;
			double	   			bulk; 
			int					quantity; 

		public: 
			inventory_entry() = default;
			inventory_entry(int owner, const std::string& name, double bulk, const std::string& category);
			virtual ~inventory_entry();

			const std::string& get_name() const;
			int get_quantity() const;

			virtual const std::string& get_category() const;
			virtual double get_bulk() const; 
			virtual const std::string& get_url() const; 
			virtual const std::string& get_description() const; 
			const std::string& get_bulk_string() const;

			virtual void update_quantity(int delta);
			virtual void remove() = 0;
			virtual void set_category(const std::string& category);
			virtual void set_bulk(const std::string& bulk);
			virtual void set_description(const std::string& description);
			virtual void set_url(const std::string& url);
	};
}

#endif