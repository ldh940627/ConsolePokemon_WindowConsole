#pragma once
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <functional>
#include "Poketmon.h"


using namespace std;

class Wildpoketmongenerator
{
public:
    static void SetMapContext(const string& mapName);
    static shared_ptr<Poketmon> Generate();

private:
    static vector<function<shared_ptr<Poketmon>()>> currentWildTable;
};

