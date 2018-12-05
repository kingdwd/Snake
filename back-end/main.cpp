#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include "controller.h"
#include "diff.h"
#include <iostream>

bool initLocale(const QString &locale, QCoreApplication& app, QTranslator &translator){

    QString defaultLocale = QLocale::system().name();
    defaultLocale.truncate(defaultLocale.lastIndexOf('_'));

    if(!locale.isEmpty() && translator.load(QString(":/languages/%0").arg(locale))){
        return app.installTranslator(&translator);
    }

    if(!translator.load(QString(":/languages/%0").arg(defaultLocale))){
        return false;
    }

    return app.installTranslator(&translator);
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QTranslator translator;

    QString locale = "";

    if(argc > 1) {
        locale = QString::fromLatin1(argv[1]);
    }

    if(!initLocale(locale, app, translator)){
        std::cout << "error load language : " << locale.toStdString() <<std::endl;
    }

    QQmlApplicationEngine engine;

    //qmlRegisterType <Controller> ("Controller", 1, 0,"Controller");
    qmlRegisterType <GuiObject> ();
    qmlRegisterType <Diff> ();

    auto root = engine.rootContext();
    if (!root)
        return -1;

    Controller contr;
    root->setContextProperty("contr", &contr);

    engine.load(QUrl(QStringLiteral("qrc:/front-end/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
