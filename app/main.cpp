#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include "analyzer/frequencyanalyzer.h"
#include "analyzer/noteanalyzer.h"

#include <QtDeclarative>
#include <QDebug>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    qmlRegisterType<FrequencyAnalyzer>("org.meetuner", 1, 0, "FrequencyAnalyzer");
    qmlRegisterType<NoteAnalyzer>("org.meetuner", 1, 0, "NoteAnalyzer");

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app->installTranslator(&qtTranslator);

    QTranslator appTranslator;
    QString path = QApplication::applicationDirPath() % QLatin1Literal("/../share/translations");
    QString name = "MeeTuner_" + QLocale::system().name();
    if (appTranslator.load(name, path)) {
        app->installTranslator(&appTranslator);
        qDebug() << "loaded translation" << name;
    } else
        qWarning() << "Unable load meetuner translation file:" << name;

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("share/qml/MeeTuner/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
