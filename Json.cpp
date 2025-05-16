#include <iostream>
#include <sstream>

#include "Json.h"

using namespace MyJson;

void Json::clear(){
    m_value.m_bool = false;
    m_value.m_int = 0;
    m_value.m_double = 0.0;
    m_value.m_string.reset();
    m_value.m_array.reset();
    m_value.m_object.reset();
}

void Json::deepcopy(const Json &other) {
    m_type = other.m_type;
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = other.m_value.m_bool;
            break;
        case json_int:
            m_value.m_int = other.m_value.m_int;
            break;
        case json_double:
            m_value.m_double = other.m_value.m_double;
            break;
        case json_string:
            m_value.m_string = std::make_shared<std::string>(*other.m_value.m_string);
            break;
        case json_array:
            m_value.m_array = std::make_shared<std::vector<Json>>(*other.m_value.m_array);
            break;
        case json_object:
            m_value.m_object = std::make_shared<std::map<std::string, Json>>(*other.m_value.m_object);
            break;
        default:
            break;
    }

}

Json::Json() : m_type(json_null) {}

Json::Json(bool value) : m_type(json_bool) {
    m_value.m_bool = value;
}

Json::Json(int value) : m_type(json_int) {
    m_value.m_int = value;
}

Json::Json(double value) : m_type(json_double) {
    m_value.m_double = value;
}

Json::Json(const char *value) : m_type(json_string) {
    m_value.m_string = std::make_shared<std::string>(value);
}

Json::Json(const std::string &value) : m_type(json_string) {
    m_value.m_string = std::make_shared<std::string>(value);
}

Json::Json(Type type) : m_type(type) {
    switch (type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = false;
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_double:
            m_value.m_double = 0.0;
            break;
        case json_string:
            m_value.m_string = std::make_shared<std::string>("");
            break;
        case json_array:
            m_value.m_array = std::make_shared<std::vector<Json>>();
            break;
        case json_object:
            m_value.m_object = std::make_shared<std::map<std::string, Json>>();
            break;
        default:
            break;
    }
}

Json::Json(const Json &other) : m_type(other.m_type) {
   deepcopy(other);
}

Json::~Json(){}

Json::operator bool() {
    if (m_type != json_bool) {
        throw std::logic_error("Json type is not bool");
    }
    return m_value.m_bool;
}

Json::operator int() {
    if (m_type != json_int) {
        throw std::logic_error("Json type is not int");
    }
    return m_value.m_int;
}

Json::operator double() {
    if (m_type != json_double) {
        throw std::logic_error("Json type is not double");
    }
    return m_value.m_double;
}

Json::operator std::string() {
    if (m_type != json_string) {
        throw std::logic_error("Json type is not string");
    }
    return *m_value.m_string;
}

Json& Json::operator[](int index) {
    if (m_type != json_array) {
        clear();
        m_type = json_array;
        m_value.m_array = std::make_shared<std::vector<Json>>();
    }

    if (index < 0) {
        throw std::logic_error("array[] index < 0");
    }
    size_t size = m_value.m_array->size();
    if (index >= size) {
        for (int i = size; i <= index ; ++i) {
            (m_value.m_array)->push_back(Json());
        }
    }

    return (m_value.m_array)->at(index); //at(index) 返回 vector 中第 index 个元素的引用
}

void Json::append(const Json &other) {
    if (m_type != json_array) {
        clear();
        m_type = json_array;
        m_value.m_array = std::make_shared<std::vector<Json>>();
    }

    (m_value.m_array)->push_back(other);
}

std::string Json::tostr() const {
    std::stringstream ss;

    switch (m_type)
    {
    case json_null:
        ss << "null";
        break;
    case json_bool:
        ss << (m_value.m_bool ? "true" : "false");
        break;
    case json_int:
        ss << m_value.m_int;
        break;
    case json_double:
        ss <<  m_value.m_double ;
        break;
    case json_string:
        ss << '\"' << *(m_value.m_string) << '\"';
        break;
    case json_array:
        ss << "[";
        for (auto it = (m_value.m_array)->begin();
            it != (m_value.m_array)->end(); ++it) {
            if (it != (m_value.m_array)->begin()) {
                ss << ",";
            }
            ss << it->tostr();
        }
        ss << "]";
        break;
    case json_object:
        ss << "{";
        for (auto it = (m_value.m_object)->begin();
            it != (m_value.m_object)->end(); ++it) {
            if (it != (m_value.m_object)->begin()) {
                ss << ",";
            }
            ss << '\"' << it->first << '\"' << ":" << it->second.tostr();
        }
        ss << "}";
        break;
    default:
        break;
    }

    return ss.str();
}

Json& Json::operator[](const char *key){
    return this->operator[](std::string(key)); // 
}

Json& Json::operator[](const std::string &key) {
    if (m_type != json_object) {
        clear();
        m_type = json_object;
        m_value.m_object = std::make_shared<std::map<std::string, Json>>();
    }
    return (*(m_value.m_object))[key]; //return map[key] -> Json
}

void Json::operator=(const Json &other) {
    clear();
    deepcopy(other);
}

std::string Json::getKey(int index) const{
    if(m_type != json_object){
        throw std::logic_error("Only json_object can use the getKey() function");
    }

    size_t size = m_value.m_object->size();
    if (index < 0 || index >= size){
        throw std::logic_error("index out of range");
    }
    return std::next(m_value.m_object->begin(), index)->first;
}

std::string Json::getValue(int index) const{
    if(m_type != json_object){
        throw std::logic_error("Only json_object can use the getValue() function");
    }

    size_t size = m_value.m_object->size();
    if (index < 0 || index >= size){
        throw std::logic_error("index out of range");
    }

    return std::next(m_value.m_object->begin(), index)->second.tostr();
}