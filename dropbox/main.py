import sys, json, os

from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget, QVBoxLayout, QHBoxLayout
from PyQt5.QtWidgets import QAction, QFileDialog, QMessageBox, QPushButton, QLineEdit
from PyQt5.QtWidgets import QLabel, QMenu, QSlider, QProgressBar, QSizePolicy, QTableView
from PyQt5.QtWidgets import QAbstractItemView, QStackedWidget, QListView, QMessageBox, QSpacerItem
from PyQt5.QtWidgets import QSizePolicy
from PyQt5.QtCore import Qt, pyqtSlot, QItemSelection
from PyQt5.QtGui import QPixmap, QIcon, QStandardItemModel, QBrush, QColor
from PyQt5.QtSql import QSqlQuery
from PyQt5.QtMultimedia import QMediaPlayer

from db import MusicDB, MyProxyModel, ComponentItem
from box import BoxHelper
from qwaitingspinner import QtWaitingSpinner
from player import MyPlayer
from customdropdown import ComboCheckBox

class MainWindow(QMainWindow):

    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)
        self.box = BoxHelper()
        self.box.update_thread.startThread.connect(self.startUpdate)
        self.box.update_thread.endThread.connect(self.endUpdate)
        
        self.db = MusicDB()
        self.query = QSqlQuery()
        self.player = MyPlayer()
        self.player.player.mediaStatusChanged.connect(self.qmp_mediaStatusChanged)
        self.player.player.stateChanged.connect(self.qmp_stateChanged)
        self.player.player.positionChanged.connect(self.qmp_positionChanged)
        self.player.player.volumeChanged.connect(self.qmp_volumeChanged)
        self.player.currentIndexChanged.connect(self.playlistIdxChanged)
        self.playlist = {}

        self.setFixedWidth(900)
        self.setFixedHeight(600)

        layout = QVBoxLayout()
        hlayout = QHBoxLayout()

        hlayout2 = QHBoxLayout()
        self.labelCover = QLabel()
        self.labelCover.setFixedWidth(200)
        self.labelCover.setFixedHeight(200)
        hlayout2.addWidget(self.labelCover)

        vlayout2 = QVBoxLayout()
        vlayout2.addStretch()
        self.labelTitle = QLabel()
        self.labelTitle.setWordWrap(True)
        vlayout2.addWidget(self.labelTitle)
        self.labelAlbum = QLabel()
        self.labelAlbum.setWordWrap(True)
        vlayout2.addWidget(self.labelAlbum)
        self.labelArtist = QLabel()
        self.labelArtist.setWordWrap(True)
        self.labelArtist.setFixedWidth(300)
        vlayout2.addWidget(self.labelArtist)
        vlayout2.addStretch()
        hlayout2.addLayout(vlayout2)

        controlArea = QVBoxLayout()  
        seekSliderLayout = QHBoxLayout()
        controls = QHBoxLayout()
        playlistCtrlLayout = QHBoxLayout()
        
        #creating buttons
        pixmap = QPixmap("pause-play-button.png")
        buttonIcon = QIcon(pixmap)
        self.pauseBtn = QPushButton()
        self.pauseBtn.setIcon(buttonIcon)
        self.pauseBtn.setIconSize(pixmap.rect().size())
        pixmap = QPixmap("stop-button.png")
        buttonIcon = QIcon(pixmap)
        self.stopBtn = QPushButton()
        self.stopBtn.setIcon(buttonIcon)
        self.stopBtn.setIconSize(pixmap.rect().size())
        pixmap = QPixmap("volumedown-button.png")
        buttonIcon = QIcon(pixmap)
        self.volumeDescBtn = QPushButton()
        self.volumeDescBtn.setIcon(buttonIcon)
        self.volumeDescBtn.setIconSize(pixmap.rect().size())
        pixmap = QPixmap("volumeup-button.png")
        buttonIcon = QIcon(pixmap)
        self.volumeIncBtn = QPushButton()
        self.volumeIncBtn.setIcon(buttonIcon)
        self.volumeIncBtn.setIconSize(pixmap.rect().size())

        self.progress = QProgressBar()
        self.progress.setRange(0, 100)
        self.progress.setTextVisible(True)
        self.progress.setValue(self.player.player.volume())
        
        #creating playlist controls
        pixmap = QPixmap("previous-track-button.png")
        buttonIcon = QIcon(pixmap)
        self.prevBtn = QPushButton()
        self.prevBtn.setIcon(buttonIcon)
        self.prevBtn.setIconSize(pixmap.rect().size())
        
        vlayout3 = QVBoxLayout()
        self.labelPlaylist = QLabel()
        self.labelPlaylist.setAlignment(Qt.AlignCenter)
        self.labelPlaylist.setText("No Songs")
        vlayout3.addWidget(self.labelPlaylist)
        pixmap = QPixmap("playlist-button.png")
        buttonIcon = QIcon(pixmap)
        self.playlistBtn = QPushButton()
        self.playlistBtn.setIcon(buttonIcon)
        self.playlistBtn.setIconSize(pixmap.rect().size())
        self.playlistBtn.setCheckable(True)
        vlayout3.addWidget(self.playlistBtn)
        pixmap = QPixmap("next-track-button.png")
        buttonIcon = QIcon(pixmap)
        self.nextBtn = QPushButton()
        self.nextBtn.setIcon(buttonIcon)
        self.nextBtn.setIconSize(pixmap.rect().size())

        #creating seek slider
        self.seekSlider = QSlider()
        self.seekSlider.setMinimum(0)
        self.seekSlider.setMaximum(100)
        self.seekSlider.setOrientation(Qt.Horizontal)
        self.seekSlider.setTracking(False)
        self.seekSlider.sliderMoved.connect(self.seekPosition)
        #self.seekSlider.valueChanged.connect(self.seekPosition)
        
        self.seekSliderLabel1 = QLabel('0.00')
        self.seekSliderLabel2 = QLabel('0.00')
        seekSliderLayout.addWidget(self.seekSliderLabel1)
        seekSliderLayout.addWidget(self.seekSlider)
        seekSliderLayout.addWidget(self.seekSliderLabel2)
        
        #Add handler for each button. Not using the default slots.
        self.pauseBtn.clicked.connect(self.play)
        self.stopBtn.clicked.connect(self.player.stopHandler)
        self.volumeDescBtn.clicked.connect(self.player.decreaseVolume)
        self.volumeIncBtn.clicked.connect(self.player.increaseVolume)
        
        #Adding to the horizontal layout
        controls.addWidget(self.volumeDescBtn)
        controls.addWidget(self.pauseBtn)
        controls.addWidget(self.stopBtn)
        controls.addWidget(self.volumeIncBtn)
        
        #playlist control button handlers
        self.prevBtn.clicked.connect(self.player.prevItemPlaylist)
        self.nextBtn.clicked.connect(self.player.nextItemPlaylist)
        self.playlistBtn.clicked.connect(self.showPlaylist)
        playlistCtrlLayout.addWidget(self.prevBtn)
        playlistCtrlLayout.addLayout(vlayout3)
        playlistCtrlLayout.addWidget(self.nextBtn)
        
        #Adding to the vertical layout
        controlArea.addLayout(seekSliderLayout)
        controlArea.addLayout(controls)
        controlArea.addWidget(self.progress)
        controlArea.addLayout(playlistCtrlLayout)
        hlayout2.addLayout(controlArea)
        layout.addLayout(hlayout2)

        self.stack = QStackedWidget()
        self.view = QTableView()
        self.view.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.proxy = MyProxyModel()
        self.proxy.setSourceModel(self.db.model)
        self.view.setModel(self.proxy)
        self.view.hideColumn(0)
        self.view.hideColumn(4)
        self.view.hideColumn(5)
        self.view.hideColumn(6)
        self.view.hideColumn(7)
        self.view.hideColumn(9)
        self.view.hideColumn(10)
        self.view.hideColumn(11)
        self.view.selectionModel().selectionChanged.connect(self.viewSelection)
        self.view.setContextMenuPolicy(Qt.CustomContextMenu)
        self.view.customContextMenuRequested.connect(self.contextMenuEvent)
        self.view.resizeColumnsToContents()
        self.view.horizontalHeader().setStretchLastSection(True)
        self.view.setSortingEnabled(True)
        self.view.verticalHeader().setVisible(False)
        self.stack.addWidget(self.view)
        self.viewpl = QListView()
        self.modelpl = QStandardItemModel()
        self.viewpl.setModel(self.modelpl)
        self.stack.addWidget(self.viewpl)
        layout.addWidget(self.stack)
        
        hlayout2 = QHBoxLayout()
        pixmap = QPixmap("search-button.png")
        buttonIcon = QIcon(pixmap)
        self.pushButton_2 = QPushButton()
        self.pushButton_2.setIcon(buttonIcon)
        self.pushButton_2.setIconSize(pixmap.rect().size())
        hlayout2.addWidget(self.pushButton_2)
        self.lineEdit = QLineEdit()
        hlayout2.addWidget(self.lineEdit)
        layout.addLayout(hlayout2)
