export module day:day05;

import :base;
import std;
import common;

export class Day05 : public Day {
public:
    Day05() : Day(5) {}

    struct Range {
        std::uint64_t start;
        std::uint64_t end;

        Range() : Range(0, 0) {}
        Range(std::uint64_t sstart, std::uint64_t size) : start(sstart), end(sstart + size) {}

        bool contains(std::uint64_t num) const {
            return num >= start && num < end;
        }

        bool intersects(const Range& other) const {
            return start < other.end
                && other.start < end;
        }

        bool empty() const {
            return start >= end;
        }

        std::uint64_t len() const {
            return end - start;
        }
    };

    struct Mapping {
        std::uint64_t dst_start;
        Range src_range;

        Mapping(std::uint64_t dstart, std::uint64_t sstart, std::uint64_t size) : dst_start(dstart), src_range(sstart, size) {}

        /*bool operator<(const Mapping& other) {
            return src_start < other.src_start;
        }*/

        bool contains(std::uint64_t src_num) const {
            return src_range.contains(src_num);
        }

        std::uint64_t get(std::uint64_t src_num) const {
            return src_num - src_range.start + dst_start;
        }

        bool intersects(const Range& other) const {
            return src_range.intersects(other);
        }

        std::string get_str() const {
            return '[' + std::to_string(dst_start) + ", " + std::to_string(src_range.start) + "-" + std::to_string(src_range.end) + ']';
        }

    };


    /*
    
    - add MappingRange::get(Range rr) -> std::vector<Range>
    
    */


    struct MappingRange {
        std::map<std::uint64_t, Mapping> mappings;

        std::uint64_t get(std::uint64_t src_num) const {
            auto it = mappings.upper_bound(src_num);

            if (it != mappings.begin()) {
                auto& mapping = (std::prev(it))->second;
                if (mapping.contains(src_num)) {
                    return mapping.get(src_num);
                }
            }
            return src_num;
        }

        std::vector<Range> get(Range range) const {
            std::vector<Range> res;

            auto it = mappings.upper_bound(range.start);
            if (it != mappings.begin()) {
                it--;
            }

            while (!range.empty()) {
                if (it == mappings.end()) {
                    break;
                }

                auto& mapping = it->second;
                if (!mapping.intersects(range)) {
                    if (mapping.src_range.start >= range.end) {
                        break;
                    } else {
                        it++;
                        continue;
                    }
                }

                // Here we know that range intersects with mapping.
                // We have 4 cases:
                // 1: |--/==|==/ we start before and end in middle 
                // 2: /==|==/--| we start in middle nad end after
                // 3: |--/==/--| we start before and end after
                // 4: /==|==|==/ we start and end in the middle


                if (!mapping.contains(range.start)) {
                    // For cases 1&3 we need to extract the prefix first
                    res.push_back({range.start, mapping.src_range.start - range.start});
                    range.start = mapping.src_range.start;
                }

                // After prefix is removed, we need to get the mapping part
                const auto end = std::min(range.end, mapping.src_range.end);
                res.push_back({mapping.get(range.start), end - range.start});
                // After this operation we have exhausted either mapping or the range
                // We increment properly both and they will be checked at the top of while
                range.start = end;
                it++;
            }
            
            if (!range.empty()) {
                res.push_back(range);
            }
            return res;
        }
    };

private:
    std::string part1() override;
    std::string part2() override;
    void prepare_input() override;

    std::vector<std::uint64_t> m_seeds;
    std::vector<MappingRange> m_input;
};