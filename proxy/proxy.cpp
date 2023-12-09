﻿// proxy.cpp : Домашнее задание к занятию «Структурные шаблоны: Proxy, Decorator, Adapter»
//
#include <map>
#include <string>
#include <iostream>
#include <memory>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept {
        return "Very Big Data String: " + key;
    }
};

class CacheProxyDB :VeryHeavyDatabase {
public:
    explicit CacheProxyDB(VeryHeavyDatabase& real_object) :real_db_(std::make_unique<VeryHeavyDatabase>(real_object)) {}
    std::string GetData(const std::string& key) noexcept {
        if (cache_.find(key) == cache_.end()){
            std::cout << "Get from real object\n";
            cache_[key] = real_db_->GetData(key);
        }else{
            std::cout << "Get from cache\n";
        }
        return cache_.at(key);
    }
private:
    std::map<std::string, std::string> cache_;
    std::unique_ptr<VeryHeavyDatabase> real_db_;
};

class TestDB :VeryHeavyDatabase 
{
public:
    explicit TestDB(VeryHeavyDatabase& real_object) :real_db_(std::make_unique<VeryHeavyDatabase>(real_object)) {}
    
        std::string GetData(const std::string & key) noexcept 
        {
            return "test_data\n";
        }
private:
    std::unique_ptr<VeryHeavyDatabase> real_db_;
};

class OneShotDB : VeryHeavyDatabase {
public:
    explicit OneShotDB(VeryHeavyDatabase& real_object, size_t shots = 1):real_db_(std::make_unique<VeryHeavyDatabase>(real_object)), shots_(shots){}
    std::string GetData(const std::string& key) noexcept {
        if(shots_)
        {
            shots_--;
            return real_db_->GetData(key);
        }
        else {
            return "error";
        }
    }
private:
    std::unique_ptr<VeryHeavyDatabase> real_db_;
    size_t shots_;
};

int main()
{
    auto real_db = VeryHeavyDatabase();
    auto cached_db = CacheProxyDB(real_db);
    auto test_db = TestDB(real_db);
    std::cout << cached_db.GetData("key") << std::endl;
    std::cout << cached_db.GetData("key") << std::endl;
    std::cout << test_db.GetData("key") << std::endl;

    auto limit_db = OneShotDB(real_db, 2);
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;

    return 0;
}

