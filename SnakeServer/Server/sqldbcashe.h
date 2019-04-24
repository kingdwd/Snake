#ifndef SQLDBCASHE_H
#define SQLDBCASHE_H
#include "sqldbwriter.h"

#include <QMap>
#include <QHash>
#include <QSet>
#include <QVariantMap>

enum class SqlDBCasheWriteMode: int {
    Default = 0x0,
    On_New_Thread = 0x1,
    Force = 0x2,
} ;

namespace ClientProtocol {
    class BaseNetworkObject;
}

class SqlDBCashe : private SqlDBWriter
{
private:
    qint64 lastUpdateTime = 0;

    QMap <int, QVariantMap> items;
    QMap <int, QVariantMap> players;
    QHash <int, QSet<int>>  owners;

    int generateIdForItem() const;
    int generateIdForPalyer() const;

    bool checkPlayer(int id) override;
    bool checkItem(int idItem, int idOwner = -1) override;

    void globalUpdateDataBasePrivate(qint64 currentTime);
    void globalUpdateDataBase(SqlDBCasheWriteMode mode = SqlDBCasheWriteMode::Default);

    bool itemIsFreeFrom(int item) const override ;

public:
    SqlDBCashe();
    ~SqlDBCashe() override;

    bool initDb(const QString &sql = DEFAULT_DB_NAME,
                const QString &path = DEFAULT_DB_PATH) override;

    bool getItem(int id, ClientProtocol::BaseNetworkObject *res) override;
    int saveItem( ClientProtocol::BaseNetworkObject *res) override;
    bool getPlayer(int id, ClientProtocol::BaseNetworkObject *res) override;
    int savePlayer( ClientProtocol::BaseNetworkObject *res) override;

    bool giveAwayItem(int player, int item);
    bool getItem(int player, int item, bool check = true);
    bool moveItem(int owner, int receiver, int item);

    bool getAllItemsOfPalyer(int player, QSet<int>& items) override;
};

#endif // SQLDBCASHE_H
