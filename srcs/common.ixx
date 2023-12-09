export module common;

export import :matrix;

import std;

export {
    std::vector<std::string_view> split(std::string_view str, char sep, size_t estimated_size = 0) {
        std::vector<std::string_view> res;
        if (estimated_size) {
            res.reserve(estimated_size);
        }

        size_t offset = 0;
        while (true) {
            const size_t cutpoint = str.find(sep, offset);
            const size_t count = cutpoint == std::string::npos ? cutpoint : cutpoint - offset;
            if (count)
                res.push_back(str.substr(offset, count));

            if (cutpoint == std::string::npos) {
                break;
            }
            offset = cutpoint + 1;
        }
        return res;
    }

    std::pair<std::string_view, std::string_view> split_once(std::string_view str, char sep) {
        const size_t cutpoint = str.find(sep);
        return std::make_pair(str.substr(0, cutpoint), str.substr(cutpoint + 1, std::string::npos));
    }

    std::pair<std::string_view, std::string_view> split_once(std::string_view str, const char* sep) {
        const size_t cutpoint = str.find(sep);
        const auto sep_size = std::strlen(sep);
        return std::make_pair(str.substr(0, cutpoint), str.substr(cutpoint + sep_size, std::string::npos));
    }

    std::vector<std::string_view> split(std::string_view str, const char* sep, size_t estimated_size = 0) {
        std::vector<std::string_view> res;
        if (estimated_size) {
            res.reserve(estimated_size);
        }

        const auto sep_size = std::strlen(sep);

        size_t offset = 0;
        while (offset < str.size()) {
            const size_t cutpoint = str.find(sep, offset);
            const size_t count = cutpoint == std::string::npos ? cutpoint : cutpoint - offset;
            if (count)
                res.push_back(str.substr(offset, count));

            if (cutpoint == std::string::npos) {
                break;
            }
            offset = cutpoint + sep_size + 1;
        }
        return res;
    }

    std::string_view trim_until_front(std::string_view str, const char* sep) {
        std::string_view result = str;
        const auto sep_size = std::strlen(sep);
        const size_t prefix_size = result.find(sep);
        if (prefix_size != std::string::npos) {
            result.remove_prefix(prefix_size + sep_size);
        }
        return result;
    }

    std::string_view trim_until_back(std::string_view str, const char* sep) {
        std::string_view result = str;
        const size_t suffix_size = result.rfind(sep);
        if (suffix_size != std::string::npos) {
            result.remove_suffix(result.size() - suffix_size);
        }
        return result;
    }

    template<typename T = int>
    T to_int(std::string_view sv) {
        T res = 0;
        std::from_chars(sv.data(), sv.data() + sv.size(), res);
        /*for (char c : sv) {
            if (c >= '0' && c <= '9')
                res = 10 * res + (c - '0');
        }*/
        return res;
    }
}