#        
        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)
#
#        self.status = QStatusBar()
#        self.setStatusBar(self.status)
#
#        # Uncomment to disable native menubar on Mac
        self.menuBar().setNativeMenuBar(False)
#
#        file_toolbar = QToolBar("File")
#        file_toolbar.setIconSize(QSize(14, 14))
#        self.addToolBar(file_toolbar)
        file_menu = self.menuBar().addMenu("&File")

        add_file_action = QAction("Upload file...", self) #QIcon(os.path.join('images', 'blue-folder-open-document.png')), "Open file...", self)
        add_file_action.setStatusTip("Upload file")
        add_file_action.triggered.connect(self.addFile)
        file_menu.addAction(add_file_action)

        save_file_action = QAction("Remove file..", self)
        save_file_action.setStatusTip("Remove Selected File")
        save_file_action.triggered.connect(self.removeFile)
        file_menu.addAction(save_file_action)

#
#        saveas_file_action = QAction(QIcon(os.path.join('images', 'disk--pencil.png')), "Save As...", self)
#        saveas_file_action.setStatusTip("Save current page to specified file")
#        saveas_file_action.triggered.connect(self.file_saveas)
#        file_menu.addAction(saveas_file_action)
#        file_toolbar.addAction(saveas_file_action)
#
#        print_action = QAction(QIcon(os.path.join('images', 'printer.png')), "Print...", self)
#        print_action.setStatusTip("Print current page")
#        print_action.triggered.connect(self.file_print)
#        file_menu.addAction(print_action)
#        file_toolbar.addAction(print_action)
#
#        edit_toolbar = QToolBar("Edit")
#        edit_toolbar.setIconSize(QSize(16, 16))
#        self.addToolBar(edit_toolbar)
#        edit_menu = self.menuBar().addMenu("&Edit")
#
#        undo_action = QAction(QIcon(os.path.join('images', 'arrow-curve-180-left.png')), "Undo", self)
#        undo_action.setStatusTip("Undo last change")
#        undo_action.triggered.connect(self.editor.undo)
#        edit_menu.addAction(undo_action)
#
#        redo_action = QAction(QIcon(os.path.join('images', 'arrow-curve.png')), "Redo", self)
#        redo_action.setStatusTip("Redo last change")
#        redo_action.triggered.connect(self.editor.redo)
#        edit_toolbar.addAction(redo_action)
#        edit_menu.addAction(redo_action)
#
#        edit_menu.addSeparator()
#
#        cut_action = QAction(QIcon(os.path.join('images', 'scissors.png')), "Cut", self)
#        cut_action.setStatusTip("Cut selected text")
#        cut_action.setShortcut(QKeySequence.Cut)
#        cut_action.triggered.connect(self.editor.cut)
#        edit_toolbar.addAction(cut_action)
#        edit_menu.addAction(cut_action)
#
#        copy_action = QAction(QIcon(os.path.join('images', 'document-copy.png')), "Copy", self)
#        copy_action.setStatusTip("Copy selected text")
#        cut_action.setShortcut(QKeySequence.Copy)
#        copy_action.triggered.connect(self.editor.copy)
#        edit_toolbar.addAction(copy_action)
#        edit_menu.addAction(copy_action)
#
#        paste_action = QAction(QIcon(os.path.join('images', 'clipboard-paste-document-text.png')), "Paste", self)
#        paste_action.setStatusTip("Paste from clipboard")
#        cut_action.setShortcut(QKeySequence.Paste)
#        paste_action.triggered.connect(self.editor.paste)
#        edit_toolbar.addAction(paste_action)
#        edit_menu.addAction(paste_action)
#
#        select_action = QAction(QIcon(os.path.join('images', 'selection-input.png')), "Select all", self)
#        select_action.setStatusTip("Select all text")
#        cut_action.setShortcut(QKeySequence.SelectAll)
#        select_action.triggered.connect(self.editor.selectAll)
#        edit_menu.addAction(select_action)

        self.setWindowTitle("Music DB")
