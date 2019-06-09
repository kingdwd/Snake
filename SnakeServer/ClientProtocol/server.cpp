#include "server.h"
#include "quasarapp.h"
#include <QTcpSocket>
#include <factorynetobjects.h>
#include <pubkey.h>
#include "clientprotocol.h"

namespace ClientProtocol {

bool Server::parsePackage(const Package &pkg, QTcpSocket* sender) {
    if (!pkg.isValid()) {
        QuasarAppUtils::Params::verboseLog("incomming package is not valid!");
        changeKarma(sender->peerAddress().toIPv4Address(), CRITICAL_ERROOR);
        return false;
    }

    if (!sender->isValid()) {
        QuasarAppUtils::Params::verboseLog("incomming package is not valid!");
        changeKarma(sender->peerAddress().toIPv4Address(), LOGICK_ERROOR);
        return false;
    }

    switch (static_cast<Command>(pkg.hdr.command)) {
    case Command::Ping: {

        if (static_cast<Type>(pkg.hdr.type) != Type::Request) {
            return false;
        }

        Package pcg;

        if (!(pcg.create(Command::Ping, Type::Responke))) {
            return false;
        };

        pcg.hdr.sig = pkg.hdr.sig;

        if (!sendPackage(pcg, sender)) {
            QuasarAppUtils::Params::verboseLog("!responce not sendet!");
        }
        break;
    }

    default: {

        emit incomingReques(static_cast<Command>(pkg.hdr.command),
                            pkg.data, sender->peerAddress().toIPv4Address());
    }
    }

    return true;
}

bool Server::sendPackage(Package &pkg, QTcpSocket * target) {
    if (!pkg.isValid()) {
        return false;
    }

    if (!target || !target->isValid()) {
        qCritical() << "destination server not valid!";
        return false;
    }

    if (!target->waitForConnected()) {
        qCritical() << "no connected to server! " << target->errorString();
        return false;
    }

    auto bytes = pkg.toBytes();
    bool sendet = bytes.size() == target->write(bytes);

    return sendet;
}

void Server::ban(quint32 target) {
    _connections[target].ban();
}

void Server::unBan(quint32 target) {
    _connections[target].unBan();
}

bool Server::registerSocket(QTcpSocket *socket) {
    auto address = socket->peerAddress().toIPv4Address();

    if (_pool) {
        QuasarAppUtils::Params::verboseLog("key pool is not inited", QuasarAppUtils::Error);
        return false;
    }

    RSAKeyPair pair;

    if (!_pool->take(QRSAEncryption::RSA_128, pair)) {
        QuasarAppUtils::Params::verboseLog("key pool is empty", QuasarAppUtils::Error);
        return false;
    }

    _connections[address] = Connectioninfo(socket, DEFAULT_KARMA,
                                           pair);

    connect(socket, &QTcpSocket::readyRead, this,  &Server::avelableBytes);
    connect(socket, &QTcpSocket::disconnected, this,  &Server::handleDisconected);

    if (!sendPubKey(socket, pair.pub)) {
        QuasarAppUtils::Params::verboseLog("not sendet pub key to client"
                                           "generate new key!", QuasarAppUtils::Error);
        return false;
    }

    return true;
}

bool Server::changeKarma(quint32 addresss, int diff) {
    auto objKarma = _connections.value(addresss).getKarma();

    if (objKarma >= NOT_VALID_CARMA) {
        return false;
    }

    if (objKarma <= BANED_KARMA) {
        return false;
    }

    _connections[addresss].setKarma(objKarma + diff);
    return true;
}

bool Server::isBaned(const QTcpSocket * adr) const {
    return _connections.value(adr->peerAddress().toIPv4Address()).isBaned();
}

int Server::connectionsCount() const {
    int count = 0;
    for (auto i : _connections) {
        if (i.getSct()) {
            if (!i.getSct()->isValid()) {
                QuasarAppUtils::Params::verboseLog("connection count, findet not valid socket",
                                                   QuasarAppUtils::Warning);
            }

            count++;
        }
    }
    return count;
}

bool Server::sendPubKey(QTcpSocket * target, const QByteArray &pubKey) {

    Package pcg;

    PubKey pubkey;

    pubkey.setKey(pubKey);
    pubkey.setTypeKey(QRSAEncryption::RSA_128);
    pubkey.setId(0);

    if (!pubkey.isValid()) {
        return false;
    }

    if (!(pcg.create(&pubkey, Type::Responke))) {
        return false;
    };

    return sendPackage(pcg, target);

}

void Server::avelableBytes() {
    auto client = dynamic_cast<QTcpSocket*>(sender());

    if (!client) {
        return;
    }

    auto array = client->readAll();

    if (_downloadPackage.hdr.isValid()) {
        _downloadPackage.data.append(array);

    } else {
        memcpy(&_downloadPackage.hdr,
               array.data(), sizeof(Header));
        _downloadPackage.data.append(array.mid(sizeof(Header)));
    }

    if (_downloadPackage.isValid()) {
        parsePackage(_downloadPackage, client);
        _downloadPackage.reset();
        return;
    }
}

void Server::handleDisconected() {
    auto _sender = dynamic_cast<QTcpSocket*>(sender());

    if (_sender) {
        // log error

        unsigned int address = _sender->peerAddress().toIPv4Address();
        if (_connections.contains(address)) {
            _connections[address].disconnect();
        } else {
            QuasarAppUtils::Params::verboseLog("system error in void Server::handleDisconected()"
                                               " address not valid",
                                               QuasarAppUtils::Error);
        }
        return;
    }

    QuasarAppUtils::Params::verboseLog("system error in void Server::handleDisconected()"
                                       "dynamic_cast fail!",
                                       QuasarAppUtils::Error);
}

void Server::handleIncommingConnection() {
    while (hasPendingConnections()) {
        auto socket = nextPendingConnection();

        if (isBaned(socket)) {
            socket->abort();
            break;
        }

        registerSocket(socket);
    }
}

Server::Server(RSAKeysPool *pool, QObject *ptr) :
    QTcpServer (ptr) {

    _pool = pool;
    connect(this, &Server::newConnection, this, &Server::handleIncommingConnection);
}

Server::~Server() {
}

bool Server::run(const QString &ip, unsigned short port) {
    if (!listen(QHostAddress(ip), port) ) {
        QuasarAppUtils::Params::verboseLog("listing fail " + this->errorString());
        return false;
    }

    return true;
}

void Server::stop(bool reset) {
    close();

    if (reset) {
        _connections.clear();
    }
}

void Server::badRequest(quint32 address) {
    auto client = _connections.value(address);

    if (!changeKarma(address, REQUEST_ERROR)) {
        return;
    }

    Package pcg;
    if (!(pcg.create(Command::BadRequest, Type::Responke))) {
        QuasarAppUtils::Params::verboseLog("Bad request detected, bud responce command nor received!",
                                           QuasarAppUtils::Error);
    };

    if (!sendPackage(pcg, client.getSct())) {
        return;
    }
}

QString Server::getWorkState() const {
    if (isListening()) {
        if (hasPendingConnections())
            return "overload";
        else {
            return "Work";
        }
    }

    return "Not running";
}

QString Server::connectionState() const {
    return QString("%0 / %1").arg(connectionsCount()).arg(maxPendingConnections());
}

QStringList Server::baned() const {
    QStringList list = {};
    for (auto i = _connections.begin(); i != _connections.end(); ++i) {
        if (i.value().isBaned()) {
            list.push_back(QHostAddress(i.key()).toString());
        }
    }

    return list;
}


}
