#include "coin.h"

coin::coin() = default;

coin::coin(const QString& id, const QString& symbol, const QString& name, double price, double change_percent):
    m_id{id}, m_symbol{symbol}, m_name{name}, m_price_usd{price}, m_change_percent24Hr{change_percent}{}

QString coin::id() const
{
    return m_id;
}

void coin::setId(const QString &id)
{
    m_id = id;
}

QString coin::symbol() const
{
    return m_symbol;
}

void coin::setSymbol(const QString &symbol)
{
    m_symbol = symbol;
}

QString coin::name() const
{
    return m_name;
}

void coin::setName(const QString &name)
{
    m_name = name;
}

double coin::price_usd() const
{
    return m_price_usd;
}

void coin::setPrice_usd(double price_usd)
{
    m_price_usd = price_usd;
}

double coin::change_percent24Hr() const
{
    return m_change_percent24Hr;
}

void coin::setChange_percent24Hr(double change_percent24Hr)
{
    m_change_percent24Hr = change_percent24Hr;
}
