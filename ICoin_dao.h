#ifndef ICOIN_DAO_H
#define ICOIN_DAO_H

#include<vector>
#include<coin.h>
#include <QString>

class ICoin_dao
{
public:
    virtual std::vector<coin> coin_list() = 0;
    virtual void start_get_coin_by_id(const QString& id) = 0;
    virtual coin get_coin() = 0;

};

#endif // ICOIN_DAO_H
