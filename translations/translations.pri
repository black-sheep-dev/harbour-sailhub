TRANSLATIONS += \
    translations/harbour-sailhub.ts \
    translations/harbour-sailhub-de.ts \
#    translations/harbour-sailhub-es.ts \
    translations/harbour-sailhub-fr.ts \
#    translations/harbour-sailhub-hu.ts \
    translations/harbour-sailhub-pl.ts \
#    translations/harbour-sailhub-ru.ts \
    translations/harbour-sailhub-zh_CN.ts
    


qm.input    = TRANSLATIONS
qm.output   = translations/${QMAKE_FILE_BASE}.qm
qm.commands = @echo "compiling ${QMAKE_FILE_NAME}"; \
                lrelease -idbased -silent ${QMAKE_FILE_NAME} -qm ${QMAKE_FILE_OUT}
qm.CONFIG   = target_predeps no_link

QMAKE_EXTRA_COMPILERS += qm

translations.files = $$OUT_PWD/translations
translations.path  = $$PREFIX/share/$$TARGET

INSTALLS += translations

