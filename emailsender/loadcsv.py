#-*- coding:utf-8 -*-
import csv
import pandas as pd

from PyQt5.QtCore import QObject, pyqtSlot, Qt
from PyQt5.QtWidgets import QTableView, QPushButton, QSpinBox, QHBoxLayout, QVBoxLayout, QFileDialog
from PyQt5.QtWidgets import QLabel, QDialog, QMessageBox, QInputDialog
from PyQt5.QtGui import QStandardItemModel, QStandardItem

class CSVLoader(QDialog):
    def __init__(self, parent = None):
        super(CSVLoader, self).__init__(parent)

        self.email_addresses = None
        self.model = QStandardItemModel(self)
        self.tableView = QTableView(self)
        self.tableView.setModel(self.model)
        self.tableView.horizontalHeader().setStretchLastSection(True)

        self.pushButtonWrite = QPushButton(self)
        self.pushButtonWrite.setText("Seleziona Elenco")

        self.spin = QSpinBox(self)
        self.label = QLabel()
        self.label.setText("Colonna indirizzi email:")

        self.layoutHorizontal = QHBoxLayout()
        self.layoutHorizontal.addWidget(self.label)
        self.layoutHorizontal.addWidget(self.spin)

        self.layoutVertical = QVBoxLayout(self)
        self.layoutVertical.addWidget(self.tableView)
        self.layoutVertical.addLayout(self.layoutHorizontal)
        self.layoutVertical.addWidget(self.pushButtonWrite)

        options = QFileDialog.Options()
        self.fileName, _ = QFileDialog.getOpenFileName(self, "Elenco Destinatari", "",
                                                       "Tutti i file (*);;CSV Files (*.csv);;CSV Files (*.xlsx)",
                                                       options=options)

        if self.fileName != '':
            if self.fileName.endswith('.csv'):
                self.loadCsv()
            else:
                self.loadXls()
            self.spin.setRange(1, self.model.columnCount())
            self.on_pushButtonWrite_clicked()
        else:
            return

    def loadXls(self):
        #xl = pd.ExcelFile('foo.xls')
        #xl.sheet_names  # see all sheet names
        #xl.parse(sheet_name)

        df = pd.read_excel(self.fileName, sheet_name="Foglio2")
        #df = df.fillna(0)
        column, res = QInputDialog.getItem(self, "Indirizzi Email", "Colonna:", df.columns)
        if res:
            self.email_addresses = df[column].dropna().to_list()
            #for v in emails:
            #    items = QStandardItem(v)
            #    self.model.appendRow(items)

    def loadCsv(self):
        df = pd.read_csv(self.fileName)
        column, res = QInputDialog.getItem(self, "Indirizzi Email", "Colonna:", df.columns)
        if res:
            self.email_addresses = df[column].dropna().to_list()
#        with open(self.fileName, "r") as fileInput:
#            for row in csv.reader(fileInput):    
#                items = [
#                    QStandardItem(field)
#                    for field in row
#                ]
#                self.model.appendRow(items)

    def writeCsv(self):
        with open(self.fileName, "w") as fileOutput:
            writer = csv.writer(fileOutput)
            for rowNumber in range(self.model.rowCount()):
                fields = [
                    self.model.data(
                        self.model.index(rowNumber, columnNumber),
                        Qt.DisplayRole
                    )
                    for columnNumber in range(self.model.columnCount())
                ]
                writer.writerow(fields)

    @pyqtSlot()
    def on_pushButtonWrite_clicked(self):
        ##self.writeCsv(self.fileName)
        #email_column = self.spin.value()-1
        #self.email_addresses = []
        #for rowNumber in range(self.model.rowCount()):
        #    it = self.model.data(self.model.index(rowNumber, email_column), Qt.DisplayRole)
        #    if it != '' and "@" in it:
        #self.email_addresses = .append(it)

        if len(self.email_addresses) == 0:
            QMessageBox.critical(self, "Colonna Errata", "Controlla la colonna indirizzi email.")
        else:
            self.close()

        