#        self.setWindowIcon(QIcon('stemma.png'))

        self.show()

        #self.pushButton.clicked.connect(self.play)
        self.pushButton_2.clicked.connect(self.searchSong)

    @pyqtSlot('QPoint')
    def contextMenuEvent(self, pos):
        if self.view.selectionModel().selection().indexes():
            for i in self.view.selectionModel().selection().indexes():
                row, column = i.row(), i.column()
            menu = QMenu()
            updateAction = menu.addAction("Update Info")
            addAction = menu.addAction("Add to Playlist")
            newAction = menu.addAction("New Playlist")
            delAction = menu.addAction("Delete Playlist")
            
            action = menu.exec_(self.view.mapToGlobal(pos))
            if action == addAction:
                self.addToPlayList(row, column, False)
            elif action == updateAction:
                self.updateInfo(row, column)
            elif action == newAction:
                self.addToPlaylist(row, column, True)
            elif action == delAction:
                self.delPlaylist()

    def delPlaylist(self):
        self.playlist = {}
        self.labelPlaylist.setText('No Songs')
        self.modelpl.clear()
        
    def addToPlayList(self, row, column, isnew):
        if isnew:
            self.delPlaylist()
        file_id = int(self.db.model.record(row).field(11).value())
        link = self.box.url(file_id)
        self.playlist[link] = self.db.model.record(row)
        #txt = "{} - {}".format(self.db.model.record(row).field(1).value(),
        #                       self.db.model.record(row).field(3).value())
        if len(self.playlist) == 1:
            self.labelPlaylist.setText('1 Song')
        else:
            self.labelPlaylist.setText('{} Songs'.format(len(self.playlist)))
        item = ComponentItem(self.db.model.record(row))
        self.modelpl.appendRow(item)
    
    def updateInfo(self, row, column):
        pass

    @pyqtSlot()
    def searchSong(self):
        pattern = {'search':self.lineEdit.text()}
        self.db.model.setFilter("title like '%{search}%' or artist like '%{search}%' or album like '%{search}%'".format(**pattern))

    @pyqtSlot()
    def startUpdate(self):
        self.w = QtWaitingSpinner(self)
        self.w.start()

    @pyqtSlot()
    def endUpdate(self):
        self.w.stop()
        QMessageBox.information(None, "File Upload", "File {} uploaded.".format(self.box.update_thread.new_filename))
        
    @pyqtSlot()
    def addFile(self):
        filter = "(All Files (*);;MP3 (*.mp3);;M4A (*.m4a)"
        file_name = QFileDialog()
        file_name.setFileMode(QFileDialog.ExistingFiles)
        names = file_name.getOpenFileNames(None, "File Upload", "/Users/sani/Music", filter)
        if len(names[0]) != 0:
            for path in names[0]:
                self.box.upload(path)

    @pyqtSlot()
    def removeFile(self):
        if self.view.selectionModel().hasSelection():
            row = self.view.selectionModel().currentIndex().row()
            file_id = int(self.db.model.record(row).field(11).value())
            self.box.remove(file_id)
            self.db.removeFile(row)
            
    def changeView(self, record):
        self.labelTitle.setText("Title: {}".format(record.field(1).value()))
        self.labelArtist.setText("Artist: {}".format(record.field(3).value()))
        self.labelAlbum.setText("Album: {}".format(record.field(2).value()))
        filename = "covers/{}.jpg".format(record.field(0).value())
        image = QPixmap(filename)
        if not image.isNull():
            self.labelCover.setPixmap(image.scaled(self.labelCover.width(),
                                                   self.labelCover.height(),
                                                   Qt.KeepAspectRatio))
        else:
            self.labelCover.setPixmap(QPixmap())
        self.repaint()
        self.update()
            
    @pyqtSlot(QItemSelection, QItemSelection)
    def viewSelection(self, new, old):
        indices = new.indexes()
        if indices == []:
            return
        record = self.db.model.record(indices[0].row())
        self.changeView(record)
        
    @pyqtSlot()
    def showPlaylist(self):
        if self.playlistBtn.isChecked():
            self.stack.setCurrentIndex(1)
            if len(self.playlist) != 0:
                print ("song", self.player.currentSong)
                record = self.modelpl.item(self.player.currentSong).record
                self.changeView(record)
        else:
            self.stack.setCurrentIndex(0)
            if self.view.selectionModel().hasSelection():
                row = self.view.selectionModel().currentIndex().row()
                print (row)
                self.changeView(self.db.model.record(row))                
        
    @pyqtSlot()
    def play(self):
        if self.player.userAction <= 0:
            if len(self.playlist) != 0:
                self.player.setPlaylist(self.playlist)
            elif self.view.selectionModel().hasSelection():
                row = self.view.selectionModel().currentIndex().row()
                file_id = int(self.db.model.record(row).field(11).value())
                link = self.box.url(file_id)
                self.player.playHandler(link)
        elif self.player.userAction == 1:
            self.player.pauseHandler()
        elif self.player.userAction == 2:
            self.player.playHandler()

    @pyqtSlot(int)
    def seekPosition(self, position):
        sender = self.sender()
        if isinstance(sender, QSlider):
            if self.player.player.isSeekable():
                self.player.player.setPosition(position)

