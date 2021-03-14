import pandas as pd
import sys

from PyQt5.QtCore import Qt, QObject, QIdentityProxyModel
from PyQt5.QtSql import QSqlDatabase, QSqlTableModel, QSqlQuery
from PyQt5.QtGui import QImage, QStandardItem, QColor, QBrush
from PyQt5.QtWidgets import QMessageBox
#from mutagen.id3 import ID3

class ComponentItem(QStandardItem):
    def __init__(self, record):
        super(ComponentItem, self).__init__()
        self.record = record
        self.selected = False

    def data(self, role):
        if role == Qt.DisplayRole:
            txt = "{} - {}".format(self.record.field(1).value(),
                                   self.record.field(3).value())
            return txt
        elif role == Qt.BackgroundRole:
            if self.selected:
                return QBrush(QColor(173, 216, 230))
            else:
                return QBrush(QColor(255, 255, 255))

        
class MyProxyModel(QIdentityProxyModel):

    def __init__(self):
        super(MyProxyModel, self).__init__()
    
    def data(self, index, role):
        sourceIndex = self.mapToSource(index)
        originalText = self.sourceModel().data(sourceIndex, Qt.DisplayRole)
        if role == Qt.DecorationRole:
            if index.column() == 0:
                image = QImage(str(originalText)+'.jpg')
                if not image.isNull():
                    return image.scaled(50, 50, Qt.KeepAspectRatio)

        if (role != Qt.DisplayRole):
            return QIdentityProxyModel.data(self, index, role)
        
        if index.column() == 9:
            if originalText != '' and originalText != '0':
                newText = "{}m {}s".format(int(originalText)//60, int(originalText)%60)
            else:
                newText = ''
            return newText
        elif index.column() == 0:
            return ''
        else:
            return originalText

class MusicDB(QObject):
    def __init__(self):
        super(MusicDB).__init__()
        self.filename = "music_library.db"
        self.createConnection()
        self.model = QSqlTableModel()
        self.model.setTable("music")
        self.model.setEditStrategy(QSqlTableModel.OnManualSubmit)
        self.model.select()
        self.model.setHeaderData(1, Qt.Horizontal, "Title")
        self.model.setHeaderData(2, Qt.Horizontal, "Album")
        self.model.setHeaderData(3, Qt.Horizontal, "Artist")
        self.model.setHeaderData(4, Qt.Horizontal, "Release")
        self.model.setHeaderData(5, Qt.Horizontal, "Label")
        self.model.setHeaderData(6, Qt.Horizontal, "Tk. Pos.")
        self.model.setHeaderData(8, Qt.Horizontal, "Rate")
        self.model.setHeaderData(9, Qt.Horizontal, "Length")
        self.q = QSqlQuery()

    def createConnection(self):
        self.con = QSqlDatabase.addDatabase("QSQLITE")
        # FIXME CHECK IF FILE EXISTS
        self.con.setDatabaseName(self.filename)
        if not self.con.open():
            QMessageBox.critical(None, "QTableView Example - Error!",
                                 "Database Error: %s" % con.lastError().databaseText())

    def queryResult(self, res):
        if not res:
            print (self.q.lastError().text())
        print (self.q.executedQuery())        
            
    def initializeFromFile(self, filename):
        df = pd.read_csv(filename, sep=';')
        for i in range(len(df)):
            print (i, len(df))
            sql = "UPDATE music SET file_id=:file_id WHERE file_name=:file_name;"
            self.q.prepare(sql)
            self.q.bindValue(":file_id", str(df.loc[i][1]))
            self.q.bindValue(":file_name", df.loc[i][0])
            self.queryResult(self.q.exec())

    def incrementPlayed(self, file_id, rate):
        sql = "UPDATE music SET rate=:rate WHERE file_id=:file_id;"
            self.q.prepare(sql)
            self.q.bindValue(":file_id", file_id)
            self.q.bindValue(":rate", rate)
            self.queryResult(self.q.exec())

    def removeFile(self, file_id):
        sql = "DELETE FROM music WHERE file_id=:file_id;"
        self.q.prepare(sql)
        self.q.bindValue(":file_id", str(file_id))
        self.queryResult(self.q.exec())
            
#    def addSong(self):
#        # seleziona il file
#        # controlla se ha i tag e leggili
#        # form per aggiornare i tag anche da internet
#        pass
#
#    def setModel(self):
#        # Set up the model
#        self.model = QSqlTableModel(self)
#        self.model.setTable("music")
#        self.model.setEditStrategy(QSqlTableModel.OnFieldChange)
#        self.model.setHeaderData(0, Qt.Horizontal, "title")
#        self.model.setHeaderData(1, Qt.Horizontal, "artist")
#        self.model.setHeaderData(2, Qt.Horizontal, "album")
#        self.model.setHeaderData(3, Qt.Horizontal, "rate")
#        self.model.select()
#        # Set up the view
#        self.view = QTableView()
#        self.view.setModel(self.model)
#        self.view.resizeColumnsToContents()
#        self.setCentralWidget(self.view)
#
#app = QApplication(sys.argv)
#win = MusicDB()
#win.show()
#sys.exit(app.exec_())
#



