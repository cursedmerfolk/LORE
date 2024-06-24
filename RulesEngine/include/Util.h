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

/*
 * Check if a vector contains an instance, rather than using operator==.
*/
template <typename CLASS>
bool containsInstance(const std::vector<CLASS>& instances, CLASS& instance)
{
    // Get a vector of addresses, and check if the address of instance is in that vector.
    std::vector<const CLASS*> addresses;
    for (auto const& instance : instances)
    {
        addresses.push_back(&instance);
    }

    return std::find(addresses.begin(), addresses.end(), &instance) != addresses.end();
}
