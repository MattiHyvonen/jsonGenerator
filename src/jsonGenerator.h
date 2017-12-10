#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

//any value that can be represented as string
class stringifiable {
public:
	std::string str;

	stringifiable(std::string str_ = "default") : str("\"" + str_ + "\"") {}
	stringifiable(float f) : str(std::to_string(f) ) {}
	stringifiable(const stringifiable& s) {
		str = s.stringify();
	}

	virtual std::string stringify() const {
		return str;
	}
};

//pair of any values represented as: <name> : <value>
class pair_json : public stringifiable {
public:
	stringifiable name;
	stringifiable value;

	pair_json(std::string name_ = "name", std::string value_ = "value") : name(name_), value(value_) {}
	pair_json(std::string name_, float value_) : name(name_), value(value_) {}
	pair_json(std::string name_, const stringifiable& value_) : name(name_), value(value_) {}

	virtual std::string stringify() const {
		std::string result = name.stringify() + " : " + value.stringify();
		return result;
	}
};

//object is a comma-separated list of name-value pairs: {"name" : value, "name" : value, "name" : value}
//an object starts & ends with braces {}
class object_json : public stringifiable {
public:
	std::vector<pair_json> members;

	object_json(const std::vector<pair_json>& members_ = std::vector<pair_json>() ) : members(members_) {}
	void add(pair_json newPair) {
		members.push_back(newPair);
	}

	virtual std::string stringify() const {
		std::string result = "{";
		for (unsigned int i = 0; i < members.size(); i++) {
			result += members[i].stringify();
			if(i != members.size() - 1)
				result += ", ";
		}
		result += "}";
		return result;
	}
};

//array is a comma-separated list of values. Note: putting pairs into array is possible,
//but not permitted in json!
//TODO: override constructor for vector<pair_json> and convert pairs into objects, adding {}
class array_json : public stringifiable {
public:
	std::vector<stringifiable> members;

	array_json(const std::vector<stringifiable>& members_ = std::vector<stringifiable>() ) : members(members_) {}

	void add(stringifiable newValue) {
		members.push_back(newValue);
	}

	virtual std::string stringify() const {
		std::string result = "[";
		for (unsigned int i = 0; i < members.size(); i++) {
			result += members[i].stringify();
			if (i != members.size() - 1)
				result += ", ";
		}
		result += "]";
		return result;
	}
};

//json object representing a 2d vector as: {"x" : <x>, "y" : <y>}
class vec2_json : public object_json {
public:
	vec2_json(float x = 0, float y = 0) : object_json(std::vector<pair_json>(2) ) {
		members[0] = pair_json("x", x);
		members[1] = pair_json("y", y);
	}
};

//json object representing a color as: {"r" : <r>, "g" : <g>, "b" : <b>}
class rgb_json : public object_json {
public:
	rgb_json(int r = 0, int g = 0, int b = 0) : object_json(std::vector<pair_json>(3)) {
		members[0] = pair_json("r", r);
		members[1] = pair_json("g", g);
		members[2] = pair_json("b", b);
	}
};

