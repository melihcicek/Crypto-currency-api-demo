#ifndef COIN_H
#define COIN_H

#include<QString>

class coin
{
public:
    coin();
    coin(const QString& id, const QString& symbol, const QString& name, double price, double change_percent);

    QString id() const;
    void setId(const QString &id);

    QString symbol() const;
    void setSymbol(const QString &symbol);

    QString name() const;
    void setName(const QString &name);

    double price_usd() const;
    void setPrice_usd(double price_usd);

    double change_percent24Hr() const;
    void setChange_percent24Hr(double change_percent24Hr);

private:
    QString m_id{};
    QString m_symbol{};
    QString m_name{};
    double m_price_usd{};
    double m_change_percent24Hr{};

};

#endif // COIN_H
