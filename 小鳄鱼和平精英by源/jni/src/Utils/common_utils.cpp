/*
    By 开源 公益分享
   搜集各个公益文件分享
    更多公益开源 文件 @BYYXnb
    TG @BYYXnb QQ群 427975011
    
源码捐赠链接
https://v.youxi186.com/shop/YIZ6ZA6X

源码捐赠地址2：
https://shop.pp13.cn/shop/byyxnb

公益网盘资源分享
https://www.123865.com/s/NxyZVv-K44U3?提取码：QWT6

QQ群过验证[有的文件需要]
https://www.123865.com/s/f4A7Vv-Pqc0A?提取码：9IVI

由于易支付漏洞 如果进不去
如您需拿卡 点击 联系我
赞助链接已重新更新 

〖如果你点开提示 站点停止运行或者进不去，那么解决办法有两个

1.复制链接去别的浏览器打开
2.清除你浏览器的数据即可
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <random>
#include <fstream>
#include <chrono>
#include "cJSON.c"
#include <iomanip>
// #include <filesystem> // 添加此头文件以使用 std::filesystem

// 将查询字符串解析为键值对
std::vector<std::pair<std::string, std::string>> parse_query_string(const std::string &query)
{
    std::vector<std::pair<std::string, std::string>> params;
    std::istringstream stream(query);
    std::string pair;

    while (std::getline(stream, pair, '&'))
    {
        size_t pos = pair.find('=');
        if (pos != std::string::npos)
        {
            std::string key = pair.substr(0, pos);
            std::string value = pair.substr(pos + 1);
            params.emplace_back(key, value);
        }
    }

    return params;
}

// 将键值对重新组合为查询字符串
std::string build_query_string(const std::vector<std::pair<std::string, std::string>> &params)
{
    std::ostringstream oss;
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (i > 0)
        {
            oss << "&";
        }
        oss << params[i].first << "=" << params[i].second;
    }
    return oss.str();
}

// 对查询字符串进行字典排序
std::string sort_dict_req(const std::string &query)
{
    auto params = parse_query_string(query);
    std::sort(params.begin(), params.end());
    return build_query_string(params);
}

// 生成32位随机字符串
std::string generate_random_string(size_t length = 32)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);

    std::string random_string;
    for (size_t i = 0; i < length; ++i)
    {
        random_string += charset[dist(rng)];
    }
    return random_string;
}

std::string getProductUUID()
{
    const std::string filePath = "/storage/emulated/0/network/mac_random.txt";
    std::ifstream file(filePath);
    std::string uuid;

    if (file.is_open())
    {
        std::getline(file, uuid);
        file.close();
        if (!uuid.empty())
        {
            return uuid;
        }
    }

    // 如果文件不存在或内容为空，生成随机字符串并写入文件
    uuid = generate_random_string(32);
    std::ofstream outFile(filePath);
    if (outFile.is_open())
    {
        outFile << uuid;
        outFile.close();
    }

    return uuid;
}

// 获取当前的13位时间戳
std::string getCurrentTimestamp()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    return std::to_string(ms.count());
}

// 递归提取 JSON 中的键值对并存入 map
void extract_params(cJSON *json, std::map<std::string, std::string> &sorted_map)
{
    cJSON *current_element = nullptr;
    cJSON_ArrayForEach(current_element, json)
    {
        const char *key = current_element->string;
        if (!key)
            continue;

        if (cJSON_IsObject(current_element))
        {
            extract_params(current_element, sorted_map);
        }
        else
        {
            std::string value;
            if (cJSON_IsString(current_element))
            {
                value = cJSON_GetStringValue(current_element);
            }
            else if (cJSON_IsNumber(current_element))
            {
                // 使用 ostringstream 来格式化数字
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(0); // 使用固定格式并设置小数位数为0
                if (current_element->valuedouble == static_cast<int>(current_element->valuedouble))
                {
                    oss << static_cast<int>(current_element->valuedouble);
                }
                else
                {
                    oss << current_element->valuedouble;
                }
                value = oss.str();
            }
            else if (cJSON_IsNull(current_element))
            {
                value = "";
            }
            sorted_map[key] = value;
        }
    }
}

// 将 map 中的键值对拼接成字符串
std::string build_sorted_string(const std::map<std::string, std::string> &sorted_map)
{
    std::ostringstream oss;
    for (const auto &pair : sorted_map)
    {
        if (pair.first == "signature")
        {
            continue;
        }
        oss << pair.first << "=" << pair.second << "&";
    }
    std::string result = oss.str();
    if (!result.empty())
    {
        result.pop_back(); // 去掉最后一个多余的 "&"
    }
    return result;
}

// 按字典顺序排序 JSON 并返回排序后的字符串
std::string sort_json_by_ascii(const std::string &json_str)
{
    cJSON *json = cJSON_Parse(json_str.c_str());
    if (!json)
    {
        std::cerr << "Error parsing JSON" << std::endl;
        return "";
    }

    std::map<std::string, std::string> sorted_map;
    extract_params(json, sorted_map);
    cJSON_Delete(json);

    return build_sorted_string(sorted_map);
}

// 从请求参数中提取安全码
std::string extract_safe_code(const std::string &params)
{
    std::map<std::string, std::string> param_map;
    std::istringstream stream(params);
    std::string key_value;
    while (std::getline(stream, key_value, '&'))
    {
        size_t pos = key_value.find('=');
        if (pos != std::string::npos)
        {
            std::string key = key_value.substr(0, pos);
            std::string value = key_value.substr(pos + 1);
            param_map[key] = value;
        }
    }
    return param_map["safeCode"];
}

// 从响应参数中提取安全码
std::string extract_safe_code_from_json(const std::string &json_str)
{
    cJSON *json = cJSON_Parse(json_str.c_str());
    if (!json)
    {
        std::cerr << "Error parsing JSON" << std::endl;
        return "";
    }
    cJSON *safe_code_item = cJSON_GetObjectItem(json, "safeCode");
    std::string safe_code = safe_code_item ? safe_code_item->valuestring : "";
    cJSON_Delete(json);
    return safe_code;
}

// 从响应参数中提取签名
std::string extract_signature_from_json(const std::string &json_str)
{
    cJSON *json = cJSON_Parse(json_str.c_str());
    if (!json)
    {
        std::cerr << "Error parsing JSON" << std::endl;
        return "";
    }
    cJSON *safe_code_item = cJSON_GetObjectItem(json, "signature");
    std::string safe_code = safe_code_item ? safe_code_item->valuestring : "";
    cJSON_Delete(json);
    return safe_code;
}

// 从响应参数中提取时间戳
std::string extract_timestamp_from_json(const std::string &json_str)
{
    cJSON *json = cJSON_Parse(json_str.c_str());
    if (!json)
    {
        std::cerr << "Error parsing JSON" << std::endl;
        return "";
    }
    cJSON *safe_code_item = cJSON_GetObjectItem(json, "timestamp");
    std::string safe_code = safe_code_item ? std::to_string(static_cast<long long>(safe_code_item->valuedouble)) : "";
    cJSON_Delete(json);
    return safe_code;
}

// 从请求参数中提取时间戳
std::string extract_timestamp(const std::string &params)
{
    std::map<std::string, std::string> param_map;
    std::istringstream stream(params);
    std::string key_value;
    while (std::getline(stream, key_value, '&'))
    {
        size_t pos = key_value.find('=');
        if (pos != std::string::npos)
        {
            std::string key = key_value.substr(0, pos);
            std::string value = key_value.substr(pos + 1);
            param_map[key] = value;
        }
    }
    return param_map["timestamp"];
}