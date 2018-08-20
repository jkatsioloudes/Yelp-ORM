#include <memory>
#include <odb/core.hxx>
#include <odb/lazy-ptr.hxx>
#include <set>
#include <string>

#pragma db view
class StarCount{
public:
	int stars;
	int count;
};

#pragma db view query("select top 1 text, last_elapsed_time from sys.dm_exec_query_stats cross apply sys.dm_exec_sql_text(sql_handle) order by last_execution_time desc")
class LastQueryTime{
public:
	std::string text;
	long elapsed_time;
};

// ---------------------------------------------
// No need to change anything above this line
// ---------------------------------------------

// out of scope declarations predeclared here.
class hour;
class category;
class business;
class review;
class user;
class photo;

# pragma db object no_id
class attribute {
public:
	std::string name;
	std::string value;

	odb::lazy_ptr<business> business_id;
};

# pragma db object
class business {
public:
# pragma db id
    std::string id;
	std::string name;
	std::string neighborhood;
	std::string address;
	std::string city;
	std::string state;
	std::string postal_code;
	float latitude;
	float longitude;
	float stars;
	int review_count;
	short int is_open;

# pragma db inverse(business_id)
	std::vector<std::shared_ptr<hour>> business_hours;
# pragma db inverse(business_id)
    std::vector<std::shared_ptr<review>> business_reviews;
# pragma db inverse(business_id)
	std::vector<std::shared_ptr<photo>> business_photos;
};

# pragma db object no_id
class category {
public:
	std::string category;

	odb::lazy_ptr<business> business_id;
};

# pragma db object no_id
class checkin {
public:
	std::string date;
	int count;

	odb::lazy_ptr<business> business_id;
};

# pragma db object no_id
class elite_years {
public:
	int year;

	odb::lazy_ptr<user> user_id;
};

# pragma db object table("friend") // because 'friend' is a reserved C++ keyword.
class friends {
public:
# pragma db id
    std::string friend_id;

	odb::lazy_ptr<user> user_id;
};

#pragma db object table("hours") // because overlaps with the attribute name.
class hour {
public:
# pragma db id
	int id;
	std::string hours;

	odb::lazy_ptr<business> business_id;
};

# pragma db object
class photo {
public:
# pragma db id
    std::string id;
	std::string caption;
	std::string label;

	odb::lazy_ptr<business> business_id;
};

# pragma db object
class review {
public:
# pragma db id
    std::string id;
	int stars;
	std::string date;
	std::string text;
	int useful;
	int funny;
	int cool;

	odb::lazy_ptr<business> business_id;
	odb::lazy_ptr<user> user_id;
};

# pragma db object no_id
class tip {
public:
	std::string text;
	std::string date;
	int likes;

	odb::lazy_ptr<business> business_id;
	odb::lazy_ptr<user> user_id;
};

# pragma db object
class user {
public:
# pragma db id
    std::string id;
	std::string name;
	int review_count;
	std::string yelping_since;
	int useful;
	int funny;
	int cool;
	int fans;
	float average_stars;
	int compliment_hot;
	int compliment_more;
	int compliment_profile;
	int compliment_cute;
	int compliment_list;
	int compliment_note;
	int compliment_plain;
	int compliment_cool;
	int compliment_funny;
	int compliment_writer;
	int compliment_photos;

# pragma db inverse(user_id)
	std::vector<std::shared_ptr<review>> user_reviews;
# pragma db inverse(user_id)
	std::vector<std::shared_ptr<friends>> user_friends;
};
