//
// Created by musta on 20.12.2022.
//

#ifndef PROJECT_2_AIRPORT_H
#define PROJECT_2_AIRPORT_H
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

class Airport {

public:

    /// @brief Empty constructor
    Airport();

    /**
     * @brief Constructor that receives input line from csv file
     * @param in -> input line from csv file
     */
    explicit Airport(const string& in);

    /// @brief Gets airport name
    string getName() const;

    /// @brief Gets airport code
    string getCode() const;

    /// @brief Gets airport city
    string getCity() const;

    /// @brief gets airport country
    string getCountry() const;

    /// @brief gets airport latitude
    double getLatitude() const;

    /// @brief gets airport longitude
    double getLongitude() const;

    bool isValid();

    void toInvalid();
    void toValid();

    /**
     * @brief Gets distance to certain coordinate
     * @param lat2 -> Latitude
     * @param lon2 -> Longitude
     * @return distance as double
     */
    double getDistanceTo(double lat2, double lon2) const;

    /// @brief Overload of <em>operator<< </em>
    friend ostream& operator<< (ostream& out, const Airport& s1);
private:

    /// @brief Airport information
    string name, code, city, country;

    /// @brief Airport coordinate
    double latitude, longitude;

    bool valid_bit;
};


#endif //PROJECT_2_AIRPORT_H
