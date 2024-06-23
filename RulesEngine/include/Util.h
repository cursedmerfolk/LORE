#pragma once

#include <functional>
#include <vector>


/*
 * Filter a vector of CLASS instances by a property of that class.
 *
 * Example: `std::vector<Player> notDone = filterBy(players, &Player::doneMulligan, true);`
*/
template <typename TYPE, typename CLASS>
std::vector<CLASS> filterBy(
    const std::vector<CLASS>& instances,
    TYPE CLASS::*property,
    TYPE value,
    std::function<bool(const TYPE& a, const TYPE& b)> compare = [](const TYPE& a, const TYPE& b) { return a == b; }
 ) {
    std::vector<CLASS> found;
    for (auto& instance : instances) {
        if (instance.*property == value) {
            found.push_back(instance);
        }
    }
    return found;
}
