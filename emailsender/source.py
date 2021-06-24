# encoding: utf-8
from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot, QThread
from PyQt5.QtWidgets import QMessageBox, QFileDialog, QInputDialog, QLineEdit
from PyQt5.QtGui import QTextDocument

import smtplib, time, traceback, mimetypes, os

from email import encoders
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.application import MIMEApplication
from email.mime.audio import MIMEAudio
from email.mime.base import MIMEBase

from loadcsv import CSVLoader
from jsoneditor import JSONEditor
import time

class External(QThread):
    countChanged = pyqtSignal(int)
    message = pyqtSignal(list)
    
    def __init__(self, logger, me, recipients, msg, password):
        super(External, self).__init__()
        self.logger = logger
        self.me = me
        self.recipients = recipients
        self.msg = msg
        self.password = password
        
    def run(self):
        to_send = list(self.recipients)
        n_recipients = len(self.recipients)
        trials = 0
        while len(to_send) != 0:
            sent = []
            for i, r in enumerate(to_send):
                self.logger.info("Sending ({}/{}) to: {}".format(i+1,
                                                                 n_recipients,
                                                                 ",".join(r)))
                try:
                    self.logger.info("Connecting to server")
                    with smtplib.SMTP_SSL('smtps.aruba.it') as s:
                        #s.set_debuglevel(1)
                        s.login(self.me, self.password) # 16agosto           
                        you = r
                        s.sendmail(self.me, you, self.msg.as_string())
                        self.countChanged.emit(i+1)
                    sent.append(1)
                except:
                    err = traceback.format_exc()
                    self.message.emit(["Errore invio email", err])
                    self.logger.error(err)
                    sent.append(0)

            to_send = []
            for i, s in enumerate(sent):
                if s == 0:
                    to_send.append(self.recipients[i])

            trials += 1
            if trials == 3:
                break

        
        if len(to_send) != 0:
            self.logger.error("The following recipients has NOT been sent:\m" + str(self.recipients))
        else:
            text = "Tutte le email sono state inviate correttamente."
            self.message.emit(["Invio email", text])
            self.logger.info(text)
 
class Sender(QObject):
    #send_email = pyqtSignal(list, int)
    
    def __init__(self, settings, ui):
        super(Sender, self).__init__()
        self.setSettings(settings)
        self.ui = ui
        self.attachments = []
        self.recipients = []

        #self.send_email.connect(self.realSending)

    def setSettings(self, settings):
        self.me = settings['sender']
        self.tester = settings['tester']
        self.indirizzi_per_email = settings['indirizzi_per_email']
        
    def prepareEmail(self):
        self.msg = MIMEMultipart()
        self.msg['Subject'] = self.ui.lineEdit.text()
        self.msg['From'] = self.me
        self.msg['To'] = self.me
        text = self.ui.editor.toHtml()
        html = """
<html>
  <head></head>
  <body>
    <div align="center">
      <img src="cid:stemma" align="center">
    </div>
    <div style='color:black'>
    """ + text + """
  </body>
</html>
"""
#    <p>  
#      <pre>""" + text + """
#      </pre>
#    </p>

        #self.msg.attach(MIMEText(text, "text"))
        self.msg.attach(MIMEText(html, 'html'))

        fp = open('stemma.png', 'rb')
        msgImage = MIMEImage(fp.read())
        fp.close()

        msgImage.add_header('Content-ID', '<stemma>')
        self.msg.attach(msgImage)

        if len(self.attachments) > 0:
            for file in self.attachments:
                self.ui.logger.info("adding attach: {}".format(file))
                ctype, encoding = mimetypes.guess_type(file)

                if ctype is None or encoding is not None:
                    ctype = 'application/octet-stream'
                    
                maintype, subtype = ctype.split('/', 1)

                if maintype == 'text':
                    fp = open(file)
                    att = MIMEText(fp.read(), _subtype=subtype)
                    fp.close()
                elif maintype == 'image':
                    fp = open(file, 'rb')
                    att = MIMEImage(fp.read(), _subtype=subtype)
                    fp.close()
                elif maintype == 'audio':
                    fp = open(file, 'rb')
                    att = MIMEAudio(fp.read(), _subtype=subtype)
                    fp.close()
                else:
                    fp = open(file, 'rb')
                    att = MIMEBase(maintype, subtype)
                    att.set_payload(fp.read())
                    fp.close()
                    encoders.encode_base64(att)

                att.add_header('Content-Disposition', 'attachment', filename=file[file.rindex("/"):])
                self.msg.attach(att) 

    @pyqtSlot()
    def send(self):
        if self.ui.editor.toPlainText() == '':
            QMessageBox.critical(None, "Invio email", "Il testo dell'email ?")
            return
        if len(self.recipients) == 0 and not self.ui.checkBox.checkState():
            QMessageBox.critical(None, "Invio email", "Mancano i destinatari dell'email.")
            return
        if self.ui.lineEdit.text() == '':
            QMessageBox.warning(None, "Invio email", "Aggiungi l'oggetto all'email.")
            return

        self.prepareEmail()

        if self.ui.checkBox.checkState():
            self.ui.logger.warning("This is a test sending")
            self.recipients = self.tester

        self.ui.logger.warning("Preparing to send {} emails with {} recipients.".format(len(self.recipients),
                                                                                        self.indirizzi_per_email))
        self.ui.progressBar.setRange(0, len(self.recipients))
        self.ui.progressBar.setTextVisible(True)

        password = QInputDialog.getText(None, "Server Connection",
                                        "Password", QLineEdit.Password)
        self.real_sender = External(self.ui.logger, self.me, self.recipients, self.msg, password[0])
        self.real_sender.countChanged.connect(self.updateProgressBar)
        self.real_sender.message.connect(self.showMessage)
        self.real_sender.start()

    @pyqtSlot(list)
    def showMessage(self, msg):
        QMessageBox.information(None, msg[0], msg[1])
        
    @pyqtSlot(int)
    def updateProgressBar(self, i):
        self.ui.progressBar.setValue(i)
        if i == len(self.recipients):
            self.recipients = []
            self.ui.labelAddr.setText('')
            self.ui.progressBar.setTextVisible(False)
            
    @pyqtSlot()
    def processCsv(self):
        loader = CSVLoader()
        #loader.exec_()
        
        lista_email = sorted(list(set(loader.email_addresses)))
        print (len(lista_email))
        self.ui.logger.info("Address file: {}".format(loader.fileName))
        self.ui.logger.info("Addresses {}".format(",".join(lista_email)))
        self.recipients = [lista_email[i:i + self.indirizzi_per_email] for i in range(0, len(lista_email), self.indirizzi_per_email)]
        self.ui.labelAddr.setText("Indirizzi caricati da: {}".format(os.path.basename(loader.fileName)))

    @pyqtSlot()
    def attach(self):
        self.attachments = []
        filter = "Tutti file (*);;TXT (*.txt);;PDF (*.pdf)"
        file_name = QFileDialog()
        file_name.setFileMode(QFileDialog.ExistingFiles)
        names = file_name.getOpenFileNames(None, "Allegati", ".", filter)
        for n in names[0]:
            self.ui.logger.info("Attachment {}".format(n))
            self.attachments.append(n)

        text = ", ".join([os.path.basename(f) for f in self.attachments])
        if len(text) > 100:
            text = text[:97]+"..."
        
        self.ui.labelAtt.setText(text)
        
    @pyqtSlot()
    def update_settings(self):
        editor = JSONEditor()
        editor.exec_()
        self.setSettings(editor.settings)