#    @pyqtSlot('qint64', bool)
    def qmp_positionChanged(self, position, senderType=False):
        if senderType == False:
            self.seekSlider.setValue(position)
        self.seekSliderLabel1.setText('%d:%02d'%(int(position/60000),int((position/1000)%60)))

    @pyqtSlot()
    def qmp_mediaStatusChanged(self):
        if self.player.player.mediaStatus() == QMediaPlayer.LoadedMedia and self.player.userAction == 1:
            durationT = self.player.player.duration()
            self.seekSlider.setRange(0, durationT)
            self.seekSliderLabel2.setText('%d:%02d'%(int(durationT/60000),int((durationT/1000)%60)))
            self.player.player.play()
            # FIXME FARE UNA FUNZIONE ????
            if len(self.playlist) != 0:
                record = self.modelpl.item(self.player.currentSong).record
                
            else:
                if self.view.selectionModel().hasSelection():
                    row = self.view.selectionModel().currentIndex().row()
            #rate = record.field(8).value()
            #self.db.incrementPlayed()

    @pyqtSlot()
    def qmp_stateChanged(self):
        if self.player.player.state() == QMediaPlayer.StoppedState:
            self.player.player.stop()
            self.player.stopHandler()
                                                        
    def qmp_volumeChanged(self):
        self.progress.setValue(self.player.player.volume())

    @pyqtSlot(int, int)
    def playlistIdxChanged(self, old, new):
        if len(self.playlist) > 0:
            if old != -1:
                self.modelpl.item(old).selected = False
            if new != -1:
                self.modelpl.item(new).selected = True

    def closeEvent(self, event):
        reply = QMessageBox.question(self, 'Message', 'Are you sure ?', QMessageBox.Yes|QMessageBox.No, QMessageBox.Yes)
        if reply == QMessageBox.Yes :
            self.close()
        else:
            try:
                event.ignore()
            except AttributeError:
                pass
                        
if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setApplicationName("Music DB")

    window = MainWindow()
    sys.exit(app.exec_())

# FIXME SAVE STATE AT EXIT
# FIXME ADD DIALOG FOR METADATA
# FIXME MODIFY PLAYLIST (INSERT REMOVE ITEMS)
# ADD TIMES OF PLAY
# FIXME CAMBIARE DURATA CANZONE PER PLAYLIST 
# FIXME SUONARE SOLO PLAYLIST ???
