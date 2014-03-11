#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "main_form.h"
//#include <qmultilineedit.h>
#include <qtextedit.h>
//#include <qprogressbar.h>
//#include <qtimer.h>
//#include <qapplication.h>
#include <qmessagebox.h>
//#include <qstringlist.h>

//#include <stdio.h>
#include <unistd.h>
//#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <sys/ioctl.h>
#include <fcntl.h>
//#include <linux/fs.h>
//#include <errno.h>
//#include <string.h>
#include <termio.h>
#include <qlcdnumber.h>
//#include <cctype>
#include <qlabel.h>
#include <cstring>
#include <stdio.h>

#include <qlineedit.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qfiledialog.h>

#include <qfileinfo.h>

#include <qdir.h>
#include <qfile.h>
class QFileDialog;
/*QPushButton *m_connectButton;
QPushButton *m_disconnectButton;
QPushButton *m_sendButton;
QCheckBox *m_enableLoggingCb;
QPushButton *m_logFileFileDialog;
QLineEdit *m_logFileLe;
QTextEdit *m_sendEdit;
QTextEdit *m_receiveEdit;
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),m_notifier(0),m_fileDlg(0)
{
    ui->setupUi(this);
    m_fd=-1;
    connect(ui->m_connectButton, SIGNAL(clicked()), this, SLOT(ConnectButtonClicked()));
    connect (ui->m_disconnectButton,SIGNAL(clicked()),this,SLOT(DisconnectButtonClicked()));

    connect(ui->m_sendButton, SIGNAL(clicked()), this, SLOT(sendButtonClicked()));
    //connect (m_logFileFileDialog,SIGNAL(clicked()),this,SLOT(chooseLogFile()));
      connect(ui->m_enableLoggingCb, SIGNAL(toggled(bool)), this, SLOT(enableLogging(bool)));
      connect (ui->m_logFileFileDialog,SIGNAL(clicked()),this,SLOT(chooseLogFile()));
      ui->m_receiveEdit->setWordWrapMode(QTextOption::WrapAnywhere);
      ui->m_receiveEdit->document()->setMaximumBlockCount(500);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectButtonClicked()
{
    if (m_fd >= 0)
      return;
    m_fd = openSerialPort();
    if (m_fd < 0) {
        QMessageBox::warning(this, tr("Error"), tr("Fail to open serial port!"));
        return ;
    }
    tcflush(m_fd,TCIOFLUSH);
    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect (m_notifier, SIGNAL(activated(int)), this, SLOT(remoteDataIncoming()));
    //connect (TMainForm->TMainFormBase->m_enableLoggingCb,SIGNAL(toggled(bool)),this,SLOT(remoteDataIncoming()));
    //connect (this->m_enableLoggingCb,SIGNAL(toggled(bool)),this,SLOT(remoteDataIncoming()));

    ui->m_logFileLe->setText("/sdcard/cutecom.log");




}

void MainWindow::DisconnectButtonClicked()
{
    if (m_notifier) {
        delete m_notifier;
        m_notifier = 0;
    }

    if (m_fd >= 0) {
      tcflush(m_fd,TCIOFLUSH);
        ::close(m_fd);
        m_fd = -1;
    }
}

void MainWindow::sendButtonClicked()
{
//    QString text( m_sendEdit->text() );
    QString text("nihao");
    if (text.isEmpty()) {
        return ;
    }
    ::write(m_fd, text.toLatin1(), text.length());
    ui->m_sendEdit->setText("");
}


int MainWindow::openSerialPort()
{
    int fd = -1;

    const char *devName = "/dev/ttyUSB0";
//    const char *devName = "/dev/ttyO1";
    fd = ::open(devName, O_RDWR&~O_NONBLOCK);
    //fd = ::open(devName, O_RDWR|O_NONBLOCK);
    if (fd < 0) {
        return -1;
    }

    termios serialAttr;
    memset(&serialAttr, 0, sizeof serialAttr);
    serialAttr.c_iflag = IGNPAR;
    serialAttr.c_cflag = B115200 | HUPCL | CS8 | CREAD | CLOCAL;
    serialAttr.c_cc[VMIN] = 55*2;//144
    if (tcsetattr(fd, TCSANOW, &serialAttr) != 0) {
        return -1;
    }
    //tcflush(fd,TCIOFLUSH);
    return fd;
}

char *strstr_gm(const char *s1,const char *s2,int s1_len);

void MainWindow::remoteDataIncoming()
{
    static char buff[2*55+1];
    //char buff_array[2*(66+49+29)+30];
    //char *buff=buff_array;
    QString buff_roll;
    char blist[5];
    //char *blist=0xfaff3232;
    blist[0]=0xFA;
    blist[1]=0xFF;
    blist[2]=0x32;
    blist[3]=0x32;
    blist[4]='\0';


//	const QString STR_FA("22");
    const char *STR_FA=blist;
    //char blist_f[4];

    char *p_start=NULL;
    char *p_data=NULL;
    //float *p_buff=NULL;

    //int index_t;
    int index_start;

    QString adjust_roll;

    float f_roll;
    float f_pitch;
    float f_yaw;
    float f_gravity;

    union u_data {
      float blist_f;
      char blist_char[4];
    } blist_data;

    unsigned int pitch_cha;
    int len1;
    int len2;

    int bytesRead=read(m_fd, buff, 55*2);
    if (bytesRead <0) {
        QMessageBox::warning(this, tr("Error"), tr("Receive error!"));
        return;
    }
    else if (bytesRead==0)
    {
       // disconnectTTY();
       MainWindow::DisconnectButtonClicked();
        return;
    }

    len1=strlen(buff);
    //QString buff_qs(buff);

    const char* c=buff;

    unsigned int m_hexBytes=0;
    QString text;
    char buf[16];
    for (int i=0; i<bytesRead; i++)
    {

          if ((m_hexBytes % 16) == 0)
          {
          snprintf(buf, 16, "%08x: ", m_hexBytes);
          text+=buf;
          }
          unsigned int b=*c;
          snprintf(buf, 16, "%02x ", b & 0xff);
          text+=buf;

          m_hexBytes++;
          if ((m_hexBytes % 16)==0)
          {
          text+="\n";
          }
          else if ((m_hexBytes % 8)==0)
          {
          text+="  ";
          }

        c++;
    }



    ui->m_receiveEdit->append(text);
   // m_receiveEdit.clear();


   // m_receiveEdit->insert(text);
    ui->m_receiveEdit->append(QString("\n@@@@@@@@@@@@@@@@@@@@\n"));

    if (m_logFile.isOpen())
    {
        m_logFile.write(buff, bytesRead);
    }

//	buff[55*2]='\0';
//	len2=strlen(buff);

    p_start=strstr_gm(buff,STR_FA,bytesRead);

    //index_start=buff_qs.find(STR_FA);
    if((p_start>=buff)&&(p_start<=buff+bytesRead-52)&&(p_start!=NULL)&&(bytesRead>=52)){   //num=15

    // f_pitch=*(float *)(p_buff+index_start+10);
    p_data=p_start+12;
    blist_data.blist_char[3]=*p_data;
    blist_data.blist_char[2]=*(p_data+1);
    blist_data.blist_char[1]=*(p_data+2);
    blist_data.blist_char[0]=*(p_data+3);
    //p_buff=(float *)p_start;
    // f_gravity=*(float *)blist_f;
    //f_gravity=blist_data.blist_f;
     ui->Label_gravity->setNum(blist_data.blist_f);

    p_data=p_start+40;
    blist_data.blist_char[3]=*p_data;
    blist_data.blist_char[2]=*(p_data+1);
    blist_data.blist_char[1]=*(p_data+2);
    blist_data.blist_char[0]=*(p_data+3);
    ui->Label_roll->setNum(blist_data.blist_f);

    p_data=p_start+44;
    blist_data.blist_char[3]=*p_data;
    blist_data.blist_char[2]=*(p_data+1);
    blist_data.blist_char[1]=*(p_data+2);
    blist_data.blist_char[0]=*(p_data+3);
    // Label_pitch->setNum(blist_data.blist_f);
    ui->Label_pitch->setNum(blist_data.blist_f);

    p_data=p_start+48;
    blist_data.blist_char[3]=*p_data;
    blist_data.blist_char[2]=*(p_data+1);
    blist_data.blist_char[1]=*(p_data+2);
    blist_data.blist_char[0]=*(p_data+3);
    // Label_yaw->setNum(blist_data.blist_f);
    ui->Label_yaw->setNum(blist_data.blist_f);
    //  buff_roll=buff_qs.mid(index_start+10,4);

     // f_roll=buff_roll.toFloat();
      //adjust_roll.setNum(f_roll);

      //time_hour=time_adjust;
      //buff_time[0]=char(time_adjust/10);
      //buff_time[1]=char(time_adjust%10);
      //buff_time.insert(0,'4');
     // buff_time.insert(0,time_hour);
      //buff_time.insert(0,char(time_adjust%10));
      //buff_time.insert(0,char(time_adjust/10));
        //buff_time.insert(0,time_hour%10);
        //buff_time.insert(0,time_hour/10);

      //buff_location_E+=char(QChar(buff_qs[index_end+1]));
     // m_label_E->setText(QString(QChar(buff_qs[index_end+1])));


    // pitch_cha=((unsigned int)(&blist_f[0])&0xff);
    //  TextLabel_test->setNum(int(pitch_cha));
/*
    blist_f[3]=0x41;
    blist_f[2]=0x1c;
    blist_f[1]=0x64;
    blist_f[0]=0xfd;
    //p_buff=(float *)p_start;
     f_roll=*(float *)blist_f;
      //f_roll=1.35423e-3;

          Label_roll->setNum(f_roll);
          Label_pitch->setNum(f_roll);
          Label_yaw->setNum(f_roll);
*/
    // TextLabel_test_2->setNum(int(blist_f+5));
     //	 pitch_cha=((unsigned int)(&blist_f[2])&0xff);
    //  TextLabel_test_2->setNum(int(pitch_cha));

      /*
       *
       if(int(QChar(buff_qs[index_end+3]))==1){
      //buff_location_N=buff_qs.mid(index_t+16,12);
      //buff_location_E=buff_qs.mid(index_t+28,12);

      m_time->display(buff_time);
      m_location_N->display(buff_location_N);
      m_location_E->display(buff_location_E);
      }
      else{
        m_debug->display(QString("N/A"));
      }
      */
     // f_roll=35.845;
    //  m_time->display(len1);
    //  m_location_N->display(int(buff_qs.length()));
    //  m_location_E->display(p_start);

     //  m_location_N->display(buff_time);
     //  m_location_E->display(int(buff_qs.length()));
      //m_debug->display(time_hour);
      ui->m_label_debug->setText(QString(""));
    }
    else{
     ui->Label_gravity->setNum(len1);
    //  m_time->display(len1);
    //  m_location_N->display(int(buff_qs.length()));
    //  m_location_E->display("");

    //  m_time->display(STR_FA);
     // m_debug->display(QString("N/A"));
     //  m_location->display(buff_time);
    // m_label_debug->setText(QString("N/A"));
     ui->Label_roll->setNum(int(p_start));
         ui->Label_pitch->setNum(bytesRead);
      ui->Label_yaw->setNum(p_start-buff);
    ui->m_label_debug->setText(QString("N/A"));

    }

    /*  s2=QString(QChar(index_t));
      test_str+=s2;
      s2=QString("\n^^^^^^^^^^^^^\n");
      test_str+=s2;
      s2=QString(QChar(buff_qs.length()));
      test_str+=s2;
      s2=QString("\n^^^^^^@@^^^^^^^\n");
      test_str+=s2;
      m_receiveEdit->insert(test_str);
    */
    //if(isdigit(c))
      //m_time->display(QString(QChar(c)));

}


