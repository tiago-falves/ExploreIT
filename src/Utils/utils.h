#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <time.h>


using namespace std;

/*vector<double> getSubStr(string in){
    std::vector<double> vect;

    std::stringstream ss(in);
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, ',' );
        double tmp = stod(substr);
        cout<<fixed;
        vect.push_back(tmp);
    }

    return vect;
}*/

template<class T> T *binarySearch(vector<T*> vector,long x)
{
    auto l=0;
    auto r=vector.size()-1;
    while (l <= r) {
        int m = l + (r - l) / 2;

        // Check if x is present at mid
        if (vector[m]->getId() == x)
            return vector.at(m);

        // If x greater, ignore left half
        if (vector[m]->getId() < x)
            l = m + 1;

        // If x is smaller, ignore right half
        else
            r = m - 1;
    }

    // if we reach here, then element was
    // not present
    return NULL;
}

template<class T> bool cmp(T *a,T*b){
    return (a->getId())<(b->getId());
}

/*std::string getUntilCharacter(std::string const& s,char character)
{
    std::string::size_type pos = s.find(character);
    if (pos != std::string::npos) return s.substr(0, pos);
    else return s;
}*/




#endif // UTILS_H
