#!/usr/bin/env python2
import os
import getpass
import subprocess
from PyQt4 import QtCore, QtGui, uic

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_MainWindow(object):

    def on_select_pdf_clicked(self):
        if int(self.from_page.value()) > int(self.to_page.value()):
            QtGui.QMessageBox.critical(None, 'Reversed Numbers',
                "From page {0} To {1} = OK\nFrom page {2} To {3} = Not working"
                .format(self.to_page.value(), self.from_page.value(), self.from_page.value(), self.to_page.value()), QtGui.QMessageBox.Ok)
        else:
            filename = QtGui.QFileDialog.getOpenFileName(None, 'Select some PDF file to convert it', '/home/{0}/Desktop/'.format(getpass.getuser()), filter='PDF files (*.pdf);;All files (*)')
            if filename:
                astor = "{0}".format(filename)
                self.pdf_to_img(astor, filename)

    def pdf_to_img(self, filename, pdffilepath):
        pdfname, ext = os.path.splitext(filename)
        resolution = self.resolution.value()
        arglist = ["gs", "-dBATCH", "-dNOPAUSE", "-dFirstPage={0}".format(self.from_page.value()), "-dLastPage={0}".format(self.to_page.value()),
                  "-sOutputFile={0}_page_%01d.{1}".format(pdfname, self.comboBox.currentText()),
                   "-sDEVICE={0}".format(self.comboBox_2.currentText()),"-r{0}".format(resolution), pdffilepath]
        sp = subprocess.Popen(args=arglist, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        sp.communicate()
        sub = range(int(self.to_page.value())+2 - int(self.from_page.value()))
        del sub[0]
        ran1 = range(int(self.from_page.value()), int(self.to_page.value())+1)
        for (x, z) in (zip(ran1, sub)):
            os.system('mv "{0}_page_{1}.{2}"'.format(pdfname, z, self.comboBox.currentText()) + ' "{0} page {1}.{2}"'.format(pdfname, x, self.comboBox.currentText()))

    def oncombo2(self):
        active = self.comboBox_2.currentText()
        if active == "png16m" or active == "pngalpha" or active == "pnggray":
            self.comboBox.setCurrentIndex(0)
        if active == "jpeg" or active == "jpegcmyk" or active == "jpeggray":
            self.comboBox.setCurrentIndex(1)
        if active == "bmp16m" or active == "bmpgray":
            self.comboBox.setCurrentIndex(2)
        if active == "tiff24nc" or active == "tiffgray":
            self.comboBox.setCurrentIndex(3)

    def oncombo(self):
        active = self.comboBox.currentText()
        if active == "png":
            self.comboBox_2.setCurrentIndex(0)
        if active == "jpg":
            self.comboBox_2.setCurrentIndex(3)
        if active == "bmp":
            self.comboBox_2.setCurrentIndex(6)
        if active == "tiff":
            self.comboBox_2.setCurrentIndex(8)

    def on_about_clicked(self):
        self.about_ui = uic.loadUi('data_pdf2img/aboutdialog.ui')
        self.about_ui.show()

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "PDF to IMG", None))
        self.label.setText(_translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#a0a0a0;\"> Resolution</span></p></body></html>", None))
        self.label_3.setText(_translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#a0a0a0;\">From page:</span></p></body></html>", None))
        self.label_4.setText(_translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#a0a0a0;\">To:</span></p></body></html>", None))
        self.label_5.setText(_translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#a0a0a0;\">Image format</span></p></body></html>", None))
        self.label_6.setText(_translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#a0a0a0;\">sDevice</span></p></body></html>", None))
        self.label_7.setText(_translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#ffffff;\">Select PDF file</span></p></body></html>", None))
        self.comboBox.setItemText(0, _translate("MainWindow", "png", None))
        self.comboBox.setItemText(1, _translate("MainWindow", "jpg", None))
        self.comboBox.setItemText(2, _translate("MainWindow", "bmp", None))
        self.comboBox.setItemText(3, _translate("MainWindow", "tiff", None))
        self.comboBox_2.setItemText(0, _translate("MainWindow", "png16m", None))
        self.comboBox_2.setItemText(1, _translate("MainWindow", "pngalpha", None))
        self.comboBox_2.setItemText(2, _translate("MainWindow", "pnggray", None))
        self.comboBox_2.setItemText(3, _translate("MainWindow", "jpeg", None))
        self.comboBox_2.setItemText(4, _translate("MainWindow", "jpegcmyk", None))
        self.comboBox_2.setItemText(5, _translate("MainWindow", "jpeggray", None))
        self.comboBox_2.setItemText(6, _translate("MainWindow", "bmp16m", None))
        self.comboBox_2.setItemText(7, _translate("MainWindow", "bmpgray", None))
        self.comboBox_2.setItemText(8, _translate("MainWindow", "tiff24nc", None))
        self.comboBox_2.setItemText(9, _translate("MainWindow", "tiffgray", None))
        self.about_button.setText(_translate("MainWindow", "  About", None))
        QtCore.QObject.connect(self.about_button, QtCore.SIGNAL('clicked()'), self.on_about_clicked)
        QtCore.QObject.connect(self.comboBox, QtCore.SIGNAL('currentIndexChanged(int)'), self.oncombo)
        QtCore.QObject.connect(self.comboBox_2, QtCore.SIGNAL('currentIndexChanged(int)'), self.oncombo2)
        QtCore.QObject.connect(self.select_pdf_button, QtCore.SIGNAL('clicked()'), self.on_select_pdf_clicked)

    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(199, 244)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(_fromUtf8("data_pdf2img/images/pdf2img_icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        MainWindow.setWindowIcon(icon)
        MainWindow.setStyleSheet(_fromUtf8("background-color: black;"))
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.label = QtGui.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(10, 10, 81, 16))
        self.label.setObjectName(_fromUtf8("label"))
        self.label_3 = QtGui.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(10, 70, 81, 16))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.label_4 = QtGui.QLabel(self.centralwidget)
        self.label_4.setGeometry(QtCore.QRect(140, 70, 21, 16))
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.label_5 = QtGui.QLabel(self.centralwidget)
        self.label_5.setGeometry(QtCore.QRect(10, 130, 101, 16))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_6 = QtGui.QLabel(self.centralwidget)
        self.label_6.setGeometry(QtCore.QRect(120, 130, 57, 14))
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.label_7 = QtGui.QLabel(self.centralwidget)
        self.label_7.setGeometry(QtCore.QRect(50, 190, 101, 21))
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.from_page = QtGui.QSpinBox(self.centralwidget)
        self.from_page.setGeometry(QtCore.QRect(10, 90, 91, 31))
        self.from_page.setStyleSheet(_fromUtf8("background-color: white;"))
        self.from_page.setMaximum(9999)
        self.from_page.setObjectName(_fromUtf8("from_page"))
        self.from_page.setValue(1)
        self.to_page = QtGui.QSpinBox(self.centralwidget)
        self.to_page.setGeometry(QtCore.QRect(100, 90, 91, 31))
        self.to_page.setStyleSheet(_fromUtf8("background-color: white;"))
        self.to_page.setMaximum(99999)
        self.to_page.setObjectName(_fromUtf8("to_page"))
        self.to_page.setValue(1)
        self.comboBox = QtGui.QComboBox(self.centralwidget)
        self.comboBox.setGeometry(QtCore.QRect(10, 150, 91, 31))
        self.comboBox.setStyleSheet(_fromUtf8("background-color: silver;"))
        self.comboBox.setObjectName(_fromUtf8("comboBox"))
        self.comboBox.addItem(_fromUtf8(""))
        self.comboBox.addItem(_fromUtf8(""))
        self.comboBox.addItem(_fromUtf8(""))
        self.comboBox.addItem(_fromUtf8(""))
        self.comboBox_2 = QtGui.QComboBox(self.centralwidget)
        self.comboBox_2.setGeometry(QtCore.QRect(100, 150, 91, 31))
        self.comboBox_2.setStyleSheet(_fromUtf8("background-color: silver;"))
        self.comboBox_2.setObjectName(_fromUtf8("comboBox_2"))
        self.comboBox_2.addItem(_fromUtf8(""))
        self.comboBox_2.addItem(_fromUtf8(""))
        self.comboBox_2.addItem(_fromUtf8(""))
        self.comboBox_2.addItem(_fromUtf8(""))
        self.comboBox_2.addItem(_fromUtf8(""))
        self.comboBox_2.addItem(_fromUtf8(""))
        self.comboBox_2.addItem(_fromUtf8(""))
        self.comboBox_2.addItem(_fromUtf8(""))
        self.comboBox_2.addItem(_fromUtf8(""))
        self.comboBox_2.addItem(_fromUtf8(""))
        self.select_pdf_button = QtGui.QPushButton(self.centralwidget)
        self.select_pdf_button.setGeometry(QtCore.QRect(8, 210, 181, 31))
        self.select_pdf_button.setStyleSheet(_fromUtf8("background-color: gray;"))
        self.select_pdf_button.setText(_fromUtf8(""))
        icon = QtGui.QIcon.fromTheme(_fromUtf8("user-home"))
        self.select_pdf_button.setIcon(icon)
        self.select_pdf_button.setObjectName(_fromUtf8("select_pdf_button"))
        self.resolution = QtGui.QSpinBox(self.centralwidget)
        self.resolution.setGeometry(QtCore.QRect(10, 30, 91, 31))
        self.resolution.setStyleSheet(_fromUtf8("background-color: white;"))
        self.resolution.setMaximum(9999)
        self.resolution.setObjectName(_fromUtf8("resolution"))
        self.resolution.setValue(100)
        self.about_button = QtGui.QToolButton(self.centralwidget)
        self.about_button.setGeometry(QtCore.QRect(100, 30, 91, 31))
        self.about_button.setStyleSheet(_fromUtf8("background-color: gray;"))
        icon = QtGui.QIcon.fromTheme(_fromUtf8("emblem-favorite"))
        self.about_button.setIcon(icon)
        self.about_button.setToolButtonStyle(QtCore.Qt.ToolButtonTextBesideIcon)
        self.about_button.setObjectName(_fromUtf8("about_button"))
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    MainWindow = QtGui.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

