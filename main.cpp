#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "analyzer/frequencyanalyzer.h"
#include <QtDeclarative>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    qmlRegisterType<FrequencyAnalyzer>("org.meetuner", 1, 0, "Analyzer");

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/MeeTuner/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
