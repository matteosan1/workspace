from PyQt5.QtCore import QObject, pyqtSlot, Qt
from PyQt5.QtWidgets import QTableView, QPushButton, QSpinBox, QHBoxLayout, QVBoxLayout, QFileDialog
from PyQt5.QtWidgets import QLabel, QDialog, QMessageBox, QInputDialog
from PyQt5.QtGui import QStandardItemModel, QStandardItem

class SpellCheckDialog(QDialog):
    def __init__(self, word, alternatives, parent = None):
        super(SpellCheckDialog, self).__init__(parent)

        self.word = word
        self.alternatives = alternatives
        self.result = None
        self.model = QStandardItemModel(self)
        self.tableView = QTableView(self)
        self.tableView.setModel(self.model)
        self.tableView.horizontalHeader().hide()#setStretchLastSection(True)
        self.tableView.verticalHeader().hide()#setStretchLastSection(True)

        for row_count, row in enumerate(self.alternatives):
            item = QStandardItem()
            item.setText(row)
            self.model.setItem(row_count, 0, item)
            
        self.pushButtonReplace = QPushButton(self)
        self.pushButtonReplace.setText("Sostituisci")
        self.pushButtonReplace.clicked.connect(self.replaceText)
        self.pushButtonSkip = QPushButton(self)
        self.pushButtonSkip.setText("Ignora")
        self.pushButtonSkip.clicked.connect(self.ignoreText)
                
        self.layoutButtons = QHBoxLayout()
        self.layoutButtons.addWidget(self.pushButtonReplace)
        self.layoutButtons.addWidget(self.pushButtonSkip)

        self.label = QLabel()
        self.label.setText(self.word)

        self.layoutVertical = QVBoxLayout(self)
        self.layoutVertical.addWidget(self.label)
        self.layoutVertical.addWidget(self.tableView)
        self.layoutVertical.addLayout(self.layoutButtons)

    @pyqtSlot()
    def replaceText(self):
        indexes = self.tableView.selectionModel().selectedRows()
        if len(indexes) != 0:
            self.result = (self.word, self.alternatives[indexes[0].row()])
            self.close()

    @pyqtSlot()
    def ignoreText(self):
        self.result = None
        self.close()
        

