#! /usr/bin/env python

import sys

class Browser:
    def __init__(self):
        self.window = KMainWindow()
        self.widget = QWidget()
        self.window.setCentralWidget(self.widget)

        layout = QVBoxLayout(self.widget)
        self.addressBar = QLineEdit(self.widget)
        layout.addWidget(self.addressBar)
        self.web = QWebView(self.widget)
        self.web.load(QUrl("http://kubuntu.org"))
        layout.addWidget(self.web)
        self.window.show()

        QObject.connect(self.addressBar, SIGNAL("returnPressed()"), self.loadUrl)
        
    def loadUrl(self):
        print "Loading " + self.addressBar.text()
        self.web.load( QUrl(self.addressBar.text()) )

from PyKDE4.kdecore import *
from PyKDE4.kdeui import *

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PyQt4.QtWebKit import *

appName = "python-kde-tutorial"
catalog = ""
programName = ki18n("PyKDE Tutorial")
version = "1.0"
description = ki18n("A Small Qt WebKit Example")
license = KAboutData.License_GPL
copyright = ki18n("(c) 2008 Canonical Ltd")
text = ki18n("none")
homePage = "www.kubuntu.org"
bugEmail = ""
 
aboutData = KAboutData (appName, catalog, programName, version, description,
license, copyright, text, homePage, bugEmail)
 
KCmdLineArgs.init(sys.argv, aboutData)
 
app = KApplication()
tutorial = Browser()
 
sys.exit(app.exec_())

