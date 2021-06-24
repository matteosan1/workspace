#-*- coding:utf-8 -*-
import json, traceback

from PyQt5.QtCore import QObject, pyqtSlot, Qt
from PyQt5.QtWidgets import QWidget, QTableView, QPushButton, QHBoxLayout, QVBoxLayout, QDialog, QMessageBox
from PyQt5.QtGui import QStandardItemModel, QStandardItem

class JSONEditor(QDialog):
    def __init__(self, parent = None):
        super(JSONEditor, self).__init__(parent)

        self.settings = None
        self.model = QStandardItemModel(self)
        self.tableView = QTableView(self)
        self.tableView.setModel(self.model)
        self.tableView.horizontalHeader().setStretchLastSection(True)

        self.pushButtonWrite = QPushButton(self)
        self.pushButtonWrite.setText("Salva Impostazioni")
        self.pushButtonWrite.clicked.connect(self.on_pushButtonWrite_clicked)

        self.layoutVertical = QVBoxLayout(self)
        self.layoutVertical.addWidget(self.tableView)
        self.layoutVertical.addWidget(self.pushButtonWrite)
        self.settings = self.loadJSON()
        
    def loadJSON(self):
        settings = json.load(open("emailsender_settings.json"))
 
        for k, v in settings.items():
            v = json.dumps(v)
            items = [QStandardItem(k), QStandardItem(v)]
            self.model.appendRow(items)

        self.model.setHeaderData(0, Qt.Horizontal, "Parametro")
        self.model.setHeaderData(1, Qt.Horizontal, "Valore")
        return settings
        
    def writeJSON(self):
        fields = []
        for rowNumber in range(self.model.rowCount()):
            fields.append([self.model.data(self.model.index(rowNumber, columnNumber), Qt.DisplayRole) for columnNumber in range(self.model.columnCount())])

        for f in fields:
            try:
                self.settings[f[0]] = json.loads(f[1])
            except:
                QMessageBox.critical(self, "Impostazioni", "Errore nella riga {}".format(f[1]))
                break
        else:
            json.dump(self.settings, open("emailsender_settings.json", 'w'))
            self.close()
            
    @pyqtSlot()
    def on_pushButtonWrite_clicked(self):
        self.writeJSON()
        

