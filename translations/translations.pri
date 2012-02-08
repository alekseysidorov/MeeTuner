TEMPLATE = subdirs

# Add here the languages supported by your application
TS = ru_RU

# The list of directories inside src/ which you want translation
DIR = $$PWD/../
TS_DIR = $$PWD
QM_DIR = $$OUT_PWD/translations

isEmpty(QMAKE_LRELEASE) {
    QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
}

isEmpty(QMAKE_LUPDATE) {
    QMAKE_LUPDATE = $$[QT_INSTALL_BINS]/lupdate
}

defineReplace(prependAll) {
    prepend = $$1
    arglist = $$2
    append  = $$3

    for(a,arglist) {
        result += $${prepend}$${a}$${append}
    }

    return ($$result)
}

defineReplace(lreleaseAll) {
    source      = $$1
    destination = $$2
    arglist     = $$3

    for(a,arglist) {
        spath = $${source}$${a}.ts
        dpath = $${destination}$${a}.qm
        result += $$QMAKE_LRELEASE $$spath -qm $$dpath &&
    }

    # hack to prevent unexpected EOF
    result += echo

    return ($$result)
}

ts.commands = $$QMAKE_LUPDATE $$DIR -ts $$prependAll($$TS_DIR/MeeTuner_,$$TS,.ts) -noobsolete

qm.depends  = ts
qm.commands = mkdir -p $$OUT_PWD/translations && \
              $$lreleaseAll($$TS_DIR/MeeTuner_,$$OUT_PWD/translations/MeeTuner_,$$TS)

translations.path    = /opt/meetuner/share/translations
translations.files   = $$QM_DIR/*.qm
translations.CONFIG += no_check_exist
translations.depends = qm

QMAKE_EXTRA_TARGETS += translations ts qm

INSTALLS += translations