char *strstr_gm(const char *s1,const char *s2,int s1_len)
{
  int n;
  int i;
  if(*s2)
  {
    for(i=0;i<s1_len;i++)
    {
      for(n=0;*(s1+n)==*(s2+n);n++)
      {
    if(!*(s2+n+1))
      return (char *)s1;
      }
      s1++;
    }
    return NULL;
  }
  else
    return (char *)s1;
}



void MainWindow::enableLogging(bool on)
{
   if (m_logFile.isOpen()==on)
   {
      return;
   }

   if (on)
   {
      m_logFile.setFileName(ui->m_logFileLe->text());
      //m_logFile.setFileName(m_logFileLe->text());
      //QIODevice::OpenMode mode=QIODevice::ReadWrite;
      //int mode=IO_ReadWrite | IO_Truncate;
      QIODevice::OpenMode mode=QIODevice::ReadWrite;

         mode=mode | QIODevice::Truncate;

       //  mode=mode | QIODevice::Truncate;

       //  mode=mode | QIODevice::Append;


      if (!m_logFile.open(mode))
      {
         QMessageBox::information(this, tr("Opening file failed"), tr("Could not open file %1 for writing").arg(ui->m_logFileLe->text()));
         ui->m_enableLoggingCb->setChecked(false);
      }
      else
      {
       //  m_logAppendCb->setEnabled(false);
         ui->m_logFileLe->setEnabled(false);
         ui->m_logFileFileDialog->setEnabled(false);
      //   saveSettings();
      }
   }
   else
   {
      m_logFile.close();

  //    m_logAppendCb->setEnabled(true);
      ui->m_logFileLe->setEnabled(true);
      ui->m_logFileFileDialog->setEnabled(true);

   }

}


void MainWindow::chooseLogFile()
{
  //static QString * workingDirectory = 0;
 // QFileDialog *dlg = new QFileDialog( *workingDirectory, QString::null, parent, name, TRUE );
 // QFileDialog *dlg = new QFileDialog( *workingDirectory, QString::null, this,m_logFileLe->text(), TRUE );
  // QFileDialog qfile_diag(QString("/sdcard"),this);
 //  QString logFile=qfile_diag->getSaveFileName( tr("Save log file ..."),tr("Save log file ..."), this,m_logFileLe->text());
//QString logFile=QFileDialog::getSaveFileName(tr("Save log file ...") ,tr("Save log file ...") , this,m_logFileLe->text(),tr("Save log file ..."));
 //  QString logFile=QFileDialog::getSaveFileName(this, tr("Save log file ..."), m_logFileLe->text());
// QString logFile = QFileDialog::getOpenFileName( QString::null, "*.cpp", this );
//QString logFile = m_fileDlg->getSaveFileName( QString::null, "*.cpp", this );
    QString logFile=QFileDialog::getSaveFileName(this, tr("Save log file ..."), ui->m_logFileLe->text());
    if (!logFile.isEmpty())
    {
       ui->m_logFileLe->setText(logFile);
    }
}


