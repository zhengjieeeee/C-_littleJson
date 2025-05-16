#include <vector>
#include <string>
#include <map>
#include <memory>

namespace MyJson
{
class Json
{
public:
    enum Type{
        json_null = 0,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_array,
        json_object
    };

    Json();
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char *value);
    Json(const std::string &value);
    Json(Type type);
    Json(const Json &other);

    ~Json();

    operator bool();
    operator int();
    operator double();
    operator std::string();

    Json& operator[](const char *key);
    Json& operator[](const std::string &key);
    void operator=(const Json &other);

    //数组重载
    Json &operator[](int index);
    void append(const Json &other);
    
    std::string tostr() const;

    //获取映射表类型的key和value
    std::string getKey(int index) const;
    std::string getValue(int index) const;

private:
    void clear();
    void deepcopy(const Json &other);

    struct Value{
        bool m_bool;
        int m_int;
        double m_double;
        std::shared_ptr<std::string> m_string;
        std::shared_ptr<std::vector<Json>> m_array;
        std::shared_ptr<std::map<std::string, Json>> m_object;
    };

    Type m_type;
    Value m_value;
};

} // namespace MyJson


