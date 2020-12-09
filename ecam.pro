debug: DEFINES += DEBUG

TARGET = ecam
QT        += widgets
QT        += network
QT        += svg

HEADERS += ecam.h \
           widgets/arcwidget.h \
           widgets/analogclock.h \
           widgets/epr.h \
           widgets/epr_text.h \
           widgets/egt.h \
           widgets/n1rpm.h \
           widgets/n2rpm.h \
           widgets/flaps.h \
           pages/ewd_page.h \
           panels/sys_stat_panel.h \
           pages/fuel_page.h \
           pages/bleed_page.h \
           pages/cond_page.h \
           pages/memopage.h \
           widgets/valve.h \
           widgets/pump.h \
           model/tmp_time.h \
           widgets/faultoffbutton.h \
           model/pt1.h \
           model/enginecfm56.h \
           interface/simulation.h \
           interface/fgfs.h \
           structures/memo.h \
    pages/pfd_page.h


SOURCES += ecam.cpp \
           widgets/arcwidget.cpp \
           widgets/analogclock.cpp \
           widgets/epr.cpp \
           widgets/epr_text.cpp \
           widgets/egt.cpp \
           widgets/n1rpm.cpp \
           widgets/n2rpm.cpp \
           widgets/flaps.cpp \
           pages/ewd_page.cpp \
           panels/sys_stat_panel.cpp \
           main.cpp \
           pages/fuel_page.cpp \
           pages/bleed_page.cpp \
           pages/cond_page.cpp \
           pages/memopage.cpp \
           widgets/valve.cpp \
           widgets/pump.cpp \
           model/tmp_time.cpp \
           widgets/faultoffbutton.cpp \
           model/pt1.cpp \
           model/enginecfm56.cpp \
           interface/simulation.cpp \
           interface/fgfs.cpp \
           structures/memo.cpp \
    pages/pfd_page.cpp


RESOURCES +=

FORMS += \
           ecam.ui \
           pages/ewd_page.ui \
           pages/fuel_page.ui \
           pages/bleed_page.ui \
           pages/cond_page.ui \
           widgets/faultoffbutton.ui \
    pages/pfd_page.ui
