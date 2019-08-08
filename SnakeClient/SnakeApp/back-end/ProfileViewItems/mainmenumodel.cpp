#include "mainmenumodel.h"
#include "userview.h"

#include <back-end/settings.h>
#include <quasarapp.h>
#include "mainclient.h"

MainMenuModel::MainMenuModel(QObject *ptr): QObject (ptr) {

    if(!ClientProtocol::initClientProtockol()) {
        QuasarAppUtils::Params::verboseLog("client protockol not inited", QuasarAppUtils::Error);
    }

    _userViewModel = new UserView (this);
    _conf = Settings::instans();

    auto adderss = _conf->value(SERVER_ADDRESS, SERVER_ADDRESS_DEFAULT).toString();
    auto port = _conf->value(SERVER_ADDRESS_PORT, SERVER_ADDRESS_DEFAULT_PORT).toInt();
    _client = new MainClient(adderss, static_cast<unsigned short>(port), this);

    connect(_client, &MainClient::sigOnlineStatusChanged,
            this , &MainMenuModel::onlineStatusChanged);

}

QObject *MainMenuModel::userViewModel() const {
    return _userViewModel;
}

int MainMenuModel::onlineStatus() const {
    return _client->onlineStatus();
}

void MainMenuModel::login(const QString &email, const QString &pass) {
    _client->login(email, pass.toUtf8());
}

void MainMenuModel::registerNewUser(const QString &email, const QString &name,
                                    const QString &pass) {
    _client->registration(email, name, pass.toUtf8());
}
