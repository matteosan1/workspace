from os.path import expanduser
from PyQt5.QtWidgets import *
from PyQt5.QtMultimedia import QMediaPlayer, QMediaPlaylist, QMediaContent
from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot, QUrl

class MyPlayer(QObject):
    currentIndexChanged = pyqtSignal(int, int)
    
    def __init__(self, parent = None):
        super(MyPlayer, self).__init__(parent)
        self.currentPlaylist = QMediaPlaylist()
        self.currentPlaylistSong = -1
        self.currentSong = -1
        self.player = QMediaPlayer()
        self.userAction = -1 #0- stopped, 1- playing 2-paused
        self.player.setVolume(60)

    def setPlaylist(self, playlist):
        for song in playlist.keys():
            self.currentPlaylist.addMedia(QMediaContent(QUrl(song)))
        self.playHandler()
        
    def playHandler(self, filename=None):
        self.userAction = 1
        if self.player.state() == QMediaPlayer.StoppedState:
            #if self.player.mediaStatus() == QMediaPlayer.NoMedia:
            if self.currentPlaylist.mediaCount() == 0:
                self.player.setMedia(QMediaContent(QUrl(filename)))
                self.currentSong = -1
            #else:
            if self.currentPlaylist.mediaCount() != 0:
                self.player.setPlaylist(self.currentPlaylist)
                self.currentPlaylistSong = 0
                self.player.playlist().currentIndexChanged.connect(self.indexChanged)
                self.currentIndexChanged.emit(-1, 0)
            elif self.player.mediaStatus() == QMediaPlayer.LoadedMedia:
                self.player.play()
            elif self.player.mediaStatus() == QMediaPlayer.BufferedMedia:
                self.player.play()
        elif self.player.state() == QMediaPlayer.PlayingState:
            pass
        elif self.player.state() == QMediaPlayer.PausedState:
            self.player.play()
                        
    def pauseHandler(self):
        if self.userAction == 2:
            self.playHandler()
            self.userAction = 1
        else:
            self.userAction = 2
            self.player.pause()
                        
    def stopHandler(self):
        self.userAction = 0
        self.player.setPosition(0)
        self.currentIndexChanged.emit(self.currentPlaylistSong, -1)
        if self.player.state() == QMediaPlayer.PlayingState:
            self.player.stop()
        elif self.player.state() == QMediaPlayer.PausedState:
            self.player.stop()
        elif self.player.state() == QMediaPlayer.StoppedState:
            pass
                
    def increaseVolume(self):
        vol = self.player.volume()
        vol = min(vol+5,100)
        self.player.setVolume(vol)
        
    def decreaseVolume(self):
        vol = self.player.volume()
        vol = max(vol-5,0)
        self.player.setVolume(vol)


#def songInfo(self):
    #    infoAc = QAction('Info',self)
    #    infoAc.setShortcut('Ctrl+I')
    #    infoAc.setStatusTip('Displays Current Song Information')
    #    infoAc.triggered.connect(self.displaySongInfo)
    #    return infoAc
        
    #def displaySongInfo(self):
    #    metaDataKeyList = self.player.availableMetaData()
    #    fullText = '<table class="tftable" border="0">'
    #    for key in metaDataKeyList:
    #        value = self.player.metaData(key)
    #        fullText = fullText + '<tr><td>' + key + '</td><td>' + str(value) + '</td></tr>'
    #    fullText = fullText + '</table>'
    #    infoBox = QMessageBox(self)
    #    infoBox.setWindowTitle('Detailed Song Information')
    #    infoBox.setTextFormat(Qt.RichText)
    #    infoBox.setText(fullText)
    #    infoBox.addButton('OK',QMessageBox.AcceptRole)
    #    infoBox.show()

    @pyqtSlot(int)
    def indexChanged(self, pos):
        self.currentIndexChanged.emit(self.currentPlaylistSong, pos)
        self.currentSong = pos
        
    def prevItemPlaylist(self):
        self.player.playlist().previous()
        
    def nextItemPlaylist(self):
        self.player.playlist().next()
